/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

menu.h

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#include "common.h"

void home()
{
	bool exit = 0;
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { exit = true; } 
		else if(Wiimote[0].Newpress.One) test();
		else if(Wiimote[0].Newpress.Two) menu_timeline();
		
		ML_DrawSprite(BG_HOME);
		ML_SetSpriteScale(FONT, 1.5, 1.5);
		ML_SimpleText(FONT, 25, 150, "Press One to send a tweet \"Twiiter Test ! \\o/\"");
		ML_SimpleText(FONT, 19, 300, "Press Two to see the lastest tweet of your timeline");
		
		if(exit)
			if(ML_FadeOut()) ML_Exit();
			
		ML_Refresh();
	}		
}

void menu_timeline()
{
	connect2Twitter();
	authenticate();
	int http_response = getTwitts(timeline, TIMELINE_SIZE, 3);
	disconnect();
	if(http_response == 200) saveTweets();
	loadTweets();	
	drawTimeline();
}

void drawTimeline()
{
	bool exit = 0;
	
	while(1)
	{
		if(Wiimote[0].Newpress.Home) { exit = true; } 
		else if(Wiimote[0].Newpress.A) home();
		
		ML_DrawSprite(BG_HOME);
		ML_SetSpriteScale(FONT, 1.5, 1.5);
		//ML_Text(FONT, 20, 20, "Name: %s     |     Username: %s\nTweet: %s", &Tweet[0].name, &Tweet[0].screen_name, &Tweet[0].text);
		ML_Text(FONT, 20, 20, "Tweet: %s", &Tweet[0].text);
		
		if(exit)
			if(ML_FadeOut()) ML_Exit();
			
		ML_Refresh();
	}	
}

void test()
{
	bool continuer = 1;
	
	connect2Twitter();
	authenticate();
	
	char *buffer = urlencode("Twiiter Test ! \\o/");	
	char buffer2[513];	
    sprintf(buffer2, "POST /statuses/update.xml HTTP/1.1\r\nAuthorization: Basic %s\r\nUser-Agent: Twiiter (Nintendo Wii)\r\nHost: twitter.com\r\nAccept: */*\r\nContent-Length: %d\r\n\r\nsource=twiiter&status=%s",auth,strlen(buffer)+7+17,buffer);
   
   	while(continuer)
	{
		if(Wiimote[0].Newpress.A) { continuer = 0; } 
		else if(Wiimote[0].Held.Home) { ML_Exit(); } 
		
		ML_SimpleText(FONT, 0, 40, "Buffer intialized ! (3)");
		
		ML_Refresh();
	}
	continuer = 1;
   
    //if(&main_server != NULL) { net_send(main_server,buffer2,strlen(buffer2),0); }
    //else { die("MAIN_SERVER NULL !"); }
    send_message(main_server, buffer2);
	
	while(continuer)
	{
		if(Wiimote[0].Newpress.A) { continuer = 0; } 
		else if(Wiimote[0].Held.Home) { ML_Exit(); } 
		
		ML_SimpleText(FONT, 0, 40, "SENT ! (I think)");
		
		ML_Refresh();
	}
	continuer = 1;
	
	disconnect();
}

