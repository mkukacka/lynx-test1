#include <stdlib.h>
#include <6502.h>
#include <lynx.h>
#include <tgi.h>
#include <conio.h>
#include <peekpoke.h>
#include <joystick.h>

extern char lynxtgi[];
extern char lynxjoy[];
extern char robot[];
extern char robot1[];

extern char pal[];

typedef struct {
	unsigned char b0;
	unsigned char b1;
	unsigned char b2;
	void *next;
	void *bitmap;
	int posx, posy, sizex, sizey;
	int stretch;
	int tilt;
	char palette[8];
} sprite_t;

sprite_t robotsprite = 
{
	BPP_4 | TYPE_NORMAL, 		// color depth and sprite type
	REHVST, 					// sprite structure type
	0x01,						// collision depository number
	0,							// next chained sprite address
	&robot1,						// bitmap data
	20, 50, 					// initial sprite position
	0x0100, 0x0100,				// size changes - 0x0100 is no change
	0x0000, 					// stretch 
	0x0000,						// tilt
	{ 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef }	// pallete indexes for each pen
};

int xpos = 30, ypos = 40;

void show_screen()
{
	char text[20];
	int tmp;

	// Clear current screen
	tgi_clear();
	
	/*
	tgi_setcolor(COLOR_WHITE);
	tgi_outtextxy(xpos, ypos, "Hello world!");
	
	itoa(xpos, text, 10);
	tgi_outtextxy(5, 5, text);
	*/

	robotsprite.b0 = BPP_4 | TYPE_NORMAL;
	robotsprite.palette[1] = 0x23;

	robotsprite.posx = xpos;
	robotsprite.posy = ypos;
	tgi_sprite(&robotsprite);

	robotsprite.b0 = BPP_4 | TYPE_NORMAL | VFLIP;
	robotsprite.posx = xpos + 10;
	tgi_sprite(&robotsprite);

	robotsprite.b0 = BPP_4 | TYPE_NORMAL | HFLIP;
	robotsprite.posx = xpos - 10;
	robotsprite.palette[1] = 0x32;
	tgi_sprite(&robotsprite);

	tgi_updatedisplay();
}

void initialize()
{
	tgi_install(&lynxtgi);
	joy_install(&lynxjoy);
	tgi_init();
	CLI();
	
	while (tgi_busy()) 
	{ 
	};

	tgi_setbgcolor(COLOR_BLACK); 
	tgi_setpalette(tgi_getdefpalette());
	
	tgi_setcolor(COLOR_BLACK);
	tgi_clear();
}

void main(void) 
{
	unsigned char joy;
	unsigned char waitForRelease = 0;
	
	initialize();

	while (1)
	{
		if (kbhit()) 
		{
			switch (cgetc()) 
			{
				case 'F':
					tgi_flip();
					break;

				default:
					break;
			}
		}

		joy = joy_read(JOY_1);
		if(JOY_BTN_DOWN(joy)){
			ypos += 1;
		}
		if(JOY_BTN_UP(joy)){
			ypos -= 1;
		}
		if(JOY_BTN_LEFT(joy)){
			xpos -= 1;
		}
		if(JOY_BTN_RIGHT(joy)){
			xpos += 1;
		}
		/*
		if (!joy) waitForRelease = 0;
		if (waitForRelease != 0) continue;

		if (JOY_BTN_RIGHT(joy))
		{
			waitForRelease = 1;
		}

		if (JOY_BTN_LEFT(joy))
		{
			waitForRelease = 1;
		}
		*/

		// if (!tgi_busy())
		// {
		// 	show_screen();
		// }
		show_screen();
		while(tgi_busy()){ }
	};
}