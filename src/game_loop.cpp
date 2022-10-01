// main game loop
#include "header.h"

Game::Game(){
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
	// SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	grid_states.resize(nx, vector<int>(ny, 0));
}

Game::~Game(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::game_loop(){

	// initialize seed
	srand(time(NULL));

	SDL_Event event;

	int x_mouse, y_mouse;
	int x_cell, y_cell;
	int n_updates_per_frame = 600;

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	// SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	uint32_t *textureBuffer = new uint32_t[width * height];


	int frame = 0;
	
	while(!(event.type == SDL_QUIT)){

		frame++;

		SDL_Delay(0);
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT) return;

		// MOVE ALL THIS LOGIC TO SEPARATE FILE ??? 

		// use tab to cycle through cell types
		if(event.type == SDL_KEYDOWN){
			key_presses(event);
		}

		// add cell type at cursor
		if(event.type == SDL_MOUSEBUTTONDOWN){
			SDL_GetMouseState(&x_mouse, &y_mouse);
			x_cell = x_mouse / cell;
			y_cell = y_mouse / cell;
			for(int ii = 0; ii < range; ii++){
				for(int jj = 0; jj < range; jj++){
					int cx = (nx + (x_cell + (ii - brush_size))) % nx;
					int cy = (ny + (y_cell + (jj - brush_size))) % ny;
					grid_states[cx][cy] = cell_type;
				}
			}
		}

		for(int i = 0; i < n_updates_per_frame; i++){
			cell_update();
		}

		SDL_RenderClear(renderer);

		// assign values to texture buffer
		for (int i = 0; i < nx; i++){
			for (int j = 0; j < ny; j++){
				for (int x = 0; x < cell; x++){
					for (int y = 0; y < cell; y++){

						int rx = i * cell + x;
						int ry = j * cell + y;

						switch(grid_states[i][j]){ // REPLACE THIS WITH A LOOP
							case 1: // trees
							textureBuffer[(ry * width) + rx] = 0xFF387D1A;
							break;

							case 2: // water
							textureBuffer[(ry * width) + rx] = 0xFF167878;
							break;

							case 3: // grass
							textureBuffer[(ry * width) + rx] = 0xFF81B830;
							break;

							case 4: // wet earth
							textureBuffer[(ry * width) + rx] = 0xFF453A2E;
							break;

							case 5: // swamp
							textureBuffer[(ry * width) + rx] = 0xFF1F5E43;
							break;

							case 6: // deep water
							textureBuffer[(ry * width) + rx] = 0xFF136464;
							break;

							case 7: // dense forest
							textureBuffer[(ry * width) + rx] = 0xFF2D6514;
							break;

							case 8: // fire
							textureBuffer[(ry * width) + rx] = 0xFFFFAD14;
							break;

							case 9: // deeper water
							textureBuffer[(ry * width) + rx] = 0xFF124949;
							break;

							case 10: // snow
							textureBuffer[(ry * width) + rx] = 0xFFB1A89F;
							break;

							case 11: // town
							textureBuffer[(ry * width) + rx] = 0xFF78381A;
							break;

							case 12: // sand
							textureBuffer[(ry * width) + rx] = 0xFFAA9A83;
							break;

							case 13: // flower
							textureBuffer[(ry * width) + rx] = 0xFFFF60A0;
							break;
							
							default:
							textureBuffer[(ry * width) + rx] = 0xFF63513E;

						}

						// // grid borders
						// if ((x == 0) || (x == cell-1) || (y == 0) || (y == cell-1)){
						// 	textureBuffer[(ry * width) + rx] = 0xFF33211E;
						// }
					}
				}
			}
		}

		SDL_UpdateTexture(texture, NULL, textureBuffer, width * sizeof(uint32_t));
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

	}
}