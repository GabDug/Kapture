#include "headers/files.h"
#include "headers/constant.h"
#include <stdlib.h>
#include <stdio.h>

int loadFile(int **map)
{
    FILE *file = NULL;
    char fileLine[NBR_BLOCK_X * NBR_BLOCK_Y + 1] = {0};
    int i = 0, j = 0;

    file = fopen("map.txt", "r");
    if (file == NULL)
        return 0;

    fgets(fileLine, NBR_BLOCK_X * NBR_BLOCK_Y + 1, file);

    for (i = 0; i < NBR_BLOCK_X; i++)
    {
        for (j = 0; j < NBR_BLOCK_Y; j++)
        {
            switch (fileLine[(i * NBR_BLOCK_X) + j])
            {
            case '0':
                map[j][i] = 0;
                break;
            case '1':
                map[j][i] = 1;
                break;
            case '2':
                map[j][i] = 2;
                break;
            case '3':
                map[j][i] = 3;
                break;
            case '4':
                map[j][i] = 4;
                break;
            }
        }
    }

    fclose(file);
    return 1;
}

int saveFile(int map[][NBR_BLOCK_Y])
{
    FILE *file = NULL;
    int i = 0, j = 0;

    file = fopen("map.txt", "w");
    if (file == NULL)
        return 0;

    for (i = 0; i < NBR_BLOCK_X; i++)
    {
        for (j = 0; j < NBR_BLOCK_Y; j++)
        {
            fprintf(file, "%d", map[j][i]);
        }
    }

    fclose(file);
    return 1;
}

