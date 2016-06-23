TARGET = VitaAudio
OBJS   = font.o Main.o \
		Nogg/src/util/memory.o \
		Nogg/src/util/float-to-int16.o \
		Nogg/src/util/decode-frame.o \
		Nogg/src/decode/stb_vorbis.o \
		Nogg/src/decode/setup.o \
		Nogg/src/decode/seek.o \
		Nogg/src/decode/packet.o \
		Nogg/src/decode/io.o \
		Nogg/src/decode/decode.o \
		Nogg/src/decode/crc32.o \
		Nogg/src/api/version.o \
		Nogg/src/api/seek-tell.o \
		Nogg/src/api/read-int16.o \
		Nogg/src/api/read-float.o \
		Nogg/src/api/open-file.o \
		Nogg/src/api/open-callbacks.o \
		Nogg/src/api/open-buffer.o \
		Nogg/src/api/info.o \
		Nogg/src/api/close.o \
		Media/WavFile.o \
		Media/FileBuffer.o \
		Media/Audio.o

LIBS = -lvita2d -lSceDisplay_stub -lSceGxm_stub -lSceCommonDialog_stub \
	-lSceCtrl_stub -lSceTouch_stub -lSceAudio_stub -lfreetype -lpng -lz -lm -lstdc++

PREFIX  	= arm-vita-eabi
CC      	= $(PREFIX)-gcc
CXX      	= $(PREFIX)-g++
CFLAGS  	= -Wl,-q -O2 -std=c99 -I./Nogg -I./Media
CXXFLAGS  	= -Wl,-q -O2 -std=c++11 -I./Nogg -I./Media
ASFLAGS 	= $(CFLAGS)

all: $(TARGET).velf

%.velf: %.elf
	$(PREFIX)-strip -g $<
	vita-elf-create $< $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf $(TARGET).velf $(TARGET).elf $(OBJS)
