#include "header.h"
#include <map>


/// GENERALIZE THIS!!! 

void Game::cell_dynamics(int size, int x1, int x2, int x3, int t, float p){

	// cout << "CD: " << x1 << " " << x2 << " " << x3 << endl;

	int i = (rand()) / (RAND_MAX/nx);
	int j = (rand()) / (RAND_MAX/ny);
	i %= nx;
	j %= ny;
	int range = 2 * size + 1;
	int this_cell = grid_states[i][j];

	if ((this_cell != x1)){
		return;	
	}

	float u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	map<int, int> types;

	for(int ii = 0; ii < range; ii++){
		for(int jj = 0; jj < range; jj++){
			int cx = (nx + (i + (ii-size))) % nx;
			int cy = (ny + (j + (jj-size))) % ny;
			int cell_type = grid_states[cx][cy];
			types[cell_type] += 1;
		}
	}

	if ((this_cell == x1) && (types[x2] >= t) && (u < p)){
		grid_states[i][j] = x3;
	}
}
