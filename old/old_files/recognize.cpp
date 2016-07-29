struct cons{
    int car;
    int cdr;
};  

void scaleimg(cons pix[], int n){
	long int xcm, ycm;
	float xtot, ytot, xstd;
	int i;
	
	for(i=0 ; i<n ; i++){
		xcm += pix[i].car ;
		ycm += pix[i].cdr ;
	}
	
	xcm = xcm/n;
	ycm = ycm/n;
	
	for(i=0 ; i<n ; i++){
		xtot += sqr(xcm - pix[i].car);
		ytot += sqr(ycm - pix[i].cdr);
	}
	
	xstd = sqrt((xtot+ytot)/(2*n));
	
	for(i=0 ; i<n ; i++){
		pix[i].car = (pix[i].car-xcm)*50/xstd;
		pix[i].cdr = (pix[i].cdr-ycm)*50/xstd;
	}
}


char evalgest(cons pix[], int N, char str[], int t){
	FILE* fp;
	float diff,min = 99999999;
	int i,j,n;
	cons img[256], scaled[N], x, y;
	char fname[10]="xfile.bin" , gest='\0';
	
	for (int k=0; str[k]!='\0' ; k++){
		fname[0]=str[k];
		fp = fopen(fname,"rb+");
		
		if(fp==NULL){
			cout<<"ERROR : Load Unsuccessful : '"<<fname<<"'.";
			break;
    }
    else cout<<"Load Successful : '"<<fname<<"'.\n";   
    
    for(i=0 ; i < 256 ; i++){
			fread(&x,8,1,fp);
			img[i] = x;
    }
     
    diff = 0;
    for(j=0; j < N ; j++){
    	n = (j * 256/ N) - 1;
    	x = img[n]; y = pix[j];
    	diff += sqr(x.car - y.car) + sqr(x.cdr - y.cdr) ;
    }
  	
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

