#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <vector>
#include <time.h>

using namespace std;

class Game{
public:
	Game();
	~Game();

	void game_loop();
	void cell_dynamics(int size, int x1, int x2, int x3, int t, float p = 1);
	void position_dynamics(float p, int r);

private:
	unsigned int width = 1000;
	unsigned int height = 800;
	unsigned int cell = 10;
	int nx = width / cell;
	int ny = height / cell;

	vector<vector<int>> grid_states;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
};