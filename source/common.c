/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

common.c

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#include "common.h"

void die(char *msg) 
{
	bool continuer = 1;
	
	ML_SetSpriteScale(FONT, 2.5, 2.5);
	
	while(continuer)
	{
		if(Wiimote[0].Newpress.A) { continuer = 0; } 
		
		ML_Text(FONT, 10, 40, "ERROR : %s", msg);
		ML_SimpleText(FONT, 10, 100, "Press A to return to the loader.");
		
		ML_Refresh();
	}
	exit(0);
}

