#include <iostream>
#include <cmath>
#include <list>
using namespace std;

// This program will calculate the following integral
//    I = integral of [2 + cos(2*sqrt(x))] dx on [0,2]
// This wil be done using the Simpson's Rule with the equation

// I ~ (x_N - x_1)*(1/ (N-1))*[(1/3)*f(x_1) + (4/3)*f(x_2) + (2/3)*f(x_3) + (4/3)*f(x_4)+ ... + (2/3)*f(x_(N-2)) + (4/3)*f(x_(N-1)) + (1/2)*f(x_N)]

// We will be using N = 3,4,8,16 and comparing the error's.

float integral( float N  ){// the wanted N is passed to the function as a function parameter

  float I=0, x, x_1 = 0, x_N = 2;
  cout << "N = " << N << ".\n";

  if (N < 3){
    cout << "N is too small \n \n";
    return 0;
  }

  // We start by finding the summing term of I.
  for (int i=1; i <= N; i++){
    
    x = x_1 + (i-1)*((2-0)/N);

    //cout << "i = " << i << ".\n";
    //cout << "x = " << x << ".\n";
    
    if ( i == 1 || i == N){// the first and last term are different to the res
      I += ((float) 1/ (float) 3)*(2+cos(2*sqrt(x)));
    }
    else if ( i % 2 == 0){// if is even
      I += ((float) 4/ (float) 3)*(2+cos(2*sqrt(x)));
    }
    else{// if i is odd
      I += ((float) 2/ (float) 3)*(2+cos(2*sqrt(x)));
    }
    
    //cout << "I = " << I << ".\n \n";
  }

  // We can multiply the summation by the frist two expressions of the fomula of I
    I = I*(x_N - x_1)*(1/(N-1));

  return I;
}

int main(){

  int Ns[] = {3, 4, 8, 16};
  float I, e_rel, e_abs;

  cout << "The actual integral is I= " << 3.4600 << ".\n \n";

  for (int i=0; i < 4; i++){
    I = integral( Ns[i] );
    
    if ( I == 0){ // if N is too  small
      continue;
    }
    else{
      cout << "This is the integral approximation: " << I << ".\n";

      e_abs = abs( 3.4600 - I );
      cout << "The absolute error is " << e_abs << ".\n";

      e_rel = abs( ((I-3.4600)/3.4600)*100 );
      cout << "The relative error is " << e_rel << "% .\n \n";
    }
  }
  return 0;
}

// the absolute error is give by 1/90 (b-a)^5 / 2^5 * abs( f'''' (s))
// where s is the x value for which  f'''' is maximum.

// Plotting the absolute error against the N-values we see that the curve can be approximated to be proportional to 1/N^2.
