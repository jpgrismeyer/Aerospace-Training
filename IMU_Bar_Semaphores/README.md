# Flight Control System - Professional RTOS Implementation

This project implements the core flight control logic for a quadcopter using an **STM32L475 (Cortex-M4)**. It demonstrates advanced embedded systems engineering, including real-time scheduling, sensor fusion, and closed-loop control.

> **Note on Directory Name:** This project is part of my 'Aerospace' development series. While the directory name reflects the initial synchronization milestones, the current implementation covers a full Attitude and Heading Reference System (AHRS).

## 🚀 Key Technical Achievements

### 1. Real-Time Operating System (FreeRTOS)
The system is built on **CMSIS-RTOS v2**, utilizing a preemptive priority-based scheduler to ensure deterministic performance:
* **IMU_Task (100Hz):** High-priority task for real-time sensor acquisition and PID calculations.
* **Telemetry_Task (10Hz):** Formatted data streaming via UART without jitter injection into the control loop.
* **Baro_Task (10Hz):** Low-priority background task for altitude estimation.

### 2. Advanced Hardware Integration (I2C + DMA)
* **Zero-CPU Overhead:** Data from the **LSM6DSL** (IMU) and **LPS22HB** (Barometer) is acquired via **I2C with DMA**.
* **Thread-Safety:** Implemented **Mutexes** to manage shared access to the I2C2 bus and **Semaphores** to synchronize DMA transfer completion with RTOS tasks.

### 3. Control Theory & Signal Processing
* **Sensor Fusion:** A **Complementary Filter** combines gyroscope and accelerometer data to produce a stable pitch/roll estimate.
* **PID Control:** Three independent PID loops (Pitch, Roll, Yaw Rate) featuring:
    * Integral Clamping (Anti-Windup).
    * Output Saturation.
    * Dynamic Delta-Time calculation for consistent response.



## 🛠️ Tech Stack
* **Hardware:** STM32L475 (Discovery Kit IoT Node).
* **Language:** C (C99).
* **Toolchain:** STM32CubeIDE / HAL Drivers.
* **OS:** FreeRTOS.

## 📈 Current Status
* [x] Initial IMU/Baro Drivers.
* [x] RTOS Task Architecture & IPC (Queues/Mutexes).
* [x] Complementary Filter & Attitude Estimation.
* [x] PID Controller Implementation.
* [ ] PWM Motor Mixing (Upcoming).

---
*Developed for professional aerospace applications and high-reliability embedded systems.*