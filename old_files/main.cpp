#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cv.h>
#include <highgui.h>

using namespace std;

int sqr (int x) {return x*x;}
int prev[2]={0};

#include "crosshair.cpp"
#include "recognize.cpp"

cons writecenter( IplImage* img , IplImage* res) {
	cons gest; gest.car = 0; gest.cdr = 0;
	int x, num=0, i;
	uchar * ptr; char* pt;
	long int x_tot=0, y_tot=0;
	for( int y=0; y<img->height; y++ ) {
		ptr = (uchar*) (img->imageData + y * img->widthStep);
		for(x=0; x<(img->width); x++) {
			if (ptr[3*x]!=127 || ptr[3*x+1]!=127 || ptr[3*x+2]!=127) {
				x_tot+=x;
				y_tot+=y;
				num++;
			}
		}
	}
	
	if (num>20) {
		pt=res->imageData + (y_tot/num)*res->widthStep + x_tot/num;
		*((uchar*)pt)=255;
		gest.car = x_tot/num ;
		gest.cdr = y_tot/num ;
	}
	return gest;
}

void differ( IplImage* imgmid, IplImage* imgnew) {
	int k, x;
	float total=0, num=1.0/(3*(imgmid->width)*(imgmid->height)), sqs=0;
	for( int y=0; y<imgmid->height; y++ ) {
		uchar* ptrmid = (uchar*) (
		imgmid->imageData + y * imgmid->widthStep
		);
		uchar* ptrnew = (uchar*) (
		imgnew->imageData + y * imgnew->widthStep
		);
		for(x=0; x<3*(imgmid->width); x++ ) {
			k=ptrnew[x]-ptrmid[x];
			if (k > 30) ptrmid[x]=255;
			else if (k < -30) ptrmid[x]=0;
			else ptrmid[x]=127;
		}
	}
}

main( int argc, char* argv[] ) {
	bool a=false;
	char g='\0', str1[8]="sumalr1";
	cons gest[256];
	int i=0,N=256;
	CvCapture* capture = cvCreateCameraCapture( 0 );

	IplImage *mid = cvQueryFrame(capture);
	IplImage *frames = cvQueryFrame(capture);

	IplImage* res = cvCreateImage(
		cvGetSize(frames),
		IPL_DEPTH_8U,
		1
	);
	
	cvNamedWindow( "Recording ...press ESC to stop !", CV_WINDOW_AUTOSIZE );

	while (true) {
		mid = cvCloneImage(frames);
		frames = cvQueryFrame( capture );
		if (!frames) break;
		
		differ(mid,frames);
		crosshair(mid);
		
		cvShowImage( "Recording ...press ESC to stop !",mid );
		char c = cvWaitKey(1);
		if( c == 27 ) break;
		if( c == 32 ) {
			if (a){
				N = i;
				scaleimg (gest, N);
				g = evalgest(gest, N , str1 , 50000);
//				if (g == 'm') system ("google-chrome on.fb.me/aamod &");
			}
			a=!a;
			i = 0; 
			cout<<i;
		}
	
		if (a) {
			if (i > 250) {
					cout<<"Too long gesture. unable to process.\n";
					a = false;
					cout<<"Try Again\n\n";
					}
			else {
				gest[i] = writecenter(mid, res);
				if (gest[i].car!=0 || gest[i].cdr!=0) i++;
			}
		}
		
		cvReleaseImage (&mid);
	}

	cvSaveImage("gesture1.jpg",res);
	cvReleaseCapture ( &capture );
	cvDestroyWindow ( "Recording ...press ESC to stop !");

	return 0;
}

