#include <bits/stdc++.h>
#include<cmath>
using namespace std;
long long int fib(long long int n){
	if(n==0){return 0;}
	else if(n==1){return 1;}
	else if(n==2){return 1;}
	else if(n%2==0){return fib(n/2)*(2*fib((n/2)+1)-fib(n/2));}
	else{
		return pow(fib((n-1)/2),2)+pow(fib(((n-1)/2)+1),2);
	}
}
int main(){
	long long int n;
	cin>>n;
	cout<<fib(n)<<endl;
}