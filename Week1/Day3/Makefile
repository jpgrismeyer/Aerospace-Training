TARGET = app
MCU = cortex-m4

CFLAGS = -mcpu=$(MCU) -mthumb -O2 -Wall -Wextra -ffunction-sections -fdata-sections
LDFLAGS = -T linker/STM32L475.ld -Wl,--gc-sections -Wl,-Map=$(TARGET).map

SRC = src/main.c src/startup_stm32l4xx.s

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(SRC)
	arm-none-eabi-gcc $(CFLAGS) $(SRC) $(LDFLAGS) -o $@

$(TARGET).bin: $(TARGET).elf
	arm-none-eabi-objcopy -O binary $< $@

flash: $(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32l4x.cfg -c "program $< verify reset exit"

clean:
	del /Q *.o *.elf *.bin *.map 2>nul || echo nothing to clean