void faispettrog(){

Double_t xx;
Double_t yy[24]={3500,48000,20000,10000,7000,3500,3000,2000,1500,800,500,350,300,200,150,60,70,60,30,20,15,15,15,6};

cout  << 8 << " " << 48000  << endl;

for ( int i=0; i<24; i++)
{
xx=(i+1)*8./24.;
cout  << xx << " " << yy[i] << endl;
}


}
