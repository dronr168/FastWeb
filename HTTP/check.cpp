#include <fstream>

using namespace std;

int checksize(char *name){
        ifstream testfile(name);
        if(!testfile){
                perror("testfile");
                testfile.close();  
                return 0;
        }
        int testsize;
        for(testsize=0; !testfile.eof(); testsize++){
                char in;
                testfile.get();
        }
        testfile.close();
        return testsize; 
}

