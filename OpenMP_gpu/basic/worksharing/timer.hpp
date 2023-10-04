#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include <iostream>
#include <cmath>
#include <string>
#include <sys/time.h>

/* simple timer that stores multiple times 
   and can print them afterwards.
   Does not support nested timing calls. 
*/
class Timer
{
public:
    Timer(): n(0) { }
    void start(std::string label) 
    { 
        if (n < 20) { labels[n] = label; gettimeofday(&times[2*n], NULL); }
        else { std::cerr << "No more timers, " << label << " will not be timed." << std::endl; }
    }

    void stop() { gettimeofday(&times[2*n+1], NULL); n++;}
    void reset() { n=0; }
    void print();
private:
    std::string labels[20];
    timeval      times[40];
    int n;
};

void Timer::print()
{
    std::cout << std::endl;
    std::cout << "    Action       ::    time/s     Time resolution = " << 1.f/(float)CLOCKS_PER_SEC << std::endl;
    std::cout << "-----------------" << std::endl;
    for (int i=0; i < n; ++i)
    {
        time_t seconds = times[2*i+1].tv_sec - times[2*i+0].tv_sec;
        suseconds_t ms = times[2*i+1].tv_usec - times[2*i+0].tv_usec;
        if (ms < 0) { ms += 1000000; seconds--; }
        std::cout << labels[i] << " ::    " << (float)seconds + ms/1000000.f << std::endl;
    }
}
#endif

