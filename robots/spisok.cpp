#include <fstream>
#include <cstdio>
//this class regulates access to files using robots.txt
#define sizes 1000

using namespace std;

class robots {
public:
	char spisok[sizes][128]; //the list size is a maximum of 1000 words, 128 characters each
	bool grap();
	int coit;
};

bool robots::grap(){
	ifstream filespi;
	filespi.open("robots.txt");
	if(!filespi){
        perror("open robots.txt");
        filespi.close();
        return 1;
	}
	
	int p = 0;
	int sch = 0;
	while(!filespi.eof() && (sch!=sizes)){
		filespi.get(spisok[sch][p]);
		if(spisok[sch][p]=='\n'){
			spisok[sch][p] = '\0';
			p = -1;
			sch++;
		}
		p++;
	}
	coit = sch;
	return 0;
}
