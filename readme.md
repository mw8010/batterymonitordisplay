# Project Description: Battery Monitor with Display and Signal K Integration**

## Project Goal:
The goal of this project is to develop an ESP32-based battery monitor display for monitoring battery systems on a boat. The system is integrated into the Signal K network and visualizes real-time data on voltage, current, temperature, and remaining battery life.

## Main Features:

- **Live Display of Battery Values:** Visualization of voltage, current, temperature, and remaining runtime for up to four batteries.
- **Signal K Integration:** Automatic adaptation of retrieved data based on Signal K paths.
- **Touchscreen Control:** Interactive display with LVGL for intuitive operation.
- **Dynamic Configuration:** Battery names can be set via the SensESP WebUI.
- **Display Timeout with Touch Wake Function:** To save energy, the display turns off after a period of inactivity and can be reactivated by touch.
- **LCARS Design:** The user interface is designed in the Star Trek LCARS style.

## Hardware Requirements:

- **ESP32 Dev Board** as the central processing unit
- **[Guition JC4827W543 4.3" ESP32 Module](https://de.aliexpress.com/item/1005006729377800.html)**
- **Signal K Server** for providing data
- **WiFi** for connection to the Signal K network

## Software Architecture:

- **Arduino GFX Library** for display control
- **LVGL (LittlevGL)** for UI design
- **SensESP** for communication with the Signal K server
- **Signal K Listener** for real-time monitoring of battery sensor values

## Functionality:

1. On startup, battery names are loaded from the configuration.
2. The corresponding Signal K paths are dynamically generated.
3. Sensor values are regularly retrieved from the network and updated on the display.
4. The display visually indicates whether the batteries are charging or discharging.
5. A touch wake function ensures energy-efficient display control.

## Configuring SensESP:
After the first startup, the ESP32 creates an access point.
Connect to the network and enter the WiFi credentials (**WiFi password: thisisfine**).
Using the SensESP WebUI, you can configure the battery (see Configuration) and integrate the ESP32 into the network where the Signal K server is running.

## License:
This project is licensed under the [**GNU General Public License (GPL)**](license.md).

