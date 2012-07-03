#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <ctime>
#include <iostream>

using namespace std;

int main(){
	Display *display;
	display = XOpenDisplay(NULL);
	unsigned int keycode1;
	keycode1 = XKeysymToKeycode(display, XK_space);
	cout<<keycode1;
	cout<<endl;
	return 0;
	}
	
