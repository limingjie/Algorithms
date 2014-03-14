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
#include <chrono> // high_resolution_clock (seed random number generator)
#include <random> // minstd_rand0 & uniform_real_distribution
#include "Stopwatch.hpp" // Stopwatch

template <typename T>
void print(T *arr, int size)
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

    return left;
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
        // pivot = hoare_partition(arr, left, right); // about 10%~15% slower, why?
        pivot = partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}

int main()
{
    const int OutterLoop = 5;
    const int InnerLoop  = 1000;
    const int ArraySize  = 100000;
    double arr[ArraySize];

    auto seed = std::chrono::high_resolution_clock::now()
                .time_since_epoch().count();
    std::minstd_rand0 generator(seed);
    std::uniform_real_distribution<double> distribution(10.00, 99.99);

    std::cout << "Loop " << OutterLoop << " times." << std::endl;
    for (int k = 0; k < OutterLoop; k++)
    {
        std::cout << std::endl << "QuickSort " << ArraySize << " double numbers "
            << InnerLoop << " times." << std::endl;

        Stopwatch<double> time("Total");
        Stopwatch<double> time_sort("QuickSort");
        Stopwatch<double> time_array("Generate Array");

        std::cout << "Sorting..." << std::endl;
        time.start();

        for (int j = 0; j < InnerLoop; j++)
        {
            time_array.start();
            for (int i = 0; i < ArraySize; i++)
            {
                arr[i] = distribution(generator);
            }
            time_array.pause();
            time_sort.start();
            quicksort(arr, 0, ArraySize - 1);
            time_sort.pause();
        }
        time.pause();
    }

    return 0;
}
