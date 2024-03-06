################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CMAP_DEPS)),)
-include $(CMAP_DEPS)
endif
ifneq ($(strip $(COMP_DEPS)),)
-include $(COMP_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(FRAGX_DEPS)),)
-include $(FRAGX_DEPS)
endif
ifneq ($(strip $(FRAG_DEPS)),)
-include $(FRAG_DEPS)
endif
ifneq ($(strip $(GEOM_DEPS)),)
-include $(GEOM_DEPS)
endif
ifneq ($(strip $(SAU_DEPS)),)
-include $(SAU_DEPS)
endif
ifneq ($(strip $(STOY_DEPS)),)
-include $(STOY_DEPS)
endif
ifneq ($(strip $(TESSCTRL_DEPS)),)
-include $(TESSCTRL_DEPS)
endif
ifneq ($(strip $(TESSEVAL_DEPS)),)
-include $(TESSEVAL_DEPS)
endif
ifneq ($(strip $(VERT_DEPS)),)
-include $(VERT_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := HoloDOS_server
BUILD_ARTIFACT_EXTENSION :=
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: HoloDOS_server

# Tool invocations
HoloDOS_server: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "HoloDOS_server" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) HoloDOS_server
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
