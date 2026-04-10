# openSenseMap Integration

Aftes setting up the data transmission to The Things Network (TTN), you need to configure openSenseMap to catch the webhook and visualize the data.

## 1. Create a senseBox
1. Log in to [openSenseMap](https://opensensemap.org/).
2. Create **New senseBox**.
3. Set the location of your canal monitoring station on the map.
4. Under **Hardware**, select `senseBox:custom`.

## 2. Add the Sensor
1. In the **Sensors** section, click **Add Sensor**.
2. **Icon:** Choose a water-related icon.
3. **Phenomenon:** `Water Flow`
4. **Unit:** `L/min`

## 3. Configure TTN Link
1. In the Dashboard, select **Edit** and open the **TheThingsNetwork** tab.
2. **Decoding Profile:** Select `Cayenne LPP (beta)`.
3. **TTN Application ID:** Enter your Application ID from the TTN console
4. **TTN Device ID:** Enter your Device ID from the TTN console
5. **Decoding Options:** for your Water Flow sensor, set **Cayenne LPP Phenomenon** to `Analog In` and **Cayenne LPP Channel** to `1`
6. Click **Save**.

Within a few minutes of the next transmission, data points will begin appearing on your public openSenseMap dashboard
