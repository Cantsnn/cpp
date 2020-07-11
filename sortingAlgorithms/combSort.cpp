//Tarak sıralama algoritması (Comb Sort)
//Kücültme parametresi varsayılan 1.24 olarak alinmis ve mesafe hesaplanirken asagiya yuvarlanmistir.
//Adım adım karsilastirma mesafesi ile göstermektedir.
#include <iostream>

using namespace std;

int main()
{
    int n;
    float gap=1.24; //küçültme parametresi
    cout<<"Eleman sayisi :";
    cin>>n;
    int dizi[n];
    for(int i =0;i<n;i++){
       cout<<i+1<<". eleman :";
        cin>>dizi[i];
     }
   int temp,count = 1,disc = n/gap;//disc, uzakligi hesaplar

   while(disc>0){
        cout<<"Karsilastirma mesafesi :"<<disc<<endl;
        cout<<count++<<". adim yer degisenler :"<<endl;
        for(int i = disc;i<n;i++){
            if(dizi[i-disc]>dizi[i]){
                cout<<dizi[i-disc]<<" ile "<<dizi[i]<<endl;
                temp = dizi[i];
                dizi[i] = dizi[i-disc];
                dizi[i-disc] = temp;
            }
        }
        disc = disc/gap;
    }
    cout<<"Siralanmis dizi : ";
    for(int i =0;i<n;i++){
    cout<<dizi[i];
        if(i!=n-1)
            cout<<",";
   }
    return 0;
}
