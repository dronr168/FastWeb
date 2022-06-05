#include "../robots/spisok.h"

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

