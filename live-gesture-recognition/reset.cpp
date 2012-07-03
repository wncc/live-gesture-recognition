
void resetimg(IplImage* img){	
	int x, t=0, temp;
	for( int y=0; y<img->height; y++ ) {
	uchar* ptr = (uchar*) (
	img->imageData + y * img->widthStep
	);
	for(x=0; x<(img->width); x++) {
		ptr[x] = 0;
		}
	}
}

	
