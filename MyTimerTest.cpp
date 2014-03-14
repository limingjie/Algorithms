#include <iostream>
#include <cstdlib> // rand()
#include <ctime>   // time()
#include <ratio>   // std::nano
#include "MyTimer.hpp"

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

template <typename T>
int partition(T *arr, int left, int right)
{
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

    return i;
}

template <typename T>
void quicksort(T *arr, int left, int right)
{
    int pivot;

    if (left < right)
    {
        median_of_three(arr, left, right);
        pivot = partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}

int main()
{
    const int ArraySize = 100000;
    const int LoopTimes = 1000;
    double arr[ArraySize];

    srand((unsigned int)time(NULL));

    MyTimer<double, std::micro> timer;
    std::cout << "QuickSort " << ArraySize << " double numbers for "
        << LoopTimes << " times" << std::endl;
    
    MyTimer<double, std::micro> timer;
    for (int j = 0; j < LoopTimes; j++)
    {
        for (int i = 0; i < ArraySize; i++)
        {
            arr[i] = rand() % 9000 / 100.0 + 10;
        }
        quicksort(arr, 0, ArraySize - 1);
    }
    
    return 0;
}
