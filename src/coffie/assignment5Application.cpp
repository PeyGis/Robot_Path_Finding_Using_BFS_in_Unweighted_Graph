/* 

    assignment5Application.cpp - Robot Path Planning using Breadth-First Search in Undirected Unweighted Graphs
   ==============================================================================================================

   Author
   ===========================================================================================

   Isaac Coffie, MSIT Carnegie Mellon University Africa
   April 01 2020


   The functionality of the program is defined as follows.
   ============================================================================================

   The purpose of this assignment is to design a program to determine the shortest path between a robot’s initial position and a destination
position using a BFS algorithm on a map
   
   This data for the robot's map environment is stored in an input file (input.txt) with a number of test cases 
   For each test case, process the map and the resulting solution is written to the output.txt file
   
  Format of the input and output file are defined below
  =============================================================================================

   Input file
   ----------
	2
	4 4
	2 0 0 0 
	0 1 1 0 
	0 0 0 0 
	0 0 0 3
	10 10
	0 0 0 0 0 0 0 0 0 0
	0 2 0 0 0 0 0 0 0 0
	0 0 0 0 0 0 0 0 0 0
	0 0 0 1 1 1 1 1 1 0
	0 0 0 1 1 1 1 0 0 0
	0 0 0 1 1 1 1 0 0 0
	0 0 0 0 0 1 1 0 0 0
	0 1 1 1 0 0 0 0 0 0
	0 1 1 1 0 0 0 0 3 0
	0 0 0 0 0 0 0 0 0 0 


   Output file
   ------
   The output file is formatted in the following way:

   first line is my Andrew ID
   The remaining line containts the shortest path route from the start to goal indices of the map

   coffie
	Scenario 1
	@       
	* # #   
	*       
	* * * $ 

	Scenario 2
                    
	  @                 
	  *                 
	  *   # # # # # #   
	  *   # # # #       
	  *   # # # #       
	  * * * * # #       
	  # # # *           
	  # # # * * * * $   



   Solution Strategy / Summary of the Algorithm
   =================================================================================
   I developed some helper functions to help address the problem
   Howerver, a huge portion of this application involves transforming the robot's map environment into a graph
   To do so, I implemented a row-major storage mapping function to map each cell in the map to a graph's vertex
   I also did the reverse to get the cell values when given a vertex number. This was particularly helping to help me identify th paths traversed by the robot

   I also adapted the find_path algorithm, which makes a recursive breadth first search traversal on the graph, to mark the indices of the paths with a static number 4

   When printing out the map in the correct aspect ratio, I used two loops to help build the correct output 


   
   Test Strategy
   =================================================================================

   This program has been tested with variety of test data sets that reflect all valid conditions, including boundary conditions:

	#TEST 1: input file with empty content
			
			INPUT:

			
			EXPECTED OUTPUT:
			no content in the output file other than my AndrewID

	#TEST 2: input file with one scenario
			
			1
			4 4
			2 0 0 0 
			0 1 1 0 
			0 0 0 0 
			0 0 0 3

			EXPECTED OUTPUT:
				
					coffie
					Scenario 1
					@       
					* # #   
					*       
					* * * $ 

	#TEST 3: input file with more than one test scenario
			

	#TEST 4: - test scenario which contains no clear path from start to goal

		INPUT:
		1
		3 3
		2 0 1 
		0 1 1 
		0 1 3

		EXPECTED OUTPUT:

			coffie
			Scenario 1
			No path from (0 0) to (2 2)
			@   # 
			  # # 
			  # $ 

	#TEST 5: test scenario with more than 100 columns and rows.... Boundary case
		
		INPUT:
		1
		102 102
			

		EXPECTED OUTPUT: 
		coffie
		Input file is greater than the required dimension (100 x 100)


	#TEST 6: map environment without valid start and goal position
		
		INPUT:
			4 4
			0 0 0 0 
			0 1 1 0 
			0 0 0 0 
			0 0 0 1


		EXPECTED OUTPUT: 
		coffie
		Robot does not have either start or goal position

	#TEST 7: map environment with all obstacles
		
		INPUT:
			4 4
			0 0 0 0 
			0 1 1 0 
			0 0 0 0 
			0 0 0 1


		EXPECTED OUTPUT: 
		coffie
		Robot does not have either start or goal position


    Time Complexity = g(n) = O(N^2)
   =================================================================================
   The order of complexity of this program is a N^2
   The worst case number of test cases we can have is N
   Also, within each test case, we use 2 for loops to build the map which takes N^2
   The breadth first search algorithm also takes O(V + E) where V is the number of vertices and E being the number of edges
   
   We also perform some constant operations in this loop such as if statements, incrementing counter, printing to file

   So, Overall, our time complexity ~  N + (N^2) + (V+E) + K
   Therefore the overall worst case time complexity is O(N^2)


   File organization -    This segement of comment is adopted from Prof David Vernon
   -----------------

   assignment5.h                  interface file:      
                              contains the declarations required to use the functions that implement the solution to this problem
                              typically, these will include the definitions of the abstract data types used in the implementation
	
  graph.h				The Graph implementation file header

   assignment4Implementation.cpp  implementation file: 
                              contains the definitions of the functions that implement the algorithms used in the implementation

    graphImplementation.cpp  implementation file: 
                              contains the definitions of the functions that implements the BFS
 
   assignment5Application.cpp     application file:    
                              contains the code that instantiates the abstract data types and calls the associated functions
                              in order to effect the required functionality for this application

*/
 
#include "graph.h"

bool alternative_map_format = true; // flag to choose different map format; not relevant here

int main() {

   bool debug = false;
   FILE *fp_in, *fp_out;
   int i;

   graph g;
   bool directed = false;
   int robot_x, robot_y;
   int goal_x,  goal_y;
   int robot;
   int goal;
   int map_dimension_x, map_dimension_y;
   int scenario; 
   int number_of_scenarios;
   int map[MAX_N][MAX_M];

   if ((fp_in = fopen("../data/input.txt","r")) == 0) {
	  printf("Error can't open input input.txt\n");
     getchar();
     exit(0);
   }

   if ((fp_out = fopen("../data/output.txt","w")) == 0) {
	  printf("Error can't open output output.txt\n");
     getchar();
     exit(0);
   }

   if (debug) printf("Robot Path Finding Breadth First Search Path Planning\n");

   fprintf(fp_out, "coffie\n");

   scenario = 0;

   fscanf(fp_in, "%d",&number_of_scenarios);

   for (i=0; i<number_of_scenarios; i++) {
      
      fprintf(fp_out, "Scenario %d\n",i+1);

      fscanf(fp_in, "%d %d",&map_dimension_x, &map_dimension_y); // read the dimensions of the map

	  //if the dimensions are greater than the required, skip this iteration
	  if(map_dimension_x > MAX_N || map_dimension_y > MAX_M){
		  fprintf(fp_out, "Input file (%d x %d) is greater than the required dimension (100 x 100)\n", map_dimension_x, map_dimension_y);
		  read_map_v2(fp_in, map_dimension_x, map_dimension_y);
		  reset_start_and_destination_coordinates(&robot_x, &robot_y, &goal_x, &goal_y);
		  fprintf(fp_out, "\n"); //blank line after each scenario
		  continue;
	  }
      
      read_map(fp_in,   map, map_dimension_x, map_dimension_y);  // read the input file and initialize the map array

	  map_to_graph(&g, directed, map, map_dimension_x, map_dimension_y);  // convert the array map to a graph
            
      /* get the robot and goal coordinates from the map, indicated by values 2 and 3. respectively*/
	  //if the robot has valid start and goal cell, do a bfs, otherwise, print error 

	  if(get_start_and_destination_coordinates(map, map_dimension_x, map_dimension_y, &robot_x, &robot_y, &goal_x, &goal_y)){

		  //get the vertex number for the robot coordinates (using the row major mapping function)	
		  robot = get_graph_vertex_number(map_dimension_y, robot_x, robot_y);            
		  goal  = get_graph_vertex_number(map_dimension_y, goal_x,  goal_y);       

	     
		  printf("Robot and goal positions: (%d %d), (%d %d)\n", robot_x, robot_y, goal_x, goal_y);
		  printf("Robot and goal vertex number: %d %d\n", robot, goal);

		  printf("Robot cordinates: %d %d\n", convert_vertex_to_map_x_cordinates(map_dimension_y, robot), convert_vertex_to_map_y_cordinates(map_dimension_y, robot)); 
	  
		  printf("Goal cordinates: %d %d\n", convert_vertex_to_map_x_cordinates(map_dimension_y, goal), convert_vertex_to_map_y_cordinates(map_dimension_y, goal)); 
	 
		  //Do breadth first traversal

		  if (!find_path_on_map(&g, robot, goal, map, map_dimension_y)) {                                                                                                // check to see whether there is a path and print a message if not
			 fprintf(fp_out, "No path from (%d %d) to (%d %d)\n", robot_x, robot_y, goal_x, goal_y);
		  }

			//print_map(fp_out, map, map_dimension_x, map_dimension_y);
	  } else{
			fprintf(fp_out, "Robot does not have either start or goal position\n");
	  }

	  print_map(fp_out, map, map_dimension_x, map_dimension_y);

	  reset_start_and_destination_coordinates(&robot_x, &robot_y, &goal_x, &goal_y);

	  fprintf(fp_out, "\n"); //blank line after each scenario
   }

   fclose(fp_in);
   fclose(fp_out);
}
