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
Versuch1.lss \

FLASH_IMAGE += \
Versuch1.hex \

EEPROM_IMAGE += \
Versuch1.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Versuch1.elf secondary-outputs

# Tool invocations
Versuch1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Versuch1.map -nostdlib -mmcu=atmega16 -o "Versuch1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Versuch1.lss: Versuch1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Versuch1.elf  >"Versuch1.lss"
	@echo 'Finished building: $@'
	@echo ' '

Versuch1.hex: Versuch1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Versuch1.elf  "Versuch1.hex"
	@echo 'Finished building: $@'
	@echo ' '

Versuch1.eep: Versuch1.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Versuch1.elf  "Versuch1.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Versuch1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Versuch1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Versuch1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
