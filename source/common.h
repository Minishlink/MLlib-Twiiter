/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

common.h

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#ifndef _COMMON_H
#define _COMMON_H

#include <MLlib.h>
#include <mxml.h>
#include "main.h"
#include "wifi.h"
#include "menu.h"
#include "twitter.h"

#include "font_png.h"
#include "compo_png.h"
#include "Home_png.h"

#define TIMELINE_SIZE 75000

enum { 
	FONT = 0,
	BG_COMPO,
	BG_HOME
};

extern void die(char *msg);

s32 main_server;
char auth[100];
char lastid[30];
char timeline[TIMELINE_SIZE];

#endif

