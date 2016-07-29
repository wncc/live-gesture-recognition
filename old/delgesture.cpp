#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
using namespace std;

int main( int argc, char* argv[] ) {

	FILE *fp;
	char* cmmd;
	char g='\0',l='\0', str1[32]="udlrsmvxoa";
	int i=0,N=32,e,j,q;
	if(argv[1]==NULL){
		cout<<"Invalid arguments\nUse as:\n";
		cout<<"delgesture [geture-character]\n\n";
		return -1;
		}
	cmmd = argv[1];
	g = cmmd[0]; i=0;
	
	while(str1[i]!='\0'){
		if (g == str1[i]){
			cout<<"Gesture for '"<<g<<"' exists and cannot be reset.\nPlease try again ...\n\n";
			return -1;
		}
	i++;
	}
	
	fp = fopen ("gestures.bin", "rb+");
	for(i=0; i<32; i++){
		fread(&l,1,1,fp);
		str1[i] = l;
	}
	fclose(fp);
	
	for (i=0; i<32; i++){
		if (str1[i]==g) break;
		else if (i == 31) {
			cout<<"Gesture doesn't exist\n";
			return -1;
			}
	}
	
	for (j=i; j<31; j++){
		str1[j] = str1[j+1];
	}
	fp = fopen ("gestures.bin", "wb+");
	for(i=0; i<32; i++){
		l = str1[i];	
		fwrite(&l,1,1,fp);
	}
	fclose(fp);
cout<<"Gesture deleted.\n";
return 0;

}
		
		
		
		
		
	
