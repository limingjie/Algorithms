//
// Algorithm Practice - TickTimer
//
// Mingjie Li (limingjie0719@gmail.com)
// Mar 14, 2014
//
// Compiled with
// - MinGW g++ 4.8.2
// - Visual Studio Express 2013
//

#include <chrono> // clock, duration, time_point
#include <ratio> // ratio
#include <string> // string
#include <iostream> // cerr
#include <iomanip> // fmt

//
// TickTimer - Measure execution time of function or any piece of code.
//
// Prerequisite - c++11 libraries <chrono>
//
// - Use variable scope
//   {
//       TickTimer<double> timer("name", true); // Timer starts
//       [Some Code]
//   } // Timer stops since out of scope.
//
// - Use new / delete
//   // Timer declared and paused
//   TickTimer<> *timer = new TickTimer<>("name");
//   while (true)
//   {
//       timer->start();
//       [Core Logic]
//       timer->pause();
//       [Console Output]
//   }
//   delete timer; // Timer stops by explicitly invoking destructor.
//
template <typename T = int, typename R = std::milli>
class TickTimer
{
    typedef std::chrono::high_resolution_clock              hr_clock;
    typedef std::chrono::high_resolution_clock::duration    hr_duration;
    typedef std::chrono::high_resolution_clock::time_point  hr_time_point;

public:
    TickTimer(std::string name = "", bool ticking = false)
    {
        m_name     = name;
        m_ticking  = ticking;
        m_duration = hr_duration::zero();
        print();

        if (m_ticking) m_time_point = hr_clock::now();
    }

    virtual ~TickTimer()
    {
        pause();
        print(true);
    }

    void pause()
    {
        if (m_ticking)
        {
            m_duration += hr_clock::now() - m_time_point;
            m_ticking = false;
        }
    }

    void start()
    {
        if (!m_ticking)
        {
            m_ticking = true;
            m_time_point = hr_clock::now();
        }
    }

    inline void resume() { start(); }
    inline void stop()   { pause(); }

private:
    std::string    m_name;
    bool           m_ticking;
    hr_duration    m_duration;   // sum(pause - resume)
    hr_time_point  m_time_point; // Last time that starts ticking

    void print(bool isEnd = false)
    {
        using namespace std;
        using namespace std::chrono;

        ios::fmtflags fmt(cerr.flags()); // keep cerr format

        cerr << "Timer [" << left << setw(16) << m_name << right << "]";

        if (isEnd)
        {
            unsigned long long min, sec, msec, usec;

            usec = duration_cast<std::chrono::microseconds>(m_duration).count();
            min  =  usec / 60000000ULL;
            sec  = (usec /  1000000ULL) %   60ULL;
            msec = (usec /     1000ULL) % 1000ULL;

            // round usec remainder up to msec
            if ((usec % 1000ULL) >= 500ULL) ++msec;

            T ticks = duration_cast<duration<T, R>>(m_duration).count();

            cerr << " Elapsed "
                << setw(2) << min << "m"
                << setfill('0')
                << setw(2) << sec << "s"
                << setw(3) << msec << "ms / "
                << setfill(' ')
                << setprecision(3) << fixed
                << setw(10) << ticks << " ticks of "
                << R::num << '/' << R::den << "s";
        }

        cerr << endl;

        cerr.flags(fmt); // restore cerr format
    }
};
