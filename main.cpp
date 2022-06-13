#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "HTTP/HTTP.h"
#include <pthread.h>
#include "noTLS.h"
#include "openssl/openssl.h"

bool checkconfig = 0;
char ***typeX;
void *potokssl(void *sock);
void *potoknossl(void *sock);
int port;
bool check_ssl;
int sizetype = 0;

int main(int argc, char *argv[]){
	if(argc > 2){
		if((argv[1][0]=='-')&&(argv[1][1]=='c')){
			checkconfig = 1;
			std::ifstream config(argv[2]);
			if(!config){
				std::cout << "./fastweb -c <config file>\n";
				return 0;
			}
			char ti;
			for(int i = 0; ti!='{'; i++)
				config.get(ti);
			char Port[6];
			int m;
			for(m=0;ti!='}';m++){
				config.get(ti);
				if(ti!='}')
					Port[m]=ti;
			}
			Port[m+1]=0;
			if(!(port = int (atoi(Port)))){
				std::cout << "error config1\n";
				return 0;
			}
			for(int i = 0; ti!='{'; i++)
				config.get(ti);
			config.get(ti);
			if(ti == 's'){
				check_ssl = 1;
			}else if(ti == 'n'){
				check_ssl = 0;
			}else{
				std::cout << "error config2\n";
				return 0;
			}
			for(int i=0;ti!='{'; i++)
				config.get(ti);
			int pos = config.tellg();
			for(int i=0;ti!='}';i++){
				config.get(ti);
				if(ti==',')
					sizetype++;
			}
			sizetype++;
			config.seekg(pos);
			typeX = new char**[sizetype];
			for(int w=0; w<sizetype; w++){
				typeX[w] = new char*[2];
				for(int h=0; h<2; h++)
					typeX[w][h] = new char[64];
			}
			for(int u; u<sizetype; u++){
				int p;
				for(p=0;ti!=',';p++){
					config.get(ti);
					if(!((ti=',')||(ti='{')))
						typeX[u][0][p] = ti;
				}
				typeX[u][0][p] = 0;
				for(p=0;ti!=';';p++){
					config.get(ti);
					if(!((ti=';')||(ti='}')))
						typeX[u][1][p] = ti;
				}
				typeX[u][1][p] = 0;
			}
		}else{
			checkconfig = 0;
			if(!(port = int (atoi(argv[1])))){
				std::cout << "./fastWEb <PORT> <ssl/nossl>\n./fastWeb -c <config file>" << '\n';
				return 0;
			}
			char *ch_ssl = argv[2];
			if((ch_ssl[0] == 's')&&(ch_ssl[1] == 's')&&(ch_ssl[2] == 'l')){
				check_ssl = 1;
			}else if((ch_ssl[0] == 'n')&&(ch_ssl[1] == 'o')&&(ch_ssl[2] == 's')&&(ch_ssl[3] == 's')&&(ch_ssl[4] == 'l')){
				check_ssl = 0;
			}else{
				std::cout << "./fastWEb <PORT> <ssl/nossl>\n./fastWeb -c <config file>" << '\n';
                        	return 0;
			}
		}
	}else{
		std::cout << "./fastWEb <PORT> <ssl/nossl>\n./fastWeb -c <config file>" << '\n';
		return 0;
	}
        struct sockaddr_in addr;
        int listener = socket(AF_INET, SOCK_STREAM, 0);
        if(listener < 0){
                perror("socket");
                exit(1);
        }
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        if((bind(listener, (struct sockaddr *)&addr, sizeof(addr))) < 0){
                perror("bind");
                exit(2);
        }
        listen(listener, 1);
        while(1){
                int sock = accept(listener, NULL, NULL);
                if(sock < 0){
                        perror("accept");
                        exit(3);
                }else{
			pthread_t tid;
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			if(check_ssl){
				pthread_create(&tid, &attr, potokssl, (int *)sock);
			}else{
				pthread_create(&tid, &attr, potoknossl, (int *)sock);
			}
		}
        }
	close(listener);
        for(int i = 0; i<sizetype; i++){
                for(int y=0; y<2;y++)
                        delete[] typeX[i][y];
                delete[] typeX[i];
        }
        delete[] typeX;
return 0;
}

void *potokssl(void *sock){
	int sk = (int &)sock;
	openssl(sk, 2048);
	pthread_exit(0);
}

void *potoknossl(void *sock){
        int sk = (int &)sock;
        noTLS(sk, 2048);
        pthread_exit(0);
}
