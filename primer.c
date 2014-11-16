/* Primer - a primer number finder, and twin primes.
 * @author Devin Rusnak
 * Copyright 2014 Devin Rusnak 
 */

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "math.h"
#include "time.h"
#include "errno.h"

// structs
typedef struct {
   double point_t1;
   double point_t2;
} time_point;

typedef struct {
   int all_found;
   int twin_found;
   time_t avg_time;
   time_t min_time;
   time_t max_time;
} stats_struct;

/* PrimeTest - 
 *
 * @param test_num -
 * @param debug -  
 * @return - 
 */
int primeTest(long int test_num, int debug)
{   
   int i;
   int roof = sqrt(test_num) + 1;   	// max number needed to test agasint

   if(test_num == 1 || test_num == 3)	// trivial cases
      return 1;

   if(debug)
      printf("\ndebug: roof is %d.\n", roof);

   for( i = 1; i <= roof; i += 2 )	// check odd numbers from 3
   {
      if(debug)
	 printf("debug: i is %d.\n", i);

      if( test_num % i == 0 )		// test
	return 0;	// not prime
   }
   return 1;		// prime
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
   int index = 0;			// flag
   int cmd_line = 0;			// count
   int loop = 1;			// flag
   int debug = 0;			// flag
   int verbose = 0;			// flag
   int result = 0;			// number
   int fresh = 1;			// flag
   double temp_time = 0.0;		// number
   long int test_num = 1;		// test_number
   long int limit = 0;			// max_test_number
   FILE *fd_all, *fd_twin;		// file discriptors 
   char *limit_char, *output_file, *twin_file;	// strings
   time_point *time1, *time2;		// struct
   stats_struct *stats;			// struct

   memset(&limit_char, 0, sizeof(char)*32);
   memset(&output_file, 0, sizeof(char)*32);
   memset(&twin_file, 0, sizeof(char)*32);
   memset(&time1, 0, sizeof(time_point));
   memset(&time2, 0, sizeof(time_point));
   memset(&stats, 0, sizeof(stats_struct));

// parse command line arguments
   opterr = 0;
   while( (cmd_line = getopt(argc, argv, "dl:o:t:vh")) != -1)
      switch( cmd_line ) {
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

	 case 'h':	// print help
	    printf("\n*** Help Info ***\n");
	    printf("-d\tDebug Mode\n");
	    printf("-l:\tLimits the search to number given\n");
	    printf("-o:\tWrites all primes found to filename given\n");
	    printf("-t:\tWrites all twin primes to filename given\n");
	    printf("-v\tVerbose Mode\n");
	    printf("-h\tPrints this info\n\n");
	    return 1;	// terminate program
	 break;

	 case '?':	// error cases
	    if(optopt == 'l' || optopt == 'o' || optopt == 't')
 	       fprintf(stderr, "command line option -%c requires an argument.\n", optopt);
	    else if(isprint(optopt))
	       fprintf(stderr, "unkown flag -%c.\n", optopt);
	    else
	       fprintf(stderr, "unkown flag character: '\\%x'.\n", optopt);

            printf("\n");
	 break;
  
	 default:	// unknown flag
	    printf("unknown command line argument: ");
	    printf("%s\n", optarg);
	 break;
      }
      for( index = optind; index < argc; index++ )	// cycle through remaining command line arguments
         printf("Non-recongnized argument: %s.\n", argv[index]);
      printf("\n");

// print program configuration
   if(debug)				// debug
      printf("...debug mode\n");

   if(verbose)				// verbose
      printf("...verbose mode\n");

   if(limit != 0) {			// limit
      printf("...limit set to ");
      printf("%lu\n", limit);
   }
   else
      printf("...no limit set\n");

   if(output_file != 0) { 		// all prime file
      printf("...writing all primes to file:\t");
      printf("%s\n", output_file);
   }
   else {
      output_file = "all_primes.txt";
      printf("...writing all primes to file:\t\tall_primes.txt\n");
   }

   if(twin_file != 0) {			// twin prime file
      printf("...writing all twin primes to file: ");
      printf("%s\n", twin_file);
   }
   else {
      twin_file = "twin_primes.txt";
      printf("...writing all twin primes to file:\ttwin_primes.txt\n");
   }
   printf("\n");

// open files for writting
   fd_all = fopen(output_file, "w+");
   if( fd_all == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return(-1);	// terminate program
   }

   fd_twin = fopen(twin_file, "w+");
   if( fd_twin == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return(-2);	// terminate program
   }
  
   printf("starting...\n");
   
// main loop
   while( loop != 0 ) 
   {
      if(fresh)
	 time1->point_t1 = time(NULL);	// take time point
      fresh = 0;

      if(verbose | debug)
	 printf("testing %lu...", test_num);

      result = primeTest(test_num, debug);		// test call
      if(verbose | debug)
	 printf("%d\n", result); 

      if(result)	// found a prime
      {
	 fresh = 1;
	 time1->point_t2 = time(NULL);	// take time point
	 temp_time = time1->point_t2 - time1->point_t1;
	 if(verbose || debug)
	    printf("time taken: %f\n", temp_time);
      }

      if(limit != 0 && limit == test_num)		// limit check
  	 loop = 0;
      else
	 test_num++;	// increase test number
   }

// print results

   return 0;
}// end Main
