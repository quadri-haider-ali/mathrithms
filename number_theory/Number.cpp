#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

//A class called Number which allows accessibility to various
//properties of numbers
//For a start, they are even, square, prime_factorization, euler_phi
//Can include prime, mersenne_prime, fermet number...and so on!!
class Number{
private:
    //these variables should not be accessible by users
    //Instead a function call should return their value
    int ephi;
    bool even;
    bool square;

    //Function to check square or not!!
    void _square_check(){
        int x = sqrt(n);
        square = (x*x == n); 
    }

//Filling the prime_factorization by Trial Division first, then using
//Pollard's Rho Factorization Algorithm if the need may be, 
//A probabilistic algorithm, so called Monte Carlo...
//Done in private since, prime_factorization array is available for access

    //The psuedo prime generator function
    //This function should be accessible to user to change
    //Maybe using constructor function, will look into it..
    //in the future!!
    int _f(int x, int N, int c=1){
        int t = (x*x + c + N) % N;
        return t;
    }

    //The Rho Factorization Algorithm
    //with parameters x0 and c
    void _rho_factorization(int N, int x0 = 2, int c = 1){
        if(N == 1){
            return;
        }

        int x = x0, y = x0, g = 1;

        while(g == 1){
            //Using the Floyd Cycle Detection Algorithm here!
            //Private function _f used here!
            x = _f(x, N, c);                   //k
            y = _f(y, N, c); y = _f(y, N, c);     //2*k

            g = __gcd(abs(x - y), N);
        }

        prime_factorization.push_back(g);
        _rho_factorization(N/g);
    }

    //Trial Division, then the Rho Algorithm
    void _integer_factorization(int N){
        prime_factorization.push_back(1);

        //Iterative Trial Division till 1e5
        for(int i=2; i < 1e5; i+=1){
            while(N%i == 0){
                prime_factorization.push_back(i);
                N = N/i;
            }
        }

        //All the squares and cubes have been removed from N
        //This allows the Rho Factorization to work accurately
        _rho_factorization(N);        
        sort(prime_factorization.begin(), prime_factorization.end());
    }

//To calculate the Euler Phi Function
    void _euler_phi(){
        ephi = 1;

        //Using the Euler Phi Formula
        for(auto p: prime_factorization){
            if(p == 1) continue;
            ephi = ephi * (p-1);
        }

        return;
    }


public:
    int n;
    vector<int> prime_factorization;

//Constuctor
    Number(int x){
        n = x;
        even = !(x%2);
        _square_check();
        _integer_factorization(x);
        _euler_phi();
    }

//Function Calls for private variables
    bool is_even(){
        return even;
    }

    bool is_square(){
        return square;
    }

    int e_phi(){
        return ephi;
    }
};

int main(){
    int n;
    cin >> n;

    Number t(n);
    for(auto p: t.prime_factorization) cout << p << " ";
    cout << endl;
    cout << t.e_phi() << " " << t.is_even() << " " << t.is_square() << endl;
}