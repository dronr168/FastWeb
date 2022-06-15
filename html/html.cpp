#include <fstream>
#include <cstdio>
#include <iostream>

using namespace std;

int BodyHtml(char *name, char *bufer, char *type){
char h1[] = "HTTP/1.1 200 OK";
char h2[] = "Content-Type: ";
char h3[] = "Content-Length: ";

ifstream htmlFile;
htmlFile.open(name);
if(!htmlFile){
	perror("open");
	htmlFile.close();
	return 0;
}
char *buf;
int size;
for(size = 0;!htmlFile.eof(); size++)
	htmlFile.get();
buf = new char[size];
htmlFile.clear();
htmlFile.seekg(0);
for(int i=0; i<size; i++)
	htmlFile.get(buf[i]);
htmlFile.close();
size--;
buf[size] = '\0';
char Siz[6];
sprintf(Siz, "%d", size);
int cg = 0;
int cp;
for(cp=0;h1[cp];cp++){
	bufer[cg] = h1[cp];
	cg++;
}
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
for(cp=0;h2[cp];cp++){
        bufer[cg] = h2[cp];
        cg++;
}
for(cp=0;type[cp];cp++){
        bufer[cg] = type[cp];
        cg++;
}
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
for(cp=0;h3[cp];cp++){
        bufer[cg] = h3[cp];
        cg++;
}
for(cp=0;Siz[cp];cp++){
        bufer[cg] = Siz[cp];
        cg++;
}
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
for(int i=0; i<size; i++){
        bufer[cg] = buf[i];
        cg++;
}
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
bufer[cg] = '\0';

delete[] buf;
return cg+1;
}

