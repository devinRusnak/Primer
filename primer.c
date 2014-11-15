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
   double time1;
   double time2;
} time_point;

typedef struct {
   int all_found;
   int twin_found;
   time_t avg_time;
   time_t min_time;
   time_t max_time;
} stats_struct;

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
   long int limit = 0;
   FILE *fd_all, *fd_twin;
   char *limit_char;
   char *output_file;
   char *twin_file;
   time_point *t1, *t2;
   stats_struct *stats;

   memset(&limit_char, 0, sizeof(char)*32);
   memset(&output_file, 0, sizeof(char)*32);
   memset(&twin_file, 0, sizeof(char)*32);
   memset(&t1, 0, sizeof(time_point));
   memset(&t2, 0, sizeof(time_point));
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
  
   printf("\nstarting...\n");
   
// main loop
   while( loop ) 
   {


   }

// print results

   return 0;
}// end Main
