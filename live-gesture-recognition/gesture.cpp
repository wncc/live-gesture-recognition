#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cv.h>
#include <highgui.h>

using namespace std;

int main( int argc, char* argv[] ){
	char c;
	while (true){
	
		system("./main");
		c =cvWaitKey(250);
		if(c == 27 || c == 32) break;
	
	}
	
	return 0;
}
