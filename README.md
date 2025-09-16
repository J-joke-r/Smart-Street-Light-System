# 🌃 Smart Street Light System (Arduino + Sensors)

This project implements a **Smart Street Light System** using an **Arduino**, **BH1750 light sensor**, **PIR motion sensor**, and multiple LEDs.  
The system automatically controls the street lights based on ambient light intensity, motion detection, and a manual switch.

---

## 🚀 Features
- **Automatic Light Control** based on ambient light intensity from the **BH1750 light sensor**.  
- **Motion Detection** using a **PIR sensor** to turn on all LEDs when movement is detected.  
- **Manual Override Switch** to force all LEDs ON regardless of sensor readings.  
- **Brightness Control**:
  - Low light → LEDs glow dim.  
  - Medium light → LEDs glow at medium brightness.  
  - High light → LEDs turn OFF.  

---

## 🛠️ Hardware Components
- Arduino (Uno/Nano/compatible board)  
- BH1750 Light Intensity Sensor  
- PIR Motion Sensor  
- Push Button (for manual override)  
- 8 LEDs + Resistors  
- Jumper Wires & Breadboard  

---

## ⚡ Circuit Connections
- **LEDs** → Digital pins `2-9`  
- **Switch** → Digital pin `10`  
- **PIR sensor** → Digital pin `11`  
- **BH1750** → I2C pins (`SDA`, `SCL`)  

---

## 📜 How It Works
1. System continuously reads **light intensity** and **motion status**.  
2. If **motion is detected**, all LEDs turn ON at full brightness.  
3. If **no motion**:  
   - Switch pressed → All LEDs ON.  
   - Otherwise, LEDs adjust brightness based on light intensity.  
4. Data (light intensity + PIR state) is printed to the Serial Monitor.  

---

## 🔧 Installation & Usage
1. Install the **BH1750 Arduino Library** (via Arduino IDE Library Manager).  
2. Upload the code to Arduino.  
3. Open **Serial Monitor** (`9600 baud`) to view sensor readings.  
4. Observe LEDs reacting to motion and light levels.  

---

## 🖼️ Demo Output
- **Low Light** → LEDs glow dim.  
- **Medium Light** → LEDs glow medium.  
- **High Light** → LEDs OFF.  
- **Motion Detected** → All LEDs ON.  

---

## 📊 Serial Monitor Example
