#include <iostream>
#include <chrono>      // high_resolution_clock (seed random number generator)
#include <random>      // minstd_rand0 & uniform_real_distribution
#include <ratio>       // std::nano
#include "MyTimer.hpp" // MyTimer

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
    const int OutterLoop = 5;
    const int InnerLoop  = 100;
    const int ArraySize  = 100000;
    double arr[ArraySize];

    auto seed = std::chrono::high_resolution_clock::now()
                .time_since_epoch().count();
    std::minstd_rand0 generator(seed);
    std::uniform_real_distribution<double> distribution(10.00, 99.99);
    
    std::cout << "Loop " << OutterLoop << " times." << std::endl;
    MyTimer<double> timer;
    for (int k = 0; k < OutterLoop; k++)
    {
        std::cout << std::endl << "QuickSort " << ArraySize << " double numbers "
            << InnerLoop << " times." << std::endl;

        MyTimer<double> timer;
        
        std::cout << "Sorting..." << std::endl;

        for (int j = 0; j < InnerLoop; j++)
        {
            for (int i = 0; i < ArraySize; i++)
            {
                arr[i] = distribution(generator);
            }
            quicksort(arr, 0, ArraySize - 1);
        }
    }
    
    std::cout << std::endl << "Overall time" << std::endl;

    return 0;
}
