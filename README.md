# BCA152-BLE-Smarthome

Smart home BLE Mesh lab on ESP32 (ESP-IDF): light sensor, relay switch, and Wi-Fi gateway nodes.

Based on Chapter 9 of *Internet of Things with ESP32* (PacktPublishing/Internet-of-Things-with-ESP32). Code is in `ch9/`; shared libraries are in `common/`.

## Environment
- Windows, VS Code + PlatformIO (Core 6.2.0)
- ESP-IDF 4.3 (`platform = espressif32@3.3.2`, board `esp32dev`)
- nRF Mesh mobile app for provisioning and testing

## Nodes and status
| Node | What it does | Status |
|---|---|---|
| Light sensor (`ch9/light_sensor`) | Reads light and publishes high/low over BLE Mesh (Generic OnOff Server) | Built, uploaded, dark/bright readings verified on hardware. Not yet provisioned in the mesh. |
| Switch (`ch9/switch`) | Drives a relay from BLE Mesh ON/OFF messages (OnOff Server + Client) | Built, uploaded, provisioned; relay verified from the nRF Mesh app. |
| Gateway (`ch9/gateway`) | Connects to Wi-Fi, serves a web page that sends ON/OFF (OnOff Client) | Builds successfully. Not uploaded or tested (board unavailable). |

## Changes from the book's code
- **Light sensor:** a TSL2561 was not available, so `app_sensor.c/.h` were rewritten for an LM393 LDR module (DO pin on GPIO34, 3V3, GND).
- **Switch:** the first build failed to link (`undefined reference to esp_ble_mesh_register_generic_server_callback`). Fixed by setting `CONFIG_BLE_MESH_GENERIC_SERVER=y` in `sdkconfig.esp32dev`.
- **Switch:** the relay module is active-low and powered from 5V, so `app_sw.c` inverts the output and starts with the relay OFF.
- **Gateway:** environment changed to `esp32dev`, custom 2 MB partition table enabled, HTTP header length set to 4096.

## Wi-Fi credentials
The gateway reads `WIFI_SSID` and `WIFI_PASS` from environment variables at build time. They are not stored in this repository.

## Not yet done
Gateway upload and web page test, sensor provisioning, and the sensor-to-switch automatic test.