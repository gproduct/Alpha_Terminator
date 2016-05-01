################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../inc \
../src


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c \
../src/actuators.c \
../src/can.c \
../src/gpio.c \
../src/greenside.c \
../src/odometry.c \
../src/purpleside.c \
../src/system.c \
../src/uart.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o \
src/actuators.o \
src/can.o \
src/gpio.o \
src/greenside.o \
src/odometry.o \
src/purpleside.o \
src/system.o \
src/uart.o

OBJS_AS_ARGS +=  \
main.o \
src/actuators.o \
src/can.o \
src/gpio.o \
src/greenside.o \
src/odometry.o \
src/purpleside.o \
src/system.o \
src/uart.o

C_DEPS +=  \
main.d \
src/actuators.d \
src/can.d \
src/gpio.d \
src/greenside.d \
src/odometry.d \
src/purpleside.d \
src/system.d \
src/uart.d

C_DEPS_AS_ARGS +=  \
main.d \
src/actuators.d \
src/can.d \
src/gpio.d \
src/greenside.d \
src/odometry.d \
src/purpleside.d \
src/system.d \
src/uart.d

OUTPUT_FILE_PATH +=malo_govno.elf

OUTPUT_FILE_PATH_AS_ARGS +=malo_govno.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=10000000ULL  -I"D:\Atmel\7.0\Packs\atmel\ATmega_DFP\1.0.90\include" -I"../inc"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -Wextra -pedantic  -mmcu=at90can128  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=10000000ULL  -I"D:\Atmel\7.0\Packs\atmel\ATmega_DFP\1.0.90\include" -I"../inc"  -O0 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -Wextra -pedantic  -mmcu=at90can128  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="malo_govno.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax  -mmcu=at90can128   
	@echo Finished building target: $@
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "malo_govno.elf" "malo_govno.hex"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "malo_govno.elf" "malo_govno.eep" || exit 0
	"C:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "malo_govno.elf" > "malo_govno.lss"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "malo_govno.elf" "malo_govno.srec"
	"C:\WinAVR-20100110\bin\avr-size.exe" "malo_govno.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "malo_govno.elf" "malo_govno.a" "malo_govno.hex" "malo_govno.lss" "malo_govno.eep" "malo_govno.map" "malo_govno.srec" "malo_govno.usersignatures"
	