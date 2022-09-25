#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <vector>
#include <time.h>
#include <map>

using namespace std;



class Game{
public:
	Game();
	~Game();

	void game_loop();
	void cell_dynamics(int size, int x1, int x2, int x3, int t, float p = 1);
	void cell_dynamics_less(int size, int x1, int x2, int x3, int t, float p = 1);
	void cell_dynamics_two(int size, int x1, int x2, int x3, int x4, int t, float p = 1);
	void position_dynamics(float p, int r);

private:
	unsigned int width = 1600;
	unsigned int height = 900;
	int cell = 10;
	int nx = width / cell;
	int ny = height / cell;
	int n_types = 13;

	vector<vector<int>> grid_states;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
};