// Display the map terrain and pawns
void display_map(SDL_Surface *screen, int **map, int **char_map);

// Display the main menu, and takes the events
int display_menu(SDL_Surface *screen);

// Display the rules of the game, with events to quit
int display_rules(SDL_Surface *screen);


void display_info(SDL_Surface *screen, int pawn_ct, int player, int turn, int mvmt_counter, int mvmt_counter_max);
