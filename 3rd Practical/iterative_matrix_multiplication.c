#include<stdio.h>
#include<stdlib.h>
#include <time.h>
void randomMatrix(int * arr, int m1, int m2){
    int MaxValue=10;
    for (int i=0;i<m1;i++){
        for(int j=0;j<m2;j++){
            arr[i*m2+j]=rand()%MaxValue;
        }
    }
}
void zeroMatrix(int * arr, int m1, int m2){
    for (int i=0;i<m1;i++){
        for(int j=0;j<m2;j++){
            arr[i*m2+j]=0;
        }
    }
}


void Multiply(int * arr1,int m1, int m2, int * arr2, int n1, int n2, int * arr3){
if(m2!=n1){
    printf("error");
    return;
}
for(int i=0;i<m1;i++){
    for(int j=0;j<n2;j++){
        for(int k=0;k<n1;k++){
            arr3[i*n2+j]+=arr1[i*m2+k]*arr2[k*n2+j];
        }
    }
}

}

int main(){

srand(time(NULL));

 int size_matrix[11] = {1,2,3,4,5,6,7,8,9,10,11};
 int m1,m2,n1,n2;
  FILE *f = fopen("results.txt", "w");
   if (!f) {
        printf("Error opening file!\n");
        return 1;
    }

     printf("Matrix Size\tTime (seconds)\n");
      printf("-------------------------------\n");
    fprintf(f, "ArraySize Time\n");  // header for Python

for(int i=0; i<11; i++){
        int size = size_matrix[i];
        
        
        m1=size*3;
        m2=size*3;
        n1=size*3;
        n2=size*3;

        int * arr1=(int*)malloc(sizeof(int)*m1*m2);
        int * arr2=(int *)malloc(sizeof(int)*n1*n2);
        int * productMatrix=(int *)malloc(sizeof(int)*m1*n2);

        double difference =0;
        zeroMatrix(productMatrix, m1, n2);

        for (int k=0; k<10000; k++){
            
            randomMatrix(arr1, m1, m2);
            randomMatrix(arr2, n1, n2);
            
            clock_t start = clock();
            Multiply(arr1, m1, m2, arr2,n1,n2, productMatrix);
            clock_t end = clock();
         
            difference += (double)(end -start);
        }
         
        double time = (difference) / CLOCKS_PER_SEC;

        // print 
        printf("%d\t\t%f\n", size*3, time);
        // write to file
        fprintf(f, "%d %f\n", size*3, time);
        free(arr1); free(arr2); free(productMatrix);
        }

    fclose(f);
    

return 0;
}