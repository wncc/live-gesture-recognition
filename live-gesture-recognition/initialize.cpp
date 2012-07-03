#include <iostream>
#include <cstdio>
#include <ctime>
#include <cv.h>
#include <highgui.h>

using namespace std;

int main () {
	int i, num;
	long int t; char c,l;
	float ram;
	FILE * fp = fopen ("waittime.bin", "wb+");
	
	cout<<"Initializing settings and gestures ...\n";
	cout<<"Please enter memory (RAM) of your computer in gigabytes(GB) : ";
	cin>>ram;
	
	if(ram<0.25){
		cout<<"Your memory is very low, "<<ram<<" GB.\n";
		cout<<"The program may not run correctly. Are you sure you want to continue?(y or n).\n";
		cin>>c;
		if(c == 'n') {
			cout<<"To change value run the file 'initialize' again.\n";
			return -1;}
	}
	
	if(ram>6){
		cout<<"Your memory seems quite high, "<<ram<<" GB.\n";
		cout<<"Are you sure that's the correct value?. Are you sure you want to continue?(y or n).\n";
		cin>>c;
		if(c == 'n') {
			cout<<"To change value run the file 'initialize' again.\n";
			return -1;}
	}
	
	if(ram>20){
		cout<<"Do you own a supercomputer!!!. Are you sure you want to continue?(y or n).\n";
		cin>>c;
		if(c == 'n') {
			cout<<"To change value run the file 'initialize' again.\n";
			return -1;}
		ram = 6;
		cout<<"RAM value has been set to 6 GB. To change value press ESC and run the file 'initialize' again\n\n";
		c = cvWaitKey(3000);
		if(c == 27)return -1;
	}
	
	cout<<"Testing the webcam ...\n";
	cout<<"Wait (about 5 to 10 seconds)...\n";
	
	c = cvWaitKey(3000);
	CvCapture* capture = cvCreateCameraCapture( 0 );
	IplImage *frames = cvQueryFrame( capture );
	i=0;t=time(0);
	while (true) {
		 c = cvWaitKey(1);
		 frames = cvQueryFrame( capture );
		 if(i>=128) break;
		 i++;
	}
	t=time (0)-t-1;
	//cout<<t<<endl;
	cvReleaseCapture ( &capture );
	
	num=(128/t)+1 ;
	cout<<"\nFrames per second set at "<<num<<" .\n\n";
	fwrite (&num, 4, 1, fp);
	fwrite (&ram, 4, 1, fp);
	fclose (fp);
	fp = fopen("gestures.bin","wb+");
	char str1[32] = "sudmalroxv";
	for(i=0; i<32; i++){
		l = str1[i];	
		fwrite(&l,1,1,fp);
	}
	fclose(fp);

	return 0;
}

