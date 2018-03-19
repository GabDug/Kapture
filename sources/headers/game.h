
#define GAME

// Move a pawn in tha data structure (no display)
void move(int **map, SDL_Rect old_pos, SDL_Rect new_pos);


// Check if the pawn can move
int check_action(int **map, SDL_Rect position);


// Main function
void play_game(SDL_Surface *screen);



