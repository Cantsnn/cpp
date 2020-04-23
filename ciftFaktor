//ikili faktöriyel ya da çift faktöriyel
//N!!=N*(N-2)*(N-4)*...
//(N>0 tam sayıdır. Son çarpan N çift sayı ise 2, tek sayı ise 1 olmaktadır)

#include <iostream>

using namespace std;

long ikiliFact(int n){

    if(n==1 || n==2)
        return n;

  return  n*ikiliFact(n-2);

}

int main()
{
    int secim;
    cout<<"Hesaplamak istediginiz sayi : ";
    cin>>secim;
    if(secim<1)
        cout<<"Daha buyuk bir sayi giriniz."<<endl;

    cout << secim<<"!! : "<<ikiliFact(secim) << endl;
    return 0;
}
