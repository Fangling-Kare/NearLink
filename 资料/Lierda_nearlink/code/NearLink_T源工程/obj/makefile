################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
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
SECONDARY_FLASH += \
NearLink_T.hex \

SECONDARY_LIST += \
NearLink_T.lst \

SECONDARY_SIZE += \
NearLink_T.siz \


# 所有目标
all: NearLink_T.elf secondary-outputs

# 工具调用
NearLink_T.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "C:\MRS_DATA\workspace\NearLink_T\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"NearLink_T.map" --specs=nano.specs --specs=nosys.specs -o "NearLink_T.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
NearLink_T.hex: NearLink_T.elf
	@	riscv-none-embed-objcopy -O ihex "NearLink_T.elf"  "NearLink_T.hex"
	@	@
NearLink_T.lst: NearLink_T.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "NearLink_T.elf" > "NearLink_T.lst"
	@	@
NearLink_T.siz: NearLink_T.elf
	@	riscv-none-embed-size --format=berkeley "NearLink_T.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) NearLink_T.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
