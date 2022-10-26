#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <vector>
#include <time.h>
#include <map>
#include <cmath>

using namespace std;



class Game{
public:
	Game();
	~Game();

	// main loop
	void game_loop();

	// key presses
	void key_presses(SDL_Event &event);
	
	// cell updates
	void cell_update();
	
	// cell dynamics
	void cell_dynamics(int size, int x1, int x2, int x3, int t, float p = 1);
	void cell_dynamics_two(int size, int x1, int x2, int x3, int x4, int t, float p = 1);
	void cell_dynamics_less(int size, int x1, int x2, int x3, int t, float p = 1);
	void cell_dynamics_temp(int x1, int x2, int t);
	void position_dynamics(float p, int r);

private:

	const float PI = 3.141592654f;

	// screen settings
	unsigned int width = 1600;
	unsigned int height = 900;
	int cell = 10;
	int nx = width / cell;
	int ny = height / cell;

	// cell settings
	const int n_types = 14;
	vector<vector<int>> grid_states;
	vector<vector<float>> temperature; 

	// input settings
	int cell_type = 1;
	int brush_size = 0;
	int range = 2 * brush_size + 1;
	const char* cell_types[14] = {
	"Earth", "Trees", "Water", "Grass", 
	"Mud", "Swamp", "Sea", "Forest", 
	"Fire", "Ocean", "Snow", "Town", 
	"Sand", "Flowers"};

	// sdl settings
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
};