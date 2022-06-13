#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "HTTP/HTTP.h"

void noTLS(int sock, int size){
        char *i_buf = new char[size];
        int size_fakt = recv(sock, i_buf, size, 0);
        i_buf[size_fakt] = '\0';
        NetHTTP client(i_buf, size_fakt), *q;
        q = &client;
        q->grap();//reading required files
        q->ClientSend();//buffer formation
        send(sock, q->o_buf, q->size_fakt, 0);
        close(sock);
        delete[] i_buf;
}
