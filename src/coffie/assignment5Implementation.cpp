/* 

   assignment4Implementation.cpp - Text Analysis Using Binary Search Tree
   ============================================================================

   This program is for Assignment No. 4, Course 04-630 Data Structures and Algorithms for Engineers. 

   Please refer to the application file - assignment4Application.cpp - for details of the functionality of this program

      
   File organization
   -----------------

   assignment4.h                  interface file:      
                              contains the declarations required to use the functions that implement the solution to this problem
                              typically, these will include the definitions of the abstract data types used in the implementation

   assignment4Implementation.cpp  implementation file: 
                              contains the definitions of the functions that implement the algorithms used in the implementation
 
   assignment4Application.cpp     application file:    
                              contains the code that instantiates the abstract data types and calls the associated functions
                              in order to effect the required functionality for this application
                                                    
   Author
   ------

   Isaac Coffie, Carnegie Mellon University Africa
  March 17, 2020

*/

 
//include the header file 
#include "assignment5.h"

//this function simply prints a message to file with no complex formatting
void print_message_to_file(FILE *fp, char message[]) {
 
   fprintf(fp,"The message is: %s\n", message);
}


/* A function to add an element of type location to the array
@param loc_array pointer to the location array
@param loc_new a location struct object
@param num_elements a pointer to the number of elements in the array
@returns nothing since it's void
*/
void add_record_to_array(struct key_value_array *keypair_array, struct key_value_array new_val, int index){

	//dereference the num_elements pointer and insert the new location record into the array index
	keypair_array[index] = new_val;
	//*num_elements +=1; //we then increment the number of elements in the array for successive insertion
}

/* A function to print the content of an array
@param loc_array pointer to the location array
@param size the size or number of elements in the array
@param fp a pointer to the file output stream
@returns nothing since it's void
*/
void print_sorted_records(FILE *fp, struct location *loc_array, int size){

	for(int i=0; i < size; i++){

		//finally print this new unique location to the output file
		float t = loc_array[i].time;
		int x = loc_array[i].x_pos;
		int y = loc_array[i].y_pos;
		fprintf(fp, "%6.3f %4d %4d \n", t, x, y);
	}
}
