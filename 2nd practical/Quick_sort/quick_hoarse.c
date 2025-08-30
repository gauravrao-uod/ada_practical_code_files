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
int hoarse_partition(int * arr, int l , int r)
{
    int pivot=arr[(l+r)/2];
    int i=l-1;
    int j=r+1;
    while(1)
    {
    do
    {
        i++;
    } while (arr[i]<pivot);
    do
    {
        j--;
    } while (arr[j]>pivot);
    
    if(i>=j)
    return  j;
    swap(&arr[i],&arr[j]);
    }
    
}

void hoarse_quicksort(int* arr, int l, int r)
{
    if(l<r){
        int p=hoarse_partition(arr, l,r);
        hoarse_quicksort(arr, l, p);
        hoarse_quicksort(arr, p+1, r);
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
            hoarse_quicksort(arr,0,size-1);
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