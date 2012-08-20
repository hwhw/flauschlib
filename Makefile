# MCU to compile for:
PROC    = 32MX220F032D

# tool configuration
CC      = xc32-gcc
AR      = xc32-ar

# compiler config
OPTIMIZE ?= -Os -mips16e
CFLAGS  = -g $(OPTIMIZE) -mprocessor=$(PROC)

# project config
OBJECTS = \
	systick.o \
	fifo.o \
	uart.o \
	spi.o \
	diskio.o

TARGET = libflausch.a

#############################################################################
# you can probably leave the following as they are:

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) -r "$@" $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c "$<" -o "$@"

clean:
	- rm $(OBJECTS) $(TARGET)
