#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int sqr (int x) {return x*x;}
int prev[2]={0};

void horize (IplImage* orig, IplImage* modif) {
//	cout<<"\nIn horize.\n";
	int x, begin, i, t;
	for( int y=0; y<orig->height; y++ ) {
		uchar* ptr = (uchar*) (orig->imageData + y * orig->widthStep);
		uchar* newptr = (uchar*) ( modif->imageData + y * modif->widthStep);
		for (t=0; t<3; t++) {
			for(x=t; x<3*(orig->width); x+=3 ) {
				if (ptr[x]!=127) {
					begin = x;
					for (i = x; ptr[i]!=127; i+=3);
					if (i - begin < 60) for (; x<i ; x+=3) newptr[x]=127;
					else for (;x<i ;x+=3) newptr[x]=ptr[x];
					newptr[x] = 127;
				}
				else newptr[x]=127;
			}
		}
	}
}

uchar& val (int x, int y, IplImage* img) {
  //return (* ((uchar*) (img->imageData)));
	return (* ((uchar *) (img->imageData + y * img->widthStep + x)));
}

void verize (IplImage* orig, IplImage* modif) {
//  cout<<"\nIn verize.\n";
	int x, y, begin, i;
	for(x=0; x < 3*(orig->width); x++) {
		for(y=0; y<(orig->height);) {
			if (val(x,y,orig)!=127) {
				begin = y;
				for (i = y; i<(orig->height) && val(x,i,orig)!=127; i++);
				if (i - begin < 20) for (;y<i ;y++) val(x,y,modif)=127;
				else for (;y<i ;y++) val(x,y,modif)=val(x,y,orig);
			}
			else {
				val(x,y,modif)=127;
				y++;
			}
		}
	}
}

void commonize (IplImage* final, IplImage* img1, IplImage* img2) {
//	cout<<"\nIn commonize.\n";
//	uchar* ptr1 = (uchar*) (img1->imageData);
//	uchar* ptr2 = (uchar*) (img2->imageData);
//	uchar* newptr = (uchar*) (final->imageData);
	int x, y, fin = (final->height) * (final->widthStep) + (final->width);
	for (y=0; y<(final->height); y++) {
		uchar* ptr1 = (uchar*) (img1->imageData + y * img1->widthStep);
		uchar* ptr2 = (uchar*) (img2->imageData + y * img2->widthStep);
		uchar* newptr = (uchar*) (final->imageData + y * final->widthStep);
		for (x=0; x<3*(final->width); x++) {
			if (ptr1[x]==127 || ptr2[x]==127) newptr[x]=127;
			else newptr[x]=ptr1[x];
		}
	}
//	cout<<"\nOutta commonize.\n";
}

void crosshair (IplImage * img) {
//	cout<<"\nIn Crosshair.\n";
	IplImage * horiz = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	IplImage * vert = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	horize (img, horiz);
	verize (img, vert);
	commonize (img, horiz, vert);
//	cvReleaseImage (&horiz);
//	cout<<"HERE!!\n";
//	cvReleaseImage (&vert);
//	cout<<"\nOutta Crosshair.\n";
}

/*
void saturate_sv( IplImage* img ) {
	int x;
	for( int y=0; y<img->height; y++ ) {
		uchar* ptr = (uchar*) (img->imageData + y * img->widthStep);
		for(x=0; x<(img->width); x++ ) ptr[x]=255-ptr[x];
	}
}
*/

void writecenter( IplImage* img, IplImage* gest) {
	cout<<prev[0]<<" "<<prev[1]<<"\nHo";
	int x, i;uchar * ptr;
	long int x_tot=0, y_tot=0, num=0;
	float slope; char* pt;
	for( int y=0; y<img->height; y++ ) {
		ptr = (uchar*) (img->imageData + y * img->widthStep);
		for(x=0; x<(img->width); x++) {
			x_tot+=(ptr[3*x]+ptr[3*x+1]+ptr[3*x+2])*x;
			y_tot+=(ptr[3*x]+ptr[3*x+1]+ptr[3*x+2])*y;
			num+=ptr[3*x]+ptr[3*x+1]+ptr[3*x+2];
		}
	}
	
	if (num>100000) {
		pt=gest->imageData + (y_tot/num)*gest->widthStep + x_tot/num;
		*((uchar*)pt)=255;
		if (prev[0]!=0 || prev[1]!=0) {
			slope=((float)(x_tot/num-prev[0]))/(y_tot/num-prev[1]);
			for (i=min((int)(y_tot/num)-prev[1],0);
						i<max((int)(y_tot/num)-prev[1],0);
						i++)
			{
				ptr=(uchar*)(pt-(int)(i*(gest->widthStep)+i*slope));
				*ptr=255;
				}
		}
		prev[0]=x_tot/num; prev[1]=y_tot/num;
	}
	cout<<"ha\n";
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
//			total+=abs(k);
//			sqs+=k*k;
			ptrmid[x]=(k*k)/255;
		}
//		cout<<endl<<total*num<<endl<<sqrt(sqs*num)<<endl;
	}
}

main( int argc, char* argv[] ) {
	bool a=true;
	short i=0;
	CvCapture* capture = NULL;
	capture = cvCreateCameraCapture( 0 );

	IplImage *mid = cvQueryFrame(capture);
	IplImage *frames = cvQueryFrame(capture);
	// get a frame size to be used by writer structure
	CvSize size = cvSize (640,480);

	// declare writer structure
	// use FOURCC ( Four Character Code ) MJPG, the motion jpeg codec
	// output file is specified by first argument
	CvVideoWriter *writer = cvCreateVideoWriter(
		argv[1],
		CV_FOURCC('M','J','P','G'),
		30, // set fps
		size
	);
	
	IplImage* out = cvCreateImage(
		cvGetSize(frames),
		IPL_DEPTH_8U,
		3
	);

	IplImage* gest = cvCreateImage(
		cvGetSize(frames),
		IPL_DEPTH_8U,
		1
	);

	char filename[10]="pic01.jpg";

	//Create a new window
	cvNamedWindow( "Recording ...press ESC to stop !", CV_WINDOW_AUTOSIZE );
	// show capture in the window and record to a file
	// record until user hits ESC key

	while(1) {
		mid = cvCloneImage(frames);
		frames = cvQueryFrame( capture ); 
		if( !frames ) break;
		//cvSmooth( frames, frames, CV_GAUSSIAN, 9, 9 );
		//cvCvtColor(frames,mid,CV_BGR2GRAY);
		// cvCanny( mid, mid,25, 60, 3 );	
		// saturate_sv(mid);
		differ(mid,frames);
//		crosshair(mid);
		cvShowImage( "Recording ...press ESC to stop !",mid );
		//cvWriteFrame( writer, out );
		char c = cvWaitKey(33);
		if( c == 27 ) break;
		if( c == 32 ) {a=!a; cout<<i;}
		if (a) {i++;
			writecenter(mid, gest);
//			cvSaveImage(filename,mid);
//			if (filename[4]==57) {filename[4]='0'; filename[3]++;}
//			else {filename[4]++;}
		}
	
		cvReleaseImage (&mid);
	}

	cvSaveImage("gesture1.jpg",gest);
	cvReleaseVideoWriter( &writer );
	cvReleaseCapture ( &capture );
	cvDestroyWindow ( "Recording ...press ESC to stop !");

	return 0;
}

