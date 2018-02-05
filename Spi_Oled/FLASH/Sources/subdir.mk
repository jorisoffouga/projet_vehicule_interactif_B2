################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/SSD1306.c" \
"../Sources/Spi.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/SSD1306.c \
../Sources/Spi.c \
../Sources/main.c \

OBJS += \
./Sources/Events_c.obj \
./Sources/SSD1306_c.obj \
./Sources/Spi_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/Events_c.obj" \
"./Sources/SSD1306_c.obj" \
"./Sources/Spi_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/Events_c.d \
./Sources/SSD1306_c.d \
./Sources/Spi_c.d \
./Sources/main_c.d \

C_DEPS_QUOTED += \
"./Sources/Events_c.d" \
"./Sources/SSD1306_c.d" \
"./Sources/Spi_c.d" \
"./Sources/main_c.d" \

OBJS_OS_FORMAT += \
./Sources/Events_c.obj \
./Sources/SSD1306_c.obj \
./Sources/Spi_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Events.args" -ObjN="Sources/Events_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SSD1306_c.obj: ../Sources/SSD1306.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SSD1306.args" -ObjN="Sources/SSD1306_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/Spi_c.obj: ../Sources/Spi.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Spi.args" -ObjN="Sources/Spi_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


