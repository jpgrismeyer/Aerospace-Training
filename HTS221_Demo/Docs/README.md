Project: HTS221 Acquisition Demo
Version: 0.1
Author: Juan Pablo Grismeyer
Date: 27.10.2025

1. Purpose
The purpose of this software component is:
- Read temperature and relative humidity from the HTS221 environmental sensor over I²C.
- Apply calibration to convert raw sensor readings into physical units (°C, %RH).
- Provide a simple health indication on the board LED based on measured temperature.
- Produce basic verification evidence similar to DO-178C Level D style:
  - Requirements
  - Design
  - Implementation
  - Verification results
  - Traceability

Target HW:
- MCU: STM32L475 (Cortex-M4F)
- Sensor: HTS221 (I²C address 0x5F)
- Bus: I²C2 @ 100 kHz
- LED: user LED on the discovery board (LED2 ->PB14)

Software constraints:
- No HAL calls in functional logic of the driver (I²C transactions done register-level).
- Startup, clock, and basic MCU init may come from STM32CubeIDE to avoid wasting time on bring-up.
- Build must be reproducible via CubeIDE and via a standalone Makefile using arm-none-eabi-gcc.

Intended Design Assurance Level (DAL):
- We treat this module as DAL D.
  Rationale: loss of this function would not create safety hazard, only loss of convenience telemetry.
  We still apply traceability and verification discipline.

2. High-Level Software Requirements (HLR)
HLR-001: The software shall initialize I²C2 peripheral to communicate with the HTS221 sensor at 100 kHz.
HLR-002: The software shall read the HTS221 WHO_AM_I register and verify that it equals 0xBC.
HLR-003: The software shall read raw humidity and temperature registers from HTS221.
HLR-004: The software shall convert raw sensor output to physical units (°C, %RH) using the calibration constants stored in HTS221.
HLR-005: The software shall toggle the user LED faster when temperature > TEMP_HIGH_THRESHOLD_C.
HLR-006: The software shall provide a periodic measurement every ~500 ms.

3. Derived / Low-Level Requirements (LLR)
LLR-001: The I²C2 peripheral clock shall be enabled in RCC.
LLR-002: PB10 shall be configured as I²C2_SCL (AF4, open-drain, pull-up).
LLR-003: PB11 shall be configured as I²C2_SDA (AF4, open-drain, pull-up).
LLR-004: I2C2_TIMINGR shall be configured for standard mode (~100 kHz) with SYSCLK from SystemClock_Config().
LLR-005: The function HTS221_ReadReg(uint8_t reg) shall:
         - generate START
         - send device address 0x5F (write)
         - send register index
         - generate RESTART
         - send device address 0x5F (read)
         - read 1 byte
         - generate STOP
LLR-006: The function HTS221_Init() shall check WHO_AM_I and only mark the sensor as "ready" if WHO_AM_I == 0xBC.
LLR-007: The function HTS221_ReadTemperatureC() shall return temperature in degrees Celsius as float.
LLR-008: The main loop shall:
         - call HTS221_ReadTemperatureC()
         - compare result with TEMP_HIGH_THRESHOLD_C (default 28.0 °C)
         - set LED blink period accordingly.

4. Software Architecture / Design
Modules:
- i2c_lowlevel.c/.h
  - Direct register access to STM32 I²C2.
  - Implements basic byte read/write on 7-bit I²C address 0x5F.
- hts221.c/.h
  - Sensor-specific logic.
  - Knows register map of HTS221.
  - Performs WHO_AM_I check, calibration math.
- main.c
  - Initializes system.
  - Periodically polls sensor.
  - Drives LED policy.

Interfaces:
- main.c calls HTS221_Init(), HTS221_ReadTemperatureC(), HTS221_ReadHumidityPerc().
- hts221.c calls i2c_lowlevel_*() functions.
- i2c_lowlevel.c touches MCU registers (RCC, GPIOB, I2C2).

5. Verification Plan
TEST-001 (REQ HLR-002):
  After init, read WHO_AM_I.
  PASS if value == 0xBC.
TEST-002 (REQ HLR-004):
  Read temperature twice: ambient, then after heating sensor (finger/soplar).
  PASS if value increases by >1°C.
TEST-003 (REQ HLR-005):
  Force TEMP_HIGH_THRESHOLD_C = 25°C.
  PASS if LED blinks fast when warm, slow when cool.

Each TEST-XXX will be logged in App/Verification/Verification_Report.md
with PASS/FAIL and measured values.

6. Traceability Matrix (initial draft)
HLR-001 -> LLR-001/002/003/004 -> i2c_lowlevel_init()
HLR-002 -> LLR-005/006         -> HTS221_Init()
HLR-003 -> LLR-005             -> HTS221_ReadReg(), HTS221_ReadHumidityRaw()
HLR-004 -> LLR-007             -> HTS221_ReadTemperatureC()
HLR-005 -> LLR-008             -> main.c LED_control_logic()
HLR-006 -> LLR-008             -> main.c loop timing

This matrix will be updated after implementation & test, and committed with the code.