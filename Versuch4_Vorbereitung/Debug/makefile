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
Versuch4_Vorbereitung.lss \

FLASH_IMAGE += \
Versuch4_Vorbereitung.hex \

EEPROM_IMAGE += \
Versuch4_Vorbereitung.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Versuch4_Vorbereitung.elf secondary-outputs

# Tool invocations
Versuch4_Vorbereitung.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Versuch4_Vorbereitung.map -L/home/mit/MIT-workspace/Versuch3_Durchfuehrung/libMIT -L/home/mit/MIT-workspace/libMIT -mmcu=atmega128 -o "Versuch4_Vorbereitung.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Versuch4_Vorbereitung.lss: Versuch4_Vorbereitung.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Versuch4_Vorbereitung.elf  >"Versuch4_Vorbereitung.lss"
	@echo 'Finished building: $@'
	@echo ' '

Versuch4_Vorbereitung.hex: Versuch4_Vorbereitung.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Versuch4_Vorbereitung.elf  "Versuch4_Vorbereitung.hex"
	@echo 'Finished building: $@'
	@echo ' '

Versuch4_Vorbereitung.eep: Versuch4_Vorbereitung.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Versuch4_Vorbereitung.elf  "Versuch4_Vorbereitung.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Versuch4_Vorbereitung.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 Versuch4_Vorbereitung.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Versuch4_Vorbereitung.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
