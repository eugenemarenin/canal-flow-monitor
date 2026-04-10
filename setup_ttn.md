# The Things Network (TTN) Configuration

This guide explains how to register ESP32 node on The Things Network and configure the data routing.

## 1. Register the End Device
1. Log in to your [TTN Console](https://eu1.cloud.thethings.network/console/).
2. Go to **Applications** and create a new application
3. Click **Register end device**
4. Enter your device specifics 
5. Choose your activation method. 
6. Generate or input your `DevEUI`, `AppEUI`, and `AppKey`. Insert these into `flow_monitor.ino` file

## 2. Set Up Payload Formatter
The ESP32 firmware is programmed to pack the water flow data into the standard Cayenne LPP format. 
1. In device menu, go to the **Payload formatters** tab.
2. Select **Uplink**.
3. Change the Formatter type to **Cayenne LPP**.
4. Click **Save changes**. 

## 3. Configure the Webhook
To forward the decoded data to openSenseMap:
1. Go to **Integrations** -> **Webhooks** in the left menu.
2. Click **Add webhook**.
3. Name the webhook (e.g., `opensensemap-webhook`).
4. Select Webhook format: **JSON**
5. Insert Base URL: `https://ttn.opensensemap.org/v3`
6. Click **Create openSenseMap webhook**
