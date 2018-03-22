#include "headers/constant.h"
// TODO Remplacer la fonction qui affiche les personnages avec le pointeur
// array structure etc tu connais


void move(int **pawn_map, Pawn ***p, int pawn_id, SDL_Rect old_pos, SDL_Rect new_pos)
{
    pawn_map[new_pos.y][new_pos.x] = pawn_map[old_pos.y][old_pos.x];
    pawn_map[old_pos.y][old_pos.x] = -1;
}



int check_win_conditions(int **map, int **pawn_map, Pawn ***pawns){


}

// Remove the flag from the board, put it "in" a pawn
void take_flag(int **pawn_map, SDL_Rect old_pos, SDL_Rect new_pos, Pawn ***p, int pawn_id)
{
    int flag_id, flag_player;
    fprintf(stderr, "Test:%d\n", pawn_map[new_pos.y][new_pos.x]);
    flag_id = pawn_map[new_pos.y][new_pos.x];
    flag_player = (*p)[flag_id]->player_id;

    (*p)[pawn_id]->flag = flag_player;

    // TODO Check that the pawn doesn't has a flag before allowing it to take another.
    pawn_map[new_pos.y][new_pos.x] = pawn_map[old_pos.y][old_pos.x];
    pawn_map[old_pos.y][old_pos.x] = -1;
}

int check_action(int **map, int **pawn_map, SDL_Rect position, SDL_Rect old_pos, Pawn ***p, int pawn_id)
{
    if (position.x >= NBR_BLOCK_X || position.x < 0 || position.y >= NBR_BLOCK_Y || position.y < 0)
        return FALSE;
    else
    {
        if (map[position.y][position.x] == TERRAIN || map[position.y][position.x] == RIVER || map[position.y][position.x] == FOREST
                || map[position.y][position.x] == FLAG_BASE_P0|| map[position.y][position.x] == FLAG_BASE_P1)
        {
            if (pawn_map[position.y][position.x] == -1)
                return TRUE;
            else
            {
                if (pawn_map[position.y][position.x]%PAWNS == 4) // If its a flag
                {
                    if((*p)[pawn_id]->type=='S') // If the pawn is a scout
                        return FALSE;
                    else
                        return FLAG_TAKEN;
                }
                else
                    return FALSE;
            }

        }
        else
            return FALSE;
    }
}


void play_game(SDL_Surface *screen)
{
    int player, action;
    int turn = 0, pawn_ct = 0, counter=0; // Counters
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
        if (i < PAWNS) // IF 0<i<5 then player 1 if 5<=i<10 then player 2
        {
            t_array[i]->player_id=0;
            if (i==4)
            {
                t_array[i]->start_pos_x=FLAG_P0_X ;
                t_array[i]->start_pos_y=FLAG_P0_Y ;
            }
            else
            {
                t_array[i]->start_pos_x=3;
                t_array[i]->start_pos_y=6+i;
            }
        }
        else
        {
            t_array[i]->player_id=1;

            if (i % PAWNS==4)
            {
                t_array[i]->start_pos_x=FLAG_P1_X ;
                t_array[i]->start_pos_y=FLAG_P1_Y ;
            }
            else
            {
                t_array[i]->start_pos_x=NBR_BLOCK_X-  4;
                t_array[i]->start_pos_y=6+i-PAWNS;
            }
        }
        t_array[i]->flag=-1;
        t_array[i]->alive=TRUE;
    }

    // now define a pointer to the array
    //Pawn ***pe = init_pawns();
    Pawn ***p = &t_array;

    fprintf(stderr, "Pointer to array defined! %d\n", p);
    //fprintf(stderr, "Pointer to array defined! %d\n", pe);

    for (int i = 0; i < PAWNS*2; i++)
    {
        fprintf(stderr, "ID: %2d Type: %c Player Id: %d  Max Displacement: %d\n", (*p)[i]->id, (*p)[i]->type,(*p)[i]->player_id, (*p)[i]->max_displacement);
    }

    int **map = init_map(NBR_BLOCK_X, NBR_BLOCK_Y);
    int **pawn_map = init_pawn_map(NBR_BLOCK_X, NBR_BLOCK_Y, p);
    fprintf(stderr, "Maps created!\n");
    //Player *players = init_players(2); // list with all the players

    SDL_Rect current_pos, action_pos;
    SDL_Event event;

    display_map(screen, map, pawn_map);
    fprintf(stderr, "Map displayed!\n");

    for (turn = 0; turn < NBR_TOUR_MAX; turn++)
    {
        fprintf(stderr, " FIRST LOOP!\n");
        // the pawncounter goes twice as high bc of double buffering incrementing twice
        for (counter = 0; counter < NBR_PLAYERS * PAWNS * 2; counter++)
        {
            fprintf(stderr, "  SECOND LOOP!\n");
            pawn_ct = counter / 2; // THe id of the pawn to operate
            if (counter % 2 == 1 && pawn_ct%PAWNS != 4)
            {
                if(pawn_ct < PAWNS)
                    player = 0;
                else
                    player = 1;

                fprintf(stderr, "  Pawn: %d, player: %d,  turn:%d, move_left: %d, flag:%d\n", pawn_ct, player, turn,(*p)[pawn_ct]->displacement_left, (*p)[pawn_ct]->flag);


                int mvmt_counter, mvmt_max;
                mvmt_counter = 0;
                mvmt_max = (*p)[pawn_ct]->max_displacement ;


                // TODO Remove
                int mvmt_counter_up=TRUE;


                fprintf(stderr, "  Before while: pawn: %d, player: %d,  turn:%d, counter:%d, mvmcounter%d, double:%d\n", pawn_ct, player,  turn, counter, mvmt_counter, mvmt_counter);

                while (mvmt_counter < mvmt_max)
                {
                    fprintf(stderr, "  %d\n", mvmt_counter);

                    //fprintf(stderr, "Enter while: pawn: %d, player: %d, round: %d, turn:%d, counter:%d, mvmcounter%d, double:%d\n", pawn_ct, player, round, turn, counter, mvmt_counter, mvmt_counter_double);
                    current_pos.x = find_x(pawn_map, (*p)[pawn_ct]->id);
                    current_pos.y = find_y(pawn_map, (*p)[pawn_ct]->id);
                    /*}*/

                    if (current_pos.x == -1 || current_pos.y == -1)
                    {
                        fprintf(stderr, "   Current pos =-1!\n");
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
                            turn = player = pawn_ct = counter=mvmt_counter = mvmt_counter = 10000;
                            // like a continue
                            break;
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                                int check;
                            case SDLK_ESCAPE:
                                turn = player = pawn_ct  =counter = mvmt_counter = mvmt_counter = 10000;
                                // like a continue
                                break;
                            case SDLK_RETURN: // END TURN
                                mvmt_counter = mvmt_counter = 10000;
                                // like a continue
                                break;
                            case SDLK_q: //UPPER LEFT
                                action_pos.x--;
                                action_pos.y--;
                                //int **map, int **pawn_map, SDL_Rect position, SDL_Rect old_posPawn, Pawn ***p, int pawn_id);
                                check = check_action(map, pawn_map, action_pos, current_pos ,p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct,current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            case SDLK_e: //UPPER RIGHT
                                action_pos.x++;
                                action_pos.y--;
                                check = check_action(map, pawn_map, action_pos, current_pos ,p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct, current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            case SDLK_z: // LOWER LEFT
                                action_pos.x--;
                                action_pos.y++;
                                check = check_action(map, pawn_map, action_pos, current_pos ,p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct, current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            case SDLK_c: // LOWER RIGHT
                                action_pos.x++;
                                action_pos.y++;
                                check = check_action(map, pawn_map, action_pos, current_pos ,p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct, current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            case SDLK_w: // UP
                                action_pos.y--;
                                check = check_action(map, pawn_map, action_pos, current_pos ,p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct, current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            case SDLK_s: // DOWN
                                action_pos.y++;
                                check = check_action(map, pawn_map, action_pos, current_pos ,p, pawn_ct);
                                //check = check_action(map, pawn_map, action_pos, p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct,current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            case SDLK_a: // LEFT
                                action_pos.x--;
                                check = check_action(map, pawn_map, action_pos,current_pos , p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct,current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            case SDLK_d: // RIGHT
                                action_pos.x++;
                                check = check_action(map, pawn_map, action_pos,current_pos , p, pawn_ct);
                                if (check)
                                {
                                    if (check==FLAG_TAKEN)
                                    {
                                        take_flag(pawn_map, current_pos, action_pos, p, pawn_ct);
                                    }
                                    else
                                        move(pawn_map, p, pawn_ct,current_pos, action_pos);
                                    mvmt_counter++;
                                }
                                break;
                            }

                        }
                        // CHECK WINcurrent_pos ,
                        //  if(mvmt_counter_up)
                        //    mvmt_counter_double++;

                        display_map(screen, map, pawn_map);
                        display_info(screen, pawn_ct, player, turn, mvmt_counter, (*p)[pawn_ct]->max_displacement);
                        //    pause();

                    }
                    fprintf(stderr, "   Pawn: %d, player: %d, turn:%d, move_left: %d, flag:%d\n", pawn_ct, player, turn,(*p)[pawn_ct]->displacement_left, (*p)[pawn_ct]->flag);

                }
            }
        }

    }

    //pause();


    // Memory Free
    // TODO Unload from memory pawns etc...
    for (i = 0; i < NBR_BLOCK_Y; i++) // i is each column
        free(map[i]);
    free(map);


//    free(players);


}

