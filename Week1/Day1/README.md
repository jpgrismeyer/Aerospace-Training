# Day 1 – Introduction to the Aerospace Environment

## 1. Summary of DO-178C

*Purpose:*  
DO-178C ensures that airborne software performs its intended function with a level of confidence in safety consistent with airworthiness requirements. Compliance is achieved through a structured process of planning, development, verification, and configuration control, producing objective evidence for certification.

*Life-Cycle Phases:*  
Planning, Development, Verification, Configuration Management, Quality Assurance, and Certification Liaison.  
Each phase must produce documented and traceable evidence.

*Verification Independence:*  
Verification must be conducted by individuals or teams independent from those who performed the development, ensuring unbiased and objective verification.  
The required independence increases with the software’s criticality.

*Design Assurance Levels (DAL):*

| Level | Failure Condition | Typical Effect |
|:--:|:--|:--|
| A | Catastrophic | Loss of aircraft / life |
| B | Hazardous | Severe injury / major damage |
| C | Major | Crew workload increase |
| D | Minor | Slight inconvenience |
| E | No effect | No safety impact |

---

## 2. Development Environment

| Item | Description |
|------|-------------|
| MCU | STM32L475  |
| Toolchain | GCC (arm-none-eabi-gcc) + OpenOCD / STM32CubeIDE |
| IDE / Editor | VS Code / STM32CubeIDE |
| RTOS | — (to be added in Week 2) |
| Test Application | LED blinking OK ✅ |
| Build Log | (insert short compilation output or screenshot) |

---

## 3. Hazard Analysis (Initial)

| Hazard | Description | Estimated DAL |
|--------|--------------|----------------|
| Sensor read failure | Loss of environmental data during flight | C |
| Actuator control error | Uncommanded motion of control surface | B |
| Unexpected reset | Temporary loss of non-critical systems | D |

---

## 4. Verification Summary

| Step | Status | Notes |
|------|---------|-------|
| Build and flash | ✅ Successful | LED blinking verified |
| Toolchain version logged | ✅ | gcc version ... |
| Documentation committed | ✅ | git commit -m "Day1 - DO-178C intro and environment setup" |

---

## 5. Conclusions

Today’s goal was to understand the fundamentals of DO-178C and set up a deterministic embedded environment.  
The STM32 environment is functional, the build process reproducible, and the first traceable document created.

Next session → *Software architecture and layered design (Day 2).*