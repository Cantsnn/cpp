#include <iostream>

using namespace std;
//Kombinasyon hesaplama
//C(N,0)=C(N,N)=1,
//C(N,K)=C(N-1,K)+C(N-1,K-1)

int C(int n , int k){

    if(k==0 || k==n)
        return 1;

    return C(n-1,k)+C(n-1,k-1);


}

int main()
{
    int n,k;
   cout<<"Kombinasyonu hesaplayacaginiz sayilari girin : ";
   cin>>n>>k;
   cout<<"C("<<n<<","<<k<<") : " << C(n,k);
}
