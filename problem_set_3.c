#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

/*

for columns 1 to 9
	checkCol

for rows 1 to 9
	checkRow

[0, 2], [3, 5], [6, 8] * [0, 2], [3, 5], [6, 8]
for i in range_1
	for j in range_2
		checkGrid(i, j)


checkCol(a)
	check items in col a

checkRow(a)
	check items in row a

checkGrid(row_range, col_range)

	for i in row_range
		for j in col_range
			check value



bool array = [false, ...]
if value > 9 or < 0
	error
	print qwadrant name send function
if !array[slot]
	array[slot] = true
else
	error, because duplicate
	print quadrant name send function

have a list of quadrants and send it into loop through it at same time as array
*/
typedef struct
{
	int low_bound;
	int high_bound;
} Range;
// https://stackoverflow.com/questions/20712572/how-to-ignore-whitespaces-in-fscanf
// setup as 2d array
int sudoku_grid[9][9] = {
	{	7, 2, 6,    3, 5, 9,    4, 1, 8	},
	{	4, 5, 8,    1, 6, 7,    2, 3, 9	},
	{	9, 1, 3,    8, 2, 4,    7, 6, 5	},

	{	1, 6, 2,    9, 7, 5,    3, 8, 4	},
	{	3, 9, 4,    2, 8, 6,    1, 5, 7	},
	{	8, 7, 5,    4, 1, 3,    9, 2, 6	},

	{	5, 3, 7,    6, 4, 1,    8, 9, 2	},
	{	6, 8, 9,    7, 3, 2,    5, 4, 1	},
	{	2, 4, 1,    5, 9, 8,    6, 7, 3	}
};
// added row_, col_, subgrid_ to prevent enum conflict
enum quadrants_rows_cols{top_left,
						top_middle,
						top_right,
						middle_left,
						middle_middle, middle_right,
						bottom_left,
						bottom_middle,
						bottom_right,
						row_,
						col_,
						subgrid_};

char* getQuadrantName(int quadrant)
{
	char* quadrant_name = malloc(sizeof(char) * 20);

	switch(quadrant)
	{
		case top_left:
		{
			memcpy(quadrant_name, "top_left", sizeof(char) * 9);
			break;
		}
		case top_middle:
		{
			memcpy(quadrant_name, "top_middle", sizeof(char) * 11);
			break;
		}

		case top_right:
		{
			memcpy(quadrant_name, "top_right", sizeof(char) * 10);
			break;
		}
		case middle_left:
		{
			memcpy(quadrant_name, "middle_left", sizeof(char) * 12);
			break;
		}
		case middle_middle:
		{
			memcpy(quadrant_name, "middle_middle", sizeof(char) * 14);
			break;
		}
		case middle_right:
		{
			memcpy(quadrant_name, "middle_right", sizeof(char) * 13);

			break;
		}
		case bottom_left:
		{
			memcpy(quadrant_name, "bottom_left", sizeof(char) * 12);

			break;
		}
		case bottom_middle:
		{
			memcpy(quadrant_name, "bottom_middle", sizeof(char) * 14);

			break;
		}
		case bottom_right:
		{
			memcpy(quadrant_name, "bottom_right", sizeof(char) * 13);
			break;

		}
		default:
		{
			break;
		}
	}
	return quadrant_name;
}
char* getArrayKind(int array_kind)
{
	char* array_kind_name = malloc(sizeof(char) * 20);

	switch(array_kind)
	{
		case row_:
		{
			memcpy(array_kind_name, "row_", sizeof(char) * 5);
			break;
		}
		case col_:
		{
			memcpy(array_kind_name, "col_", sizeof(char) * 5);
			break;
		}

		case subgrid_:
		{
			memcpy(array_kind_name, "subgrid_", sizeof(char) * 9);
			break;
		}

		default:
		{
			break;
		}
	}
	return array_kind_name;
}

typedef struct {

	/*
	bool __rows;
	bool __columns;
	bool __subgrids;
	int** _subgrids;
	int** _cols;
		*/
	int** _rows;
	int * row_col_or_sub_grid;
	int array_kind;
	int array_number;
	int * sudoku_check_grid;
	// each threads reads a subgrid, col, or row
	// each thread writes to rows, columns, subgrids
	// loop through each subgrid and map the ith subgrid to the ith subgrid checking function

} InfoToPassToChildThread;


void* check(//int* row_col_or_sub_grid, int array_kind, int array_number, int* sudoku_check_grid
			//InfoToPassToChildThread * master_struct
			void * arg
			)
{
	// lock.aquire()
	// array_kind is the kind of array: row array, col array, subgrid array
	// array_number is the ith arrray from array_kind
	// putting 1-9 into 0-8 slots

	InfoToPassToChildThread * master_struct = arg;
	printf("Creating the master_struct\n" );

	bool result = malloc(sizeof(bool));
	bool values_to_check[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for(int i = 0; i < 9; i++)
	{

		//int index = master_struct->_rows[master_struct->array_number][i];

		for(int j = 0 ; j < 9; j++)
		{
			for(int k = 0; k < 9; k ++)

				printf("%i ", master_struct->_rows[j][k]);
			printf("------\n");
		}
		printf("%i\n", index);
		printf("Working...1\n" );
		//printf("value = %i\n", row_col_or_sub_grid[i]);

		/*if(!values_to_check[ index - 1 ])
		{
			//printf("add value = %i\n", row_col_or_sub_grid[i]);
			values_to_check[ index - 1 ] = 1;
			printf("Working...2\n" );
		}

		else
		{
			// items has been seen already, so this array_number of array_kind is invalid

			if(master_struct->array_kind != subgrid_)
			{
				printf("array kind: %s array number %i is invalid\n", getArrayKind(master_struct->array_kind),
				 master_struct->array_number);
				// free after printing
				// lock.release()
				//return false;
				result = false;
				pthread_exit((void*)result);
			}
			else
			{
				printf("%s subgrid is invalid\n", getQuadrantName(master_struct->array_number));
				// lock.release()
				//return false;
				result = false;
				pthread_exit((void*)result);

			}

		}*/
	}
	printf("Finished!!");

	// set a true or a false to the ith row in the bool slot of row_col_or_sub_grid
	//printf("--------\n");
	// lock.release()
	//return true;
	result = true;
	pthread_exit((void*)result);

}
//int** subgrids
//int** cols
//int** rows
//struct



int main()
{
	// subgrid horizontal direction
	// 0 1 2, 9 10 11 18 19 20

	// cols
	// 0, 9, 18, 27 36 45 54 63 72
	// 1, 10, 19, 28 37 46 55 64 73
	// .
	//	.
	//	.
	//	.
	// 8 17 26 62 44 53 62 71 80

	// row
	/*
	zip cols
	*/
	/*
	InfoToPassToChildThread* master_struct = malloc(sizeof(InfoToPassToChildThread));
	master_struct->_rows = malloc(9);
	*/



	int* sudoku_check_grid = malloc(sizeof(int) * 81);
	memcpy(sudoku_check_grid, sudoku_grid, sizeof(int) * 81);

	Range* zero_two = malloc(sizeof(Range));
	Range* three_five = malloc(sizeof(Range));
	Range* six_eight = malloc(sizeof(Range));

	zero_two->low_bound = 0;
	zero_two->high_bound = 3;

	three_five->low_bound = 3;
	three_five->high_bound = 6;

	six_eight->low_bound = 6;
	six_eight->high_bound = 9;
	Range** ranges = malloc(sizeof(Range*) * 3);
	ranges[0] = zero_two;
	ranges[1] = three_five;
	ranges[2] = six_eight;

	//int offset = 27;
	//int multiplier = 1;
	//int scale = 0;
	int** subgrids = malloc(sizeof(int*) * 9);

	int ith_subgrid = 0;
	/*
		for range_i in ranges
			for range_j in ranges
				ij
	*/
	for(int x = 0; x < 3; x++)
	{
		// make an array of scale values
		for(int i = 0; i < 3; i++)
		{
			// generate index locations of items in each 3x3 grid

			int* subgrid = malloc(sizeof(int) * 9);

			int count = 0;

			//scale = x * 27; // 0 3 times 27 3 times 54 3 times
			// needs to start
			//printf("start\n");
			for(int k = ranges[x]->low_bound; k < ranges[x]->high_bound; k++)
			{

				for(int l = ranges[i]->low_bound; l < ranges[i]->high_bound; l++)
				{
					subgrid[count] = sudoku_grid[k][l];//l + scale;
					//printf("%i\n", sudoku_grid[k][l]);
					//printf("%i count = %i\n", l+scale, count);
					count++;

				}

				//printf("\n");
				//scale += 9;
			}

			subgrids[ith_subgrid] = subgrid;
			//printf("end\n");
			ith_subgrid++;
			//printf("end of subgrid %i\n", i+x);
			//scale += 27;

		}
		//printf("end of subgrid row %i-------\n", x+1);
	}

	for(int i  = 0; i < 3; i++)
	{
		free(ranges[i]);
	}
	free(ranges);

	int** cols = malloc(sizeof(int*) * 9);

	//printf("cols\n");
	for(int i = 0; i < 9; i++)
	{
		int* col = malloc(sizeof(int) * 9);
		for(int j = 0; j < 9; j++)
		{
			if(j % 3 == 0)
			{
				//printf("\n");
			}
			//printf("%i\n", sudoku_grid[j][i]);
			col[j] = sudoku_grid[j][i];
			//col[j] = i + (j * 9);
			//printf("%i\n", i + (j * 9));
		}
		cols[i] = col;
		//printf("---------\n");
	}
	
	InfoToPassToChildThread* master_struct = malloc(sizeof(InfoToPassToChildThread));

	master_struct->_rows = malloc(sizeof(int*) * 9);
	//memset(master_struct->_rows, 0, sizeof(int*) * 9);
	//printf("rows\n");
	for(int i = 0; i < 9; i++)
	{
		int* row = malloc(sizeof(int) * 9);
		for(int j = 0; j < 9; j++)
		{
			if(j % 3 == 0)
			{
				//printf("\n");
			}
			//printf("%i\n", sudoku_grid[i][j]);
			row[j] = sudoku_grid[i][j];
			//row[i] = i + (j * 9);
			//printf("%i\n", i + (j * 9));
		}
		master_struct->_rows[i] = row;
		//printf("--------\n");
	}

	//exit(1);

	master_struct->array_kind = subgrid_;

	//master_struct->sudoku_check_grid = malloc(sizeof(sudoku_check_grid));
	//memcpy(master_struct->sudoku_check_grid, sudoku_check_grid, sizeof(sudoku_check_grid));

	//master_struct->_rows = malloc(9);


	pthread_t subgrid_thread[9];
	pthread_t row_thread;
	pthread_t col_thread;

	int passes = 0;
	printf("checking subgrids\n");
	/*
	InfoToPassToChildThread* master_struct = malloc(sizeof(InfoToPassToChildThread));
	master_struct->_rows = malloc(9);
	*/
			bool *result;

	for(int i = 0; i < 9; i++)
	{
		bool pass;
		//printf("foo3\n");

		//bool pass = check(subgrids[i], subgrid_, i, sudoku_check_grid);
		//master_struct->row_col_or_sub_grid = malloc(sizeof(int)*9);
		//printf("foo1\n");
		//memcpy(master_struct->row_col_or_sub_grid, subgrids[i], sizeof(int)*9);
		

		master_struct->array_number = i;
		//printf("foo2\n");
		pthread_create(&subgrid_thread[i], NULL, &check, &master_struct);
		printf("foo\n");
		if(pass)
		{
			//printf("%i\n", pass);
			passes++;

		}
		pthread_join(subgrid_thread[0],(void**)&result);
		printf("%i\n", (int) *result);

	}
	
	exit(1);
	/*
	printf("\nchecking rows\n");
	for(int i = 0; i < 9; i++)
	{
		bool pass = check(rows[i], row_, i, sudoku_check_grid);
		if(pass)
		{
			//printf("%i\n", pass);
			passes++;

		}
	}

	printf("\nchecking columns\n");
	for(int i = 0; i < 9; i++)
	{
		bool pass = check(cols[i], col_, i, sudoku_check_grid);
		if(pass)
		{
			//printf("%i\n", pass);
			passes++;

		}
	}
	if(passes == 27)
	{
		printf("grid is valid\n");
	}
	*/
	/*
	for all 81 points, make 1 modification that will ensure the grid is invalid
		the grid should be invalid in 3 places for each change
	if there is 1 round such that 3 mistakes are not caught
		the index values for the rows, columns, subgrids were not calculated correctly
	*/

	return 0;
}
