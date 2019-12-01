/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

twitter.c

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#include "common.h"

int getTwitts(char *retbuffer, int size, int numtweets)
{
	char buffer[513], buffer2[513];
	int response_int = 200;

	// Send query
	if(strlen(lastid)==0) sprintf(buffer, "GET /statuses/friends_timeline.xml?count=%d HTTP/1.1\r\nAuthorization: Basic %s\r\nUser-Agent: Twiiter (Nintendo Wii)\r\nHost: twitter.com\r\nAccept: */*\r\n\r\n", numtweets, auth);
	else sprintf(buffer, "GET /statuses/friends_timeline.xml?since_id=%s&count=%d HTTP/1.1\r\nAuthorization: Basic %s\r\nUser-Agent: Twiiter (Nintendo Wii)\r\nHost: twitter.com\r\nAccept: */*\r\n\r\n", lastid, numtweets, auth);
	net_send(main_server, buffer, strlen(buffer), 0);

	// Receive response
	int br = 1;
	do
	{
		br = net_recv(main_server, buffer2, 512, 0);
		if(br<512) buffer2[br]='\0';
		strcat(retbuffer, buffer2);
	} while(br > 0);

	// Get HTTP Status        
	char *r = strstr(retbuffer,"Status:");
	if(r!=NULL)
	{
		r+=8;
		r[3]='\0';
		response_int = atoi(r);
		r[3]=' ';
	}
	else
	{
		response_int = -2;
	}


	// Jump headers. Instead of copy them over the place, we just fill it with blanks, it's WAY faster
	char *p2 = strstr(retbuffer,"<?xml");
	int i;
	for(i=0; i<(p2-retbuffer); i++)
	{
		retbuffer[i]=' ';
	}

	return response_int;
}

void saveTweets()
{
	FILE *f = fopen("twiiter_timeline.xml", "wb");
	if(f!=NULL)
	{
		fputs("<?xml version=\"1.0\"?>", f);
		fwrite(timeline, strlen(timeline), 1, f);
		if(f) fclose(f);
	}
	
	bool continuer = 1;
	while(continuer)
	{
		if(Wiimote[0].Newpress.A) { continuer = 0; } 
		else if(Wiimote[0].Held.Home) { ML_Exit(); } 
		
		ML_SimpleText(FONT, 0, 40, "(3) Wrote the timeline !");
		
		ML_Refresh();
	}
}

void loadTweets()
{
	FILE *fp;
	mxml_node_t *tree;
	mxml_node_t *data;
	//mxml_node_t *user;

	// Load XML file
	fp = fopen("twiiter_timeline.xml", "r");
	if(fp==NULL) return;
	
	tree = mxmlLoadFile(NULL, fp, MXML_NO_CALLBACK);
	fclose(fp);

	data = mxmlFindElement(tree, tree, "status", NULL, NULL, MXML_DESCEND);
	if(data->child->next->next->type == MXML_TEXT)
		Tweet[0].text = data->child->next->next->value.text.string;
	else if(data->child->next->next->type == MXML_OPAQUE) 
		Tweet[0].text = data->child->next->next->value.opaque;
	else Tweet[0].text = "lol";
	
 	//Tweet[0].name = user->child->value.text.string;
	//Tweet[0].screen_name = user->child->value.text.string;

	//mxmlDelete(user);
	mxmlDelete(data);
	mxmlDelete(tree);
	
	bool continuer = 1;
	while(continuer)
	{
		if(Wiimote[0].Newpress.A) { continuer = 0; } 
		else if(Wiimote[0].Held.Home) { ML_Exit(); } 
		
		ML_SimpleText(FONT, 0, 40, "(4) Parsed the file !");
		
		ML_Refresh();
	}
}

void connect2Twitter()
{
	bool continuer = 1; 
	
	ML_SetSpriteScale(FONT, 1.5, 1.5);
	ML_Refresh();
	
	verify_network();
    
    ML_Refresh();
    ML_SimpleText(FONT, 0, 40, "Attempting to connect to server...");
	main_server = server_connect();
	ML_SimpleText(FONT, 0, 40, "Connection established.");
	
	while(continuer)
	{
		if(Wiimote[0].Newpress.A) { continuer = 0; } 
		else if(Wiimote[0].Held.Home) { ML_Exit(); } 
		
		ML_SimpleText(FONT, 0, 40, "(1) Connected to Twitter server !");
		
		ML_Refresh();
	}
}

void authenticate()
{
	bool continuer = 1;

	char username[50] = "";
	char password[50] = "";
	char tmpstr[100];

	strncpy(tmpstr,username,49);
	strcat(tmpstr,":");
	strncat(tmpstr,password,49);

	base64_encode(auth,tmpstr,strlen(tmpstr));
	
	while(continuer)
	{
		if(Wiimote[0].Newpress.A) { continuer = 0; } 
		else if(Wiimote[0].Held.Home) { ML_Exit(); } 
		
		ML_SimpleText(FONT, 0, 40, "(2) Authenticated !");
		
		ML_Refresh();
	}
}



