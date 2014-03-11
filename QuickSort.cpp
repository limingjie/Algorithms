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

int partition(int *arr, int left, int right, int pivot)
{
    std::cout << "left = " << left
        << ", right = " << right
        << ", pivot = " << arr[pivot] << std::endl;

    while (true)
    {
        while (arr[left] < arr[pivot]) left++;
        while (arr[right] >= arr[pivot]) right--;

        if (left < right)
        {
            swap(arr[left], arr[right]);
        }
        else
        {
            swap(arr[left], arr[pivot]);
            break;
        }
    }

    print(arr);
    return left;
}

void quicksort(int *arr, int left, int right)
{
    int pivot;

    if (left < right)
    {
        // TODO: better pivot
        pivot = partition(arr, left, right - 1, right);
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

    print(arr);
    quicksort(arr, 0, arraySize - 1);

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();

    return 0;
}
