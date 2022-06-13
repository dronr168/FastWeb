#include <fstream>
#include <cstdio>

using namespace std;

class robots {
public:
	char **spisok;
	bool grap();
	int coit;
	~robots();
};

robots::~robots(){
	for(int i=0;i<coit;i++)
		delete[] spisok[i];
	delete[] spisok;
}

bool robots::grap(){
	ifstream filespi;
	filespi.open("robots.txt");
	if(!filespi){
        perror("open robots.txt");
        filespi.close();
        return 1;
	}
	
	int p = 0;
	int pm = 0;
	int sch = 0;
	for(int i = 0; !filespi.eof(); i++){
		char r;
		filespi.get(r);
		if(r!='\n'){
			p++;
		}else{
			sch++;
			if(pm < p)
				pm = p;
			p = 0;
		}
	}
	coit = sch;
	spisok = new char*[sch];
	for (int i=0; i<sch; i++)
		spisok[i] = new char[pm];
	filespi.clear();
	filespi.seekg(0);
	p = 0;
	sch = 0;
        for(int i = 0; !filespi.eof(); i++){
                char r;
                filespi.get(r);
                if(r!='\n'){
			spisok[sch][p] = r;
                        p++;
                }else{
                        sch++;
                        p = 0;
                }
        }
	return 0;
}
