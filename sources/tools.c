#include "headers/constant.h"

void pause()
{
    int keep = 1;
    SDL_Event event;

    while (keep)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            keep = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                keep = 0;
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
            if ((j == size_x / 2 && i >= NBR_BLOCK_Y / 2) || (i <= NBR_BLOCK_Y / 2 && j == size_x / 2 -1))
            {
                map[i][j] = RIVER;
            }
            else if ((i == 0 || j == 0 || i == size_y - 1 || j == size_x - 1) || (i ==5 &&j==8)||(i ==5 &&j==7)||(i ==6 &&j==8)
                     || (i ==8 &&j==18)||(i ==8 &&j==17)||(i ==9 &&j==18))
            {
                // Just put some forest in the map and on the edges
                map[i][j] = FOREST;
            }
            else if (j == FLAG_P0_X  && i == FLAG_P0_Y)
            {
                map[i][j] = FLAG_BASE_P0;
            }
            else if (j == FLAG_P1_X  && i == FLAG_P1_Y )
            {
                map[i][j] = FLAG_BASE_P1;
            }
            else
            {
                map[i][j] = TERRAIN;
            }
        }
    }
    return map;
}

int **init_pawn_map(int size_x, int size_y, Pawn ***pawns)
{
    fprintf(stderr, "Player map size: %d by %d\n", size_x, size_y);
    int i, j, pawn_id;

    int **map = (int **) malloc(size_y * sizeof(int *));


    for (i = 0; i < size_y; i++)
    {
        map[i] = (int *) malloc(size_x * sizeof(int));

        for (j = 0; j < size_x; j++)
        {
            map[i][j] = -1;
        }
    }

    for(pawn_id=0; pawn_id < PAWNS*2; pawn_id++)
    {
        for (i = 0; i < size_y; i++)
        {
            for (j = 0; j < size_x; j++)
            {
                if (i == (*pawns)[pawn_id]->start_pos_y && j == (*pawns)[pawn_id]->start_pos_x)
                {
                    map[i][j] = pawn_id;
                    fprintf(stderr, "Pawn Id:%d   Pos:%d/%d\n", pawn_id, j, i);
                }
            }
        }
    }

    return map;
}
Pawn *init_pawns()
{
    Pawn *ptr;
    ptr = (Pawn*) malloc(PAWNS*2 * sizeof(Pawn));

    int i = 0;
    // allocate pointers (array)
    Pawn **t_array = malloc(PAWNS*2 * sizeof(Pawn *));

    // allocate pawns and have the array point to them
    for (i = 0; i < PAWNS*2; i++)
    {
        t_array[i] = malloc(sizeof(Pawn));
    }

    // Fill each pawn in this order for each player:
    // 2 S, 1 I, 1 T
    fprintf(stderr, "Debug 3\n");
    for (i = 0; i < PAWNS*2; i++)
    {
        t_array[i]->id = i;

        if (i % PAWNS == 0 || i % PAWNS==1)
        {
            t_array[i]->type = 'S';
            t_array[i]->max_displacement = 5;
            t_array[i]->displacement_left = 5;
        }
        else
        {
            if (i%PAWNS == 2)
            {
                t_array[i]->type = 'I';
                t_array[i]->max_displacement = 3;
                t_array[i]->displacement_left = 3;
            }
            else
            {
                if (i % PAWNS == 3)
                {
                    t_array[i]->type = 'T';
                    t_array[i]->max_displacement = 2;
                    t_array[i]->displacement_left = 2;
                }
                else
                {
                    if (i % PAWNS == 4)
                    {
                        t_array[i]->type = 'F';
                        t_array[i]->max_displacement = 0;
                        t_array[i]->displacement_left = 0;
                    }
                    else
                        t_array[i]->type = 'X';
                }
            }
        }
        if (i < PAWNS) // IF 0<i<5 then player 1 if 5<=i<10 then player 2
        {
            t_array[i]->player_id=0;
            if (i==4)
            {
                t_array[i]->start_pos_x=3;
                t_array[i]->start_pos_y=10;
            }
            else
            {
                t_array[i]->start_pos_x=2;
                t_array[i]->start_pos_y=7+i;
            }
        }
        else
        {
            t_array[i]->player_id=1;

            if (i % PAWNS==4)
            {
                t_array[i]->start_pos_x=NBR_BLOCK_X - 3;
                t_array[i]->start_pos_y=10;
            }
            else
            {
                t_array[i]->start_pos_x=NBR_BLOCK_X-3;
                t_array[i]->start_pos_y=4+i;
            }
        }
        t_array[i]->flag=-1;
        t_array[i]->alive=TRUE;
    }
    fprintf(stderr, "%d\n,", &t_array);
    return t_array;
}


int find_x(int **map, int id)
{
    int i, j;

    for (i = 0; i < NBR_BLOCK_Y; i++)
    {
        for (j = 0; j < NBR_BLOCK_X; j++)
        {
            // fprintf(stderr, "Looking for x at: %d_%d\n,", i, j);
            if (map[i][j] == id)
            {
                // fprintf(stderr, "Returning j: %d\n,", j);
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
