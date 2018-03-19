#include "headers/constant.h"

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                continuer = 0;
            break;
        }
    }
}


int **init_map(int size_x, int size_y)
{
    fprintf(stderr, "Map size: %d by %d\n", size_x, size_y);
    int i, j;
    int **map = (int **) malloc(size_y * sizeof(int *));

    for (i = 0; i < size_y; i++)
    {
        map[i] = (int *) malloc(size_x * sizeof(int));

        for (j = 0; j < size_x; j++)
        {
            if (i == 0 || j == 0 || i == size_y - 1 || j == size_x - 1)
            {
                map[i][j] = FOREST;
            }
            else if (i % 2 == 0 && j % 2 == 0)
            {
                map[i][j] = FOREST;
            }
            else
            {
                map[i][j] = TERRAIN;
            }
        }
    }

    return map;
}

int **init_player_map(int size_x, int size_y){
    fprintf(stderr, "Player map size: %d by %d\n", size_x, size_y);
    int i, j;
    int **map = (int **) malloc(size_y * sizeof(int *));

    for (i = 0; i < size_y; i++)
    {
        map[i] = (int *) malloc(size_x * sizeof(int));

        for (j = 0; j < size_x; j++)
        {
            if (i == 4 && j == 4)
            {
                map[i][j] = CHARACTER0;
            }
            else if (i == 6 && j==6)
            {
                //map[i][j] = CHARACTER1;
                map[i][j] = -1;
            }
            else
            {
                map[i][j] = -1;
            }
        }
    }

    return map;
}

Player *init_players(int nbr_player)
{
    fprintf(stderr, "Initplayers nbr player : %d\n", nbr_player);
//s    fprintf(stderr, "Initplayers nbr pawnse : %d\n", pawnse);
    int i;
    Player *players = (Player *) malloc(nbr_player * sizeof(Player));
//    fprintf(stderr, "%d\n", pawns);
    //  fprintf(stderr, "%d\n", pawns);

    for (i = 0; i < nbr_player; i++)
    {
        players[i].id = i + 20;
        players[i].alive = TRUE;
//        if (i==0)
//            players[i].pawns_ptr = &pawns[0];
//        if (i==1)
//            players[i].pawns_ptr = &pawns[1];
    }

    return players;
}



int find_x(int **map, int id)
{
    int i, j;

    for (i = 0; i < NBR_BLOCK_Y; i++)
    {
        for (j = 0; j < NBR_BLOCK_X; j++)
        {
            fprintf(stderr, "Looking for x at: %d_%d\n,", i, j);
            if (map[i][j] == id)
            {
                fprintf(stderr, "Returning j: %d\n,", j);
                return j;
            }
        }
    }

    return -1;
}


int find_y(int **map, int id)
{
    int i, j;

    for (i = 0; i < NBR_BLOCK_Y; i++)
    {
        for (j = 0; j < NBR_BLOCK_X; j++)
        {
            if (map[i][j] == id)
            {
                return i;
            }
        }
    }

    return -1;
}
