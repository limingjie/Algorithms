//
// Algorithm Practice - Quick Sort
//
// Author: Mingjie Li (limingjie0719@gmail.com)
// Date  : Mar 11, 2014
//

#include <iostream>
#include <cstdlib> // rand()
#include <ctime>   // time()

const int MAX = 20;

void print(int *arr)
{
    for (int i = 0; i < MAX; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int *partition(int *arr, int *left, int *right)
{
    int *p = right--;

    std::cout << left - arr << ' ' << right - arr << ' ' << *p << std::endl;

    while (right >= left)
    {
        while (*left < *p) left++;
        while (*right >= *p) right--;

        if (right > left)
        {
            swap(left, right);
        }
        else
        {
            swap(left, p);
            break;
        }
    }

    print(arr);
    return left;
}

void quicksort(int *arr, int *left, int *right)
{
    if (left < right)
    {
        int *p = partition(arr, left, right);
        quicksort(arr, left, p - 1);
        quicksort(arr, p + 1, right);
    }
}

int main()
{
    int arr[MAX];

    srand(time(NULL));
    for (int i = 0; i < MAX; i++)
    {
        arr[i] = rand() % 300;
    }

    print(arr);
    quicksort(arr, arr, arr + MAX - 1);
    print(arr);

    std::cout << "Press any key to exit." << std::endl;
    std::cin.get();

    return 0;
}
