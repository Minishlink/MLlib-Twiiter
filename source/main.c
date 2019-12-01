/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

main.c

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#include <MLlib.h>

#include "common.h"

int main(int argc, char **argv) 
{	ML_Init();
	//ML_SplashScreen();
	
	init();	
	//compo();
	home();
	    	
	return 0;
}

void compo()
{	
	ML_DrawSprite(BG_COMPO);
	ML_Refresh();
	
	sleep(5);
		
	ML_Refresh();
}

void init()
{
	ML_InitFAT();
	
	ML_LoadSpriteFromBuffer(BG_COMPO, compo_png, 0, 0);
	ML_LoadSpriteFromBuffer(FONT, font_png, 0, 0);
	ML_InitTile(FONT, 8, 8);
	ML_LoadSpriteFromBuffer(BG_HOME, Home_png, 0, 0);
}

