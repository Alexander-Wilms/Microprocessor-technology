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
Versuch4_Laborbericht.lss \

FLASH_IMAGE += \
Versuch4_Laborbericht.hex \

EEPROM_IMAGE += \
Versuch4_Laborbericht.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Versuch4_Laborbericht.elf secondary-outputs

# Tool invocations
Versuch4_Laborbericht.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Versuch4_Laborbericht.map -L/home/mit/MIT-workspace/Versuch3_Durchfuehrung/libMIT -L/home/mit/MIT-workspace/Versuch4_Vorbereitung/libMIT -L/home/mit/MIT-workspace/libMIT -mmcu=atmega128 -o "Versuch4_Laborbericht.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Versuch4_Laborbericht.lss: Versuch4_Laborbericht.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Versuch4_Laborbericht.elf  >"Versuch4_Laborbericht.lss"
	@echo 'Finished building: $@'
	@echo ' '

Versuch4_Laborbericht.hex: Versuch4_Laborbericht.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Versuch4_Laborbericht.elf  "Versuch4_Laborbericht.hex"
	@echo 'Finished building: $@'
	@echo ' '

Versuch4_Laborbericht.eep: Versuch4_Laborbericht.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Versuch4_Laborbericht.elf  "Versuch4_Laborbericht.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Versuch4_Laborbericht.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 Versuch4_Laborbericht.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Versuch4_Laborbericht.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
