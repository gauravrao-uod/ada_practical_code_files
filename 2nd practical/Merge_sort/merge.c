#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int* arr, int size){
for(int i=0; i<size; i++){
            arr[i] = rand() % (size * 10);
    }
    }


void merge(int * arr,int l,int m,int r)
{
    int L[m-l+1];
    int R[r-m];
    for(int i=0;i<m-l+1;i++)
    {
        L[i]=arr[l+i];
    }
    for(int i=0;i<r-m;i++)
    {
        R[i]=arr[m+1+i];
    }
    int j=0,k=0;
for(int i=0;i<r-l+1;i++){
    if( (k==r-m) || (j<m-l+1 && L[j]<R[k]))
    {
        arr[l+i]=L[j];
        j++;
    }
    else 
    {
        arr[l+i]=R[k];
            k++;
        
    }
}
}
void merge_sort(int* arr, int l, int r){
if(l<r)
{
    int m=(l+r)/2;
    merge_sort(arr,l,m);
    merge_sort(arr,m+1,r);
    merge(arr,l,m,r);
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
            merge_sort(arr,0, size-1);
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