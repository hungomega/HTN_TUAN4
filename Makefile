TARGET = main

CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

CPU = cortex-m3

CFLAGS = \
	-mcpu=$(CPU) \
	-mthumb \
	-mfloat-abi=soft \
	-O0 \
	-g3 \
	-Wall \
	-ffunction-sections \
	-fdata-sections \
	-fno-common \
	-std=c11

CFLAGS += \
	-IFreeRTOS/include \
	-IFreeRTOS/portable/ARM_CM3 \
	-I.

LDFLAGS = \
	-mcpu=$(CPU) \
	-mthumb \
	-mfloat-abi=soft \
	-Tlinker.ld \
	-Wl,--gc-sections \
	-Wl,-Map=$(TARGET).map \
	-nostartfiles \
	-specs=nano.specs \
	-specs=nosys.specs

SRC = \
	src/startup.c \
	src/main.c \
	FreeRTOS/tasks.c \
	FreeRTOS/queue.c \
	FreeRTOS/list.c \
	FreeRTOS/timers.c \
	FreeRTOS/event_groups.c \
	FreeRTOS/stream_buffer.c \
	FreeRTOS/croutine.c \
	FreeRTOS/portable/ARM_CM3/port.c \
	FreeRTOS/portable/MemMang/heap_4.c

OBJ = $(SRC:.c=.o)

all: $(TARGET).elf $(TARGET).bin

$(TARGET).elf: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).bin $(TARGET).map

flash: $(TARGET).bin
	st-flash write $(TARGET).bin 0x08000000