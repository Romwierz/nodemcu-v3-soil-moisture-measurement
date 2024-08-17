# Soil Moisture Measurement with ESP8266
This is a small prototyping project aimed at measuring soil moisture levels using a ESP8266 module (NodeMCU V3 board) and multiple sensors. The project allows for real-time monitoring of soil moisture via a web interface with the ability to control an LED and save/load plant names through a simple web server. 

## Hardware requirements
- NodeMCU V3 (or any board with ESP8266 module)
- Soil Moisture Sensors (HW-103 detector + probe) (4)
- Silicon Diodes (1N4148 or similar) (4)
- Wires for connections
- Breadboard

## Software requirements
- VS Code with PlatformIO plugin
- ESP8266 Board Package (installable via the PlatformIO)
- Libraries:
  - ESP8266WiFi
  - ESP8266WebServer
  - FS

## Connections
<img src="https://github.com/user-attachments/assets/c4f823a0-0868-4cd1-8d39-b63226c4e12c" alt="connections" width="600"/>

## Installation
1. Clone the repository into a desired folder on your system:
   ```bash
   git clone https://github.com/Romwierz/nodemcu-v3-soil-moisture-measurement
   ```
2. Open the project folder through PlatformIO in VS Code.
3. Install the necessary libraries.
4. Upload the code to your ESP8266.
5. Upload data folder to your ESP8266 (PlatformIO -> Project Tasks -> nodemcuv2 -> Platform -> Upload Filesystem Image).

## Configuration
### WiFi Configuration
The WiFi credentials are stored in data/config.txt. This file must be updated with your network's SSID and password. Then update data folder on your ESP8266 (Upload Filesystem Image through PlatformIO).

### Sensor Pins Configuration
Sensor pins are defined in config.h. Modify this file if you use different pins.

## Usage
1. **Power On:**
    - Power on the NodeMCU and it will connect to your configured WiFi network.
2. **Access the Web Interface:**
    - Open your web browser and navigate to the IP address displayed in the serial monitor to access the web interface.
3. **Control the LED:**
    - Use the web interface to turn the LED on or off.
4. **Monitor Soil Moisture:**
    - The interface will display real-time soil moisture readings from all four sensors.
5. **Manage Plant Names:**
    - Save and load plant names through the provided interface for better management of your plants.
6. **Timeout**
    - Few seconds after closing the web page all sensors will be turned off.

## Acknowledgments
- Inspiration from various soil moisture measurement projects and tutorials available online.
