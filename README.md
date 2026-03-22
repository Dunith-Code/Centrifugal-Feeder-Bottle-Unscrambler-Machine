# Centrifugal-Feeder-Bottle-Unscrambler-Machine

## 📌 Project Overview
This project presents a centrifugal bottle unscrambler machine designed for Phoenix Industries, a manufacturer of PVC solvent cement and solvent bottles in sizes 25 ml, 50 ml, and 100 ml. The machine automates the task of orienting randomly placed bottles so that they exit with the hole facing upward, a critical requirement for downstream filling and capping processes. The system replaces manual labour, increases throughput, and ensures consistent orientation.

## 🎯 Problem Statement & Objective
Currently, a worker manually picks bottles from a basket and places them correctly on the conveyor. This is time‑consuming, inconsistent, and limits production speed.
Objective: Design, build, and test an automated centrifugal feeder that:

- Accepts a bulk load of bottles (all three sizes)
- Orients them to the correct neck‑up position
- Feeds them reliably onto a conveyor line

## 👤 What I did
I was responsible for the entire project lifecycle, from concept to 90% completion of the final machine. My contributions include:

**Conceptualisation & Prototyping**
- Developed initial sketches and built two functional prototypes.
- Tested the first prototype to validate the centrifugal orientation principle.
- Refined the design in the second prototype, adjusting scallop sizes and turning mechanisms for all three bottle sizes.

**Mechanical Design & Calculations**
- Performed all necessary calculations: motor torque, speed, pulley and timing belt sizing, bearing selection, worm gearbox specification, and structural loads.
- Created detailed 3D models and engineering drawings using SolidWorks.
- Designed custom components: scallop wheels, rotating base plates, angle‑changing mechanism, bottle clearing wing, and exit guides.

**Manufacturing & Assembly**
- Sourced components and prepared a comprehensive costing list.
- Supervised the cutting and fabrication of mechanical parts together with technicians.

**Control System & Software**
- Programmed the stepper motor (NEMA 34) with microstepping for smooth and precise motion.
- Developed a C++ control logic (Arduino) and a Python graphical user interface (GUI) for operator‑friendly control of RPM, direction, start/stop, and status monitoring.

**Testing & Optimisation**
- Conducted iterative testing to fine‑tune the turning mechanism, exit path, and bottle clearing system.
- Solved real‑world issues such as bottle jamming, improper orientation, and exit misalignment.

## 🏗️ System Architecture & Key Components
**Hardware**
|  Component |	Specification / Role |
| :--- | :--- |
| Scallop Wheels | Custom‑cut wheels with scallop pockets sized for 25, 50, and 100 ml bottles. |
| Rotating Base Plate	| Transfers bottles to the turning mechanism. |
| Bottle Turning Mechanism	| 90° rotation device that flips bottles to neck‑up orientation. |
| Bottle Clearing Item |	Wing‑shaped attachment that sweeps overloaded bottles and ensures they enter scallops. |
| Angle Changing Mechanism	| Threaded bar system to adjust the machine tilt angle for optimal centrifugal action. |
| Exit Guide	| Aluminium wire / shaped plate to guide correctly oriented bottles out of the machine. |
| NEMA 34 Stepper Motor |	200 steps/rev, with microstepping (up to 1/16) for smooth motion. |
| OK2D872 Stepper Driver |	Fully digital driver, 24‑110V DC or 18‑80V AC, 7.2 A peak. |
| Worm Gear | Reducer (NMR40)	5:1 ratio, non‑backdrivable, increases torque. |
| Power Supply |	MEAN WELL DR‑120‑24, 24 V DC, 5 A. |
| Arduino Uno |	Microcontroller for motor control and serial communication. |

**Software**
- Arduino C++ – Low‑level stepper motor control with acceleration, direction, and RPM management.
- Python (Tkinter, PySerial) – GUI that sends commands to the Arduino via serial port.
- SolidWorks – Full mechanical design and assembly.

## ⚙️ Mechanisms Explained
1. Scallop Wheel & Centrifugal Feeding
Bottles are placed into the rotating bowl. Centrifugal force pushes them toward the edge, where they settle into scallop pockets. Incorrectly oriented bottles (neck‑down or sideways) fall out or are forced to re‑enter until they align properly.

2. Turning Mechanism
A dedicated 90° rotating support flips the bottles so that the neck faces upward. The bottle’s head is guided by the edge of the rotating base plate during this motion.

3. Bottle Clearing System
A motor‑driven wing rotates above the scallop wheel, clearing any overload of bottles and helping them find their way into empty scallops.

4. Angle Adjustment
The entire feeder can be tilted using a threaded bar mechanism. This angle is critical for achieving the right centrifugal force and bottle flow.

5. Exit Guide
After correct orientation, bottles are guided along a precisely shaped aluminium wire (or plate) that leads them smoothly out of the machine onto the conveyor.

## 🧪 Challenges & Solutions
|  Component |	Specification / Role |
| :--- | :--- |
| Prototype 1 turning mechanism failed | Built second prototype with a redesigned 90° rotating support. |
| Scallop sizes not suitable for all three bottle sizes |	Manufactured new scallop wheels with pocket dimensions optimised for each size. |
| Bottles not entering scallops / jamming |	Added a bottle clearing mechanism (wing with fibres) driven by an auxiliary motor. |
| Turning mechanism reduced cycle time |	Designed a new turning plate and upper part, tested adjustments thoroughly before final build. |
| Bottles exiting incorrectly after rotation |	Iteratively adjusted the aluminium exit guide to create a precise, tight path. |
| Exit plate angle not perpendicular – bottles misaligned	| Re‑shaped the exit plate to have a gradual angle transition, ensuring bottles exit correctly. |
| Centrifugal feeder required variable tilt angle |	Implemented a practical angle‑changing mechanism using a thread bar and lockable pivot. |

## 📈 Results & Outcomes
### Prototype 1
- Validated the concept: centrifugal force can orient bottles.
- Demonstrated the feasibility of automated unscrambling.

### Prototype 2
- Successfully handled all three bottle sizes.
- Refined the turning mechanism and exit guide.
- Achieved stable cycle times and orientation reliability.

### Final Project (90% Complete)
- All mechanical components designed, calculated, and fabricated.
- Control system (Arduino + Python GUI) fully functional.
- Machine can handle 25 ml, 50 ml, and 100 ml bottles with consistent orientation.

### Key performance features:
- Adjustable RPM from 0 to 600 (driver‑limited).
- Direction selectable (CW/CCW).
- Acceleration ramping for smooth start/stop.
- Real‑time RPM display and status monitoring.
- Tilt angle easily adjustable for optimal feeding.

## 💻 Code Explanation
### Arduino Code (`stepper.ino`)
- Pins: STEP, DIR, ENABLE on pins 3,4,5.
- Microstepping: 4× microstepping (800 steps/rev) for smooth motion.
- RPM Control: Accepts commands via serial (e.g., RPM 30).
- Acceleration: Gradual ramp‑up/down to avoid stalling.
- Direction: CW (clockwise) and CCW commands.
- Simulation Mode: SIM toggles a simulation that prints status without moving the motor (useful for testing the GUI).

### Python GUI (`gui_mine.py`)
- Libraries: Tkinter (UI), PySerial (serial communication).
- Auto‑detects Arduino port (or falls back to COM3).
- Features:
  - RPM entry and display (progress bar + numeric label).
  - Direction radio buttons (Clockwise / Counter‑Clockwise).
  - Start / Stop buttons.
  - Status bar showing last sent command.
- Commands Sent: `RPM <value>`, `CW`, `CCW`, `START`, `STOP`.


## 🚀 How to Use
### Prerequisites
- Python 3.x with pyserial installed (pip install pyserial).
- Arduino IDE (to upload `stepper.ino` to the Uno board).
- Hardware connections: NEMA 34 motor, OK2D872 driver, power supply, etc., as per the schematic.

### Setup
- Upload Arduino code – Open `stepper.ino` in Arduino IDE, select correct board and port, upload.
- Connect Arduino to PC via USB.
- Run Python GUI – Execute `gui_mine.py`. It will automatically detect the Arduino port (if not, edit the port manually in the code).
- Power on the machine – Ensure the motor driver and power supply are energised.

### Operation
- Enter desired RPM (≤ 600) and click Apply.
- Select direction (CW or CCW).
- Press Start Motor to begin rotation; press Stop Motor to halt.
- Observe status messages and RPM meter.

## 📚 Knowledge Gained
- Mechanical Design: Real‑world application of torque, friction, and load calculations beyond textbook theory.
- Prototyping & Iteration: Importance of building successive prototypes to uncover hidden issues (e.g., turning mechanism, scallop dimensions).
- Control Systems: Programming stepper motors with microstepping, acceleration profiles, and serial communication.
- Integration: Bridging mechanical, electrical, and software components into a cohesive machine.
- Industrial Problem Solving: Handling constraints like cycle time, reliability, and operator‑friendly interfaces.

## 🔮 Future Improvements
- Complete final assembly – Integrate the last 10% of components (safety guards, final wiring, etc.).
- Add sensors – Use photoelectric sensors to detect bottle presence and synchronise with the conveyor.
- Touchscreen HMI – Replace the Python GUI with a dedicated industrial touch panel.
- Full production automation – Link the feeder with filling/capping machines via PLC.

## 🤝 Acknowledgments
- Phoenix Industries for the opportunity and guidance.
- Supervisor for technical support and component procurement.
- Workshop technicians for fabrication assistance.

## 📄 License
This project is for educational and industrial application purposes. Please contact the author for reuse details.
