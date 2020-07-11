// Çinlilerin Kalan Teoremi (Chinese Remainder Theorem-CRT)
//Sayının mod işlemine göre kalanı ve mod degeri girildiginde sayıyı vermektedir.

#include <iostream>

using namespace std;

int main()
{
    int n;
    cout<<"Eleman sayisini giriniz : ";
    cin>>n;
    int m[n],a[n],M[n+1];
    for(int i =0; i<n;i++){
        cout<<i+1<<". eleman : ";
        cin>>a[i];
        cout<<"Mod degeri : ";
        cin>>m[i];
    }

    int carpim =1;
    for(int i=0;i<n;i++){
    carpim*=m[i];

    }

    M[0]=carpim;

    for(int i=1;i<n+1;i++){
        M[i]=M[0]/m[i-1];

    }
    int temp,y[n];
    for(int i =0;i<n;i++){
        for(int j=1;j<50;j++){
            temp = M[i+1]*j;
            if(temp%m[i]==a[i]){
                y[i]=j;
                break;}
        }
    }

 int x =0;
 for(int i = 0;i<n;i++){
    x+= M[i+1]*y[i];
 }
    cout<<"Sonuc : "<<x%M[0];


    return 0;
}
