#include <iostream>
#include "../html/html.h"
#include "../robots/spisok.h"

#define size 104857700 //максимальный размер предаваемого файла 100 MB

class NetHTTP : public robots{
	char *i_buf;
	char path[31];
	char type[5];
public:
	int sock;
	int size_fakt;
        char *body = new char[size-100];
        char *o_buf = new char[size];
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
	//initializing an array containing types
	char types[32][2][32] = {
		{"js", "application/x-javascript"},
		{"gif", "image/gif"},
		{"png", "image/png"},
		{"jpg", "image/jpg"},
		{"css", "text/css"},
		{"mp3", "mpeg/mp3"},
		{"wav", "audio/wav"},
		{"mp4", "mpeg/mp4"},
		{"avi", "video/avi"}
	};

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
	for(sizeT=0; types[sizeT][0][0]; sizeT++);  //calculate the size of the list of types
	sizeT++;
	
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
		p = BodyHtml("index.html", o_buf, "text/html");
		if(p==0){
			char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
			while(err[p]){
				o_buf[p] = err[p];
				p++;
			}
			o_buf[p] = '\0';
			p++;
		}
	}else if(path[p-3]=='i' && path[p-2]=='c' && path[p-1]=='o'){
                p = BodyHtml((path+1), o_buf, "image/x-icon");
                if(p==0){
                        char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
                        while(err[p]){
                                o_buf[p] = err[p];
                                p++;
                        }
                        o_buf[p] = '\0';
                        p++;
                }
	}else if(resultPass){
                p = BodyHtml((path+1), o_buf, TypeS);
		if(p==0){
                        char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
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
		p = 0;
                char err[] = "HTTP/1.1 404 Not Found\r\n\r\n<html>404</html>\r\n";
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
	return 0;
}
