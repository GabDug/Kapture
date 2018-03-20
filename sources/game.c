#include "headers/constant.h"
#include "headers/tools.h"
#include "headers/display.h"
#include "headers/game.h"

// TODO Remplacer la fonction qui affiche les personnages avec le pointeur
// array structure etc tu connais


void move(int **pawn_map, SDL_Rect old_pos, SDL_Rect new_pos)
{
    pawn_map[new_pos.y][new_pos.x] = pawn_map[old_pos.y][old_pos.x];
    pawn_map[old_pos.y][old_pos.x] = -1;
}


int check_action(int **map, int **pawn_map, SDL_Rect position)
{
    if (position.x >= NBR_BLOCK_X || position.x < 0 || position.y >= NBR_BLOCK_Y || position.y < 0)
        return FALSE;
    else
    {
        if (map[position.y][position.x] == TERRAIN)
        {
            if (pawn_map[position.y][position.x] == -1)
                return TRUE;
            else
                return FALSE;
        }
        else
            return FALSE;
    }
}


void play_game(SDL_Surface *screen)
{
    int player, action;
    int turn = 0, pawn_ct = 0, round = 0, counter=0; // Counters
    SDL_Rect pos;

    // dynamic array for pawns
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
    fprintf(stderr, "58\n");
    for (i = 0; i < PAWNS*2; i++)
    {
        t_array[i]->id = i;

        if (i%PAWNS == 0 || i%PAWNS==1)
        {
            t_array[i]->type = 'S';
            t_array[i]->max_displacement=5;
            t_array[i]->displacement_left=5;
        }
        else
        {
            if (i%PAWNS == 2)
            {
                t_array[i]->type = 'I';
                t_array[i]->max_displacement=3;
                t_array[i]->displacement_left=3;
            }
            else
            {
                if (i%PAWNS == 3)
                {
                    t_array[i]->type = 'T';
                    t_array[i]->max_displacement=2;
                    t_array[i]->displacement_left=2;
                }
                else
                {
                    if (i%PAWNS == 4)
                    {
                        t_array[i]->type = 'F';
                        t_array[i]->max_displacement=0;
                        t_array[i]->displacement_left=0;
                    }
                    else
                        t_array[i]->type = 'X';
                }
            }
        }
        if (i <PAWNS) // IF 0<i<5 then player 1 if 5<=i<10 then player 2
        {
            t_array[i]->player_id=0;
            t_array[i]->start_pos_x=2;
            t_array[i]->start_pos_y=7+i;
        }
        else
        {
            t_array[i]->player_id=1;
            t_array[i]->start_pos_x=NBR_BLOCK_X-3;
            t_array[i]->start_pos_y=4+i;
        }
        t_array[i]->hasEnemyFlag=FALSE;
        t_array[i]->alive=TRUE;
    }

    // now define a pointer to the array
    Pawn ***p = &t_array;
    fprintf(stderr, "Pointer to array defined!\n");
    for (int i = 0; i < PAWNS*2; i++)
    {
        fprintf(stderr, "ID: %2d Type: %c Player Id: %d  Max Displacement: %d\n", (*p)[i]->id, (*p)[i]->type,(*p)[i]->player_id, (*p)[i]->max_displacement);
    }

    int **map = init_map(NBR_BLOCK_X, NBR_BLOCK_Y);
    int **pawn_map = init_player_map(NBR_BLOCK_X, NBR_BLOCK_Y, p);
    fprintf(stderr, "Maps created!\n");
    Player *players = init_players(2); // list with all the players

    SDL_Rect current_pos, action_pos;
    SDL_Event event;

    //place_characters(map, players);
    display_map(screen, map, pawn_map);
    fprintf(stderr, "Map displayed!\n");

    for (turn = 0; turn < NBR_TOUR_MAX; turn++)
    {
        fprintf(stderr, "FIRST LOOP!\n");
        // the pawncounter goes twice as high bc of double buffering incrementing twice
        for (counter = 0; counter < NBR_PLAYERS * PAWNS * 2; counter++)
        {
            fprintf(stderr, "SECOND LOOP!\n");
            pawn_ct = counter / 2; // THe id of the pawn to operate
            if (counter % 2 == 1 && pawn_ct%5!=4)
            {
                if(pawn_ct < PAWNS)
                    player = 0;
                else
                    player = 1;

                fprintf(stderr, "Pawn: %d, player: %d, round: %d, turn:%d\n", pawn_ct, player, round, turn);

                int mvmt_counter;
                mvmt_counter = 0;
                int mvmt_counter_double;
                mvmt_counter_double = 0;
                int mvmt_max;
                mvmt_max = (*p)[pawn_ct]->max_displacement * 2;

                int mvmt_counter_up=TRUE;


                fprintf(stderr, "Before while: pawn: %d, player: %d, round: %d, turn:%d, counter:%d, mvmcounter%d, double:%d\n", pawn_ct, player, round, turn, counter, mvmt_counter, mvmt_counter_double);

                while (mvmt_counter_double < mvmt_max)
                {
                    mvmt_counter = mvmt_counter_double / 2;
                    fprintf(stderr, "Enter while: pawn: %d, player: %d, round: %d, turn:%d, counter:%d, mvmcounter%d, double:%d\n", pawn_ct, player, round, turn, counter, mvmt_counter, mvmt_counter_double);
                    current_pos.x = find_x(pawn_map, (*p)[pawn_ct]->id);
                    current_pos.y = find_y(pawn_map, (*p)[pawn_ct]->id);
                    /*}*/

                    if (current_pos.x == -1 || current_pos.y == -1)
                    {
                        fprintf(stderr, "Current pos =-1!\n");
                        continue;
                    }
                    // TODO Delete the continue by inversing the conditions in the if-else
                    else
                    {
                        action_pos.x = current_pos.x;
                        action_pos.y = current_pos.y;

                        //SDL_EnableKeyRepeat(100, 100);
                        // TODO IMPORTNT We used a single 1D Array to store all the pawns to avoid using
                        // 2D Arrays and multiples structures that would be unnecessary and  we didn't have
                        // to implement a Player structure.
                        SDL_WaitEvent(&event);
                        switch (event.type)
                        {
                        case SDL_QUIT:
                            turn = player = pawn_ct = round = counter=mvmt_counter = mvmt_counter_double = 10000;
                            // like a continue
                            break;
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                            case SDLK_ESCAPE:
                                turn = player = pawn_ct = round =counter = mvmt_counter = mvmt_counter_double = 10000;
                                // like a continue
                                break;
                            case SDLK_RETURN:
                                mvmt_counter = 10000;
                                // like a continue
                                break;
                            case SDLK_r:
                                action_pos.x--;
                                action_pos.y--;
                                if (check_action(map, pawn_map, action_pos))
                                {
                                    move(pawn_map, current_pos, action_pos);
                                    mvmt_counter_double++;
                                    mvmt_counter_double++;
                                }
                                break;
                            case SDLK_y:
                                action_pos.x++;
                                action_pos.y--;
                                if (check_action(map, pawn_map, action_pos))
                                {
                                    move(pawn_map, current_pos, action_pos);
                                    mvmt_counter_double++;
                                    mvmt_counter_double++;
                                }
                                break;
                            case SDLK_v:
                                action_pos.x--;
                                action_pos.y++;
                                if (check_action(map, pawn_map, action_pos))
                                {
                                    move(pawn_map, current_pos, action_pos);
                                    mvmt_counter_double++;
                                    mvmt_counter_double++;
                                }
                                break;
                            case SDLK_n:
                                action_pos.x++;
                                action_pos.y++;
                                if (check_action(map, pawn_map, action_pos))
                                {
                                    move(pawn_map, current_pos, action_pos);
                                    mvmt_counter_double++;
                                    mvmt_counter_double++;
                                }
                                break;
                            case SDLK_DOWN:
                                action_pos.y++;
                                if (check_action(map, pawn_map, action_pos))
                                {
                                    move(pawn_map, current_pos, action_pos);
                                    mvmt_counter_double++;
                                    mvmt_counter_double++;
                                }
                                break;
                            case SDLK_LEFT:
                                action_pos.x--;
                                if (check_action(map, pawn_map, action_pos))
                                {
                                    move(pawn_map, current_pos, action_pos);
                                    mvmt_counter_double++;
                                    mvmt_counter_double++;
                                }
                                break;
                            case SDLK_RIGHT:
                                action_pos.x++;
                                if (check_action(map, pawn_map, action_pos))
                                {
                                    move(pawn_map, current_pos, action_pos);
                                    mvmt_counter_double++;
                                    mvmt_counter_double++;
                                }
                                break;
                            }

                        }
                        // CHECK WIN
                      //  if(mvmt_counter_up)
                        //    mvmt_counter_double++;

                        display_map(screen, map, pawn_map);
                        display_info(screen, pawn_ct, player, round, turn, mvmt_counter, (*p)[pawn_ct]->max_displacement);
                        //    pause();

                    }
                }
            }
        }

    }

    //pause();


    // Memory Free
    // TODOUnload from memory pawns etc...
    for (player = 0; player < NBR_BLOCK_Y; player++)
        free(map[player]);
    free(map);


    free(players);


}

