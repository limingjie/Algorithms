//
// Algorithm Practice - Quick Sort
//
// Mingjie Li (limingjie0719@gmail.com)
// Mar 11, 2014
//

#include <iostream>
#include <cstdlib> // rand()
#include <ctime>   // time()

const int ArraySize = 30;

void print(int *arr, int size = ArraySize)
{
    for (int i = 0; i < size; i++)
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

// Find median of three, and swap it with right most element
void median_of_three(int *arr, int left, int right)
{
    // (left + right) / 2 may exceed INT_MAX
    int mid = left + (right - left) / 2;
    int l = arr[left], m = arr[mid], r = arr[right];

    if (l < r)
    {
        if (m < l)
            swap(arr[left], arr[right]);
        else if (m < r)
            swap(arr[mid], arr[right]);
        // else use right as median
    }
    else
    {
        if (l < m)
            swap(arr[left], arr[right]);
        else if (r < m)
            swap(arr[mid], arr[right]);
        // else use right as median
    }
}

// Hoare partition
int hoare_partition(int *arr, int left, int right)
{
    int keep = right;
    int pivot = arr[right--];

    std::cout << "left = " << left
        << ", right = " << right
        << ", pivot = " << pivot << std::endl;

    while (true)
    {
        while (arr[left] < pivot) left++;
        while (right >= left && arr[right] >= pivot) right--;
    
        if (left < right)
        {
            swap(arr[left], arr[right]);
        }
        else
        {
            if (left != keep) swap(arr[left], arr[keep]);
            break;
        }
    }

    print(arr);
    return left;
}

int partition(int *arr, int left, int right)
{
    int p = right;
    int pivot = arr[right--];

    std::cout << "left = " << left
        << ", right = " << right
        << ", pivot = " << pivot << std::endl;

    // TODO: partition

    print(arr);
    return left;
}

void quicksort(int *arr, int left, int right)
{
    int pivot;

    if (left < right)
    {
        median_of_three(arr, left, right);
        pivot = hoare_partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}

int main()
{
    int arr[ArraySize];

    srand((unsigned int)time(NULL));
    for (int i = 0; i < ArraySize; i++)
    {
        arr[i] = rand() % 89 + 10;
    }
    // arr[ArraySize - 1] = 0;

    print(arr);
    quicksort(arr, 0, ArraySize - 1);

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();

    return 0;
}
