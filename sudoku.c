#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>


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

/*
int sudoku_grid[9][9] = {
	{	7, 4, 6,    3, 5, 9,    4, 1, 8	},
	{	4, 5, 8,    1, 4, 7,    2, 3, 9	},
	{	9, 1, 3,    8, 2, 4,    7, 4, 5	},

	{	1, 4, 2,    9, 7, 5,    3, 8, 4	},
	{	3, 9, 4,    2, 4, 6,    1, 5, 7	},
	{	8, 7, 5,    4, 1, 3,    9, 4, 6	},

	{	5, 4, 7,    6, 4, 1,    8, 9, 2	},
	{	6, 8, 9,    7, 4, 2,    5, 4, 1	},
	{	2, 4, 1,    5, 9, 8,    6, 4, 3	}
};
*/
bool check_col(int sudoku_grid[9][9], int column){
	int returner[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	bool result = malloc(sizeof(bool));

	for(int i = 0; i < 9; i++){
		if(1 == sudoku_grid[i][column]){
			returner[0] = 0;
			continue;
		}
		if(2 == sudoku_grid[i][column]){
			returner[1] = 0;
			continue;
		}
		if(3 == sudoku_grid[i][column]){
			returner[2] = 0;
			continue;
		}
		if(4 == sudoku_grid[i][column]){
			returner[3] = 0;
			continue;
		}
		if(5 == sudoku_grid[i][column]){
			returner[4] = 0;
			continue;
		}
		if(6 == sudoku_grid[i][column]){
			returner[5] = 0;
			continue;
		}
		if(7 == sudoku_grid[i][column]){
			returner[6] = 0;
			continue;
		}
		if(8 == sudoku_grid[i][column]){
			returner[7] = 0;
			continue;
		}
		if(9 == sudoku_grid[i][column]){
			returner[8] = 0;
			continue;
		}
	}
	for (int i = 0; i < 9; ++i){
		if(returner[i] != 0){
			result = false;
			return result;
		}
	}
	result = true;
	return true;
}

bool check_row(int sudoku_grid[9][9], int row){
	int returner[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	bool result = malloc(sizeof(bool));

	for (int i = 0; i < 9; ++i){
		if(1 == sudoku_grid[row][i]){
			returner[0] = 0;
			continue;
		}
		if(2 == sudoku_grid[row][i]){
			returner[1] = 0;
			continue;
		}
		if(3 == sudoku_grid[row][i]){
			returner[2] = 0;
			continue;
		}
		if(4 == sudoku_grid[row][i]){
			returner[3] = 0;
			continue;
		}
		if(5 == sudoku_grid[row][i]){
			returner[4] = 0;
			continue;
		}
		if(6 == sudoku_grid[row][i]){
			returner[5] = 0;
			continue;
		}
		if(7 == sudoku_grid[row][i]){
			returner[6] = 0;
			continue;
		}
		if(8 == sudoku_grid[row][i]){
			returner[7] = 0;
			continue;
		}
		if(9 == sudoku_grid[row][i]){
			returner[8] = 0;
			continue;
		}
	}
	for (int i = 0; i < 9; ++i)
	{
		if (returner[i] != 0){
			result = false;
			return result;
		}
	}

	result = true;
	return result;
}
typedef struct
	{
		int sudoku_grid[9][9];
		int row_low_bound;
		int row_high_bound;
		int col_low_bound;
		int col_high_bound;
		int pass;

	} GridStuct;
void* check_grid(void* stuff_from_pthread_create){


	GridStuct* subgrids = stuff_from_pthread_create;
	/*
	int sudoku_grid[9][9],
	int row_low_bound,
	int row_high_bound,
	int col_low_bound,
	int col_high_bound
	*/

	bool result = malloc(sizeof(bool));
	int returner[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	subgrids->pass = 1;
	//printf("%d\n", (GridStuct*) stuff_from_pthread_create->row_low_bound);

	for (int i = subgrids->row_low_bound; i <= subgrids->row_high_bound; ++i)
	{
		for (int j = subgrids->col_low_bound; j <= subgrids->col_high_bound; ++j)
		{
			//printf("%d\n", subgrids->sudoku_grid[i][j]);
			if (1 == subgrids->sudoku_grid[i][j]){
				returner[0] = 0;
			}
			if (2 == subgrids->sudoku_grid[i][j]){
				returner[1] = 0;
			}
			if (3 == subgrids->sudoku_grid[i][j]){
				returner[2] = 0;
			}
			if (4 == subgrids->sudoku_grid[i][j]){
				returner[3] = 0;
			}
			if (5 == subgrids->sudoku_grid[i][j]){
				returner[4] = 0;
			}
			if (6 == subgrids->sudoku_grid[i][j]){
				returner[5] = 0;
			}
			if (7 == subgrids->sudoku_grid[i][j]){
				returner[6] = 0;
			}
			if (8 == subgrids->sudoku_grid[i][j]){
				returner[7] = 0;
			}
			if (9 == subgrids->sudoku_grid[i][j]){
				returner[8] = 0;
			}
		}
	}
	for (int i = 0; i < 9; ++i)
	{
		if (returner[i] != 0){
			//result = false;
			subgrids->pass = 0;

			//return result;
		}
	}

	if(subgrids->pass)
	{
		//subgrids->pass = 1;
		printf("True!\n");

	}
	else
	{
		printf("False!\n");
	}
	//result = true;

	//return result;

}


typedef struct
{
	int *sudoku_grid[9][9];
	int row_col;
	int pass;

} RowColStuct;

int main()
{
	/*
	bool cols_result = check_col(sudoku_grid, 0);
	bool rows_result = check_row(sudoku_grid, 2);
	0, 3, 6
	2, 5, 8


	0 2 0 2
	0 2 3 5
	0 2 6 8

	3 5 0 2
	3 5 3 5
	3 5 6 8

	6 8 0 2
	6 8 3 5
	6 8 6 8

	bool grids_result = check_grid(sudoku_grid, 0, 2, 6, 8);
	printf("%d\n", cols_result);
	printf("%d\n", rows_result);
	printf("%d\n", grids_result);
	*/
	pthread_t grid_threads[9];
	pthread_t row_threads[9];
	pthread_t col_threads[9];



	typedef struct
	{
		int *sudoku_grid[9][9];
		int row_col;
		int pass;

	} RowColStuct;


	// Checking the grids
	GridStuct* subgrids = malloc(sizeof(GridStuct) * 9);
	//subgrids->sudoku_grid = sudoku_grid;
	//subgrids->row_low_bound = 0;
	//subgrids->row_high_bound = 2;
	//subgrids->col_low_bound = 6;
	//subgrids->col_high_bound = 8;

	int row_low_bounds[9] = {0, 0, 0, 3, 3, 3, 6, 6, 6};
	int row_high_bounds[9] = {2, 2, 2, 5, 5, 5, 8, 8, 8};
	int col_low_bounds[9] = {0, 3, 6, 0, 3, 6, 0, 3, 6};
	int col_high_bounds[9] = {2, 5, 8, 2, 5, 8, 2, 5, 8};
	for(int k = 0; k < 9; k++)
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				subgrids[k].sudoku_grid[i][j] = sudoku_grid[i][j];
			}
		}
		subgrids[k].row_low_bound = row_low_bounds[k];
		subgrids[k].row_high_bound = row_high_bounds[k];
		subgrids[k].col_low_bound = col_low_bounds[k];
		subgrids[k].col_high_bound = col_high_bounds[k];
		subgrids[k].pass = 0;
	}






	/*for(int i = 0; i < 9; i++)
	{

	}*/

	/*
	int num_args = argc - 1;

	// thread id:
	pthread_t tids[num_args];
	sum_runner_struct args[num_args];

	for(int i = 0; i < num_args; i++)
	{

		args[i].limit = atoll(argv[i + 1]);

		// create attribures
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, sum_runner, &args[i]);

	}

	for(int i = 0; i < num_args; i++)
	{
		pthread_join(tids[i], NULL);
		printf("Sum is %lld\n", args[i].answer);

	}
	*/
	for (int i = 0; i < 9; ++i)
	{
		pthread_create(&grid_threads[i], NULL, &check_grid, &subgrids[i]);
	}

	for(int i = 0; i < 9; i++)
	{
		pthread_join(grid_threads[i], NULL);

		printf("resuld is %d\n", subgrids[i].pass);

	}
	return 0;
}
