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

typedef struct {
   long p1;
   long p2;
   long p3;
   long p4;
} prime_holder;

/* PrimeTest() - 
 *
 * @param test_num - assuming that test_num is always odd. not checking if even
 * @return - 0 if not prime, 1 if prime
 */
int primeTest(long test_num)
{   
   int i;
   int roof = sqrt(test_num) + 1;   	// max number needed to test agasint

   if(test_num == 1 || test_num == 3)	// trivial cases
      return 1;
   if(test_num % 2 == 0)
      return 0; 

   for( i = 3; i <= roof; i += 2 )	// check odd numbers from 3
   {
      if( test_num % i == 0 )		// test
	return 0;	// not prime
   }
   return 1;		// prime
}

/* addToHolder() - adds a prime to the array struct and shifts it
 *
 * @param prime - prime number to be added
 * @param prime_holder - struct where primes are held
 */
int addToHolder(long prime, prime_holder *phold)
{
  long temp1 = phold->p1;
  long temp2 = phold->p2;
  phold->p1 = prime;
  phold->p2 = temp1;
  temp1 = phold->p3;
  phold->p3 = temp2;
  phold->p4 = temp1;

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
   int index = 0;			// flag
   int cmd_line = 0;			// count
   int counter = 0;			// count
   int twin_counter = 0;		// count
   int trip_counter = 0;		// count
   int quad_counter = 0;		// count
   int cos_counter = 0;			// count
   int sexy_counter = 0;		// count
   int loop = 1;			// flag
   int debug = 0;			// flag
   int verbose = 0;			// flag
   int result = 0;			// number
   int fresh = 1;			// flag
   double temp_time = 0.0;		// number
   long test_num = 1;			// test_number
   long limit = 0;			// max_test_number
   time_point *time1, *time2;		// struct
   stats_struct *stats;			// struct
   prime_holder holder;			// struct
   FILE *fd_all, *fd_twin, *fd_trip, *fd_quad, *fd_cos, *fd_sexy; // file discriptors 
   char *limit_char, *output_file, *twin_file, *trip_file, *quad_file, *cos_file, *sexy_file, *buffer; // strings

   memset(&limit_char, 0, sizeof(char)*32);
   memset(&output_file, 0, sizeof(char)*32);
   memset(&twin_file, 0, sizeof(char)*32);
   memset(&trip_file, 0, sizeof(char)*32);
   memset(&quad_file, 0, sizeof(char)*32);
   memset(&cos_file, 0, sizeof(char)*32);
   memset(&sexy_file, 0, sizeof(char)*32);
   memset(&buffer, 0, sizeof(char));
   memset(&time1, 0, sizeof(time_point));
   memset(&time2, 0, sizeof(time_point));
   memset(&stats, 0, sizeof(stats_struct));
 //  memset(&holder, 0, sizeof(prime_holder));


// parse command line arguments
   opterr = 0;

   while( (cmd_line = getopt(argc, argv, "dl:o:t:r:q:c:s:vh")) != -1)
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

   	 case 'r':	// file to write triple primes to
	    trip_file = optarg;
	 break;

	 case 'q':	// file to write quad primes to
	    quad_file = optarg;
         break;

	 case 'c':	// file to write cousin primes to
	    cos_file = optarg;
	 break;

	 case 's':	// file to write sexy primes to
	   sexy_file = optarg;
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
	    printf("-r:\tWrites all triple primes to filename given\n");
	    printf("-q:\tWrites all quadtruple primes to filename given\n");
	    printf("-c:\tWrites all cousin primes to filename given\n");
            printf("-s:\tWrites all sexy primes to filename given\n");
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

   if(output_file != 0) 		// all prime file
      printf("...writting all primes to file:\t%s\n", output_file);
   else {
      output_file = "all_primes.txt";
      printf("...writting all primes to file:\t\tall_primes.txt\n");
   }

   if(twin_file != 0) 			// twin prime file
      printf("...writting all twin primes to file:\t%s\n", twin_file);
   else {
      twin_file = "twin_primes.txt";
      printf("...writting all twin primes to file:\ttwin_primes.txt\n");
   }

   if(trip_file != 0) 			// triple prime file
      printf("...writting all triple primes to file:\t%s\n", trip_file);
   else {
      trip_file = "triple_primes.txt";
      printf("...writting all triple primes to file:\ttriple_primes.txt\n");
   }

   if(quad_file != 0) 			// quadtruple prime file
      printf("...writting all quad primes to file:\t%s\n", quad_file);
   else {
      quad_file = "quadtruple_primes.txt";
      printf("...writting all quad primes to file:\tquadtruple_primes.txt\n");
   }

   if(cos_file != 0) 			// cousin prime file	
      printf("...writting all cousin primes to file:\t%s\n", cos_file);
   else {
      cos_file = "cousin_primes.txt";
      printf("...writting all cousin primes to file:\tcousin_primes.txt\n");
   }

   if(sexy_file != 0)
      printf("...writting all sexy primes to file:\t%s\n", sexy_file);
   else {
      sexy_file = "sexy_primes.txt";
      printf("...writting all sexy primes to file:\tsexy_primes.txt\n"); 
   }

// open files for writting
   fd_all = fopen(output_file, "w+");
   if( fd_all == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return -1;	// terminate program
   }

   fd_twin = fopen(twin_file, "w+");
   if( fd_twin == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return -2;	// terminate program
   }
   fd_trip = fopen(trip_file, "w+");
   if( fd_trip == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return -3;	// terminate program
   }
   fd_quad = fopen(quad_file, "w+");  
   if( fd_quad == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return -4;	// terminate program
   }
   fd_cos = fopen(cos_file, "w+");
   if( fd_cos == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return -5;	// terminate program
   }
   fd_sexy = fopen(sexy_file, "w+");
   if( fd_sexy == NULL )
   {
      printf("file error: %s.\n\n", strerror(errno));
      return -6;
   }

   loop = 1;
   fresh = 1;
   printf("starting...\n");

   
// main loop
   while( loop )
   {
   //if( fgets(buffer, 8, stdin) != NULL && strcmp(buffer, "q") == 0 ) // cancle loop on 'q' input
   //	loop = 0;

/*
      if(fresh)
	 time1->point_t1 = time(NULL);	// take time point
      fresh = 0;
*/
      if(verbose || debug)
	 printf("testing %lu...", test_num);

      result = primeTest(test_num);			// test call

      if(verbose || debug)
	 printf("%d\n", result); 

      if(result)	// found a prime
      {
	// take time point here!!

         counter++;
	 if( (counter%12) == 0)
	    fprintf(fd_all, "\n");

	 fprintf(fd_all, "%lu,\t", test_num);		// write to all prime file
         if(debug)
	    printf("wrote to all primes\n");
         if(verbose)
	    printf("found a prime\n");

	 addToHolder(test_num, &holder);		// add to prime array struct
         if(debug)
            printf("added to array\n");

//	 fresh = 1;
//	 time1->point_t2 = time(NULL);	// take time point
//	 temp_time = time1->point_t2 - time1->point_t1;
//	 if(verbose || debug)
//	    printf("time taken: %f\n", temp_time); 

         if(test_num > 2 && (holder.p2 == (test_num - 2)) )
         {
	    twin_counter++;
	    if(twin_counter%5 == 0)
  	      fprintf(fd_twin, "\n");

            if(verbose)
	      printf("twin prime found\n");

	    fprintf(fd_twin, "( %lu, %lu )\t", (test_num-2), test_num);
         } // end twin
         
	 if(test_num > 10 && (holder.p3 == (test_num - 6))
		&& ( (holder.p2 == (test_num - 2)) || (holder.p2 == (test_num - 4)) ) )
         {
	    trip_counter++;
            if(trip_counter%3 == 0)
               fprintf(fd_trip, "\n");

	    if(verbose)
	       printf("triple prime found\n");

	    fprintf(fd_trip, "( %lu, %lu, %lu )\t", holder.p3, holder.p2, holder.p1);
         } // end triple
         
	 if( test_num > 12 && (holder.p2 == (test_num - 2)) && (holder.p3 == (test_num - 6))
	   	&& (holder.p4 == (test_num - 8)) )
	 {
	    quad_counter++;
 	    if(quad_counter%2 == 0)
	      fprintf(fd_quad, "\n");

	    if(verbose)
	      printf("quadruple prime found\n");

	    fprintf(fd_quad, "( %lu, %lu, %lu, %lu )\t", holder.p4, holder.p3, holder.p2, holder.p1);
 	 } // end quadruple

         if( (holder.p2 == (test_num - 4)) )
         {
 	    cos_counter++;
            if(cos_counter%4 == 0)
	      fprintf(fd_cos, "\n");

	    if(verbose)
	      printf("cousin prime found\n");

	    fprintf(fd_cos, "( %lu, %lu )\t", holder.p2, holder.p1);
         } // end cousin

	 if( (holder.p2 == (test_num - 6)) )
 	 {
	    sexy_counter++;
	    if(sexy_counter%6 == 0)
	      fprintf(fd_sexy, "\n");

	    if(verbose)
	      printf("sexy prime found\n");

	    fprintf(fd_sexy, "( %lu, %lu )\t", holder.p2, holder.p1);
	 } // end sexy
      }
      if( limit != 0 && test_num >= limit )
	 loop = 0;
      else 
	 test_num++;	// increase test number
      
   }//end main loop

// print results

   fclose(fd_all);
   fclose(fd_twin);
   printf("...exiting\n");
   return 0;
}// end Main
