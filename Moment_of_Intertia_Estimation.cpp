#define USE_MATHS_DEFINES // in order to use M_PI

#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;
/* This program will calculate the moment of intertia of a crescent bounded by the following equations;
   x^2 + y^2 = a^2        (x-c)^2 + y^2 = b^2
where a,b,c are constants, b < a and (a-b) < c < (a+b).
The crescent is assumed to be uniform in the z-direction.

The moment of intertia is about the axis x=y=0.


We have that I = integral over Q of r^2 dm where Q is the entire mass and r is the distance to from the axis.
Hence using Monte Carlo; I ~ (x_N - x_1) * (1/N) * sum 1:N of f(x_i) we get the following equation;

     I ~ M_crescent / N * sum 1:N of r^2
This equation will be used in this program to calculate the moment of inertia.

The sum will be calculated in a for loop which generates random point in a a by a square.
Then if the points lie within the crescent their distance to (0,0) will be squared and added to a sum.
A counter of how many points that lie within the crescent will be updated.

The total mass of the crescent will be found using the total mass of the square with a density equal to the one of the crescent;
Mass_cresent = (Mass_square/N) * number of points inside crescent.

*/

// ----------- Program ------------
int main(){

  // ----------- Variables -----------
  float a,b,c; // a = bigger radius, b = smaller radius, c = cnetre of smaller circle
  float N,count1=0, count2=0, count3=0; // number of iterations, number of points inside crescent.
  float M_s, M_c; // Mass of square containing the crescent, Mass of crescent.
  float rho,I_est,I_act; // density of crescent, moment of intertia estimation and actual
  float S1=0, S2=0,S3=0,f; // sum of distances from centre squared, fraction of points inside crescent = count/N.
  float x,y; // point coordinates.
  float e_abs, e_rel; // absolute and relative error

  srand(time(NULL)); // for generating random points.

  // Getting variables
  cout << "Enter iteration number: ";
  cin >> N;

  cout << "Enter density of crescent: "; 
  cin >> rho;

  // cout << "Enter a mass of crescent: ";
  //cin >> M_c;

  cout << "Enter radii: \n";
  cout << "a= ";
  cin >> a;
  cout << "b= ";
  cin >> b;

  cout << "Enter smaller circle centre: \n";
  cout << "c= ";
  cin >> c;

  // check initial conditions
  // if (b  >= a || (a-b) > c || c > (a+b) ){
  //cout << "a,b and c values cannot be used. \n";
  //return 1;
  //}

  // Calculation of mass of points
  //M_s = rho*pow(2*a,2);
  M_s = rho*N;
  //cout << "Mass of square is  " << M_s << ".\n";

  // Iterating over points
  for (int i=0; i< (int)N; i++){
    //cout << "i=" << i << ".\n";

    x = a-2*(((double) rand() / (RAND_MAX))*a); // creates a random number between -a and a.
    y = a-2*(((double) rand() / (RAND_MAX))*a);

    // cout << "coordinates = (" << x << "," << y << ")\n";

    if (pow(x,2) + pow(y,2) <= pow(a,2)){// if the point is inside the cresent shape
      S1 += pow(x,2) + pow(y,2);
      //cout << pow(x,2) + pow(y,2) << ".\n";
      //cout << "S= " << S << ".\n";
      count1 += 1;
    }
    if (pow(x-c,2) + pow(y,2) <= pow(b,2)){
      S2 += pow(x,2) + pow(y,2);
      count2 += 1;
    }

    if ( pow(x,2) + pow(y,2) <= pow(a,2) && pow(x-c,2) + pow(y,2) >= pow(b,2)) {
      S3 += pow(x,2) + pow(y,2);
      count3 += 1;
    }
      
    //cout << "\n";
  }
  //cout << "count= " << count << ".\n";

  // Calculation of moment of intertia
  M_c = M_s*(count3 / N);
  //cout << "Mass of cresent is " << M_c << ".\n";
 
  I_est = rho*S3;
  //I_est = (M_c/ (float) count3) *S3;
  cout << "The estimated moment of inertia is " << I_est << ".\n";

  // Actual moment of intertia
  //I_act = 0.5*(rho*count3)*(pow(a,2) + pow(b,2)); FOR c=0

  //I_act = 0.5*M_s*(count1/N)*pow(a,2) - 0.5*M_s*(count2/N)*pow(b,2) - M_s*(count2/N)*pow(c,2);

  I_act = 0.5*rho*count1*pow(a,2) - 0.5*rho*count2*pow(b,2) - rho*count2*pow(c,2);
  cout << "The actual moment of inertia is " << I_act << ".\n";

  // Errors 
  e_abs = abs(I_act - I_est);
  cout << "The absolute error is " << e_abs << ".\n";
    
  e_rel = abs(e_abs / I_act) * 100;
  cout << "The relative error is " << e_rel << ".\n";

  return 0;
}
