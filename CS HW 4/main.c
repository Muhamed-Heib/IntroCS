#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY '_'
#define MAX 100
#define NUM_LETTERS 26
#define NUM_POOLS 2



void print_enter_pool_character()
{
    printf("Enter new character for the pool\n");
}

char get_new_pool_character()
{ // Receives a new character from the user to insert to the pool, and returns this character
    char c;
    scanf(" %c",&c);
    return c;

}

void print_board(char** board,int size)
{ //Print the current state of the given board of size sizeXsize
    printf("Current Board:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("| %c |", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


void prompt_vocab_words()
{
    printf("Enter Vocabulary Words: \n");
}

void get_word_for_vocab(char* word_address)
{ //Receives a single word for the vocabulary from the user, and saves it in the address passed as parameter
    scanf("%s",word_address);
}

void print_scores(int score1,int score2)
{ //Prints the current scores of both players. 'score1' is the score of player 1, 'score2' is the score of player 2
    printf("Player 1 Score: %d\nPlayer 2 Score: %d\n", score1,score2);
}



int input_game_constant(char* prompt)
{ //Recevies from the user a single
    printf("%s\n",prompt);
    int value;
    while (1) {

        if (scanf("%d", &value) != 1) {
            // If scanf fails, clear the input buffer

            scanf("%*s");
            printf("Invalid input. Please Re-enter.\n");
        }
        else if (value < 1)
        {
            printf("Invalid input. Please Re-enter.\n");
        }
        else {
            return value;
        }
    }

}


int input_game_size()
{
    return input_game_constant("Enter Board Size");
}


int input_pool_size()
{
    return input_game_constant("Enter Character Pool Size");
}

int input_time_limit()
{
    return input_game_constant("Enter Game Time Limit");
}

int input_score_limit()
{
    return input_game_constant("Enter Game Score Limit");
}

//void con_character(char character, )// complete



void get_turn_inputs(char* character,int* row, int* col)
{
    scanf(" %c %d %d",character,row,col);
}

void prompt_turn_player(int player_idx)
{
    printf("Player %d, Enter Turn character, board row and board column:\n",player_idx);
}




void print_pool(char* pool1, char* pool2,int pool_size)
{
    printf("Current Pools:\n");
    printf("Pool1: ");
    for (int i = 0; i < pool_size; i++)
        printf(" %c,",pool1[i]);
    printf("\n");
    printf("Pool2: ");
    for (int i = 0; i < pool_size; i++)
        printf(" %c,",pool2[i]);
    printf("\n");

}



void invalid_turn_character_choice()
{
    printf("Invalid Choice! Character not available to you.\nPlease Re-enter:\n");
}
void taken_turn_placement_choice()
{
    printf("Invalid Choice! Placement choice taken.\nPlease Re-enter:\n");
}
void out_of_bounds_turn_choice()
{
    printf("Invalid Choice! Placement Out Of Board Bounds.\nPlease Re-enter:\n");
}

void print_achieved_score(int score)
{
    printf("Achieved Score: %d!\n", score);
}

void print_winner(int player_idx,int score)
{
    printf("Player %d Wins! Score: %d", player_idx, score);
}

void print_tie(int score)
{
    printf("Tie! Score: %d",score);
}



int get_vocab_size()
{
    int size;
    printf("Enter Vocabulary Size: \n");
    scanf("%d", &size);
    return size;
}

void prompt_pool_character_input(int player_idx)
{//Prompt player <player_idx> to provide character to insert to his pool
    printf("Enter Characters For Pool %d\n",player_idx);

}

/*void target_words_input(char word[MAX][MAX],int n){
    prompt_vocab_words();
    for(int i=0;i<n;i++){
        get_word_for_vocab(word[i]);
    }
}*/

void construct_words(char*** word,int n){
    (*word)=(char**)malloc(sizeof(char*)*n);
    if((*word)==NULL){printf("error");}
    for(int i=0; i<n;i++){
        (*word)[i]=(char*)malloc(sizeof(char)*(MAX+1));
        if((*word)[i]==NULL){printf("error");}
    }
    for(int i=0;i<n;i++){
        get_word_for_vocab((*word)[i]);
    }
}


void construct_pools(char*** pool, int L) {
    *pool = (char**)malloc(sizeof(char*) * 2);
    if((*pool)==NULL){printf("error");}
    for (int i = 0; i < 2; i++) {
        (*pool)[i] = (char*)malloc(sizeof(char) * L);
        if((*pool)[i]==NULL){printf("error");}
    }

    prompt_pool_character_input(1);
    for(int i=0;i<L;i++){
        (*pool)[0][i]=get_new_pool_character();
    }
    prompt_pool_character_input(2);
    for(int i=0;i<L;i++){
        (*pool)[1][i]=get_new_pool_character();
    }
}




void start(int *N,int *L,int *T,int *S, int *n, char*** word)//, int *player)
{
    printf("************** Welcome To The Scrabbles Game! **************\n");
    *N=input_game_size();
    *L=input_pool_size();
    *T=input_time_limit();
    *S=input_score_limit();
    *n=get_vocab_size();
    prompt_vocab_words();
    construct_words(word, *n);

}

void construct_board(char*** board,int N){
    (*board)=(char**)malloc(sizeof(char*)*N);
    if((*board)==NULL){printf("error");}
    for(int i=0;i<N;i++){
        (*board)[i]=(char*)malloc(sizeof(char)*N);
        if((*board)[i]==NULL){printf("error");}
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            (*board)[i][j]=EMPTY;
        }
    }
}

int cond(char *aot,int *row, int *col,int N,char** pool,int L, char** board,
         int curr_player,int* index){
    *index = -1;
    get_turn_inputs(aot, row, col);
    for(int j=0;j<L;j++){
        if(pool[curr_player-1][j]==*aot && *index == -1){
            *index=j;
        }
    }
    if(*index==-1){
        invalid_turn_character_choice();
        return 0;
    }
    if(*row < 0 || *row >= N || *col < 0 || *col >= N){
        out_of_bounds_turn_choice();
        return 0;
    }
    if(board[*row][*col]!=EMPTY){
        taken_turn_placement_choice();
        return 0;
    }
    board[*row][*col] = *aot;
    return 1;
}


void print_get_pool(char*** pool,int player, int index){
    print_enter_pool_character();
    *pool[player][index]=get_new_pool_character();
}


void horizental_vertical(int row,int col,char** board,int N, char **horizental,
                         char** vertical){
    int temp_col=col;
    while(temp_col>= 0 && board[row][temp_col] != EMPTY){
        temp_col --;
    }
    temp_col ++;

    int temp_row=row;
    while(temp_row>= 0 && board[temp_row][col] != EMPTY){
        temp_row --;
    }
    temp_row ++;


    for(int i=0;i<N;i++){

        if((temp_col+i < N) && board[row][temp_col+i] != EMPTY){
            (*horizental)[i] = board[row][temp_col+i];}
        else
            (*horizental)[i] = 0;
        if((temp_row+i < N) && board[temp_row+i][col] != EMPTY){
            (*vertical)[i] = board[temp_row+i][col];}
        else
            (*vertical)[i]=0;
    }
    (*horizental)[N]=0;
    (*vertical)[N]=0;

}

int calc_word_score(char* word){
    int sum=0;
    int i=0;
    while(word[i] != 0){
        sum += ((word[i]-'a'+1)%7);
        i++;
    }
    if(sum!=0){
        print_achieved_score(sum);}
    return sum;
}



int check(char** board,int row, int col,int N,char** word, int n){
    char (*vertical)=(char*)malloc(sizeof(char)*(N+1));
    if((vertical)==NULL){printf("error");}
    char (*horizental)=(char*)malloc(sizeof(char)*(N+1));
    if((horizental)==NULL){printf("error");}
    horizental_vertical(row, col, board, N, &horizental, &vertical);


    int score=0;



    for(int i=0;i<n;i++){
        if(strcmp(word[i],horizental)==0){

            score += calc_word_score(word[i]);
        }

        if(strcmp(word[i],vertical)==0){

            score += calc_word_score(word[i]);
        }


    }

    free(vertical);
    free(horizental);


    return score;
}

int end_game(char **board,int N,int score[], int S,int T,int count){
    if (T < count){
        return 1;
    }
    if (score [0] >= S || score[1] >= S){
        return 1;
    }
    for(int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (board[i][j] == EMPTY){
                return 0;
            }
        }
    }
    return 1;
}



void change_pool(int player, int index,char** pool){
    print_enter_pool_character();
    char new_aot= get_new_pool_character();
    pool [player-1][index] = new_aot;
}




void print_all(char** board, int N, char** pool,int L, int* score){
    print_board(board, N);
    print_pool(pool[0], pool[1], L);
    print_scores(score[0],score[1]);
}

void play_game(int N, int L,int T,int S,int n,char** word,char** pool,
               char **board,int *score){
    int row , col,count =1,player=1,index;
    char aot;

    print_board(board, N);
    print_pool(pool[0], pool[1], L);
    while (end_game(board, N, score, S, T, count)==0){

        prompt_turn_player(player);
        while(cond(&aot,&row, &col, N, pool, L, board, player,&index )==0){

        }
        change_pool(player,index,pool);
        int curr_score = check( board, row, col, N, word,n);
        score[player-1] +=curr_score;
        print_all(board, N, pool, L, score);

        count ++;
        player = (player==1)? 2 : 1;
    }
}


void free_all(char** word,char **pool,char** board,int N, int n ){
    for(int i=0;i<N;i++){
        free(board[i]);
    }
    free(board);
    for(int i=0;i<n;i++){
        free(word[i]);
    }
    free(word);
    for(int i=0;i<2;i++){
        free(pool[i]);
    }
    free(pool);
}

int main()
{
    int N, L, T, S, n, score[2]={0,0};
    char **word, **pool, **board, aot;
    start(&N, &L, &T, &S, &n, &word);//   ,&player);
    construct_pools( &pool, L);
    construct_board(&board, N);


    play_game( N,  L, T, S, n, word, pool,board,score);


    if(score[0]>score[1]){
        print_winner(1,score[0]);
    }
    if(score[0]<score[1]){
        print_winner(2,score[1]);
    }
    if(score[0] == score[1]){
        print_tie(score[0]);
    }
    free_all( word,pool, board, N,  n );
    return 0;
}