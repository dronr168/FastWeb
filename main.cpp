#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "HTTP/HTTP.h"
#include <pthread.h>
#include "noTLS.h"
#include "openssl/openssl.h"

#define size 104857700 //maximum transfer file size 100 MB

void *potokssl(void *sock);
void *potoknossl(void *sock);

int port;
bool check_ssl;

int main(int argc, char *argv[]){
	if(argc > 2){
		if(!(port = int (atoi(argv[1])))){
			std::cout << "./fastWEb <PORT> <ssl/nossl>" << '\n';
			return 0;
		}
		char *ch_ssl = argv[2];
		if((ch_ssl[0] == 's')&&(ch_ssl[1] == 's')&&(ch_ssl[2] == 'l')){
			check_ssl = 1;
		}else if((ch_ssl[0] == 'n')&&(ch_ssl[1] == 'o')&&(ch_ssl[2] == 's')&&(ch_ssl[3] == 's')&&(ch_ssl[4] == 'l')){
			check_ssl = 0;
		}else{
			std::cout << "./fastWEb <PORT> <ssl/nossl>" << '\n';
                        return 0;
		}
	}else{
		std::cout << "./fastWEb <PORT> <ssl/nossl>" << '\n';
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
        if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0){
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
return 0;
}

void *potokssl(void *sock){
	int sk = (int &)sock;
	openssl(sk);
	pthread_exit(0);
}

void *potoknossl(void *sock){
        int sk = (int &)sock;
        noTLS(sk);
        pthread_exit(0);
}
