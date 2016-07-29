

void scaleimg(cons pix[], int n){
	long int xcm=0, ycm=0;
	float xtot=0, ytot=0, xstd;
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
	//cout<<"\nxstd = "<<xstd<<endl;
	for(i=0 ; i<n ; i++){
		pix[i].car = (pix[i].car-xcm)*50/xstd;
		pix[i].cdr = (pix[i].cdr-ycm)*50/xstd;
		//cout<<pix[i].car<<"      "<<pix[i].cdr<<"\n\n";
	}
}


float evaldiff(cons img[], int M, int N, cons pix[], int P, int Q){
	//cout<<M<<"   "<<N<<"  ... ...  "<<P<<"   "<<Q<<endl;
	int A,B,i,j,k,n;
	cons x,y;
	float diff=0;
	if ((N-M)<(Q-P)) {
		diff = evaldiff(pix, P, Q, img, M, N);
		return diff;
		}
	
	A = N-M; B = Q-P;
	//cout<<A<<"        "<<B<<endl;
	//if(B == 0) cout<<"\nERROR\n!!! ... ... ... !!!\n\n";
	//else cout<<"\ncool!\n!!! ... ... ... !!!\n\n";
  diff = 0;
  //cout<<diff<<endl;	
  for(j=P; j <= Q ; j++){
  	n = M + ((j-P)*A/B);
  	x = img[n]; y = pix[j];
  	//cout<<n<<"   "<<x.car<<"   "<<x.cdr<<"  ... ...  "<<j<<"   "<<y.car<<"   "<<y.cdr<<endl;
  	diff = diff + sqr(x.car - y.car) + sqr(x.cdr - y.cdr) ;
  }
	//cout<<diff<<endl;	
	diff = diff*10/(B+1);
  //cout<<diff<<endl;	
	return diff;
}


char evalgest(cons pix[], int N, char str[], int t){
	FILE* fp;
	float diff,min = 99999999;
	int i,j,n,nframe = 20,nframe1;
	int waittime=15,start,end;
	cons img[64], scaled[N], x, y;
	char fname[10]="xfile.bin" , gest='\0';
	
	for (int k=0; str[k]!='\0' ; k++){
			fname[0]=str[k];
			fp = fopen(fname,"rb+");
		
			if(fp==NULL){
				cout<<"ERROR : Load Unsuccessful : '"<<fname<<"'.";
				continue;
		  }
		  else cout<<"Load Successful : '"<<fname<<"'.\n";   
		  
		  fread(&nframe,4,1,fp);
		  for(i=0 ; i < nframe ; i++){
				fread(&x,8,1,fp);
				//cout<<x.car<<"  "<<x.cdr<<endl;
				img[i] = x;
				
		  }
		/*
		cout<<"\nimg frames = "<<nframe<<"\npix frames = "<<N<<"\n\n";
		for(i=0 ; i<nframe ; i++){
			cout<<"img["<<i<<"].car = "<<img[i].car;
			cout<<"     ; img["<<i<<"].cdr = "<<img[i].cdr<<endl;
		}
 		for(i=0 ; i<N ; i++){
			cout<<"pix["<<i<<"].car = "<<pix[i].car;
			cout<<"     ; pix["<<i<<"].cdr = "<<pix[i].cdr<<endl;
		}
		*/
		nframe1 = (waittime*nframe/15);
		if(nframe < N/2) {
			cout<<"Gesture too long for '"<<str[k]<<"'. Continuing ...\n";
			continue;	}
		 
	  else if (nframe <= (3*N/2+1)){
	 		start = 2*N/3 ; end = N; }
	 		
 		else if (nframe <= 2*N){
 			start = N/2 ; end = 5*N/6+1 ;}
 			
		else {
			cout<<"Gesture too short for '"<<str[k]<<"'. Continuing ...\n";
			continue; }
		  
		  for (i=start; i< end ; i++){
		  	
		  	for (j = 0; j < (N-i) ; j++){
		  		
		  		diff = evaldiff (pix, j, (j+i-1), img, 0, (nframe-1) );
		  		if (diff < min && diff < t) {
						min = diff;
						gest = str[k];
						//cout<<"Min value renewwed as "<<min<<" ,for '"<<str[k]<<endl;
					} 
				
				}
			}
		
			fclose(fp);
	}
	
	cout<<endl<<"Gesture : '"<<gest<<"'."<<endl;
	return gest;
}
    	
