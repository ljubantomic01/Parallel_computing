#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 10
 
int* array;
int part = 0;
 
void merge(int low, int mid, int high);
void merge_sort(int low, int high);
int initialize_array(int array[]);
int print_array(int array[]);

int main()
{

    int low = 0;
    int high = SIZE-1;
    double time = 0.0;
    clock_t start, end;

    array = malloc(SIZE*sizeof(int));
    initialize_array(array);

    //printf("Unsorted array : ");
    //print_array(array);
 
    start = clock();

    merge_sort(low, high);
     
    end = clock();
    
    //printf("Sorted array : ");
    //print_array(array);

    time = (((double)end-start)/CLOCKS_PER_SEC);
    printf("Sorting execution time : %lf s", time);

    free(array);
 
    return 0;
}

void merge(int low, int mid, int high)
{
    int* left = malloc((mid-low+1)*sizeof(int));
    int* right = malloc((high-mid)*sizeof(int));

    int size_left = mid - low + 1;
    int size_right = high - mid;
    int i, j;
    
 
    //punjenje lijevog niza
    for (i = 0; i < size_left; i++)
        left[i] = array[i + low];
 
    //punjenje desnog niza
    for (i = 0; i < size_right; i++)
        right[i] = array[i + mid + 1];
 
    int k = low;
    i = j = 0;
 
    //stvaranje glavnog niza uspoređujući elemente lijevog i desnog
    while (i < size_left && j < size_right) {
        if (left[i] <= right[j])
            array[k++] = left[i++];
        else
            array[k++] = right[j++];
    }
 
    //dodavanje preostalih elemenata iz lijevog u glavni niz
    while (i < size_left) {
        array[k++] = left[i++];
    }
 
    //dodavanje preostalih elemenata iz desnog u glavni niz
    while (j < size_right) {
        array[k++] = right[j++];
    }

    free(left);
    free(right);
}
 
void merge_sort(int low, int high)
{
   
    if (low < high) {
        int mid = low + (high - low) / 2;
 
        // lijeva strana
        merge_sort(low, mid);
 
        // desna strana
        merge_sort(mid + 1, high);
 
        //spajanje
        merge(low, mid, high);
    }
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
