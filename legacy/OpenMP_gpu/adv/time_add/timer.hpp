#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include <iostream>
#include <iomanip>    //setprecision
#include <cmath>
#include <string>
#include <sys/time.h>
using namespace std;

/* simple timer that stores multiple times 
   and can print them afterwards.
   Does not support nested timing calls. 
*/
class Timer_Collector
{
public:
    Timer_Collector(): n(0) { }
    void start(string label) 
    { 
        if (n < 20) { labels[n] = label; gettimeofday(&times[2*n], NULL); }
        else { cerr << "No more timers, " << label << " will not be timed." << endl; }
    }

    void stop() { gettimeofday(&times[2*n+1], NULL); n++;}
    void reset() { n=0; }
    void print();
private:
    string labels[20];
    timeval      times[40];
    int n;
};

void Timer_Collector::print()
{
    cout << endl;
    cout << "Action           ::    time/s     Time resolution = " << 1.f/(float)CLOCKS_PER_SEC << endl;
    cout << "------" << endl;
    for (int i=0; i < n; ++i)
    {
        time_t seconds = times[2*i+1].tv_sec  - times[2*i+0].tv_sec;
        suseconds_t us = times[2*i+1].tv_usec - times[2*i+0].tv_usec;
        if (us < 0) { us += 1000000; seconds--; }
        double secs = (double)seconds + us/1000000.0f;
        cout << labels[i] << " :: " << setiosflags(ios::fixed)<<setprecision(6)<< setw(12)<<secs<<endl;
    }
}
#endif
