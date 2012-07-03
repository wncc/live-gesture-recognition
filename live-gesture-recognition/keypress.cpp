/*#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <ctime>
#include <iostream>

using namespace std;
*/
void wait (unsigned int t) {
	unsigned int t0=time(0);
	while (time(0)<t0+t);
}

void fakepress(char g) {
	int i; bool s=false;
	FILE* fp; char c;
	Display *display;
	unsigned int keycode1;
	unsigned int keycode2;
	display = XOpenDisplay(NULL);
	
	//XTestFakeKeyEvent(display, 65, True, 0);
	//XTestFakeKeyEvent(display, 65, False, 0);

	
	//cout<<"Final = '"<<g<<"'.\n\n";
	
	if(g=='l'){
		XTestFakeKeyEvent(display, 80, True, 0);
		XTestFakeKeyEvent(display, 80, False, 0);
	}
	else if(g=='r'){
		XTestFakeKeyEvent(display, 88, True, 0);
		XTestFakeKeyEvent(display, 88, False, 0);
	}
	else if(g=='o'){
		XTestFakeKeyEvent(display, 65, True, 0);
		XTestFakeKeyEvent(display, 65, False, 0);
	}
	else if(g=='s'){
		XTestFakeKeyEvent(display, 133, True, 0);
		XTestFakeKeyEvent(display, 133, False, 0);
	}
	else if(g=='a'){
		XTestFakeKeyEvent(display, 36, True, 0);
		XTestFakeKeyEvent(display, 36, False, 0);
	}
		
		
	else if(g=='u'){
		for (i=0; i<4; i++){
			XTestFakeKeyEvent(display, 37, True, 0);
			XTestFakeKeyEvent(display, 80, True, 0);
			XTestFakeKeyEvent(display, 80, False, 0);
			XTestFakeKeyEvent(display, 37, False, 0);
		}
	}
	else if(g=='d'){s=true;
		for (i=0; i<4; i++){
			XTestFakeKeyEvent(display, 37, True, 0);
			XTestFakeKeyEvent(display, 88, True, 0);
			XTestFakeKeyEvent(display, 88, False, 0);
			XTestFakeKeyEvent(display, 37, False, 0);
		}
	}

			
	else if(g=='x'){
			XTestFakeKeyEvent(display, 37, True, 0);
			XTestFakeKeyEvent(display, 24, True, 0);
			XTestFakeKeyEvent(display, 24, False, 0);
			XTestFakeKeyEvent(display, 37, False, 0);
		}

	else if(g=='m')	{
		system("firefox &"); return;}
	else if(g=='v'){
		system("vlc &"); return;}
	
	else {
		char com[34],fname[10]="xcmmd.bin";
		fname[0] = g;
		fp = fopen(fname,"rb+");
		for(i=0; i<32; i++){
			fread(&c,1,1,fp);
			com[i] = c;
		}
		fclose(fp);
		for(i=0;i<32;i++){
			if(com[i]=='\0'){
				com[i] = 32;
				com[i+1] = '&';
				com[i+2] = '\0';
				break;
			}
		}
		
		system(com);
	}
	
	XFlush(display);
	return;
}
