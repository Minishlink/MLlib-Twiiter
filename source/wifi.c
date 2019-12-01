/*			-==========================-
			|		   Twiiter    	   |
			-==========================-

wifi.c

Author : Minishlink
Created : May 2009
Latest modified : 30/05/09 (Day/Month/Year)

Twitter : http://twitter.com/Minishlink
Website : http://minishlink.dev-fr.org and http://louislagrange.free.fr
MLlib Website : http://louislagrange.free.fr/MLlib 							*/

#include "common.h"

// ---- Thanks joedj (FTPii) and acdrtux (DSTwitter)

s32 initialise_network() 
{
	s32 result;
	while ((result = net_init()) == -EAGAIN);
	return result;
}

void verify_network()
{
	ML_Text(FONT, 0, 40, "Waiting for network to initialise...");
	ML_Refresh();
    if (initialise_network() >= 0) {
        char myIP[16];
        if (if_config(myIP, NULL, NULL, true) < 0) exit(0);
        ML_Text(FONT, 0, 40, "Network initialised.");
    } else exit(0);
}

// Write our message to the server
s32 send_message(s32 server, char *msg)
{
	u32 msglen = strlen(msg);
	char msgbuf[msglen + 1];
	if (msgbuf == NULL) return -ENOMEM;
	sprintf(msgbuf, "%s", msg);
	printf("Sent message: %s", msgbuf);
	return write_exact(server, msgbuf, msglen);
}


char* urlencode(char *s)
{
	char *rs = (char*) malloc (sizeof(char)*240);
	char hex[] = "0123456789abcdef";
	unsigned int i,j;
	char c;

	for(i=0,j=0;i<strlen(s);i++,j++)
	{
		c = s[i];
		if( ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') )
		{
			rs[j] = c;
		} 
		else 
		{
			switch(c)
			{
				// enhe cedilla ENHE CEDILLA
				case '\347': case '\361': case '\321': case '\307':
				// tildes normales
				case '\301': case '\311': case '\315': case '\323': case '\332': case '\341': case '\351': case '\355': case '\363': case '\372':
				// tildes al reves
				case '\300': case '\310': case '\314': case '\322': case '\331': case '\340': case '\350': case '\354': case '\362': case '\371':
				// tildes... de las otras xD
				case '\304': case '\313': case '\317': case '\326': case '\334': case '\344': case '\353': case '\357': case '\366': case '\374':
				rs[j++] = '\303'; rs[j] = c-64; break;
				// other cases
				default: rs[j++] = '%';  rs[j++] = hex[c >> 4]; rs[j] = hex[c & 15];
			}
		}
	}
	rs[j]='\0';
	return rs;
}

s32 server_connect()
{
	struct sockaddr_in connect_addr;

	s32 server = net_socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (server < 0) die("Error creating socket, exiting");

	memset(&connect_addr, 0, sizeof(connect_addr));
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_port = SOCKET_PORT;
	connect_addr.sin_addr.s_addr= inet_addr(IP_ADDRESS);

	if (net_connect(server, (struct sockaddr*)&connect_addr, sizeof(connect_addr)) == -1) 
	{
		net_close(server);
		die("Failed to connect to the remote server.\n");
	}

	return server;
}

void disconnect()
{
	net_close(main_server);
}

char* base64_encode(char *dst, const char *src, unsigned int len)
{
	char base64_table[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz""0123456789+/"};
	int x, y = 0, i, flag = 0, m = 0;
	int n = 3;
	char triple[3], quad[4];
	static char encode[1024]={0};

	for(x = 0; x < len; x = x + 3)
	{
		if((len - x) / 3 == 0) n = (len - x) % 3;

		for(i=0; i < 3; i++) triple[i] = '0';
		for(i=0; i < n; i++) triple[i] = src[x + i];
		quad[0] = base64_table[(triple[0] & 0xFC) >> 2]; // FC = 11111100
		quad[1] = base64_table[((triple[0] & 0x03) << 4) | ((triple[1] & 0xF0) >> 4)]; // 03 = 11
		quad[2] = base64_table[((triple[1] & 0x0F) << 2) | ((triple[2] & 0xC0) >> 6)]; // 0F = 1111, C0=11110
		quad[3] = base64_table[triple[2] & 0x3F]; // 3F = 111111
		if(n < 3) quad[3] = '=';
		if(n < 2) quad[2] = '=';
		for(i=0; i < 4; i++) dst[y + i] = quad[i];
		y = y + 4;
		m = m + 4;
		if((m != 0)&&((m % MAXLINE) == 0))
		{
			dst[y] = '\r';
			dst[y+1] = '\n';
			flag++;
			y += 2;
			m = 0;
		}
	}
	dst[y] = '\0';
	sprintf(encode,dst);
	return encode;
} 

s32 transfer_exact(s32 s, char *buf, s32 length, transferrer_type transferrer) 
{
	s32 bytes_transferred = 0;
	s32 remaining = length;
	
	while (remaining) 
	{
		if ((bytes_transferred = transferrer(s, buf, remaining > NET_BUFFER_SIZE ? NET_BUFFER_SIZE : remaining)) > 0) 
		{
			remaining -= bytes_transferred;
			buf += bytes_transferred;
		} 
		else if (bytes_transferred < 0) 
		{
			return bytes_transferred;
		} 
		else 
		{
			return -ENODATA;
		}
	}
	return 0;
}

s32 write_exact(s32 s, char *buf, s32 length) 
{
	return transfer_exact(s, buf, length, (transferrer_type)net_write);
}

