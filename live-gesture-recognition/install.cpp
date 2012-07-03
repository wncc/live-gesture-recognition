#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(){

	system("g++ `pkg-config opencv --cflags` initialize.cpp -o initialize `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` addgesture.cpp -o addgesture `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` checkgesture.cpp -o checkgesture `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` delgesture.cpp -o delgesture `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` main.cpp -o main `pkg-config opencv --libs` -lX11 -lXtst");
	system("g++ `pkg-config opencv --cflags` gesture.cpp -o gesture `pkg-config opencv --libs` -lX11 -lXtst");

return 0;
}
