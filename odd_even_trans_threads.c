//Odd-Even Transposition Sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define SIZE 1000
//Napomena : uzimamo u obzir da je početni index 0, ali je na tom indexu element 1 pa od 
//njega počinje odd faza, a od indexa 1, odnosno elementa 2 počinje even faza.

int print_array(int array[]);
int odd_even_trans(int array[]);
void* compare_elements(void* argument);
int initialize_array(int array[]);
int swap_elements(int* num1, int* num2);

int init_position = 0;

int main(){

   int* array;
   clock_t start, end;
   double time = 0.0;
   array = malloc(SIZE*sizeof(int));
   
   initialize_array(array);

   printf("Unsorted array : ");
   //print_array(array);

   start = clock();
   odd_even_trans(array);
   end = clock();

   printf("Sorted array : ");
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
    int num_threads = (SIZE+1)/2;
    pthread_t threads[num_threads];

    for(i = 1; i <= SIZE; i++)
    {
        //Neparna faza - odd
       if(i % 2 == 1)
       {
            init_position = 0;
            for(j = 0; j < num_threads; j++)
                pthread_create(&threads[j], NULL, compare_elements, array);
            
            for(j = 0; j < num_threads; j++)
                pthread_join(threads[j], NULL);
       }
        //Parna faza - even
       else
       {
            init_position = 1;
            for(j = 0; j < num_threads-1; j++)
                pthread_create(&threads[j], NULL, compare_elements, array);
            
            for(j = 0; j < num_threads-1; j++)
                pthread_join(threads[j], NULL);

       }
    }

    return 0;
}

void* compare_elements(void* array_arg){

    int index = init_position;
    int* array = (int*)array_arg;

    init_position += 2;

    if(array[index] > array[index+1] && (index+1) < SIZE){
        swap_elements(&array[index], &array[index+1]);
    }            
}

int swap_elements(int* num1, int* num2){
    
    int temp = 0;

    temp = *num1;
    *num1 = *num2;
    *num2 = temp;

    return 0;
}

