/* 

  assignment5Implementation.cpp - Robot Path Planning using Breadth-First Search in Undirected Unweighted Graphs
   ============================================================================

   This program is for Assignment No. 5, Course 04-630 Data Structures and Algorithms for Engineers. 

   Please refer to the application file - assignment5Application.cpp - for details of the functionality of this program

                                                    
   Author
   ------

   Isaac Coffie, Carnegie Mellon University Africa
  April 01, 2020

*/

 
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>
#include <time.h>
#include <math.h>


#define TRUE 1
#define FALSE 0
#define MAX_MESSAGE_LENGTH 81
#define MAX_BUFFER_SIZE 1024


/* function prototypes go here */

/*A structure to store location details*/
struct location {float time; int x_pos; int y_pos;};

struct key_value_array {int data; };

void print_message_to_file(FILE *fp, char message[]);

/*A function to hide the implementation of adding a record to the list*/
void add_record_to_array(struct key_value_array *keypair_array, struct key_value_array new_val, int index);

/*This function prints the contents of elements in the array*/
void print_sorted_records(FILE *fp, struct location *loc_array, int size);


