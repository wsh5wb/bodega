#CPP = clang++
#C = clang
CPP = g++-8

### 32 bit Windows

#LDFLAGS = -LC:\SDL2-2.0.8\i686-w64-mingw32\lib \
-LC:\SDL2_ttf-2.0.14\i686-w64-mingw32\lib \
-LC:\SDL2_image-2.0.3\i686-w64-mingw32\lib \
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf \
-mwindows -m32 -march=i686
#CFLAGS = -IC:\SDL2-2.0.8\i686-w64-mingw32\include \
-IC:\SDL2-2.0.8\i686-w64-mingw32\include\SDL2 \
-IC:\SDL2_ttf-2.0.14\i686-w64-mingw32\include \
-IC:\SDL2_image-2.0.3\i686-w64-mingw32\include \
-Wall -c -std=c89 -m32 -march=i686
#BIN1 = kiss_example1.exe
#BIN2 = kiss_example2.exe

### 64 bit Windows

#LDFLAGS = -LC:\SDL2-2.0.8\x86_64-w64-mingw32\lib \
-LC:\SDL2_ttf-2.0.14\x86_64-w64-mingw32\lib \
-LC:\SDL2_image-2.0.3\x86_64-w64-mingw32\lib \
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf \
-mwindows
#CFLAGS = -IC:\SDL2-2.0.8\x86_64-w64-mingw32\include \
-IC:\SDL2-2.0.8\x86_64-w64-mingw32\include\SDL2 \
-IC:\SDL2_ttf-2.0.14\x86_64-w64-mingw32\include \
-IC:\SDL2_image-2.0.3\x86_64-w64-mingw32\include \
-Wall -c -std=c89
#BIN1 = kiss_example1.exe
#BIN2 = kiss_example2.exe

### macOS

#LDFLAGS = -framework SDL2 -framework SDL2_ttf -framework SDL2_image
#CFLAGS = -I/Library/Frameworks/SDL2.framework/Headers \
-I/Library/Frameworks/SDL2_ttf.framework/Headers \
-I/Library/Frameworks/SDL2_image.framework/Headers \
-Wall -c -std=c89
#BIN1 = kiss_example1
#BIN2 = kiss_example2

### Linux

LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
CFLAGS = -Wall -c -std=c89
CPPFLAGS ?= -lstdc++fs
CPPSRCS := $(shell find ./engine -name *.cpp)
CSRCS := $(shell find . -name '*.c')
SRCS := $(CPPSRCS:%=$(CSRCS))
OBJS := $(SRCS:%=%.o)

run: $(OBJS)
	$(CPP) $(OBJS) $(LDFLAGS) -o $@

kiss_draw.o: kiss_draw.c kiss_sdl.h
kiss_example1.o: kiss_example1.c kiss_sdl.h
kiss_general.o: kiss_general.c kiss_sdl.h
kiss_posix.o: kiss_posix.c kiss_sdl.h
kiss_widgets.o: kiss_widgets.c kiss_sdl.h

clean:
	rm *.o && rm $(BIN1)
#	del *.o
#	del $(BIN1)

