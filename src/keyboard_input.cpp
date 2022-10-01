#include "header.h"

void Game::key_presses(SDL_Event &event){

	switch(event.key.keysym.sym){

		// LOGIC FOR KEY PRESSES
		case 9: // TAB
		cell_type += 1;
		cell_type = cell_type % n_types;
		cout << "Switching to: " << cell_types[cell_type] << endl;
		break;

		case 48: // 0
		brush_size = 0;
		range = 2 * brush_size + 1;
		cout << "Setting brush size: " << brush_size << endl;
		break;

		case 49: // 1
		brush_size = 1;
		range = 2 * brush_size + 1;
		cout << "Setting brush size: " << brush_size << endl;
		break;

		case 50: // 2
		brush_size = 2;
		range = 2 * brush_size + 1;
		cout << "Setting brush size: " << brush_size << endl;
		break;

		case 51: // 3
		brush_size = 3;
		range = 2 * brush_size + 1;
		cout << "Setting brush size: " << brush_size << endl;
		break;

		case 114: // R
		fill(grid_states.begin(), grid_states.end(), vector<int>(height,0));
		break;

		default:
		cout << event.key.keysym.sym << endl;
		break;
	}
}