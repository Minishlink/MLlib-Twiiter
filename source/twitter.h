/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

twitter.h

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#ifndef _TWITTER_H
#define _TWITTER_H

typedef struct {
	const char *text;
	const char *name;
	const char *screen_name;
} s_tweets;

s_tweets Tweet[100];

extern int getTwitts(char *retbuffer, int size, int numtweets);
extern void saveTweets();
extern void loadTweets();
extern void connect2Twitter();
extern void authenticate();

#endif
