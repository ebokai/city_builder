// main game loop
#include "header.h"

Game::Game(){
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
	//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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
	int cell_type = 1;
	int n_updates_per_frame = 500;

	const char* cell_types[13] = { "Earth", "Trees", "Water", "Grass", "Mud", "Swamp", "Sea", "Forest", "Fire", "Ocean", "Snow", "Town", "Sand"};

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	uint32_t *textureBuffer = new uint32_t[width * height];

	int frame = 0;
	
	while(!(event.type == SDL_QUIT)){

		frame++;

		SDL_Delay(0);
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT) return;

		// use tab to cycle through cell types
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == 9){
				cell_type += 1;
				cell_type = cell_type % n_types;
			}
			cout << "Switching to: " << cell_types[cell_type] << endl;
		}

		// add cell type at cursor
		if(event.type == SDL_MOUSEBUTTONDOWN){
			SDL_GetMouseState(&x_mouse, &y_mouse);
			x_cell = x_mouse / cell;
			y_cell = y_mouse / cell;
			grid_states[x_cell][y_cell] = cell_type;
		}

		for(int i = 0; i < n_updates_per_frame; i++){

			// CREATES EARTH
			cell_dynamics(1, 4, 4, 0, 0); // wet earth dries
			cell_dynamics(1, 2, 8, 0, 2, 0.5f); // fire dries shallow water
			cell_dynamics(1, 10, 10, 0, 0, 0.01f); // snow disappears
			cell_dynamics(1, 9, 0, 0, 1, 0.05f);

			// CREATES SAND
			cell_dynamics(1, 8, 8, 12, 0); // fire goes out -> sand
			cell_dynamics(1, 3, 3, 12, 2, 0.2f);
			cell_dynamics(1, 7, 2, 12, 2);
			cell_dynamics(1, 7, 2, 12, 1, 0.2f);


			// CREATES TREES
			cell_dynamics(1, 0, 1, 1, 1); // grow trees
			cell_dynamics(1, 3, 1, 1, 1, 0.05f); // trees spread over grass
			cell_dynamics(1, 3, 7, 1, 1, 0.01f); 
			cell_dynamics(1, 3, 3, 1, 1, 0.1f);

			// CREATES WATER
			cell_dynamics(1, 0, 2, 2, 1, 0.5f); // grow water
			cell_dynamics(1, 4, 0, 2, 0, 0.1f); // mud next to earth creates water
			cell_dynamics(1, 6, 1, 2, 1);
			cell_dynamics(1, 6, 7, 2, 1);

			// CREATES GRASS
			cell_dynamics(1, 1, 0, 3, 4, 0.1f); // too much earth around trees creates grass
			cell_dynamics(1, 0, 3, 3, 1, 0.1f);
			cell_dynamics(1, 12, 1, 3, 1, 0.5f);
			cell_dynamics(2, 1, 11, 3, 1);
			cell_dynamics(2, 12, 11, 3, 1);

			// CREATES MUD
			cell_dynamics(1, 2, 0, 4, 4, 0.5f); // too much earth around water creates mud
			cell_dynamics(1, 8, 8, 4, 0); // fire goes out -> mud
			cell_dynamics(1, 12, 2, 4, 1, 0.7f);
			cell_dynamics_less(4, 7, 2, 4, 2);

			// CREATES SWAMP
			cell_dynamics(1, 1, 2, 5, 2); // too much water around trees creates swamp

			// CREATES SEA
			cell_dynamics(1, 2, 2, 6, 5); // water creates deep water
			cell_dynamics(1, 2, 6, 6, 3); // deep water spreads
			cell_dynamics(1, 9, 1, 6, 1);
			cell_dynamics(1, 9, 7, 6, 1);
			cell_dynamics(1, 9, 0, 6, 1, 0.05f); // deeper water can dry up
			cell_dynamics(1, 9, 1, 6, 1, 0.05f); // deeper water can dry up
			cell_dynamics(1, 9, 7, 6, 1, 0.05f); // deeper water can dry up

			// CREATES OCEAN
			cell_dynamics(1, 6, 6, 9, 3); // deeper water 
			cell_dynamics(1, 6, 9, 9, 3); // deeper water spreads
			cell_dynamics(1, 2, 9, 9, 3); // deeper water spreads

			// CREATES FOREST
			cell_dynamics(1, 1, 1, 7, 5); // dense forest
			cell_dynamics(1, 1, 7, 7, 3); // dense forest spreads
			cell_dynamics(1, 3, 7, 7, 3); // dense forest spreads over grass			
			
			// CREATES FIRE
			cell_dynamics(1, 1, 8, 8, 0); // forest catches fire
			cell_dynamics(1, 3, 8, 8, 0); // grass catches fire
			cell_dynamics(1, 7, 8, 8, 1, 0.5f); // dense forest catches fire
			cell_dynamics(1, 7, 7, 8, 4, 0.0001f); // dense forest starts fire
			cell_dynamics(1, 3, 3, 8, 2, 0.0002f); // dense forest starts fire

			// SNOW
			position_dynamics(0.002, 5);
			position_dynamics(0.004, 4);
			position_dynamics(0.006, 3);
			position_dynamics(0.008, 2);
			position_dynamics(0.010, 1);
			

			cell_dynamics(1, 2, 1, 1, 2, 0.5f); // water can replace trees
			cell_dynamics(1, 1, 2, 2, 2, 0.5f); // trees can replace water
			cell_dynamics(1, 7, 7, 1, 2, 0.25f); // dense forest can shrink


			cell_dynamics(1, 6, 0, 2, 1, 0.05f); // deep water can dry up
			cell_dynamics(1, 6, 1, 0, 1, 0.05f); // deep water can dry up
			cell_dynamics(1, 6, 7, 1, 1, 0.05f); // deep water can dry up

			cell_dynamics(1, 9, 5, 0, 1, 0.35f);
			cell_dynamics(1, 6, 5, 0, 1, 0.35f);
			cell_dynamics(1, 5, 9, 6, 1, 0.35f);
			cell_dynamics(1, 5, 6, 2, 1, 0.35f);
			cell_dynamics(1, 5, 2, 0, 1, 0.35f);

			cell_dynamics_two(2, 0, 1, 2, 11, 3, 0.5f); // create town
			cell_dynamics_less(1, 11, 1, 0, 1); // abandon town
			cell_dynamics_less(1, 11, 2, 0, 1); // abandon town
			cell_dynamics(1, 1, 11, 2, 1);
			cell_dynamics(1, 2, 11, 1, 1);
			cell_dynamics(1, 7, 9, 2, 1);
			

			
			cell_dynamics(1, 3, 9, 6, 1); // remove grass from deep water
			cell_dynamics(1, 3, 6, 2, 1); // remove grass from deep water

			cell_dynamics(1, 0, 0, 1, 0, 0.001f); // spontaneous trees
			cell_dynamics(1, 0, 0, 2, 0, 0.001f); // spontaneous water

		}

		

		SDL_RenderClear(renderer);

		// assign values to texture buffer
		for (int i = 0; i < nx; i++){
			for (int j = 0; j < ny; j++){

				// cout << grid_states[i][j] << endl;
				
				for (int x = 0; x < cell; x++){
					for (int y = 0; y < cell; y++){

						int rx = i * cell + x;
						int ry = j * cell + y;

						switch(grid_states[i][j]){
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
							
							default:
							textureBuffer[(ry * width) + rx] = 0xFF63513E;

						}

						// grid borders
						if ((x == 0) || (x == cell-1) || (y == 0) || (y == cell-1)){
							textureBuffer[(ry * width) + rx] = 0xFF33211E;
						}
					}
				}
			}
		}

		SDL_UpdateTexture(texture, NULL, textureBuffer, width * sizeof(uint32_t));
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

	}
}