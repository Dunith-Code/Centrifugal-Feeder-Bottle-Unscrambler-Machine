# Centrifugal-Feeder-Bottle-Unscrambler-Machine

## 📌 Project Overview
This project automates the feeding of PVC solvent bottles (25 ml, 50 ml, 100 ml) onto a production line with the neck facing upward. A centrifugal unscrambler replaces manual labour, ensuring consistent orientation and higher throughput.

## 👤 What I did
I was responsible for the entire project lifecycle, from concept to 90% completion of the final machine.
- Concept & Prototyping – First and second prototypes validated the centrifugal principle and refined scallop pockets for all bottle sizes.
- Mechanical Design – Full SolidWorks model; calculated motor torque, speed, gearbox, bearings, and structural loads.
- Fabrication – Supervised cutting and assembly of mechanical parts.
- Control System – Arduino (C++) stepper motor control with acceleration; Python GUI for operator interface (RPM, direction, start/stop).
- Testing & Optimisation – Solved issues with turning mechanism, bottle jamming, exit guide, and tilt angle adjustment.

## ⚙️ Key Mechanisms
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

## 📈 Results & Outcomes
- Prototype 1 – Concept proven; orientation achieved via centrifugal force.
- Prototype 2 – Successfully handled all three bottle sizes; turning and exit mechanisms refined.
- Final Project (90% complete) – All mechanical components fabricated; control system fully functional; machine reliably orients and feeds bottles.

## 🤝 Acknowledgments
This system was developed as part of an internship project within a professional industrial setting. The success of this project was made possible by the guidance and support of the Automation Engineering team(including my supervisors and workshop technicians) of Phoenix Industries Ltd, Makandura, Sri Lanka.

## 📄 License & Copyright
This project was developed during an internship at Phoenix Industries.
All rights to the design, documentation, and software are owned by Phoenix Industries.
