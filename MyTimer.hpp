//
// Algorithm Practice - Timer
//
// Mingjie Li (limingjie0719@gmail.com)
// Mar 13, 2014
//
// Compiled with
// - MinGW g++ 4.8.2
//
#include <chrono> // clock & duration
#include <ratio>  // ratio
#include <iostream>

//
// This class is to measure execution time of function or any piece of code.
//
// Prerequisite - c++11 is required for <chrono> library
//
// Usage -
//
// 1. Implicitly. Timer stops when out of scope.
//    {
//        MyTimer<> timer; // Timer starts...
//        [Some Code]
//    } // Timer stops since out of scope.
//
// 2. Explicitly. Timer stops by invoking destructor.
//    MyTimer<float> *timer = new MyTimer<float>(); // Timer starts...
//    [Some Code]
//    delete timer; // Timer stops by explicitly invoking destructor.
//
template <typename T = double, typename R = std::milli>
class MyTimer
{
public:
    MyTimer()
    {
        std::cout << "Timer Started..." << std::endl;
        
        // Always start timer at the end of constructor
        tp_start = std::chrono::high_resolution_clock::now();
    }
    
    ~MyTimer()
    {
        using namespace std::chrono;
        
        // Always end timer at the beginning of destructor
        tp_end = std::chrono::high_resolution_clock::now();
        auto t = tp_end - tp_start;
        std::cout << "Timer End. Elapsed: "
            << duration_cast<duration<T, R>>(t).count()
            << " x (" << R::num << '/' << R::den << ") seconds ["
            << duration_cast<duration<double>>(t).count() << "s / "
            << duration_cast<duration<double, std::milli>>(t).count() << "ms / "
            << duration_cast<duration<double, std::nano>>(t).count() << "ns]"
            << std::endl;
    }
    
private:
    std::chrono::system_clock::time_point tp_start;
    std::chrono::system_clock::time_point tp_end;
};
