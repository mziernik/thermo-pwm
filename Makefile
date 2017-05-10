# Plik wygenerowany przez AvrMake

#Procesor
MMCU =		attiny24
#Zegar
F_CPU =		1000000
#Optimalizacja
OPTIMIZE =	s

DEVKIT_HOST =    devkit
AVRDUDE_PARAMS	= -V
AVRDUDE_FLASH	= $(OUT_DIR)/$(OUT_NAME).hex
AVRDUDE_EEPROM  =

#=========================================================================================
# Katalog źródeł
SRC_DIR =	src
# Katalog docelowy
OUT_DIR =	bin

BUILD_DIR = $(OUT_DIR)/build
# Nazwa pliku docelowego
OUT_NAME =	dist
# Ścieżki toolchain-a
#TOOLCHAIN =	C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain
TOOLCHAIN =	D:\Apps\AVR

include nbproject/MakefileImpl.mk

#-------------------------------------------------------------------------------

