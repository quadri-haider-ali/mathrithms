/* code adapted from - https://cs.nyu.edu  */

//libraries
#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;

//the Matrix class to represent our matrix object
//the dimension is required in the least
//may create int or double valued matrices or using another predefined matrix 
class Matrix {
   private:
   //not accessible to users
      int n;
      double* _rep;

   public:

      Matrix(int d) : n(d) { _rep   = new double [n*n]; }   //to instantiate a null matrix object with the dimension only

      Matrix(int d, double M[]); 
      Matrix(int d, int M[]); 
      Matrix(const Matrix&);  

      const Matrix& operator=(const Matrix&); //operator overloading(=) for matrix objects
      ~Matrix() { delete [] _rep; } //deconstructor

      //to extract matrix value m(r,c)
      const double& operator()(int r, int c) const { return _rep[r * n + c]; }
      double& operator()(int r, int c) { return _rep[r * n + c]; }

      //determinant method
      double determinant() const;

      //for overloading stream insertion as global functions using the object and ostream
      friend ostream& operator<<(ostream&, const Matrix&);
};

//constructors

//real valued matrix
Matrix::Matrix(int d, double M[]) : n(d) {
   int i, j;
   _rep   = new double [n*n];
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M[i * n + j];
}

//integer valued matrix
Matrix::Matrix(int d, int M[]) : n(d) {
   int i, j;
   _rep   = new double [n*n];
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M[i * n + j];
}

//making another object using one
//eg-- Matrix p(m) 
Matrix::Matrix(const Matrix& M) : n(M.n) {
   int i, j;
   _rep   = new double [n*n];
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M._rep[i * n + j];
}

//to have a matrix be equal to another
//eg-- p=m
//matrix p has same values as m 
//the dimensionality of p is also changed if need be

const Matrix& Matrix::operator=(const Matrix& M) {
   int i, j;
   if (n != M.n) {
      delete [] _rep;
      n = M.n;
      _rep = new double [n*n];
   }
   for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
         _rep[i * n + j] = M._rep[i * n + j];
   return *this;
}

//using Bareiss Algorithm to calculate determiant
double Matrix::determinant() const {
   Matrix A = *this;
   double det;
   int i, j, k;

   for (i = 0; i < n-1; i++) {
      for (j = i + 1; j < n; j++)
         for (k = i + 1; k < n; k++) {
            A(j,k) = (A(j,k)*A(i,i)-A(j,i)*A(i,k));
	    if (i) A(j, k) /= A(i-1,i-1);
         }
   }

   return A(n-1,n-1);
}


ostream& operator<<(ostream& o, const Matrix& M) {
   int i, j;
   for (i = 0; i < M.n; i++) {
     for (j = 0; j < M.n; j++) {
       double d = M(i,j);
       o << M(i, j) << " ";
     }
      o << endl;
   }
   return o;
}

///driving function
int main() {

   int n;
   double det;
   cin>>n;
   double A[n*n];
   for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
         cin>>A[i*n+j];

   Matrix m(n,A);

   det=m.determinant();
   cout<<"Determinant="<<det<<endl;

  return 0;

}