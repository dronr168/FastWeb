#include "../robots/spisok.h"

#define sized 104857700 //maximum transfer file size 100 MB

class NetHTTP : public robots{
        char *i_buf;
        char path[31];
        char type[5];
public:
        int sock;
        int size_fakt;
        char *body = new char[sized-100];
        char *o_buf = new char[sized];
        NetHTTP(char *opop, int faktS);
        ~NetHTTP();
        int ClientSend();
};

