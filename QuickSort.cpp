//
// Algorithm Practice - Quick Sort
//
// Mingjie Li (limingjie0719@gmail.com)
// Mar 11, 2014
//
// Compiled with
// - MinGW g++ 4.8.2
// - Visual Studio Express 2013
//

#include <iostream>
#include <cstdlib> // rand()
#include <ctime>   // time()

const int ArraySize = 20;

template <typename T>
void print(T *arr, int size = ArraySize)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
inline void swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

// Find median of three, and swap it with right most element
template <typename T>
void median_of_three(T *arr, int left, int right)
{
    // (left + right) / 2 may exceed INT_MAX
    int mid = left + (right - left) / 2;
    T l = arr[left], m = arr[mid], r = arr[right];

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
template <typename T>
int hoare_partition(T *arr, int left, int right)
{
    std::cout << "left = " << left
        << ", right = " << right << std::endl;

    int keep = right;
    T pivot = arr[right--];

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

template <typename T>
int partition(T *arr, int left, int right)
{
    std::cout << "left = " << left
        << ", right = " << right << std::endl;

    T pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[++i], arr[right]);

    print(arr);
    return i;
}

template <typename T>
void quicksort(T *arr, int left, int right)
{
    int pivot;

    if (left < right)
    {
        median_of_three(arr, left, right);
        // pivot = hoare_partition(arr, left, right);
        pivot = partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}

int main()
{
    double arr[ArraySize];

    srand((unsigned int)time(NULL));
    for (int i = 0; i < ArraySize; i++)
    {
        arr[i] = rand() % 9000 / 100.0 + 10;
    }

    print(arr);
    quicksort(arr, 0, ArraySize - 1);

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();

    return 0;
}
