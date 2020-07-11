//Bubble Sort (Kabarcık sıralama) Algoritmasi
//Adım adım karsilastirma sayilari((n-1)^2) ile göstermektedir.
#include <iostream>

using namespace std;

int main()
{
    int n;
    cout<<"Eleman sayisi :";
    cin>>n;
    int dizi[n];
    for(int i =0;i<n;i++){
        cout<<i+1<<". eleman :";
        cin>>dizi[i];
    }
    int temp,count=1;
    for(int i = 0; i<n-1;i++){
        for(int j=0;j<n-1;j++){
                cout<<count++<<". karsilastirma : ";
                cout<<dizi[j]<<" ile "<<dizi[j+1];
            if(dizi[j]>dizi[j+1]){
                temp = dizi[j];
                dizi[j]=dizi[j+1];
                dizi[j+1]=temp;
                cout<<" <->";//yer degirtirdigini gosterir
            }
            cout<<endl;
        }
    }
    cout<<"Siralanmis dizi : ";
    for(int i =0;i<n;i++){
      cout<<dizi[i];
        if(i!=n-1)
            cout<<",";
   }
    return 0;
}

