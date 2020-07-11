//Selection Sort sıralama algoritmasi
//iterasyon ve karsilastirma sayilari ile birlikte göstermektedir.

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

    int temp,count=1;;
    for(int i =0;i<n;i++){
        for(int j=i+1;j<n;j++){
                cout<<i+1<<". iterasyon ve "<<count++<<". karsilastirma : "<<dizi[i]<<" ile "<<dizi[j];
            if(dizi[i]>dizi[j]){
                temp = dizi[i];
                dizi[i]=dizi[j];
                dizi[j]=temp;
                cout<<" <-->"; //yer degistirmeyi gosterir.
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
