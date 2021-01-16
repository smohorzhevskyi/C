// Надано масив A[N]. Якщо N – парне, знайти максимальний елемент,
// інакше – мінімальний.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quick_search(const void *, const void *);

int main()
{
    int N;

    printf("Enter the size of array: ");
    scanf("%d",&N);

    int randArray[N],i;
    int *ptr;
    ptr = randArray;

    srand(time(NULL));
    for (i=0;i<N;i++)
        *(ptr+i)=rand();
    printf("\nElements of the array:\n");

    for (i=0;i<N;i++)
        printf("\nElement number %d: %d",i+1,*(ptr+i));

    qsort(randArray,N,sizeof(int),quick_search);

    switch (N%2) {
        case 0:
            printf("\n\nMaximum element in array is %d.\n",*(ptr+N-1));
            break;
        default:
            printf("\n\nMinimum element in array is %d.\n",*ptr);
            break;
    }

    return (0);
}

int quick_search(const void *a, const void *b) {
    return ( *(int *)a - *(int *)b );
}
