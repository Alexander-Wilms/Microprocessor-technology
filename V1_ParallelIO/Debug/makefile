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
V1_ParallelIO.lss \

FLASH_IMAGE += \
V1_ParallelIO.hex \

EEPROM_IMAGE += \
V1_ParallelIO.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: V1_ParallelIO.elf secondary-outputs

# Tool invocations
V1_ParallelIO.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,V1_ParallelIO.map -nostdlib -mmcu=atmega128 -o "V1_ParallelIO.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

V1_ParallelIO.lss: V1_ParallelIO.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S V1_ParallelIO.elf  >"V1_ParallelIO.lss"
	@echo 'Finished building: $@'
	@echo ' '

V1_ParallelIO.hex: V1_ParallelIO.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex V1_ParallelIO.elf  "V1_ParallelIO.hex"
	@echo 'Finished building: $@'
	@echo ' '

V1_ParallelIO.eep: V1_ParallelIO.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex V1_ParallelIO.elf  "V1_ParallelIO.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: V1_ParallelIO.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 V1_ParallelIO.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) V1_ParallelIO.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
