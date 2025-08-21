#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int* arr, int size){
for(int i=0; i<size; i++){
            arr[i] = rand() % (size * 10);
    }
    }

int linear_search(int *arr, int size, int key){
        for(int i = 0; i < size; i++){
            if(arr[i] == key){
            return i;
            }
    }
    return -1;
}

int main(){
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
 
        generate_random_array(arr, size);

         clock_t start = clock();
        for (int k=0; k<10000; k++){
            linear_search(arr, size, arr[size-1]); // always search last element
        }
         clock_t end = clock();
        double time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // print 
        printf("%d\t\t%f\n", size, time);
        // write to file
        fprintf(f, "%d %f\n", size, time);
        }

    fclose(f);
    return 0;
}
