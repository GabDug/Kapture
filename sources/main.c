#include "headers/constant.h"
#include "headers/tools.h"
#include "headers/display.h"
#include "headers/game.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

void pause();

int main(int argc, char *argv[])
{
    int i, j, keep = TRUE;
    srand(time(NULL));

    SDL_Surface *screen = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("Kaptur", NULL);

    screen = SDL_SetVideoMode(REAL_SCREEN_WIDTH, REAL_SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // main window init

    if (screen == NULL)
    {
        fprintf(stderr, "Can't load video: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Can't load text (TTF_Init): %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "KAPTUR\n");

    do
    {
        switch (main_menu(screen))
        {
        case 1:
            play_game(screen);
            break;
        case 2:
            break;
        case 3:
            display_rules(screen);
            break;
        case 4:
            keep = FALSE;
            break;
        default:
            keep = FALSE;
            break;
        }
    }
    while (keep);

    //TTF_CloseFont(police); /* Has to be before TTF_Quit() */
    //TTF_Quit();
    SDL_Quit();
    return 0;
}
