#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int* arr, int size){
for(int i=0; i<size; i++){
            arr[i] = rand() % (size * 10);
    }
    }

void swap(int *i, int*j)
{
    int t= *i;
    *i=*j;
    *j=t;
}

void bubble_sort(int arr[], int size) {
    for (int j = size - 1; j > 0; j--) {
        int swapped = 0;  // Optimization flag
        for (int i = 0; i < j; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(&arr[i], &arr[i + 1]);
                swapped = 1;
            }
        }
        if (!swapped)
            break;  // Already sorted
    }
}

int main()
{
    srand(time(NULL));

 int size_arr[11] = {1,10,50,100,500,1000,3000,5000,6000,7000,8000};

  FILE *f = fopen("results.txt", "w");
   if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

     printf("Array Size\tTime (seconds)\n");
      printf("-------------------------------\n");
    fprintf(f, "ArraySize Time\n");  // header for Python

    for(int i=0; i<11; i++){
        int size = size_arr[i];
         int arr[size];
         
        double difference =0;
        
         clock_t start = clock();
        for (int k=0; k<1000; k++){
            
            generate_random_array(arr, size);

            clock_t start = clock();
            bubble_sort(arr, size);
            clock_t end = clock();
         
            difference += (double)(end -start);
        }
         
        double time = (difference) / CLOCKS_PER_SEC;

        // print 
        printf("%d\t\t%f\n", size, time);
        // write to file
        fprintf(f, "%d %f\n", size, time);
        }

    fclose(f);
    return 0;
}