#include<stdio.h>
#include<stdlib.h>

FILE*  open_input_file();
int** array_alloc(FILE* B, int N, int M);
int  array_test(int** A, int N, int M);
void array_remove(int** A, int N, int M, int fd);
void array_print(int**A, int N, int M);

int main (void){

  int** A;
  int N, M, fd;
  FILE* input_file;

  input_file = open_input_file();
  fscanf(input_file, "%d", &N);
  fscanf(input_file, "%d", &M);
  A = array_alloc(input_file, N, M);
  fd = array_test(A, N, M);
  array_remove(A, N, M, fd);
  array_print(A, N, M);
}

FILE* open_input_file(){
  FILE* input_file;
  input_file = fopen("F:/prog/data.dat", "r");
  if (NULL == input_file){
    printf("Файл с входными данными не обнаружен");
    exit(13);
  }
  return input_file;
}

int** array_alloc(FILE* input_file, int N, int M){
  int** A;
  A = (int**)malloc(N*sizeof(int*) + N*M*sizeof(int));
  int* start = (int*)((char*)A + N*sizeof(int*));
  for (int i = 0; i < N; i++)
    A[i] = start + i * M;
  for (int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      fscanf(input_file, "%d", &A[i][j]);
    }
  }
  return A;
}

int  array_test(int** A, int N, int M){
  int sum = 0, ar_mean;
  int fd = -1;
  for (int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      sum = sum + A[i][j];
    }
  }
  ar_mean = sum / (N * M);
  for (int j = 0; j < M; j++){
    for(int i = 0; i < N; i++){
      if (A[i][j] == ar_mean){
       fd = j;
         if (fd != -1){
         break;
        }
      }
    }
      if (fd != -1){
      break;
    }
  }
  if (fd == -1){
        printf("Нет элемента, удовлетворяющего условию\n");
        printf("\n");
        for (int i = 0; i < N; i++){
          for(int j = 0; j < M; j++){
            printf("%4d", A[i][j]);
          }
          printf("\n");
        }
        free (A);
        exit(10);
  }
  return fd;
}

void array_remove(int** A, int N, int M, int fd){
   int* adress;
   int i;
   for (int i = 0; i < N; i++){
     for (int j = fd; j < M - 1; j++){
       A[i][j] = A[i][j+1];
     }
   }
   for (int i = 0; i < N; i++){
   adress = &A[i][M-1];
   realloc(adress, 0);
   }
}

void array_print(int**A, int N, int M){
  for (int i = 0; i < N; i++){
    for(int j = 0; j < M - 1; j++){
      printf("%4d", A[i][j]);
    }
    printf("\n");
  }
  free(A);
  system ("pause");
}
