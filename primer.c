/* Primer - a primer number finder, and twin primes.
 * @author Devin Rusnak
 * Copyright 2014 Devin Rusnak 
 */

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "math.h"

// structs
typedef struct {
   double time1;
   double time2;
} time_point;

/*
 *
 */
int primeTest(int t)
{
   int i;
   int roof = sqrt(t);   

   for( i = 0; i <= roof; i += 2 )
   {
      if( t % i != 0 ) 
	return 1;
   }
   return 0;
}


/* 
 * MAIN 
 */
int main( int argc, char** argv ) 
{

// print header info
   printf("\n***********************\n");
   printf("Primer\nA prime number finder\n");
   printf("Author: Devin Rusnak\n");
   printf("***********************\n");


// variables
   int index = 0;
   int cmd_line = 0;
   int loop = 0;
   int debug = 0;
   int verbose = 0;
   char *limit_char = 0;
   long int limit = 0;
   char *output_file;
   char *twin_file;

   memset(&output_file, 0, sizeof(char)*32);
// parse command line arguments
   opterr = 0;

   while( (cmd_line = getopt(argc, argv, "dl:o:t:v")) != -1)
      switch( cmd_line )
      {
         case 'd':	// debug mode
	    debug = 1;
      	 break;

	 case 'l':	// limit the search
	    limit_char = optarg;
	    limit = atol(limit_char);
	 break;

	 case 'o':	// file to write all primes to
	    output_file = optarg;
         break;

 	 case 't':	// file to write twin primes to
	    twin_file = optarg;
	 break;

	 case 'v':	// verbose mode
	    verbose = 1;
	 break;

	 case '?':	// error cases

	 break;
  
	 default:	// unknown flag
	    printf("unknown command line argument: ");
	    printf("%s", optarg);
	    printf("\n");
	 break;
      }

// print program configuration
   if(debug)				// debug
      printf("...debug moden\n");

   if(limit != 0)			// limit
   {
      printf("...max number is ");
      printf("%lu\n", limit);
   }
   else
      printf("...no limit\n");

   if(output_file != 0) 		// all prime file
   {
      printf("...writing all primes to file: ");
      printf("%s", output_file);
   }
   else
   {
      strcpy(output_file, "all_primes.txt");
      printf("...writing all primes to file: all_primes.txt");
   }

   
// main loop
   while( loop ) 
   {


   }

// print results

   return 0;
}// end Main
