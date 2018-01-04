
include Makefile_lynxcc65.mk

target = game.lnx
objects = lynx-160-102-16.o lynx-stdjoy.o \
	robot.o robot1.o \
	game.o

robot.o: robot.bmp
	$(SPRPCK) -t6 -p2 -a004003 robot.bmp
	$(ECHO) .global _robot > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _robot: .incbin \"robot.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

#robot1.o: robot1.pcx
#	$(SP) -r $< -c lynx-sprite,mode=literal,ax=0,ay=0,edge=0 -w $*.c,ident=$*
#	$(CC) $(SEGMENTS) $(CFLAGS) $*.c
#	$(AS) -o $@ $(AFLAGS) $(*).s
#	$(RM) $*.c

robot1.o: robot1.bmp
	$(SPRPCK) -t6 -p2 -a004003 $<
	$(ECHO) .global _robot1 > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _robot1: .incbin \"robot1.spr\" >> $*.s
	$(AS) -t lynx -o $@ $(AFLAGS) $*.s

all: $(target)

$(target) : $(objects)
	$(CL) -t $(SYS) -o $@ $(objects) lynx.lib 

clean:
	$(RM) *.tgi
	$(RM) *.s
	$(RM) *.joy
	$(RM) *.o
	$(RM) *.pal
	$(RM) *.spr
	$(RM) *.lnx