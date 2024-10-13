// /******************************************************************************

// Welcome to GDB Online.
// GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
// C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
// Code, Compile, Run and Debug online from anywhere in world.

// *******************************************************************************/

//Rory Harrington
//R00233458
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dna.h"


// my main with menu 
int menu() {

int option;
  printf ("\nMenu:\n");
  printf ("1. Generate DNASequence\n");
  printf ("2. clear memory\n");
    printf ("3. Exit\n");
  printf ("Enter Option: ");
  scanf ("%d", &option);
  return option;
}
// gets user input 
int main() {
   
    srand (time (NULL)); //generates a random seed

  DNASequence *sequence = NULL;
  int option;
  do
    {
      option = menu ();// display the menu and get user option
      switch (option)
	{
	case 1:
	  if (sequence)
	    {
	      free (sequence);	// Clear memory using  built in C 
	    }
	  sequence = createDNASequence ();
	  for (int i = 0; i <= 20; i++)
	    {
	      char base_type = "ACGT"[rand () % 4];
	      addBase (sequence, base_type);
	    }
	  simulateDNALifecycle (sequence);
	  printf ("\nPress Enter to continue");
	  getchar ();		// user input
	  getchar ();		//  get the  newline 
	  break;
	case 2:
	    if (sequence != NULL){
	        clearDNASequence(sequence);
	        sequence = NULL;
	        printf("\nmemory cleared.");
	    }
	  
	  break;
	case 3 :
	printf ("Exiting the program.Goodbye\n");
	    break;
	default:
	  printf ("Invalid option.Try again.\n");
	}
	
    }
  while (option != 3);

  if (sequence)
    {
      free (sequence);// Deallocate memory
    }

  return 0;
}