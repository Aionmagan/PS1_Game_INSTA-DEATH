CC=gcc
CFLAGS	= -Wall -O2
LINKER  = -Xlinker -Ttext -Xlinker 80140000

HEADER  = DATA.H
PROG	= main.exe
OBJS    = main.o  player.o enemy.o particle.o bullet.o \
		Framework/OBJECT.o Framework/PAD.o \
		Framework/RENDER.o Framework/AABB.o \
		Framework/CAMERA.o \

all: $(PROG)

main.exe: $(OBJS)
	$(CC) $(LINKER) $(OBJS) -o $@
#	strip $@

#.c.o:
#	$(CC) $(CFLAGS) -funsigned-char -c $<

psx.exe: $(PROG)
	yarexe DATA.MAK

run: psx.exe
	nopsx psx.exe
clean:
	del $(PROG)
	del *.o
	del psx.exe
	del *.iso
	del *.cue
	del *.bin

