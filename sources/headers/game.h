

// Move a pawn in tha data structure (no display)
void move(int **map, Pawn ***p, int pawn_id,SDL_Rect old_pos, SDL_Rect new_pos);

// Check if the pawn can move
int check_action(int **map, int **pawn_map, SDL_Rect position, SDL_Rect old_posPawn, Pawn ***p, int pawn_id);


// Main function
void play_game(SDL_Surface *screen);



