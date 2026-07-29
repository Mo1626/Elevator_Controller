# Elevator_Controller

1- Abd AL_Rahman Farouk Mohamed ( DIO , ADC , UART , EXTI , TIMER0 ) { Team Leader & Supporter }

2- Mena Roziq Kamel Ayoup (depugging , testing , Management , Problem solving ) { Co_Leader & Software Architect }

3- Khadija Talaat Mahmoud Hassan ( Buzzer , lcd , led , Switch , keypad ) { Hard Working , Executor }

4- Athar Nassar Soliman Hamed ( State_Machine , Scheduler , Elevator_Manager ) { Application & motivation }

5- Lamiaa Essam Mohamed Saied ( Door , Sensor , Queue , Safety ) { Integrator , documentation }


Info:

# 🚀 Elevator Controller

A smart **4-floor Elevator Controller** implemented in **Embedded C** using the **ATmega32** microcontroller. The project simulates a real elevator control system in **Proteus** following a layered software architecture (MCAL / HAL / APP).

---

# 📌 Project Overview

The system controls a four-floor elevator by receiving requests from the keypad, storing them in a queue, and moving the elevator to the requested floors while managing the door and ensuring safe operation.

The project was developed to demonstrate embedded systems concepts including drivers, interrupts, timers, ADC, finite state machines, and modular software design.

---

# ✨ Features

* Four-floor elevator simulation
* Floor request queue management
* Automatic door opening and closing
* Elevator movement (Up / Down)
* LCD status display
* Keypad input for floor selection
* IR sensor for obstruction detection
* Overload detection using ADC
* Buzzer alerts for errors
* Interrupt-based safety handling
* Modular driver architecture

---

# 🏗 Software Architecture

The project follows a three-layer architecture:

```
Application (APP)

Elevator Logic
Queue Management
State Machine

HAL

LCD
Keypad
IR Sensor
Buzzer

MCAL

DIO
TIMER0
ADC
EXTI
GPIO


---

# ⚙ Hardware Components

* ATmega32
* 16×2 LCD
* 4×4 Keypad
* IR Sensor
* Buzzer
* LEDs
* ADC Input (Load Sensor Simulation)

---

# 🔄 Elevator Operation

1. The user selects a floor from the keypad.
2. The request is stored in the queue.
3. The controller determines the next destination.
4. The elevator moves toward the requested floor.
5. The current floor is displayed on the LCD.
6. The door opens automatically upon arrival.
7. After a delay, the door closes.
8. The controller processes the next request.

---

# 🛡 Safety Features

* Door obstruction detection using an IR sensor.
* Automatic door reopening when an obstacle is detected.
* Elevator overload detection using ADC.
* Buzzer warning during fault conditions.
* Door locking while the elevator is moving.

---

# 🛠 Development Tools

* Programming Language: Embedded C
* Microcontroller: ATmega32
* IDE: Eclipse
* Simulation: Proteus

---

# 📂 Project Structure

```
MCAL/
HAL/
APP/
main.c
```

---

# 🎯 Learning Objectives

This project demonstrates:

* Embedded C programming
* Driver development
* Queue implementation
* Finite State Machine (FSM)
* Interrupt handling
* Timer configuration
* ADC usage
* Embedded software architecture
* Modular programming

---


This project was developed as an educational Embedded Systems project to simulate a real elevator controller using the ATmega32 microcontroller.
