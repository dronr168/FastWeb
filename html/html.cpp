#include <fstream>
#include <cstdio>
#include <iostream>

#define size 104857600 //maximum transfer file size 100 MB

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
char *buf = new char[size];
int p = 0;
while(!htmlFile.eof()){
	if(p < size){
		htmlFile.get(buf[p]);
		p++;
	}else{
		break;
	}
}
htmlFile.close();
char Siz[6];
sprintf(Siz, "%d", (p-1));
int cg = 0;
int cp = 0;
while(h1[cp]){
	bufer[cg] = h1[cp];
	cg++;
	cp++;
}
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
cp = 0;
while(h2[cp]){
        bufer[cg] = h2[cp];
        cg++;
        cp++;
}
cp = 0;
while(type[cp]){
        bufer[cg] = type[cp];
        cg++;
        cp++;
}
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
cp = 0;
while(h3[cp]){
        bufer[cg] = h3[cp];
        cg++;
        cp++;
}
cp = 0;
while(Siz[cp]){
        bufer[cg] = Siz[cp];
        cg++;
        cp++;
}
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
bufer[cg] = '\r';
cg++;
bufer[cg] = '\n';
cg++;
for(int i=0; i<p; i++){
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

