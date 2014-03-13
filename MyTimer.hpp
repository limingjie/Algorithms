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
#include <random> // minstd_rand0 & uniform_int_distribution
#include <string>
#include <iostream>

//
// MyTimer - Measure execution time of function or any piece of code.
//
// Prerequisite - c++11 libraries <chrono> & <random>
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

typedef std::chrono::high_resolution_clock hr_clock;
typedef std::chrono::duration<hr_clock::rep, hr_clock::period> hr_clock_duration;

template <typename T = int, typename R = std::milli>
class MyTimer
{
public:
    MyTimer(std::string name = "")
    {
        mp_is_paused = false;
        mp_duration = hr_clock_duration::zero();
        mp_id = getId();
        mp_name = (name.size() == 0) ? "" : ("[" + name + "]");
        
        std::cout << "Timer [" << "#" << mp_id << "] " << mp_name << " Started..." << std::endl;

        // Always start timer at the end of constructor
        mp_time_point = hr_clock::now();
    }

    virtual ~MyTimer()
    {
        using namespace std::chrono;

        // Always end timer at the beginning of destructor
        mp_duration += hr_clock::now() - mp_time_point;
        std::cout << "Timer [" << "#" << mp_id << "] " << mp_name << " Stopped. Elapsed: "
            << duration_cast<duration<T, R>>(mp_duration).count()
            << " x (" << R::num << '/' << R::den << ") seconds ["
            << duration_cast<duration<double>>(mp_duration).count() << "s / "
            << duration_cast<duration<double, std::milli>>(mp_duration).count() << "ms / "
            << duration_cast<duration<double, std::nano>>(mp_duration).count() << "ns]"
            << std::endl;
    }

    void pause()
    {
        if (!mp_is_paused)
        {
            mp_duration += hr_clock::now() - mp_time_point;
            mp_is_paused = true;
        }
    }

    void resume()
    {
        if (mp_is_paused)
        {
            mp_is_paused = false;
            mp_time_point = hr_clock::now();
        }
    }

private:
    hr_clock::time_point mp_time_point;
    hr_clock_duration mp_duration;
    bool mp_is_paused;

    std::string mp_name;
    unsigned int mp_id;

    static bool is_seeded;
    static std::minstd_rand0 generator;
    static std::uniform_int_distribution<int> distribution;

    unsigned int getId()
    {
        if (!is_seeded)
        {
            generator.seed(std::chrono::high_resolution_clock::now()
                           .time_since_epoch().count());
            is_seeded = true;
        }

        return distribution(generator);
    }
};

template <typename T, typename R>
bool MyTimer<T, R>::is_seeded = false;

template <typename T, typename R>
std::minstd_rand0 MyTimer<T, R>::generator;

template <typename T, typename R>
std::uniform_int_distribution<int> MyTimer<T, R>::distribution(1000000, 9999999);
