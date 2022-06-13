#include <openssl/ssl.h>
#include <openssl/err.h>

SSL_CTX* create_context();
void configure_server_context(SSL_CTX *ctx);
void openssl(int sock, int size);
