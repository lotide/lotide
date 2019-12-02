/* integral.c defines integrateTrap(), a function to approximate
 *  definite integrals using the trapezoidal rule. 
 *
 * Joel Adams, Fall 2013.
 */

#include "integral.h"

/* declaration of the function to be integrated,
 * which must be defined in the caller of integrate()
 * or a linking error will occur
 */
extern double f(double x); 

/* function to approximate an integral:
 * parameters: xLo, the left endpoint
 *             xHi, the right endpoint
 *             numTrapezoids, the number of trapezoids to use
 * return: the approximate integral of f(x) from x1 to x2.
 */
long double integrateTrap(double xLo, double xHi,
                           unsigned long long numTrapezoids) {
   long double delta = (xHi - xLo) / numTrapezoids;
   long double result = 0;
   unsigned long long i = 0;

   result = (f(xLo) + f(xHi)) * 0.5;
   for (i = 1; i < numTrapezoids; i++) {
     result += f(xLo + i*delta);
   }
   result *= delta;

   return result;
} 

/* Note: The integral is approximately
 *   delta * (f(xLo) + f(x1)) / 2
 * + delta * (f(x1) + f(x2)) / 2
 * + delta * (f(x2) + f(x3)) / 2
 * ...
 * + delta * (f(x[n-2] + f(x[n-1]) / 2
 * + delta * (f(x[n-1]) + f(x[n])) / 2
 */

