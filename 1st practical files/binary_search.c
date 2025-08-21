#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void generate_random_array(int* arr, int size){
    for(int i=0; i<size; i++){
        arr[i]=rand()%(size*10);
    }
}

int binary_search(int * arr, int size, int key){
    int l=0;
    int r=size-1;
    int mid;
    while(r>=l){
        mid=l+ (r-l)/2;
        if(arr[mid]==key){
            return mid;
        }
        else if(arr[mid]<key){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    return -1;
}

int main(){
    int size_arr[11]={1,10,50,100,500,1000,3000,5000,6000,7000,8000};

    FILE *f = fopen("results.txt", "w");
    if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Array Size\tTime (seconds)\n");
    printf("-------------------------------\n");
    fprintf(f, "ArraySize Time\n");  // header for Python

    for(int i=0;i<11;i++){
        int size=size_arr[i];
        int arr[size];

        generate_random_array(arr,size);

        qsort(arr, size, sizeof(int), compare);//sorting

        clock_t start = clock();
        for (int k=0;k<10000;k++){
            binary_search(arr,size,arr[0]);         // always search for 1st element in binary
        }
        clock_t end = clock();
        double time = ((double)(end-start))/CLOCKS_PER_SEC;

        
        printf("%d\t\t%f\n", size, time);
        // write to file
        fprintf(f, "%d %f\n", size, time);
    }

    fclose(f);
    return 0;
}
