/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

wifi.h

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#ifndef _WIFI_H
#define _WIFI_H

#define IP_ADDRESS "128.121.146.100" // www.twitter.com
#define SOCKET_PORT 80
#define MAXLINE 76
#define NET_BUFFER_SIZE 1024

extern s32 initialise_network();
extern void verify_network();
extern s32 send_message(s32 server, char *msg);
extern s32 server_connect();
extern char* urlencode(char *s);
extern char* base64_encode(char *dst, const char *src, unsigned int len);
extern void disconnect();

typedef s32 (*transferrer_type)(s32 s, void *mem, s32 len);
extern s32 transfer_exact(s32 s, char *buf, s32 length, transferrer_type transferrer);
extern s32 write_exact(s32 s, char *buf, s32 length);

#endif
