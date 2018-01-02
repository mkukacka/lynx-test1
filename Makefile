
include Makefile_lynxcc65.mk

target = game.lnx
objects = lynx-160-102-16.o lynx-stdjoy.o \
	robot.o \
	game.o

robot.o: robot.bmp
	$(SPRPCK) -t6 -p2 -a004003 robot.bmp
	$(ECHO) .global _robot > $*.s
	$(ECHO) .segment \"$(RODATA_SEGMENT)\" >> $*.s
	$(ECHO) _robot: .incbin \"robot.spr\" >> $*.s
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