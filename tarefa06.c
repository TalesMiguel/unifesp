
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char a[], char b[]) {
  char temp[20];
  strcpy(temp, a);
  strcpy(a, b);
  strcpy(b,temp);
}

void heapify(char *arr[], int n, int i) {
  int esq = 2 * i + 1, dir = 2 * i + 2, maior = i, tmp = 0;

  while (esq < n && arr[esq][tmp] == arr[maior][tmp]) tmp++;
  while (dir < n && arr[dir][tmp] == arr[maior][tmp]) tmp++;

  if (esq < n && arr[esq][tmp] > arr[maior][tmp]) maior = esq;

  if (dir < n && arr[dir][tmp] > arr[maior][tmp]) maior = dir;

  if (maior != i) {
    swap(arr[i], arr[maior]);
    heapify(arr, n, maior);
  }
}

void heapSort(char *arr[], int n) {
  int i;
  for (i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

  printf("build_heap:");
  for(i = 0; i < n; i++) printf(" %s", arr[i]);

  for (i = n - 1; i >= 0; i--) {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

int main() {
  int i, j, b, c;
  scanf("%d", &c);
  char *input[c];

  for (i = 0; i < c; i++) {
    char temp[20];

    scanf("%s", temp);
    int size = strlen(temp);
    input[i] = malloc(size*sizeof(char));
    strcpy(input[i], temp);

    for (j = 0; j < size; j++) {
      if(input[i][j]<97 || input[i][j]>122) {
        printf("a palavra %s eh invalida", input[i]);
        return 0;
      }
    }
  }
  scanf("%d", &b);
  char *heap[b];

  for (i = 0; i < b; i++) {
    int tmp, size;
    scanf("%d", &tmp);
    size = strlen(input[tmp]);
    heap[i] = malloc(size*sizeof(char));
    strcpy(heap[i], input[tmp]);
  }
  heapSort(heap, b);
  printf("\npalavras:");
  for(i = 0; i < b; i++) printf(" %s", heap[i]);
  return 0;
}
