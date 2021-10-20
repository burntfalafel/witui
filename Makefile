CC=clang
LIB = lib/libwpa_client.a
CFLAGS=-lpthread -D CONFIG_CTRL_IFACE -D CONFIG_CTRL_IFACE_UNIX
CCFLAGS=-Wall
DEPS = include/includes.h include/wpa_ctrl.h include/common.h
SRC = src/wpa_interface.c
TARGET = witui

all: $(TARGET)

$(TARGET): $(SRC) 
	$(CC) $(CCFLAGS) $(SRC) $(LIB) -o $@ $(CFLAGS)

.PHONY: clean

clean:
		rm -f *.o $(TARGET) 