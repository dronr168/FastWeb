#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "../HTTP/HTTP.h"
#include <iostream>

SSL_CTX* create_context()
{
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    method = TLS_server_method();
    ctx = SSL_CTX_new(method);
    if (ctx == NULL) {
        perror("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    return ctx;
}

void configure_server_context(SSL_CTX *ctx)
{
    /*установка ключа и сертификата*/
    if (SSL_CTX_use_certificate_chain_file(ctx, "cert.pem") <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    if (SSL_CTX_use_PrivateKey_file(ctx, "key.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
}

void openssl(int sock, int size){
	SSL_CTX *ssl_ctx = NULL;
	SSL *ssl = NULL;
	ssl_ctx = create_context();
	configure_server_context(ssl_ctx);
	ssl = SSL_new(ssl_ctx);
	SSL_set_fd(ssl, sock);
        char *i_buf = new char[size];
	int size_fakt;
        if (SSL_accept(ssl) <= 0) {
		ERR_print_errors_fp(stderr);
		SSL_shutdown(ssl);
		SSL_free(ssl);
		close(sock);
		delete[] i_buf;
		return;
        }else{
                if ((size_fakt = SSL_read(ssl, i_buf, size)) <= 0) {
			ERR_print_errors_fp(stderr);
			if (ssl != NULL) {
				SSL_shutdown(ssl);
				SSL_free(ssl);
			}
			close(sock);
			delete[] i_buf; 
			return;
                }
		i_buf[size_fakt] = '\0';
        	NetHTTP client(i_buf, size_fakt), *q;
        	q = &client;
        	q->grap();//читаем файл
        	q->ClientSend();//отправляем ответ
		if (SSL_write(ssl, q->o_buf, q->size_fakt) <= 0) {
			ERR_print_errors_fp(stderr);
			if (ssl != NULL) {
				SSL_shutdown(ssl);
				SSL_free(ssl);
			}
			close(sock);
			delete[] i_buf; 
			return;
                }
	}
	if (ssl != NULL) {
        	SSL_shutdown(ssl);
        	SSL_free(ssl);
	}
	SSL_CTX_free(ssl_ctx);
        close(sock);
        delete[] i_buf;
}

