#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* DEFINEs*/
/* -------------------------------------------------------- */

/* N*M maze. N is the number of rows and M is the number of columns. */
#define N 4
#define M 5
/* Assuming each number has length of am most 10 characters. */
#define MAX_NUMBER_LENGTH 2

/* Maximum size of a two tuple with brackets ("(2,3)").
  +3 for the brackets and comma. */
#define MAX_TWO_TUPLE_WITH_BRACKETS_LENGTH (MAX_NUMBER_LENGTH*2+3)

/* Helper FUNCTIONS */
/* -------------------------------------------------------- */

bool find_path(int board_array[N][M], unsigned int totalWhiteTilesNumber,
               unsigned int row, unsigned int col);

bool find_path1(int board_array[N][M], unsigned int totalWhiteTilesNumber,
                unsigned int row, unsigned int col,unsigned int yellow_tiles);

/*
   get_tiles_string - Gets tiles from standard input.
   This function prints a message to the standard output and gets the tiles
   string from standard input.
   This function does not validate the input string other than basic validation.
   Inputs: tiles - the tiles string.
   Returns true if and only if the function gets the input successfully.
*/
bool get_tiles_string(char* tiles) {
    printf("Please enter the maze tiles.\n");
    printf("Example: (0,1),(1,2),(5,6),(2,3),(7,1)\n");
    return (scanf("%s", tiles) == 1);
}

bool valid_tile(char* s)
{
    unsigned int a, b;
    if (sscanf(s, "(%u,%u)", &a, &b) != 2)
        return false;
    return (a < N) && (b < M);
}

/*
   validate_input - Validates program input.
   Returns true if and only if the input is valid.
*/
bool validate_input(char* tiles) {
    while (*tiles != '\0')
    {
        if (!valid_tile(tiles)) {
            printf("Note: the tiles string contains an invalid tile.\n");
            return false;
        }
        while (*tiles != ')')
            ++tiles;
        ++tiles;
        if ((*tiles != ',') && (*tiles != '\0')) {
            printf("Note: the tiles string contains an invalid separator(non comma).\n");
            return false;
        }

        if (*tiles == ',')
            ++tiles;
    }
    return true;
}


void get_tile_position(char* tile,
                       unsigned int* row_ptr,
                       unsigned int* col_ptr) {
    sscanf(tile, "(%u,%u)", row_ptr, col_ptr);
}

/*
 Fill valid_tiles array with -1's in positions of tiles/source/destination.
 Assumes valid_tiles is initialized with zeros.
 returns : number of valid ties
   */
int fill_valid_tiles_array(char* tiles,
                           int valid_tiles[N][M]) {
    unsigned int row, column;
    int counter = 0;
    while (*tiles != '\0')
    {
        get_tile_position(tiles, &row, &column);
        valid_tiles[row][column] = -1;
        ++counter;
        while (*tiles != ')')
            ++tiles;
        ++tiles;
        if (*tiles == ',')
            ++tiles;
    }
    return counter;
}







/*
   main function.
   Inputs: none.
   Returns 0 when the program run successfully.
   Any other value indicates an error.
*/
int main() {
    unsigned int max_tiles_string_length;
    char* tiles = NULL;
    bool path_exist;
    int board_array[N][M] = { {0} }; /* Initialize the array with zeros. */
    /*
      Calculate the maximum length of the tiles string.
      (It is a function of n).
   */
    max_tiles_string_length = N * M *
                              (MAX_TWO_TUPLE_WITH_BRACKETS_LENGTH + 1) - 1;

    /* Allocate memory of the tiles string.
      +1 for the terminating null character. */
    tiles = (char*)malloc(max_tiles_string_length + 1);
    if (NULL == tiles) {
        printf("Memory allocation error\n");
        return 1;
    }

    if (!get_tiles_string(tiles))
        return 1;


    if (!validate_input(tiles)) {
        printf("ERROR: invalid input\n");
        return 2;
    }

    int white_tiles = 20 - fill_valid_tiles_array(tiles, board_array);

    path_exist = find_path(board_array, white_tiles, 0, 0);

    /* Print the results  */
    if (path_exist) {
        printf("Success ! There is a path !\n");
    }
    else
        printf("Failure ... There is no legal path ...\n");


    return 0;
}

/** Do not edit until here */
/** Do not edit until here */
/** Do not edit until here */

/** Put your implemnetation here: */
bool is_legal( unsigned int row,unsigned int col){
    if(row<0 || row>=4 || col <0 || col>=5){
        return false;
    }
    return true;
}

bool find_path1(int board_array[N][M], unsigned int totalWhiteTilesNumber,
               unsigned int row, unsigned int col,unsigned int yellow_tiles){

    if(yellow_tiles ==0 && totalWhiteTilesNumber ==0){
        return true;
    }
    if (!is_legal(row,col))
        return false;

    if(totalWhiteTilesNumber != 0){
        if(board_array[row][col] !=0){
            return false;
        }else{
            totalWhiteTilesNumber--;
        }
    }else{
        if(board_array[row][col]!=-1){
            return false;
        }else{
            yellow_tiles--;
        }
    }


    int temp=board_array[row][col];
    board_array[row][col]=1;

    if( find_path1(board_array,totalWhiteTilesNumber,
                  row+1,col+2,yellow_tiles)){
        return true;
    }
    if(find_path1(board_array,totalWhiteTilesNumber,
                 row+1,col-2,yellow_tiles)){
        return true;
    }
    if(find_path1(board_array,totalWhiteTilesNumber,
                 row-1,col+2,yellow_tiles)){
        return true;
    }
    if(find_path1(board_array,totalWhiteTilesNumber,
                 row-1,col-2,yellow_tiles)){
        return true;
    }
    if(find_path1(board_array,totalWhiteTilesNumber,
                 row+2,col+1,yellow_tiles)){
        return true;
    }
    if(find_path1(board_array,totalWhiteTilesNumber,
                 row+2,col-1,yellow_tiles)){
        return true;
    }
    if(find_path1(board_array,totalWhiteTilesNumber,
                 row-2,col+1,yellow_tiles)){
        return true;
    }
    if(find_path1(board_array,totalWhiteTilesNumber,
                 row-2,col-1,yellow_tiles)){
        return true;
    }
    if(temp==0){
        totalWhiteTilesNumber+=1;
    }else{
        yellow_tiles+=1;
    }

    board_array[row][col]=temp;
    return false;
}
bool find_path(int board_array[N][M], unsigned int totalWhiteTilesNumber,unsigned int row, unsigned int col){
    int yellow_tiles=N*M-totalWhiteTilesNumber;
    return (find_path1(board_array,totalWhiteTilesNumber,row,col,yellow_tiles));
}