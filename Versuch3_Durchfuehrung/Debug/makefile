################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include myCode/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Versuch3_Durchfuehrung.lss \

FLASH_IMAGE += \
Versuch3_Durchfuehrung.hex \

EEPROM_IMAGE += \
Versuch3_Durchfuehrung.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Versuch3_Durchfuehrung.elf secondary-outputs

# Tool invocations
Versuch3_Durchfuehrung.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Versuch3_Durchfuehrung.map -L/home/mit/MIT-workspace/Versuch3_Durchfuehrung/libMIT -L/home/mit/MIT-workspace/libMIT -mmcu=atmega128 -o "Versuch3_Durchfuehrung.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Versuch3_Durchfuehrung.lss: Versuch3_Durchfuehrung.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Versuch3_Durchfuehrung.elf  >"Versuch3_Durchfuehrung.lss"
	@echo 'Finished building: $@'
	@echo ' '

Versuch3_Durchfuehrung.hex: Versuch3_Durchfuehrung.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Versuch3_Durchfuehrung.elf  "Versuch3_Durchfuehrung.hex"
	@echo 'Finished building: $@'
	@echo ' '

Versuch3_Durchfuehrung.eep: Versuch3_Durchfuehrung.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Versuch3_Durchfuehrung.elf  "Versuch3_Durchfuehrung.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Versuch3_Durchfuehrung.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 Versuch3_Durchfuehrung.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Versuch3_Durchfuehrung.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
