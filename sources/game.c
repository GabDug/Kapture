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
    /*Pawn pawn = {0, '0', 0, 0, 3, 3, 1, 1, 1};
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

        fprintf(stderr, "Pointer to pawns: %d\n", (int) &pawn);
        a = (int) &pawn;


        fprintf(stderr, "Pawn: %d\n,", a);*/
    //pause();

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
                            turn = NBR_TOUR_MAX + 2;
                            pawn_ct = 100;// like a continue
                            break;
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym)
                            {
                            case SDLK_ESCAPE:
                                turn = NBR_TOUR_MAX + 2;
                                pawn_ct = 100;// like a continue
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
    pause();


    // Memory Free

    for (player = 0; player < NBR_BLOCK_Y; player++)
        free(map[player]);
    free(map);

    free(players);


}

