
include Makefile_lynxcc65.mk

target = game.lnx
objects = lynx-160-102-16.o lynx-stdjoy.o game.o

all: $(target)

$(target) : $(objects)
	$(CL) -t $(SYS) -o $@ $(objects) lynx.lib 

clean:
	$(RM) *.tgi
	$(RM) *.s
	$(RM) *.joy
	$(RM) *.o
	$(RM) *.lnx