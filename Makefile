
TARGET = ps1pong
TYPE = ps-exe

SRCS = third_party/nugget/common/crt0/crt0.s \
main.c \
vec2.c \
gfx.c \
music_player.c \
sfx.c \
controller.c \
pong.c \
paddle.c \
ball.c \
third_party/nugget/modplayer/modplayer.c \
music.o \
sounds/sound0.o \
sounds/sound1.o \
sounds/sound2.o \

CPPFLAGS += -msoft-float
CPPFLAGS += -Ithird_party/psyq-iwyu/include
LDFLAGS += -Lthird_party/psyq/lib
LDFLAGS += -Wl,--start-group
LDFLAGS += -lapi
LDFLAGS += -lc
LDFLAGS += -lc2
LDFLAGS += -lcard
LDFLAGS += -lcd
LDFLAGS += -lcomb
LDFLAGS += -lds
LDFLAGS += -letc
LDFLAGS += -lgpu
LDFLAGS += -lgs
LDFLAGS += -lgte
LDFLAGS += -lgun
LDFLAGS += -lhmd
LDFLAGS += -lmath
LDFLAGS += -lmcrd
LDFLAGS += -lmcx
LDFLAGS += -lpad
LDFLAGS += -lpress
LDFLAGS += -lsio
LDFLAGS += -lsnd
LDFLAGS += -lspu
LDFLAGS += -ltap
LDFLAGS += -Wl,--end-group

%.o: %.hit
	$(PREFIX)-objcopy -I binary --set-section-alignment .data=4 --rename-section .data=.rodata,alloc,load,readonly,data,contents -O $(FORMAT) -B mips $< $@

%.o: %.vag
	$(PREFIX)-objcopy -I binary --set-section-alignment .data=4 --rename-section .data=.rodata,alloc,load,readonly,data,contents -O $(FORMAT) -B mips $< $@

include third_party/nugget/common.mk
