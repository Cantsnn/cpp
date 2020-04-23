#include <iostream>

using namespace std;
// Sadece toplama işlemi kullanarak çarpım işlemi
int carpim(int a , int b){
    int sonuc=0;
    for(int i =0;i<b;i++)
        sonuc+=a;

    return sonuc;

}

int main()
{
    int sayi,sayi1;
    cout<<"Carpmak istediginiz sayilari giriniz : ";
    cin>>sayi>>sayi1;
    cout<<"Sonuc : "<<carpim(sayi,sayi1)<<endl;
}
