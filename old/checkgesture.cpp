#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cv.h>
#include <highgui.h>

using namespace std;

struct cons{
    int car;
    int cdr;
};  

int sqr (int x) {return x*x;}
int prev[2]={0};

void writeimg (cons fin[], int N, IplImage* res){
	int x, y, i, j, ht, wd;
	uchar * ptr;
	float slope; 
	char* pt;
		
		ht=res->height; wd = res->width;
	for(j=0; j<N; j++){
		x = fin[j].car + ht/2 ; 
		y = fin[j].cdr + wd/2 ;
		if (x<0)x=0;if (y<0)y=0;if (x>=wd)x=wd-1; if(y>=ht)y=ht-1;
	
		pt=res->imageData + y*res->widthStep + x;
			*((uchar*)pt)=255;
			if (prev[0]!=0 || prev[1]!=0) {
				slope=((float)(x-prev[0]))/(y-prev[1]);
				for (i=min((int)(y)-prev[1],0);
							i<max((int)(y)-prev[1],0);
							i++)
				{
					ptr=(uchar*)(pt-(int)(i*(res->widthStep)+i*slope));
					*ptr=255;
				}
			}
			prev[0]=x; prev[1]=y;
	}
}
	
int main( int argc, char* argv[] ) {
	
	FILE *fp;
	int nframe, i,j;
	char* cmmd;
	char g='\0', c='\0', 
			 com[32] = "Command not found.",
			 fname[10] = "xfile.bin",
			 fname1[10] = "xcmmd.bin",
			 fname2[10] = "xgest.jpg";
	cons x, img[64];
	if(argv[1]==NULL){
		cout<<"Invalid arguments\nUse as:\n";
		cout<<"checkgesture [geture-character]\n\n";
		return -1;
		}

	cmmd = argv[1];
	g = cmmd[0]; i=0;
	
		IplImage* res = cvCreateImage(
		cvSize(640,480),
		IPL_DEPTH_8U,
		1
	);
	
	fname[0]=g;
	fp = fopen(fname,"rb+");

	if(fp==NULL){
		cout<<"ERROR : Load Unsuccessful : '"<<fname<<"'.\n";
		cout<<"Gesture '"<<g<<"' not found.\n\n";
		return -1;
  }
  else cout<<"Load Successful : '"<<fname<<"'.\n";   
  
  fread(&nframe,4,1,fp);
  for(i=0 ; i < nframe ; i++){
		fread(&x,8,1,fp);
		img[i] = x;
	}
	fclose(fp);
	
	fname1[0] = g;
	fp = fopen(fname1,"rb+");
	if(fp==NULL){
		cout<<"ERROR : Load Unsuccessful : '"<<fname1<<"'.\n";
  }
  else {
  	cout<<"Load Successful : '"<<fname1<<"'.\n";   
		for(i=0; i<32; i++){
			fread(&c,1,1,fp);
			com[i] = c;
		}
		for(i=0;i<32;i++){
			if(com[i]=='\0'){
				com[i] = 32;
				com[i+1] = '&';
				com[i+2] = '\0';
				break;
			}
		}
	}
	fclose(fp);
	cout<<"Command : "<<com<<endl;
	cout<<"\nLoading gesture image.\n";
	cvWaitKey(1000);
	
	writeimg(img, nframe, res);
	
	cout<<"\nPress ESC to close...\n";
	cvNamedWindow("Gesture. Press ESC to close...", CV_WINDOW_AUTOSIZE); 
	cvShowImage("Gesture. Press ESC to close...", res); 
	while(true){
		c = cvWaitKey(100); // wait until user hits a key
	  if(c == 27 || c == 32) {
	  	cvDestroyWindow("Display");
	  	break;}
	}

	//system(com);
	return 0;
}
