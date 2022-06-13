#include <iostream>
#include <fstream>
#include "../html/html.h"
#include "../robots/spisok.h"
#include "check.h"
#include "strcp.h"
#include "../main.h"

using namespace std;

class NetHTTP : public robots{
	int size = 0;
	char *i_buf;
	char path[31];
	char type[5];
public:
	int sock;
	int size_fakt;
        char *body = new char[2048-100];
        char *o_buf;
	NetHTTP(char *opop, int faktS);
	~NetHTTP();
	int ClientSend();
};

NetHTTP::NetHTTP(char *opop, int faktS){
	size_fakt = faktS;
	i_buf = opop;
}

NetHTTP::~NetHTTP(){
	delete[] body;
	delete[] o_buf;
}

int NetHTTP::ClientSend(){
	char ***types;//initializing an array containing types
        if(checkconfig){
                types = typeX;
        }else{
                types = new char**[32]; 
                for(int w=0; w<32; w++){ 
                        types[w] = new char*[2];
                        for(int h=0;h<2;h++)
                                types[w][h] = new char[64];
                }
                strcp(types[0][0], "js", 2);
                strcp(types[0][1], "application/x-javascript", 24);
                strcp(types[1][0], "gif", 3);
                strcp(types[1][1], "image/gif", 9);
                strcp(types[2][0], "png", 3);
                strcp(types[2][1], "image/png", 9);
                strcp(types[3][0], "jpg", 3);
                strcp(types[3][1], "image/jpg", 9);
                strcp(types[4][0], "css", 3);
                strcp(types[4][1], "text/css", 8);
                strcp(types[5][0], "mp3", 3);
                strcp(types[5][1], "mpeg/mp3", 8);
                strcp(types[6][0],  "wav", 3);
                strcp(types[6][1], "audio/wav", 9);
                strcp(types[7][0], "mp4", 3);
                strcp(types[7][1], "video/mp4", 9);
                strcp(types[8][0], "avi", 3);
                strcp(types[8][1], "video/avi", 9);
        }
	int i = 0;
	int p = 0;
	while(i_buf[i] != ' '){
		type[p] = i_buf[i];
		i++;
		p++;
	}
	type[p] = '\0';
	i++;
	p = 0;
	while(i_buf[i] != ' '){
		path[p] = i_buf[i];
		i++;
		p++;
	}
	path[p] = '\0';
	i++;
	int sizeB=0;
	if(type[0]=='P' && type[1]=='O' && type[2]=='S' && type[3]=='T'){
		bool check = 0;
		while(!check){
			while(i_buf[i]!='\n') i++;
			i+=2;
			if(i_buf[i]=='\n'){
				check = 1;
				i+=2;
			}
		}
		while(i_buf[i]){
			body[sizeB] = i_buf[i];//getting the POST body if present
			i++;
			p++;
		}
		body[sizeB] = '\0';
	}

	int sizeT;
	if(checkconfig)
		sizeT = sizetype;
	else
		sizeT = 32;
	//looking for matching data types
	int CheT=-1;
	for(int i=0; i<sizeT; i++){
		int sT;
		for(sT=0; types[i][0][sT]; sT++);
		sT++;
		bool ErT=0;
		for(int h=0; types[i][0][h] && path[p-sT+h]; h++){
			if(types[i][0][h] != path[p-sT+h]) ErT=1;
		}
		if(!ErT) CheT=i;
	}
	char TypeS[32]; //type string size
	if(CheT != -1){
		for(int i=0; types[CheT][1][i]; i++) TypeS[i] = types[CheT][1][i];
	}

	//checking file extension request
	bool resultPass = 0;
	int coitPass = 0;
	for(int i=0; i<coit; i++){
		bool err = 0;
		for(int r=0; path[r+1]; r++){
			if(spisok[i][r] != path[r+1]) err=1;
		}
		if(err==0) coitPass++;
	}
	if(coitPass >= 1) resultPass = 1;
	//start building a response
	if(path[0]=='/' && (!path[1])){
		size = checksize("index.html");
		if(size!=0){
			o_buf = new char[size+100];
			p = BodyHtml("index.html", o_buf, "text/html");
			size+=100;
		}else{
			p = 0;
		}
		if(p==0){
			char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
			for(p = 0; err[p]; p++);
			o_buf = new char[p];
			size = p;
			p = 0;
			while(err[p]){
				o_buf[p] = err[p];
				p++;
			}
			o_buf[p] = '\0';
			p++;
		}
	}else if(path[p-3]=='i' && path[p-2]=='c' && path[p-1]=='o'){
		size = checksize((path+1));
		if(size!=0){
			o_buf = new char[size+100];
                	p = BodyHtml((path+1), o_buf, "image/x-icon");
			size+=100;
		}else{
			p = 0;
		}
                if(p==0){
                        char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
                        for(p = 0; err[p]; p++);
                        o_buf = new char[p];
			size = p;
                        p = 0;
                        while(err[p]){
                                o_buf[p] = err[p];
                                p++;
                        }
                        o_buf[p] = '\0';
                        p++;
                }
	}else if(resultPass){
                size = checksize((path+1));
                if(size!=0){
                        o_buf = new char[size+100];
                	p = BodyHtml((path+1), o_buf, TypeS);
			size+=100;
                }else{
                        p = 0;
                }
		if(p==0){
                        char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
                        for(p = 0; err[p]; p++);
                        o_buf = new char[p];
			size = p;
                        p = 0;
			while(err[p]){
                                o_buf[p] = err[p];
                                p++;
                        }
                        o_buf[p] = '\0';
			p++;
                }
/*somewhere here you can add support
					for your modules ..*/
	}else{
                char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
                for(p = 0; err[p]; p++); 
                o_buf = new char[p];
		size = p;
                p = 0;
                while(err[p]){
			o_buf[p] = err[p];
			p++;
                }
                o_buf[p] = '\0';
                p++;

	}
	if(p < size)
		size_fakt = p;
	else
		size_fakt = size;
	if(!checkconfig){
                for(int i=0;i<32;i++){
                        for(int y=0;y<2;y++)
                                delete[] types[i][y];
                        delete[] types[i];
                }
                delete[] types;
        }
	return 0;
}
