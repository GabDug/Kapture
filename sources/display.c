#include "headers/constant.h"
#include "headers/tools.h"

void display_map(SDL_Surface *screen, int **map, int **pawn_map)
{
    int i, j;
    SDL_Rect position;
    SDL_Surface *terrain = NULL, *forest = NULL, *river = NULL; // Background sprites
    SDL_Surface *flag_red = NULL, *flag_blue = NULL; // Transparent sprites
    SDL_Surface *p0_scout = NULL, *p0_scout_1 = NULL, *p0_infantry = NULL, *p0_troops = NULL, *p1_scout = NULL,*p1_scout_1 = NULL, *p1_infantry = NULL, *p1_troops = NULL; // Characters sprites
    SDL_Surface *p0_flag = NULL, *p1_flag = NULL;

    terrain = SDL_LoadBMP("images/tile-terrain.bmp");
    forest = SDL_LoadBMP("images/tile-forest.bmp");
    river = SDL_LoadBMP("images/tile-river.bmp");

    p0_scout = SDL_LoadBMP("images/tile-pawn-scout.bmp");
    p0_scout_1 = SDL_LoadBMP("images/tile-pawn-scout.bmp");
    p0_infantry = SDL_LoadBMP("images/tile-pawn-infantryman.bmp");
    p0_troops = SDL_LoadBMP("images/tile-pawn-shock-troop.bmp");

    p1_scout = SDL_LoadBMP("images/tile-pawn-scout-2.bmp");
    p1_scout_1 = SDL_LoadBMP("images/tile-pawn-scout-2.bmp");
    p1_infantry = SDL_LoadBMP("images/tile-pawn-infantryman.bmp");
    p1_troops = SDL_LoadBMP("images/tile-pawn-shock-troop.bmp");

    p0_flag = SDL_LoadBMP("images/flag-blue.bmp");
    SDL_SetColorKey(p0_flag, SDL_SRCCOLORKEY, SDL_MapRGB(p0_flag->format, 255, 0, 255));
    p1_flag = SDL_LoadBMP("images/flag-red.bmp");
    SDL_SetColorKey(p1_flag, SDL_SRCCOLORKEY, SDL_MapRGB(p0_flag->format, 255, 0, 255));


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
            switch (pawn_map[i][j])
            {
            case 0:
                SDL_BlitSurface(p0_scout, NULL, screen, &position);
                break;
            case 1:
                SDL_BlitSurface(p0_scout_1, NULL, screen, &position);
                break;
            case 2:
                SDL_BlitSurface(p0_infantry, NULL, screen, &position);
                break;
            case 3:
                SDL_BlitSurface(p0_troops, NULL, screen, &position);
                break;
            case 4:
                SDL_BlitSurface(p0_flag, NULL, screen, &position);
                break;
            case 5:
                SDL_BlitSurface(p1_scout_1, NULL, screen, &position);
                break;
            case 6:
                SDL_BlitSurface(p1_scout, NULL, screen, &position);
                break;
            case 7:
                SDL_BlitSurface(p1_infantry, NULL, screen, &position);
                break;
            case 8:
                SDL_BlitSurface(p1_troops, NULL, screen, &position);
                break;
            case 9:
                SDL_BlitSurface(p1_flag, NULL, screen, &position);
                break;
            default:
                break;
            }
        }
    }

    SDL_Flip(screen);

    SDL_FreeSurface(terrain);
    SDL_FreeSurface(forest);
    SDL_FreeSurface(river);

    SDL_FreeSurface(p0_flag);
    SDL_FreeSurface(p1_flag);
    SDL_FreeSurface(p0_infantry);
    SDL_FreeSurface(p1_infantry);
    SDL_FreeSurface(p0_troops);
    SDL_FreeSurface(p1_troops);
    SDL_FreeSurface(p0_scout);
    SDL_FreeSurface(p0_scout_1);
    SDL_FreeSurface(p1_scout);
    SDL_FreeSurface(p1_scout_1);
}


void display_info(SDL_Surface *screen, int pawn_ct, int player, int round, int turn, int mvmt_counter, int mvmt_counter_max)
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
    snprintf(text, 1024, "Turn %d - Player %d - Moving pawn %d (%d/%d moves)", turn, player, pawn_ct, mvmt_counter, mvmt_counter_max);
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
