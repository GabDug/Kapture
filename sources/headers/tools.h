#ifndef TOOLS
#define TOOLS

// Pause the game, ESC to leave pause (DEBUG)
void pause();

// Generates a map (data, not display)
int **init_map(int size_y, int size_x);

// Generates a map with the id of each pawn
int **init_player_map(int size_x, int size_y);

// Find the first occurrence of an ID in a map (pawn or terrain)
int find_x(int **map, int id);

// Find the first occurrence of an ID in a map (pawn or terrain)
int find_y(int **map, int id);


#endif
