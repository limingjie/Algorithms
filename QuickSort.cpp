//
// Algorithm Practice - Quick Sort
//
// Author: Mingjie Li (limingjie0719@gmail.com)
// Date  : Mar 11, 2014
//

#include <iostream>
#include <cstdlib> // rand()
#include <ctime>   // time()

const int arraySize = 30;

void print(int *arr)
{
    for (int i = 0; i < arraySize; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

inline void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Hoare partition
int hoare_partition(int *arr, int left, int right, int pivot)
{
    if (pivot != right)
    {
        swap(arr[pivot], arr[right]);
        pivot = right;
    }
    int p = arr[right--];

    std::cout << "left = " << left
        << ", right = " << right
        << ", pivot = " << arr[pivot] << std::endl;

    while (true)
    {
        while (arr[left] < p) left++;
        while (right >= left && arr[right] >= p) right--;
    
        if (left < right)
        {
            swap(arr[left], arr[right]);
        }
        else
        {
            if (left != pivot) swap(arr[left], arr[pivot]);
            break;
        }
    }

    print(arr);
    return left;
}


int partition(int *arr, int left, int right, int pivot)
{
    if (pivot != right)
    {
        swap(arr[pivot], arr[right]);
        pivot = right;
    }
    int p = arr[right--];

    std::cout << "left = " << left
        << ", right = " << right
        << ", pivot = " << arr[pivot] << std::endl;

    if (pivot != right)
    {
        swap(arr[pivot], arr[right]);
        pivot = right--;
    }
    int p = arr[pivot];

    // TODO: partition

    print(arr);
    return left;
}

void quicksort(int *arr, int left, int right)
{
    int pivot;

    if (left < right)
    {
        // TODO: better pivot
        pivot = hoare_partition(arr, left, right, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}

int main()
{
    int arr[arraySize];

    srand((unsigned int)time(NULL));
    for (int i = 0; i < arraySize; i++)
    {
        arr[i] = rand() % 89 + 10;
    }
    // arr[arraySize - 1] = 100;

    print(arr);
    quicksort(arr, 0, arraySize - 1);

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();

    return 0;
}
