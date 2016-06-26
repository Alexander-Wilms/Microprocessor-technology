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
AssemblerTest.lss \

FLASH_IMAGE += \
AssemblerTest.hex \

EEPROM_IMAGE += \
AssemblerTest.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: AssemblerTest.elf secondary-outputs

# Tool invocations
AssemblerTest.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,AssemblerTest.map -nostdlib -mmcu=atmega128 -o "AssemblerTest.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AssemblerTest.lss: AssemblerTest.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AssemblerTest.elf  >"AssemblerTest.lss"
	@echo 'Finished building: $@'
	@echo ' '

AssemblerTest.hex: AssemblerTest.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex AssemblerTest.elf  "AssemblerTest.hex"
	@echo 'Finished building: $@'
	@echo ' '

AssemblerTest.eep: AssemblerTest.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex AssemblerTest.elf  "AssemblerTest.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AssemblerTest.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 AssemblerTest.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) AssemblerTest.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
