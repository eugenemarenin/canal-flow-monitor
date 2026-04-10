#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

// --- WATER SENSOR SETTINGS ---
const int FLOW_SENSOR_PIN = 14; 
const int POWER_5V_PIN = 21;    
const float ML_PER_PULSE = 2.25;

volatile uint32_t pulseCount = 0; 

void IRAM_ATTR pulseCounter() {
  pulseCount++;
}

// --- THE THINGS NETWORK KEYS (OTAA) ---

// AppEUI: 0000000000000000 (LSB format)
static const u1_t PROGMEM APPEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}

// DevEUI: 0000000000000000 (LSB format). Insert your value
static const u1_t PROGMEM DEVEUI[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}

// AppKey: 00000000000000000000000000000000 (MSB format). Insert your value
static const u1_t PROGMEM APPKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

static osjob_t sendjob;
const unsigned TX_INTERVAL = 60; // Send interval in seconds

// Pin mapping for senseBox Eye (ESP32 LoRa)
const lmic_pinmap lmic_pins = {
    .nss = LORA_CS,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = LMIC_UNUSED_PIN,                        
    .dio = {LORA_INT, LORA_INT, LMIC_UNUSED_PIN},  
};

void onEvent (ev_t ev) {
    switch(ev) {
        case EV_JOINING:
            Serial.println(F("EV_JOINING: Attempting to connect to TTN..."));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED: CONNECTED SUCCESSFULLY!"));
            LMIC_setLinkCheckMode(0);
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED: Connection failed"));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE: Data sent to cloud!"));
            os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
            break;
        default:
            break;
    }
}

void do_send(osjob_t* j){
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("Radio busy, waiting..."));
    } else {
        noInterrupts();
        uint32_t currentPulses = pulseCount;
        pulseCount = 0; 
        interrupts(); 

        float flowRate_L_per_min = (currentPulses * ML_PER_PULSE) / 1000.0;
        
        // Cayenne LPP Encoding (Channel 1, Analog Input)
        int16_t payloadValue = (int16_t)(flowRate_L_per_min * 100.0); 
        byte payload[4];
        payload[0] = 0x01; // Channel 1
        payload[1] = 0x02; // Analog Input type
        payload[2] = highByte(payloadValue); 
        payload[3] = lowByte(payloadValue);  

        LMIC_setTxData2(1, payload, sizeof(payload), 0);

        Serial.print(F("Flow: "));
        Serial.print(flowRate_L_per_min);
        Serial.println(F(" L/min. Packet queued."));
    }
}

void setup() {
    Serial.begin(115200);
    delay(2000); 
    Serial.println(F("\n--- MONITORING SYSTEM STARTING ---"));
    
    // Power up the 5V rail for the sensor
    pinMode(POWER_5V_PIN, OUTPUT);
    digitalWrite(POWER_5V_PIN, HIGH);
    
    // Initialize flow sensor interrupt
    pinMode(FLOW_SENSOR_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), pulseCounter, RISING);

    // Initialize LoRaWAN radio
    os_init();
    LMIC_reset();

    // Clock error compensation for ESP32 timing inaccuracy
    LMIC_setClockError(MAX_CLOCK_ERROR * 10 / 100);
    
    do_send(&sendjob);
}

void loop() {
    os_runloop_once();
}