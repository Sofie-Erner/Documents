#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

// We need to calculate the volume of a sphere in n <= 10 dimensions.
// We have that the set of point of a sphere in n<= dimensions is 
//     S_n = { x in R^n : ||x|| = r}

// hence points that lay within the radius r away from origin, both positive and negative. We therefore have that the absolute value of all coordinates of a point should be in [-r,r].

// say we have an n-dimensions, and x^2 + y^2 + z^2 + q^2 + ... = r^2 for radius r.
// we can then generate N number of points in the interval [-r,r] and check whether they fall within the sphere. 


// ------------- Variables -------------------
/*
n - number of dimensions
r - radius of n-dimensional sphere
N - number of itterations
count - number of points inside sphere
s - sum of coordinates squared
x[n] - list of lenght n with coordinates as entries
i,j - variables for itteration
f - fraction of number of points in sphere / number of itterations (count / N)
V - volume of n-dimensional box the sphere is located in
I - aprroximate volume of sphere
S - actual volume of sphere
e_abs = absolute error on volume of sphere
e_rel = relative error on volume of sphere

 */

// ------------- Program -------------------

int main(){

  int n; // empty variable that will store the number of wanted dimensions.
  cout << "How many dimensions? ";
  cin >> n;

  int r; // empty variable that will store the wanted radius.
  cout << "What is the radius? ";
  cin >> r;
  //cout << "r^2 = " << pow(r,2) << ".\n";

  int N;//
  cout << "Number of itterations: ";
  cin >> N;

  int count=0;
  float s=0;
  // a counter of how many points were inside the sphere
  // s will be used to sum the coordinates in x to see if they satisfy
  //       x^2 + y^2 + z^2 + q^2 + ... <= r^2

  float x[n];// list of coordinates for each point.

  srand(time(NULL));

  for (int i=0; i < N; i++){
    s=0;
    //cout << "i= " << i << ".\n";

    for (int j=0; j < n; j++){// iterating over entries in x.
      x[j] = ((double) rand() / (RAND_MAX))*r; // this creates a random number betwen 0 and 1 and multiplies it with r.
      
      //cout << "x" << j << "= " << x[j] << ".\n";
      s += pow(x[j],2);
      //cout << "s= " << s << ".\n";
    }

    //cout << "s= " << s << ".\n";
    //cout << "r^2 = " << pow(r,2) << ".\n";
    //cout << "\n";
    if (s <= pow(r,2)){
      count += 1;
    }
  }

  // Calculation of volume
  cout << "count = " << count << ".\n";
  float f = (float) count / (float) N;
  cout << "Fraction of iterations inside sphere: " << f << ".\n";

  float V =  pow(2*r,n);
  cout << "The box volume is " << V << ".\n";

  float I = f * V;
  cout << "Approximate volume of the sphere is " << I << ".\n";

  // Comparison with actual volume
  float S = (pow(M_PI,((float) n/ (float) 2)))/(tgamma(((float) n/ (float) 2)+1)) *( pow(r,n));
  cout << "Actual volume of the sphere is " << S << ".\n";

  float e_abs = abs( I - S );
  float e_rel = e_abs / S;

  cout << "The absolute error is " << e_abs << ".\n";
  cout << "The relative error is " << (e_rel*100) << "% .\n";

return 0;
}
