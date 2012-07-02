struct cons{
    int car;
    int cdr;
};  

float gestdiff(IplImage* img , int pix[][100]){
	float diff=0;
	int x ;
	for( int y=0; y<img->height; y++ ) {
		uchar* ptr = (uchar*) (
		img->imageData + y * img->widthStep
		);
		for(x=0; x<(img->width); x++ ) {
			if (ptr[x] >200) {
				diff+= pix[x][y];
				}
		}
		}
	return diff;
	}
	
	
char evalgest(IplImage *img , char str[], int t){
	FILE* fp;
	int i,j,x,n,pix[100][100];
	float sum,diff,min = 99999999;
	char fname[10]="xinfo.bin" , gest='\0';
	for (int k=0; str[k]!='\0' ; k++){
		fname[0]=str[k];
		fp = fopen(fname,"rb+");
		if(fp==NULL){
           cout<<"ERROR : Load Unsuccessful : '"<<fname<<"'.";break;
       }
    else cout<<"Load Successful : '"<<fname<<"'.\n";   
        for(i=0;i<100;i++){
            for(j=0;j<100;j++){
                fread(&x,4,1,fp);
                pix[i][j]=x;
                }
        }
        fread(&sum,4,1,fp); 
		diff = gestdiff(img, pix);
		cout<<str[k]<<" : "<<diff<<endl;
		if (diff < min && diff < t) {
			min = diff;
			gest = str[k];
			}
		fclose(fp);
		}
	cout<<endl<<"Gesture : '"<<gest<<"'."<<endl;
	return gest;
}
		

