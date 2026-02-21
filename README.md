IoT Smart Temperature Monitoring System 🌡️🔥

A real-time cloud-connected IoT system that monitors temperature using ESP8266 and DHT11 sensor, triggers alerts when thresholds are exceeded, and displays live data on a public web dashboard using Firebase Realtime Database.

---

🚀 Features

- Real-time temperature monitoring using DHT11
- Cloud data sync using Firebase Realtime Database
- Threshold-based alert logic (HIGH / NORMAL status)
- Automatic LED & Buzzer alerts when temperature exceeds limit
- Live web dashboard with real-time updates
- Temperature history graph (last 20 readings)
- Public deployment using Vercel

---

🧠 System Architecture

DHT11 Sensor → ESP8266 NodeMCU → Firebase Realtime Database → Web Dashboard

---

🛠️ Hardware Components

- ESP8266 NodeMCU  
- DHT11 Temperature Sensor  
- LED Indicator  
- Buzzer  
- Jumper wires  

---

💻 Software & Tools

- Arduino IDE  
- Firebase Realtime Database  
- HTML, JavaScript  
- Chart.js (for graph)  
- Vercel (for hosting)  

---

🌐 Live Dashboard

👉 https://iot-smart-temp-monitor.vercel.app  

(Displays real-time temperature, system status and graph)

---

📂 Project Files

- `index.html` → Web dashboard  
- `esp8266_firebase_alert.ino` → ESP8266 firmware  
- `block_diagram.png` → System block diagram  

---

⚙️ Alert Logic
If Temperature > 30°C: LED ON Buzzer ON Status = HIGH
Else: LED OFF Buzzer OFF Status = NORMAL
---

📸 Screenshots

- Firebase Realtime Data  
- Live Dashboard  
- Alert Status Display  

---

## System Block Diagram

![Block Diagram](IMG-20260221-WA0009.jpg)
👨‍💻 Author

Sai Darshan  
Electrical & Electronics Engineering Student  
Interested in Embedded Systems & IoT  

---

⭐ Future Improvements

- Mobile app integration  
- Multiple sensor nodes  
- Email/SMS alerts  
- Data analytics dashboard  

---
