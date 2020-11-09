// İsmailcan Tosun
//Matris sınıfı ve bu sınıfı kullanarak görüntü işleme
//işlemleri yapabilen sınıf

#include <iostream>
#include<stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

template <typename A>
class Matrix
{
public:
	Matrix();
	Matrix(int,int,char);
	Matrix(int,int,int);
	void MatrisOlustur(int);
	virtual void print();
	void print(string);
	void resize(int,int);
	Matrix& operator+(const Matrix&);
    Matrix& operator+(const A&);
	Matrix& operator-(const Matrix&);
	Matrix& operator-(const A&);
	Matrix& operator*(const Matrix&);
	Matrix& operator*(const A&);
	Matrix& operator/(const A&);
	Matrix& operator%( float);
	Matrix& operator^(const float&);
	void operator=(const Matrix&);
	Matrix& emul(const Matrix&);
	Matrix& T();
	Matrix& inv();
	float det();
	~Matrix();

protected:
    int satir;
	int sutun;
	int deger;
	A** matris;

};

//default constructor
template <typename A>
Matrix<A>::Matrix()
{
	this->satir = 10;
	this->sutun = 10;
	this->deger = 0;
	MatrisOlustur(0);

}

template <typename A>
Matrix<A>::Matrix(int x, int y, int z)
{
	this->satir = x;
	this->sutun = y;
	this->deger = z;
	MatrisOlustur(z);

}

template <typename A>
Matrix<A>::Matrix(int x, int y, char c)
{
	this->satir = x;
	this->sutun = y;
	if (c == 'e'){//birim matris
		MatrisOlustur(1);
		deger = 1;
		}
	if (c == 'r'){//random değer oluşturmak için parametre
		MatrisOlustur(-1);
		deger = -1;
		}

}
template <typename A>
void Matrix<A>::MatrisOlustur(int value) {
	srand(time(0));//random değer oluşturmak için

    //bellekte matris için yer oluşturuyoruz
	matris = new A *[satir];

	for (int i = 0; i < satir; i++)
		matris[i] = new A[sutun];


	for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
			if (value == -1) {
				matris[i][j] = rand() % 256;
			}
			else
				matris[i][j] = value;
		}
	}
}
//Matrisi tekrar boyutlandırıyor
template <typename A>
void Matrix<A>::resize(int y_satir,int y_sutun){
    //var olan değerleri tutmak için atama yapıyor.
    Matrix<A> *temp = new Matrix<A> (y_satir,y_sutun,deger);
    if(y_satir<this->satir){
        for(int i=0;i<y_satir;i++){
            for(int j=0;j<sutun;j++){
                temp->matris[i][j] =  this->matris[i][j] ;
                }
            }
        }

     else{
        for(int i=0;i<this->satir;i++){
            for(int j=0;j<this->sutun;j++){
                temp->matris[i][j] =  this->matris[i][j] ;
                }
            }
        }
    //eski matrisi bellekten silip yenisini atıyoruz.
    this->~Matrix();
    this->satir=temp->satir;
    this->sutun=temp->sutun;
    this->matris=temp->matris;
    this->deger = this->deger;
}

//+ operatörü overloading
template<typename A>
Matrix<A>& Matrix<A>::operator+(const Matrix& m){
    //matrislerin boyutlarını karşılaştırıyor.
    if(this->satir!=m.satir || this->sutun!=m.sutun){
        cout<<"Matrislerin boyutları uyumsuz!!!"<<endl;
        exit(0);
    }
    Matrix<A> *sonuc = new Matrix<A>(satir,sutun,deger);

     for (int i = 0;i <this->satir;i++) {
		for (int j = 0;j < this->sutun;j++) {
            sonuc->matris[i][j] = this->matris[i][j] + m.matris[i][j];
            }
	}
    return *sonuc;
}


// - operatoru overloading
template<typename A>
Matrix<A>& Matrix<A>::operator-(const Matrix& m){
    if(this->satir!=m.satir || this->sutun!=m.sutun){
        cout<<"Matrislerin boyutları uyumsuz!!!"<<endl;
        exit(0);
    }
   Matrix<A> *sonuc = new Matrix<A>(satir,sutun,deger);

     for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
            sonuc->matris[i][j] = this->matris[i][j] - m.matris[i][j];
		}
	}
    return *sonuc;
}

// = operatoru overloading
template<typename A>
void Matrix<A>::operator=(const Matrix& m){
    //belleği temizleyip tekrar dolduruyoruz
        this->~Matrix();

        this->sutun = m.sutun;
        this-> satir = m.satir;
        this->deger = m.deger;
        MatrisOlustur(deger);

        for(int i = 0;i<satir;i++){
            for(int j=0;j<sutun;j++){
                matris[i][j] = m.matris[i][j];
            }
        }
}

// * operatoru overloading
template<typename A>
Matrix<A>&  Matrix<A>::operator*(const Matrix& m){

    if(this->sutun!=m.satir){
        cout<<"Matrislerin satir sutun sayilari uyumsuz!!!"<<endl;
        exit(0);
    }
    Matrix<A> *temp = new Matrix<A>(satir,m.sutun,0);
    float toplam = 0;

    for(int i = 0; i<satir;i++){
        for(int j = 0; j<m.sutun;j++){
            for(int k=0;k<sutun;k++){
                toplam+= (this->matris[i][k]*m.matris[k][j]);
            }
            temp->matris[i][j]=toplam;
            toplam = 0;
        }
    }
    return *temp;
}

// skaler + operatoru overloading
template<typename A>
Matrix<A>& Matrix<A>:: operator+(const A& sayi){

   Matrix<A> *temp = new Matrix<A>(satir,sutun,deger);

    for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
            temp->matris[i][j] = this->matris[i][j] + sayi;
		}
	}
    return *temp;
}

// skaler - operatoru overloading
template<typename A>
Matrix<A>& Matrix<A>::operator-(const A& sayi){

    Matrix<A> *temp = new Matrix<A>(satir,sutun,deger);

    for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
            temp->matris[i][j] = this->matris[i][j] - sayi;
		}
	}
   return *temp;
}

// skaler * operatoru overloading
template<typename A>
Matrix<A>& Matrix<A>::operator*(const A& sayi){

    Matrix<A> *temp = new Matrix<A>(satir,sutun,deger);

    for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
            temp->matris[i][j] = this->matris[i][j] * sayi;
		}
	}
   return *temp;
}

// skaler / operatoru overloading
template<typename A>
Matrix<A>& Matrix<A>::operator/(const A& sayi){

    Matrix<A> *temp = new Matrix<A>(satir,sutun,deger);

    for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
            temp->matris[i][j] = this->matris[i][j] / sayi;
		}
	}
   return *temp;
}

// skaler mod operatoru overloading
template<typename A>
Matrix<A>& Matrix<A>::operator%(float sayi){


    Matrix<A> *temp = new Matrix<A>(satir,sutun,deger);
    int bolen = sayi;
    int bolunen,kalan=0;

    for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
           // temp->matris[i][j] = this->matris[i][j] % sayi;

           bolunen = this->matris[i][j];

                        if(bolen == 0){
                          puts("Bölen sıfır olamaz.");

                          continue;
                        }
                        else if(bolunen == 0){
                          kalan=0;
                          temp->matris[i][j]=kalan;
                        }
                        else
                       {
                          d:         //sonsuz döngü
                            kalan = bolunen - bolunen / bolen * bolen;

                            if(kalan > bolen) bolunen = kalan;
                            else{
                              temp->matris[i][j]=kalan;
                              continue;
                                }
                        goto d;
                    }
            }
	}
   return *temp;
}

// üs operatoru overloading
template<typename A>
Matrix<A>& Matrix<A>::operator^(const float& sayi){

    Matrix<A> *temp = new Matrix<A>(satir,sutun,deger);

    for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
            temp->matris[i][j] = pow(this->matris[i][j] ,sayi);
		}
	}
   return *temp;
}

template<typename A>
Matrix<A>& Matrix<A>::T(){//transpoz

    Matrix<A> *temp= new Matrix<A>(sutun,satir,deger);

    for(int i = 0; i<satir;i++){
        for(int j=0;j<sutun;j++){
            temp->matris[j][i] = this->matris[i][j];
        }
    }
return *temp;
}

template <typename A>
void Matrix<A>::print() {//Matrisi ekrana basar
	for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
			cout << matris[i][j] << "\t";
		}
		cout << endl;
	}
	cout<<endl;
}

template <typename A>
void Matrix<A>::print(string dosyaAdi){//Matrisi verilen dosyaya yazar

    ofstream dosya;
    dosya.open(dosyaAdi);

	for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
			dosya << matris[i][j] << "\t";
		}
		dosya << endl;
	}
	cout<<endl;
    dosya.close();
}
//verilen matrisle eleman düzeyinde çarpma yapar.
template<typename A>
Matrix<A>&  Matrix<A>::emul(const Matrix& m){
    if(this->satir!=m.satir || this->sutun!=m.sutun){
            cout<<"Verilen matrisin boyutları aynı olmalidir."<<endl;
            exit(0);
        }

        Matrix<A> *temp = new Matrix<A>(satir,sutun,deger);

    for (int i = 0;i < satir;i++) {
		for (int j = 0;j < sutun;j++) {
            temp->matris[i][j]=this->matris[i][j] * m.matris[i][j];
		}
	}
    return *temp;
}

template <typename A>
Matrix<A>& Matrix<A>::inv(){//Matrisin tersini alır.
    if(this->satir!=this->sutun){
        cout<<"Kare matris değil. Tersi alınamaz.!!!"<<endl;
        exit(0);
    }
    if(this->det()==0){
        cout<<"Determinant 0 olduğu için tersi yoktur!!!"<<endl;
        return *this;
    }

    Matrix<A> *temp2 = new Matrix<A>(satir,sutun,deger);
    Matrix<A> *temp = new Matrix<A>(satir,sutun,1);

    for(int i=0;i<satir;i++){
        for(int j=0;j<sutun;j++){
            temp2->matris[i][j]=this->matris[i][j];
        }
    }

    for(int i = 0; i<satir;i++){
        for(int j = 0;j<sutun;j++){
            if(i==j)
                temp->matris[i][j]=1;
            else
                temp->matris[i][j]=0;
        }
    }

    float a,b;
    for(int i =0;i<satir;i++){
        a = temp2->matris[i][i];
        for(int j=0;j<sutun;j++){
            temp2->matris[i][j] = temp2->matris[i][j]/a;
            temp->matris[i][j] = temp->matris[i][j]/a;
        }
        for(int x = 0;x<satir;x++){
            if(x!=i){
                b = temp2->matris[x][i];
                for(int j = 0;j<sutun;j++){
                    temp2->matris[x][j] = temp2->matris[x][j]-(temp2->matris[i][j]*b);
                    temp->matris[x][j] = temp->matris[x][j] - (temp->matris[i][j]*b);
                }
            }
        }
    }
return *temp;
}

template<typename A>
float Matrix<A>::det(){//Matrisin determinantını alır
    if(this->satir!=this->sutun){
        cout<<"Kare matris değil. Determinantı yok!!!"<<endl;
        exit(0);}
  float determ=0;
  if(satir==1){
    determ = this->matris[0][0];
      return determ;
  }
  else if(satir==2){
    determ = this->matris[0][0]*this->matris[1][1]-this->matris[0][1]*this->matris[1][0];
    return determ;

  }
  else{
    for(int p=0;p<sutun;p++){

        Matrix<A> temp(satir-1,sutun-1,0);

        for(int j = 1;j<satir;j++){
            for(int k=0;k<sutun;k++){
                if(k<p){
                    temp.matris[j-1][k] = this->matris[j][k];
                }
                else if(k>p){
                    temp.matris[j-1][k-1] = this->matris[j][k];
                }
            }
        }
        determ+=this->matris[0][p]*pow(-1,(int)p)*temp.det();
    }
  }
    return determ;
}


template <typename A>
Matrix<A>::~Matrix(){//destructor
    //matrisi boşaltıp siliyoruz.
	for (int i = 0; i < satir; i++)
		delete[]matris[i];

	delete[]matris;
}


template <typename A>
class Table : public Matrix<A>
{
    public:
        Table();
        Table(A,A,A);
        Table(A,A,char);
        int itemAt(int,int) ;
        int itemAt(string);
        int itemAt(string,string);
        void setRowNames(string[],int);
        void setColNames(string[],int);
        void isimDoldur(A,A);
        virtual void print();
        virtual ~Table();

    private:
        string *satirAd;
        string *sutunAd;
};

template <typename A>
Table<A>::Table()
{
//önce matrix sınıfının destructorı çağrılıyor.
    satirAd = new string[this->satir];
    sutunAd = new string[this->sutun];
     isimDoldur(10,10);
}

template <typename A>
Table<A>::Table(A row,A column,A value){
//verilen değerlere göre tablo oluşturuyor.
    this->satir = row;
    this->sutun = column;
    this->deger = value;
    this->MatrisOlustur(value);
    satirAd = new string[this->satir];
    sutunAd = new string[this->sutun];
    isimDoldur(row,column);
}

template <typename A>
Table<A>::Table(A row,A column,char ch){
    if(ch!='r'){
        cout<<"HATALI GIRIS!!!"<<endl;
        exit(0);}
//random değer oluşturan destructor
    this->satir = row;
    this->sutun = column;
    this->deger = -1;
    this->MatrisOlustur(this->deger);
    satirAd = new string[this->satir];
    sutunAd = new string[this->sutun];
    isimDoldur(row,column);
}

//Satir ve sutun sayisi kadar tablo oluşturuyor.
template<typename A>
void Table<A>::isimDoldur(A satirsayi,A sutunsayi){

    if(sutunsayi>26){
        cout<<"Sutun ismi Z'den fazla olamaz!!!"<<endl;
        exit(10);
        }

   for(int i = 0; i<satirsayi;i++){
        this->satirAd[i]=to_string(i);

   }
   for(int j = 0; j<sutunsayi;j++){
        this->sutunAd[j]=65+j;

    }

}

template <typename A>
int Table<A>::itemAt(int r,int c) {
//Verilen değerlerdeki matrisi çağırır.
    if (r>=this->satir){
        cout<<"Hatali Arama!!!"<<endl;
            exit(0);
    }
     if (c>=this->sutun){
        cout<<"Hatali Arama!!!"<<endl;
            exit(0);
    }
    int sonuc = this->matris[r][c];
    return sonuc;
}

template <typename A>
int Table<A>::itemAt(string s) {
//String olarak verilen adresteki değeri döndürür.
    string ch,rc;
    ch = s.substr(0,1);
    cout<<ch<<endl;
    rc = s.substr(1,3);
    cout<<rc<<endl;

    int sonuc = this->itemAt(rc,ch);
    return sonuc;
}

template <typename A>
int Table<A>::itemAt(string rs,string cs){
//satir sutun isimlerine göre değer döndürür.
    int i,j;
    bool sutunvarmi=false;
    bool satirvarmi=false;
    for(i=0;i<this->satir;i++){
        if(satirAd[i]==rs){
            satirvarmi = true;
            break;
            }
    }

    for(j=0;j<this->sutun;j++){
        if(sutunAd[j]==cs){
            sutunvarmi = true;
            break;
            }
    }

    if(satirvarmi==false || sutunvarmi==false){
        cout<<"HATALI ARAMA !!!"<<endl;
        exit(0);
    }
    return this->matris[i][j];
}

template<typename A>
void Table<A>::setRowNames(string s[],int n){
//verilen stringteki elemanları satir ismi olarak setler.
    if(n>this->satir){
        cout<<"Dizi boyutu satir sayisindan fazla!!!"<<endl;
        exit(10);
    }
    for(int i=0;i<n;i++){
        this->satirAd[i]=s[i];
    }
}

template<typename A>
 void Table<A>::setColNames(string s[],int n){
//verilen stringteki elemanları sutun ismi olarak setler.
    if(n>this->sutun){
        cout<<"Dizi boyutu sutun sayisindan fazla!!!"<<endl;
        exit(10);
    }
     for(int i=0;i<n;i++){
        this->sutunAd[i]=s[i];
    }
 }

//Tabloyu ekrana basar.
template <typename A>
 void Table<A>::print(){
     cout<<setw(11)<<right<<"";
    for(int j = 0;j<this->sutun;j++){
        cout<<setw(8)<<left<<sutunAd[j];

    }
    for(int i=0;i < this->satir;i++){
        cout<<endl<<setw(11)<<left<<satirAd[i];
        for(int k=0;k<this->sutun;k++){
            cout<<setw(8)<<this->matris[i][k];
        }
    }

}

template <typename A>
Table<A>::~Table(){
//matrisi ve dizileri bellekten siliyoruz.
	delete[]this->satirAd;
	delete[]this->sutunAd;

}

template <typename A>
class Image : public Matrix<int>
{
    public:
        Image();
        Image(int,int);
        Image(string,string);
        A color;
        bool isGray(string,string);
        void imread(string ,string);
        void imwrite(string,string );
        void color2gray();
        void gray2binary(int);
        void erosion();
        void yerAc(int,int);
        void dilation();
        void opening();
        void closing();

    private:
        int width;
        int height;
        bool isBinary=true;
        bool isGry;
        int boskisim[1078];
};


struct rgb {
//piksel degerlerini tutan struct
    int **red;
    int **green;
    int **blue;

};

template<typename A>
Image<A>::Image(){
//default constructor
    width=255;
    height = 255;
   yerAc(width,height);
}

template<typename A>
Image<A>::Image(int w,int h){
//parametlere göre default matris olusturuyor.
    this->width = w;
    this->height = h;
    yerAc(width,height);
}

template<typename A>
bool Image<A>::isGray(string fname,string format){
//resmin gri olup olmadığını kontrol ediyor.
    ifstream resim;
    resim.open(fname+"."+format,ios::binary | ios :: in);
    if(format=="bin"){//ilk iki bit w,h oluyor.
        int w=resim.get();
        int h=resim.get();
        int i=0;
        while(!resim.eof()){
                resim.get();
                i++;
                }
        int sonuc = (w*h);
        //dosya boyutu width*height kadarsa gridir.
        if(i-1==sonuc){ return true;}
        else{ return false;}
    }
    else{//bmp icon dosyada 1078 fazlalık var.18ve22. bit boyutu verir
            for(int i=0;i<18;i++)
                resim.get();

            int h=resim.get();
            for(int i=0;i<3;i++)
                    resim.get();

            int w=resim.get();
            for(int i=0;i<1055;i++)
                resim.get();


            int a=0;
            while(!resim.eof()){
                    resim.get();
                    a++;
            }

            if(a-1==w*h){ return true;}
            else{ return false;}

    }

}

template <typename A>
void Image<A>::imread(string filename,string format){
//dosyayı okuyoruz.
    //tekrar fonk çağırmamak için değişkene atıyoruz.
     isGry = isGray(filename,format);
     ifstream resim;
    resim.open(filename+"."+format,ios::binary | ios :: in);


    if (resim.is_open()){
        if(format=="bin"){
            width= resim.get();
            height = resim.get();
            yerAc(width,height);
            int i=0;
            while(i<width){
                for(int j=0;j<height;j++){
                    if(isGry==true){
                        color.green[i][j]=resim.get();
                         if(color.green[i][j]!=0)
                            if(color.green[i][j]!=255)
                                isBinary =  false;
                        color.red[i][j]=0;
                        color.blue[i][j]=0;}
                    else{
                                isBinary =  false;
                        color.red[i][j]=resim.get();
                        color.green[i][j]=resim.get();
                        color.blue[i][j]=resim.get();
                    }
                }
                i++;
            }
            if(isGry==true)
                cout<<"Gri bin dosyasi okundu."<<endl;
            else   cout<<"Renkli bin dosyasi okundu."<<endl;

        }

        if(format=="bmp"){
            int sayac=0;
            for(int i=0;i<18;i++){
               boskisim[sayac]= resim.get();
                sayac++;
                }

            this->height=resim.get();
            boskisim[sayac]=height;
            sayac++;
            for(int i=0;i<3;i++){
                    boskisim[sayac]=resim.get();
                    sayac++;
                    }

            this->width=resim.get();
            boskisim[sayac]=width;
            sayac++;
            for(int i=0;i<1055;i++){
               boskisim[sayac]=resim.get();
               sayac++;}

            cout<<"width:"<<width<<endl;
            cout<<"height:"<<height<<endl;
            yerAc(width,height);

            for(int k=0;k<width;k++){
                for(int l=0;l<height;l++){
                    if(isGry==true){
                        color.green[k][l]=resim.get();

                        if(color.green[k][l]!=0)
                            if(color.green[k][l]!=255)
                                isBinary =  false;

                        color.red[k][l]=0;
                        color.blue[k][l]=0;}

                    else{
                        color.red[k][l]=resim.get();
                        color.green[k][l]=resim.get();
                                isBinary =  false;
                        color.blue[k][l]=resim.get();}
                        }

                    }
                }
            }

    else
        cout<<"Dosya acilamadi."<<endl;

}



template<typename A>
Image<A>::Image(string fname,string format){

    ifstream resim;
    resim.open(fname+"."+format,ios::binary | ios :: in);

    if (resim.is_open())
    {
        imread(fname,format) ;
        resim.close();
    }
    else
        cout << "Dosya acilamadi";
}

template<typename A>
void Image<A>::yerAc(int w,int h){
//Struct elemanları için matris oluşturuyor.
    this->satir=w;
    this->sutun=h;
    this->deger=0;
    this->MatrisOlustur(this->deger);
    color.red=this->matris;
    this->MatrisOlustur(this->deger);
    color.blue=this->matris;
    this->MatrisOlustur(this->deger);
    color.green=this->matris;

}


template<typename A>
void Image<A>::imwrite(string fname,string format){

    ofstream dosya;
    dosya.open(fname+"."+format,ios::binary | ios :: out);

        unsigned char ch;

    if(format=="bin"){
       ch=width;
        dosya<<ch;
        ch=height;
        dosya<<ch;

        for (int i = 0;i < this->width;i++) {
            for (int j = 0;j < this->height;j++) {
                if(isGry==true){
                ch = color.green[i][j];
                dosya<<ch;
                }
                else{
                    ch = color.red[i][j];
                        dosya<<ch;
                    ch=color.green[i][j];
                        dosya<<ch;
                    ch=color.blue[i][j];
                        dosya<<ch;
                    }
            }
        }
            cout<<endl;
            dosya.close();
            if(isGry==true)
                cout<<"Gri bin resmi dosyaya yazildi."<<endl;
            else
                cout<<"Renkli bin resmi dosyaya yazildi."<<endl;

        }

    else{
            for(int i=0;i<1078;i++){
                    ch=boskisim[i];
                    dosya<<ch;
            }
            for(int k=0;k<this->width;k++){
                for(int l=0;l<this->height;l++){
                    if(isGry==true){
                        ch = color.green[k][l];
                        dosya<<ch;
                }
                else{
                    ch = color.red[k][l];
                        dosya<<ch;
                    ch=color.green[k][l];
                        dosya<<ch;
                    ch=color.blue[k][l];
                        dosya<<ch;
                    }

                }
            }
            if(isGry==true)
                cout<<"Gri bmp resmi dosyaya yazildi."<<endl;
            else
                cout<<"Renkli bmp resmi dosyaya yazildi."<<endl;
    }
}

template<typename A>
void Image<A>::color2gray(){//renkli resimi griye çevirir
    if(isGry==true){
        cout<<"Resim renkli değildir!!!"<<endl;
            exit(0);
        }
    int griton=0;
    for(int i=0;i<this->width;i++){
        for(int j=0;j<this->height;j++){
                griton =(color.red[i][j]*0.3)+(color.green[i][j]*=0.59)+(color.blue[i][j]*=0.11);
                color.red[i][j] = griton;
                color.green[i][j] = griton;
                color.blue[i][j] = griton;
        }
    }
    isGry=true;
}

//eşik değerine göre resmi ikiliye çevirir.
template<typename A>
void Image<A>::gray2binary(int thr){
    isBinary = true;

    for(int i=0;i<this->width;i++){
        for(int j=0;j<this->height;j++){
            if(color.green[i][j]<thr)
                color.green[i][j]=0;
            if(color.green[i][j]>=thr)
                color.green[i][j]=255;
        }
    }
}

template<typename A>
void Image<A>::dilation(){


    if(isBinary==0){
        cout<<"Dosya binary degildir!!!"<<endl;
        exit(0);
    }
    int satirindis[this->width * this->height];
    int sutunindis[this->width *this->height];
    int sayac=0;
    for(int i =0;i<this->width;i++){
        for(int j=0;j<this->height;j++){
            bool degisim = false;
            if(color.green[i][j]==255){
                for(int k=0;k<sayac;k++){
                    if(satirindis[k]==i && sutunindis[k]==j){
                        degisim=true;
                        break;
                        }
                }
                if(degisim == true)
                    continue;

                if(i>0){
                    if(color.green[i-1][j]!=255){
                        color.green[i-1][j]=255;
                    }
                }

                if(j>0){
                    if(color.green[i][j-1]!=255){
                        color.green[i][j-1]=255;
                    }

            }
                if(i<this->width-1){
                    if( color.green[i+1][j]!=255){
                        color.green[i+1][j]=255;
                        satirindis[sayac]=i+1;
                        sutunindis[sayac]=j;
                        sayac++;
                    }

                }

                if(j<this->height-1){
                    if( color.green[i][j+1]!=255){
                        color.green[i][j+1]=255;
                        satirindis[sayac]=i;
                        sutunindis[sayac]=j+1;
                        sayac++;
                    }
                }
            }

        else
            continue;
        }
    }
}

template<typename A>
void Image<A>::erosion(){

    if(isBinary==0){
        cout<<"Dosya binary degildir!!!"<<endl;
        exit(0);
        }
    int satirindis[this->width * this->height];
    int sutunindis[this->width *this->height];
    int sayac=0;

    for(int i =0;i<this->width;i++){
        for(int j=0;j<this->height;j++){
            bool degisim = false;
            if(color.green[i][j]==0){
                for(int k=0;k<sayac;k++){
                    if(satirindis[k]==i && sutunindis[k]==j){
                        degisim=true;
                        break;
                        }
                }
                if(degisim == true)
                    continue;

                if(i>0){
                    if(color.green[i-1][j]!=0){
                        color.green[i-1][j]=0;
                    }
                }

                if(j>0){
                    if(color.green[i][j-1]!=0){
                        color.green[i][j-1]=0;
                    }

            }
                if(i<this->width-1){
                    if( color.green[i+1][j]!=0){
                        color.green[i+1][j]=0;
                        satirindis[sayac]=i+1;
                        sutunindis[sayac]=j;
                        sayac++;
                    }
                }

                if(j<this->height-1){
                    if( color.green[i][j+1]!=0){
                        color.green[i][j+1]=0;
                        satirindis[sayac]=i;
                        sutunindis[sayac]=j+1;
                        sayac++;
                    }
                }
            }

        else
            continue;
        }
    }
}

template<typename A>
void Image<A>::opening(){
    this->erosion();
    this->dilation();
}

template<typename A>
void Image<A>::closing(){
    this->dilation();
    this->erosion();
}

int main()
{

	return 0;
}
