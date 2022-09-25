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
	int n_updates_per_frame = 1;

	const char* cell_types[4] = { "Earth", "Trees", "Water", "Swamp"};

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
				cell_type = cell_type % 3;
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

		

		SDL_RenderClear(renderer);

		// assign values to texture buffer
		for (int i = 0; i < nx; i++){
			for (int j = 0; j < ny; j++){

				// cout << grid_states[i][j] << endl;
				
				for (int x = 0; x < cell; x++){
					for (int y = 0; y < cell; y++){

						int rx = i * cell + x;
						int ry = j * cell + y;

						// grid borders
						if ((x == 0) || (x == cell-1) || (y == 0) || (y == cell-1)){
							textureBuffer[(ry * width) + rx] = 0xFF000000;

						// TURN THIS INTO A SWITCH?
						// trees
						} else if (grid_states[i][j] == 1){
							textureBuffer[(ry * width) + rx] = 0xFF387D1A;
						// water
						} else if (grid_states[i][j] == 2){
							textureBuffer[(ry * width) + rx] = 0xFF167878;
						// swamp
						} else if (grid_states[i][j] == 3){
							textureBuffer[(ry * width) + rx] = 0xFFC1B993;
						// earth
						} else {
							textureBuffer[(ry * width) + rx] = 0xFF63513E;
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