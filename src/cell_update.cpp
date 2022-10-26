#include "header.h"

void Game::cell_update(){

	// CREATES EARTH
	cell_dynamics(1, 4, 4, 0, 0); // wet earth dries
	cell_dynamics(1, 2, 8, 0, 2, 0.5f); // fire dries shallow water
	cell_dynamics(1, 10, 10, 0, 0, 0.01f); // snow disappears
	cell_dynamics(1, 9, 0, 0, 1, 0.01f);
	cell_dynamics(1, 9, 5, 0, 1, 0.25f);
	cell_dynamics(1, 6, 5, 0, 1, 0.25f);
	cell_dynamics_less(1, 11, 1, 0, 1); // abandon town
	cell_dynamics_less(1, 11, 2, 0, 1); // abandon town
	cell_dynamics(1, 6, 1, 0, 1, 0.05f); // deep water can dry up
	cell_dynamics(1, 5, 0, 0, 2, 0.35f);
	cell_dynamics(1, 8, 8, 0, 0, 0.75f); // fire goes out -> mud

	// CREATES SAND
	cell_dynamics(1, 8, 8, 12, 0, 0.75f); // fire goes out -> sand
	cell_dynamics(1, 3, 3, 12, 2, 0.2f);
	cell_dynamics(1, 7, 2, 12, 2);
	cell_dynamics(1, 7, 2, 12, 1, 0.2f);
	cell_dynamics(1, 5, 1, 12, 1, 0.05f);

	// CREATES TREES
	cell_dynamics(1, 0, 1, 1, 1); // grow trees
	cell_dynamics(1, 3, 1, 1, 1, 0.05f); // trees spread over grass
	cell_dynamics(1, 3, 7, 1, 1, 0.01f); 
	cell_dynamics(1, 3, 3, 1, 1, 0.1f);
	cell_dynamics(1, 7, 7, 1, 2, 0.25f); // dense forest can shrink
	cell_dynamics(1, 6, 7, 1, 1, 0.05f); // deep water next to forest can dry up
	cell_dynamics(1, 2, 11, 1, 1);
	cell_dynamics(1, 2, 1, 1, 2, 0.5f); // water can replace trees
	cell_dynamics(1, 5, 1, 1, 1, 0.05f);

	// CREATES WATER
	cell_dynamics(1, 0, 2, 2, 1, 0.5f); // grow water
	cell_dynamics(1, 4, 0, 2, 0, 0.1f); // mud next to earth creates water
	cell_dynamics(1, 6, 1, 2, 1);
	cell_dynamics(1, 6, 7, 2, 1);
	cell_dynamics(1, 3, 6, 2, 1); // remove grass from deep water
	cell_dynamics(1, 1, 2, 2, 2, 0.5f); // trees can replace water
	cell_dynamics(1, 6, 0, 2, 1, 0.05f); // deep water can dry up
	cell_dynamics(1, 5, 6, 2, 1, 0.35f);
	cell_dynamics(1, 7, 9, 2, 1);
	cell_dynamics(1, 5, 2, 2, 1, 0.05f);
	// cell_dynamics(1, 1, 11, 2, 1);

	// CREATES GRASS
	cell_dynamics(1, 1, 0, 3, 4, 0.1f); // too much earth around trees creates grass
	cell_dynamics(1, 0, 3, 3, 1, 0.1f);
	cell_dynamics(1, 12, 1, 3, 1, 0.5f);
	cell_dynamics(2, 1, 11, 3, 1);
	cell_dynamics(2, 12, 11, 3, 1);
	cell_dynamics(1, 13, 3, 3, 1, 0.5f);
	cell_dynamics(2, 1, 2, 3, 1, 0.5f);

	// CREATES MUD
	cell_dynamics(1, 2, 0, 4, 4, 0.5f); // too much earth around water creates mud

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
	cell_dynamics(1, 3, 9, 6, 1); // remove grass from deep water
	cell_dynamics(1, 5, 9, 6, 1, 0.35f);

	// CREATE TOWN
	cell_dynamics_two(2, 0, 1, 2, 11, 2, 0.5f); // create town

	// CREATES FLOWERS
	cell_dynamics(1, 3, 2, 13, 1, 0.15f);

	// CREATES OCEAN
	cell_dynamics(1, 6, 6, 9, 3); // deeper water 
	cell_dynamics(1, 6, 9, 9, 3); // deeper water spreads
	cell_dynamics(1, 2, 9, 9, 3, 0.1f); // deeper water spreads

	// CREATES FOREST
	cell_dynamics(1, 1, 1, 7, 5); // dense forest
	cell_dynamics(1, 1, 7, 7, 3); // dense forest spreads
	cell_dynamics(1, 3, 7, 7, 3); // dense forest spreads over grass			

	// CREATES FIRE
	cell_dynamics(1, 1, 8, 8, 0); // forest catches fire
	cell_dynamics(1, 3, 8, 8, 0); // grass catches fire
	cell_dynamics(1, 7, 8, 8, 1); // dense forest catches fire
	cell_dynamics(1, 13, 8, 8, 1); // flowers catch fire
	cell_dynamics(1, 7, 7, 8, 4, 0.0001f); // dense forest starts fire
	cell_dynamics(1, 3, 3, 8, 2, 0.0002f); // dense forest starts fire

	// SNOW
	position_dynamics(0.002, 5);
	position_dynamics(0.004, 4);
	position_dynamics(0.006, 3);
	position_dynamics(0.008, 2);
	position_dynamics(0.010, 1);

	// cell_dynamics(1, 0, 0, 1, 0, 0.001f); // spontaneous trees
	// cell_dynamics(1, 0, 0, 2, 0, 0.001f); // spontaneous water

}