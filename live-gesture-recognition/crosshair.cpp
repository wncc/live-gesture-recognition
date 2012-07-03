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
					if (i - begin < 70) for (; x<i ; x+=3) newptr[x]=127;
					else for (;x<i ;x+=3) newptr[x]=ptr[x];
					newptr[x] = 127;
				}
				else newptr[x]=127;
			}
		}
	}
}

uchar& val (int x, int y, IplImage* img) {
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

