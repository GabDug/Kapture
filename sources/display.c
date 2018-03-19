#include "headers/constant.h"
#include "headers/tools.h"

void display_map(SDL_Surface *screen, int **map, int **char_map)
{
    int i, j;
    SDL_Rect position;
    SDL_Surface *terrain = NULL, *forest = NULL, *river = NULL; // Background sprites
    SDL_Surface *flag_red = NULL, *flag_blue = NULL; // Transparent sprites
    SDL_Surface *perso1 = NULL, *perso2 = NULL, *perso3 = NULL, *perso4 = NULL; // Characters sprites

    terrain = SDL_LoadBMP("images/tile-terrain.bmp");
    forest = SDL_LoadBMP("images/tile-forest.bmp");
    river = SDL_LoadBMP("images/tile-river.bmp");

    perso1 = SDL_LoadBMP("images/tile-pawn-scout.bmp");
    perso2 = SDL_LoadBMP("images/tile-pawn-infantryman.bmp");
    perso3 = SDL_LoadBMP("images/tile-pawn-shock-troop.bmp");
    perso4 = SDL_LoadBMP("images/tile-pawn-scout-2.bmp");

    for (i = 0; i < NBR_BLOCK_Y; i++)
    {
        for (j = 0; j < NBR_BLOCK_X; j++)
        {
            position.x = j * BLOCK_SIZE;
            position.y = i * BLOCK_SIZE;

            switch (map[i][j])
            {
            case TERRAIN:
                SDL_BlitSurface(terrain, NULL, screen, &position);
                break;
            case FOREST:
                SDL_BlitSurface(forest, NULL, screen, &position);
                break;
            case RIVER:
                SDL_BlitSurface(river, NULL, screen, &position);
                break;
            }
            switch (char_map[i][j])
            {
            case CHARACTER0:
                SDL_BlitSurface(perso1, NULL, screen, &position);
                break;
            case CHARACTER1:
                SDL_BlitSurface(perso2, NULL, screen, &position);
                break;
            case CHARACTER2:
                SDL_BlitSurface(perso3, NULL, screen, &position);
                break;
            case CHARACTER3:
                SDL_BlitSurface(perso4, NULL, screen, &position);
                break;
            }
        }
    }

    SDL_Flip(screen);

    SDL_FreeSurface(terrain);
    SDL_FreeSurface(forest);
    SDL_FreeSurface(river);
    SDL_FreeSurface(perso1);
    SDL_FreeSurface(perso2);
    SDL_FreeSurface(perso3);
    SDL_FreeSurface(perso4);
}


void display_info(SDL_Surface *screen, int pawn_ct, int player, int round, int turn)
{
    SDL_Rect position;
    position.x = 10;
    position.y = NBR_BLOCK_Y * BLOCK_SIZE;

    SDL_Surface *texte=NULL, *background=NULL;

    background = SDL_CreateRGBSurface(SDL_HWSURFACE, SCREEN_WIDTH-10, WINDOW_OFFSET_Y, 32, 0, 0, 0, 0);
    SDL_FillRect(background, NULL, SDL_MapRGB(screen->format, 27, 27, 27));
    SDL_BlitSurface(background, NULL, screen, &position); // Collage de la surface sur l'écran

    TTF_Font *police = NULL;
    police = TTF_OpenFont("data/abel.ttf", 22);
    SDL_Color font_color = {250, 250, 255};
    SDL_Color bg_color = {27, 27, 27};

    char text[1024];
    snprintf(text, 1024, "Turn %d - Player %d - Moving pawn %d (3 moves left)", turn, player, pawn_ct);
    texte = TTF_RenderText_Shaded(police, text, font_color, bg_color);
    SDL_BlitSurface(texte, NULL, screen, &position);
    SDL_Flip(screen);
}

int main_menu(SDL_Surface *screen)
{
    int choice;
    SDL_Surface *menu = NULL;
    SDL_Event event;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;

    menu = SDL_LoadBMP("images/display-menu.bmp");

    SDL_BlitSurface(menu, NULL, screen, &pos);
    SDL_Flip(screen);

    do
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            choice = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                choice = 0;
                break;
            case SDLK_1: // Regular Key
                choice = 1;
                break;
            case SDLK_2:
                choice = 2;
                break;
            case SDLK_3:
                choice = 3;
                break;
            case SDLK_4:
                choice = 4;
                break;
            }
            break;
        }
    }
    while (choice < 0 || choice > 4);

    SDL_FreeSurface(menu);
    return choice;
}


void display_rules(SDL_Surface *screen)
{
    SDL_Surface *rules = NULL;
    SDL_Event event;
    SDL_Rect pos;
    pos.x = 0;
    pos.y = 0;

    rules = SDL_LoadBMP("images/display-rules.bmp");

    SDL_BlitSurface(rules, NULL, screen, &pos);
    SDL_Flip(screen);

    pause();

    SDL_FreeSurface(rules);
}
