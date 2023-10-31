//Odd-Even Transposition Sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

int print_array(int array[]);
int odd_even_trans(int array[]);
int initialize_array(int array[]);
int swap_elements(int* num1, int* num2);

int main(){

   int* array;
   clock_t start, end;
   double time = 0.0;
   array = malloc(SIZE*sizeof(int));
   
   initialize_array(array);

   //printf("Unsorted array : ");
   //print_array(array);

   start = clock();
   odd_even_trans(array);
   end = clock();

   //printf("Sorted array : ");
   //print_array(array);
   
   time = (((double)(end-start))/CLOCKS_PER_SEC);
   printf("Sorting execution time : %lf s", time);

   free(array);

    return 0;
}

int initialize_array(int array[]){
    
    int i = 0;

    srand(time(0));  

    for(i = 0; i < SIZE; i++)
        array[i] = rand() % SIZE;

    return 0;

}

int print_array(int array[]){

    int i = 0;

    for(i = 0; i < SIZE; i++)
    printf("%d ", array[i]);
    printf("\n");

    return 0;

}

int odd_even_trans(int array[]){

    int i, j = 0;
    int counter = SIZE-1;

    for(i = 1; i <= SIZE; i++)
    {
        //Neparna faza - odd - index 0, ali prvi, neparni element
       if(i % 2 == 1)
       {
            for(j = 0; j < counter; j+=2)
            {
                if(array[j] > array[j+1])
                    swap_elements(&array[j], &array[j+1]);

            }
       }
        //Parna faza - even - index 1, ali drugi, parni element
       else
       {

            for(j = 1; j < counter; j+=2)
            {
              if(array[j] > array[j+1])
                    swap_elements(&array[j], &array[j+1]);

            }
       }
    }

    return 0;
}

int swap_elements(int* num1, int* num2){
    
    int temp = 0;

    temp = *num1;
    *num1 = *num2;
    *num2 = temp;

    return 0;
}

