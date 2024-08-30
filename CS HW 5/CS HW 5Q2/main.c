#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* DEFINEs*/
/* -------------------------------------------------------- */

/* N*M array. N is the number of rows and M is the number of columns. */
#define N 5
#define M 5


/* Helper FUNCTIONS */
/* -------------------------------------------------------- */

int findNum(int array[N][M], int num,unsigned int* row, unsigned int* col);


/*
   fill_array - fill the array from standard input.
   This function prints a message to the standard output and gets the numbers
   from standard input.
   This function does not validate the input  other than basic validation.
   Inputs: the numbers in the array, row by row, from left to right
   Returns true if and only if the function gets the input successfully.
*/
bool fill_array(int array[N][M]) {
    printf("Please enter the array.\n");
    printf("Example:1 3 7 8 12 \n");
    printf("        14 20 23 37 41 \n");
    printf("        43 44 58 60 62 \n");
    printf("        73 89 102 114 165 \n");
    printf("        203 313 317 325 423 \n");
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            if(!scanf("%d", &array[i][j]))
                return false;
        }
    }
    return true;
}

/*
   main function.
   Inputs: none.
   Returns 0 when the program run successfully.
   Any other value indicates an error.
*/
int main() {

    printf("Insert a number\n");
    int num;
    if(!scanf("%d", &num))
        return 1;
    bool num_found;
    int array[N][M] = {{0}}; /* Initialize the array with zeros. */
    if (!fill_array(array))
        return 1;


    unsigned int row;
    unsigned int col;

    num_found =findNum(array, num, &row, &col);

    /* Print the results  */
    if (num_found) {
        printf("The number %d was found at row %d and col %d\n", num, row, col);
    }
    else
        printf("The number %d was not found in this array\n", num);

    return 0;
}

/******** Do not edit until here */
/******** Do not edit until here */
/******** Do not edit until here */

/******** Put your implemnetation here: */

bool binary_search(int array[N][M],int num, unsigned int *row, unsigned int *col){
    int low = 0;
    int high = 24;
    int mid;
    int midPointVal[2];
    while(low<=high){
        mid=(low+high)/2;
        midPointVal[0]=mid/5;
        midPointVal[1]=mid%5;
        if(array[mid/5][mid%5]==num){
            *row=midPointVal[0];
            *col=midPointVal[1];
            return true;
        }else if(array[mid/5][mid%5]>num){
            high=mid-1;
        }else {
            low = mid + 1;
        }
    }
    return false;
}



int findNum(int array[N][M], int num,unsigned int* row, unsigned int* col){
    if(binary_search(array,num,row,col)){
        return 1;
    }
    return 0;
}