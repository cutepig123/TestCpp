#include <iostream>
#include "boost/date_time/posix_time/posix_time.hpp" 
 
typedef boost::posix_time::ptime Time;
typedef boost::posix_time::time_duration TimeDuration;


int test_time (){
 
    Time t1(boost::posix_time::microsec_clock::local_time());
 
    Time t2(boost::posix_time::microsec_clock::local_time());
 
    TimeDuration dt = t2 - t1;
 
    //print formatted date
	std::cout << t1 << std::endl; 
    std::cout << dt << std::endl; 
 
    //number of elapsed miliseconds
    long msec = dt.total_milliseconds();
 
    //print elapsed seconds (with millisecond precision)
    std::cout << msec/1000.0 << std::endl; 
 
    return 0;
}