#include "headers/constant.h"
#include "headers/tools.h"
#include "headers/display.h"
#include "headers/game.h"


void move(int **char_map, SDL_Rect old_pos, SDL_Rect new_pos)
{
    char_map[new_pos.y][new_pos.x] = char_map[old_pos.y][old_pos.x];
    char_map[old_pos.y][old_pos.x] = -1;
}


int check_action(int **map, SDL_Rect position)
{
    if (position.x >= NBR_BLOCK_X || position.x < 0 || position.y >= NBR_BLOCK_Y || position.y < 0)
        return FALSE;
    else
    {
        if (map[position.y][position.x] == TERRAIN)
            return TRUE;
        else
            return FALSE;
    }
}


/*
void play_game(SDL_Surface *screen)
{
    int player, action;
    int turn = 0, pawn_ct = 0, round = 0; // Counters

    //  We generate the pawns, the players and we put them in a Game struct

    // Pawns (I don't use the typedef bc of IDE which doesn't understand as well
    Pawn pawn = {0, '0', 0, 0, 3, 3, 1, 1, 1};
    Pawn pawn2 = {0, '0', 0, 0, 3, 3, 1, 1, 1};
    Pawn pawns[10];
    pawns[0] = pawn;
    Pawn pawns2[10];
    pawns2[0] = pawn2;
    Pawn pawns_all = {pawns, pawns2};
    void *pawns_all_ptr;
    pawns_all_ptr = &pawns_all;
    fprintf(stderr, "Pointer to pawns_all : %d\n", (int) pawns_all_ptr);
    int a;
    a = (int) pawns_all_ptr;
    fprintf(stderr, "Pawn: %d\n,", a);

    //pause();

    int **map = init_map(28, 16);
    fprintf(stderr, "AAA\n", a);
    Player *players = init_players(2); // list with all the players

    SDL_Rect current_pos, action_pos;
    SDL_Event event;

    place_characters(map, players);
    display_map(screen, map);

*/

void play_game(SDL_Surface *screen)
{
    int player, action;
    int turn = 0, pawn_ct = 0, round = 0; // Counters
    SDL_Rect pos;
    pos.x = 4;
    pos.y = 4;
    //  We generate the pawns, the players and we put them in a Game struct

    // Pawns (I don't use the typedef bc of IDE which doesn't understand as well
    // Unique declaration of each pawn
    /*Pawn pawn_scout_1_player_1 = {0, 'S', 1, FALSE, 5, 5, TRUE};
    Pawn pawn_scout_2_player_1 = {1, 'S', 1, FALSE, 5, 5, TRUE};
    Pawn pawn_infantry_1_player_1 = {2, 'I', 1, FALSE, 3, 3, TRUE};
    Pawn pawn_shocktroop_1_player_1 = {3, 'T', 1, FALSE, 3, 3, TRUE};
    Pawn pawn_scout_1_player_2 = {4, 'S', 2, FALSE, 3, 3, TRUE};
    Pawn pawn_scout_2_player_2 = {5, 'S', 2, FALSE, 3, 3, TRUE};
    Pawn pawn_infantry_1_player_2 = {6, 'I', 1, FALSE, 3, 3, TRUE};
    Pawn pawn_shocktroop_1_player_2 = {7, 'T', 1, FALSE, 3, 3, TRUE};
    */
    // dynamic array for pawns

    Pawn *ptr;
    ptr = (Pawn*) malloc(8 * sizeof(Pawn));

    int i;
    // allocate 100 pointers, effectively an array
    Pawn **t_array = malloc(8 * sizeof(Pawn *));

    // allocate 100 structs and have the array point to them
    for (int i = 0; i < 8; i++)
    {
        t_array[i] = malloc(sizeof(Pawn));
    }

    // Fill each pawn in this order for each player:
    // 2 S, 1 I, 1 T
    for (int i = 0; i < 8; i++)
    {
        t_array[i]->id = i;

        if (i%PAWNS == 0 || i%PAWNS==1)
        {
            t_array[i]->type = 'S';
        }
        else
        {
            if (i%PAWNS == 2)
            {
                t_array[i]->type = 'I';
            }
            else
            {
                if (i%PAWNS == 3)
                {
                    t_array[i]->type = 'T';
                }
                else
                {
                    t_array[i]->type = 'X';

                }
            }
        }
        if (i <PAWNS)
        {
            t_array[i]->player_id=0;
        }
        else
        {
            t_array[i]->player_id=1;
        }
        t_array[i]->hasEnemyFlag=FALSE;
        t_array[i]->max_displacement=5;
        t_array[i]->displacement_left=5;
        t_array[i]->alive=TRUE;
    }

    // now define a pointer to the array
    Pawn ***p = &t_array;

    for (int i = 0; i < 8; i++)
    {
        fprintf(stderr, "ID: %2d Type: %c Player Id: %d  Max Displacement: %d\n", (*p)[i]->id, (*p)[i]->type,(*p)[i]->player_id, (*p)[i]->max_displacement);
    }

    //ptr[0] = Pawn pawn_scout_1_player_1 = {0, 'S', 1, FALSE, 5, 5, TRUE};

    /*fprintf(stderr, "Pointer to pawns ptr : %d\n", (int) ptr);
    fprintf(stderr, "Pointer to pawn scout 1 p1 : %d\n", (int) &pawn_scout_1_player_1);
    fprintf(stderr, "Pointer to pawn scout 1 p1 : %d\n", (int) &pawn_scout_2_player_1);
    fprintf(stderr, "Pointer to pawn scout 1 p1 : %d\n", (int) &ptr[0]);
    fprintf(stderr, "Pointer to pawn scout 1 p1 : %d\n", (int) &ptr[1]);*/

    /*Pawn pawns[10];
    pawns[0] = pawn;
    Pawn pawns2[10];
    pawns2[0] = pawn2;
    Pawn pawns_all = {pawns, pawns2};
    void *pawns_all_ptr;
    pawns_all_ptr = &pawns_all;
    fprintf(stderr, "Pointer to pawns_all : %d\n", (int) pawns_all_ptr);
    int a;
    a = (int) pawns_all_ptr;
    fprintf(stderr, "Pawn: %d\n,", a);

    fprintf(stderr, "Pointer to pawns: %d\n", (int) &pawn);
    a = (int) &pawn;


    fprintf(stderr, "Pawn: %d\n,", a);
    //pause();
    */
    int **map = init_map(NBR_BLOCK_X, NBR_BLOCK_Y);
    int **char_map = init_player_map(NBR_BLOCK_X, NBR_BLOCK_Y);

    //fprintf(stderr, "AAA\n", a);
    Player *players = init_players(2); // list with all the players

    SDL_Rect current_pos, action_pos;
    SDL_Event event;

    //place_characters(map, players);
    display_map(screen, map, char_map);

    for (turn = 0; turn < NBR_TOUR_MAX; turn++)
    {
        for (round = 0; round < NBR_PLAYERS * NBR_TOUR_MAX; round++)
        {
            for (player = 0; player < NBR_PLAYERS; player++)
            {
                for (pawn_ct = 0; pawn_ct < 5; pawn_ct++)
                {
                    fprintf(stderr, "Pawn: %d, player: %d, round: %d, turn:%d\n", pawn_ct, player, round, turn);
                    current_pos.x = find_x(char_map, CHARACTER0);
                    current_pos.y = find_y(char_map, CHARACTER0);

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

                        SDL_WaitEvent(&event);
                        switch (event.type)
                        {
                        case SDL_QUIT:
                            turn = player = pawn_ct = round = 10000;
                            // like a continue
                            break;
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                            case SDLK_ESCAPE:
                                turn = player = pawn_ct = round = 10000;
                                // like a continue
                                break;
                            case SDLK_UP:
                                action_pos.y--;
                                if (check_action(map, action_pos))
                                    move(char_map, current_pos, action_pos);
                                break;
                            case SDLK_DOWN:
                                action_pos.y++;
                                if (check_action(map, action_pos))
                                    move(char_map, current_pos, action_pos);
                                break;
                            case SDLK_LEFT:
                                action_pos.x--;
                                if (check_action(map, action_pos))
                                    move(char_map, current_pos, action_pos);
                                break;
                            case SDLK_RIGHT:
                                action_pos.x++;
                                if (check_action(map, action_pos))
                                    move(char_map, current_pos, action_pos);
                                break;
                            }
                            break;

                        }
                        // CHECK WIN

                        display_map(screen, map, char_map);
                        display_info(screen, pawn_ct, player, round, turn);
                        //    pause();

                    }
                }
            }
        }
    }
    //pause();


    // Memory Free

    for (player = 0; player < NBR_BLOCK_Y; player++)
        free(map[player]);
    free(map);

    free(players);


}

