#include <stdio.h>
#include <assert.h> 		
#include <math.h>
#include <iostream>
#include "fbcFBAProblem.hxx" 	
 	
/** \brief Test for solving LP formatted models. 	
 * Loads a simple LP model and solves it using lp_solve library. 	
 */ 	
int main (int argc, char *argv[]) 	
{ 	
   fbc::FBAProblem pbm;
   pbm.initFromLPFile(argv[1]);	
   return 0; 	
}
