/*
bool try_lock();
(since C++11)
Tries to lock (i.e., takes ownership of) the associated mutex without blocking. Effectively calls mutex()->try_lock().

std::system_error is thrown if there is no associated mutex or if the mutex is already locked by this std::unique_lock.

Parameters
(none)

Return value
true if the ownership of the mutex has been acquired successfully, false otherwise.

Exceptions
Any exceptions thrown by mutex()->try_lock() (Mutex types do not throw in try_lock, but a custom Lockable might)
If there is no associated mutex, std::system_error with an error code of std::errc::operation_not_permitted
If the mutex is already locked by this std::unique_lock, std::system_error with an error code of std::errc::resource_deadlock_would_occur
*/

/*
template< class Rep, class Period >
bool try_lock_for( const std::chrono::duration<Rep,Period>& timeout_duration );
(since C++11)
Tries to lock (i.e., takes ownership of) the associated mutex. Blocks until specified timeout_duration has elapsed or the lock is acquired, whichever comes first. On successful lock acquisition returns true, otherwise returns false. Effectively calls mutex()->try_lock_for(timeout_duration).

This function may block for longer than timeout_duration due to scheduling or resource contention delays.

The standard recommends that a steady clock is used to measure the duration. If an implementation uses a system clock instead, the wait time may also be sensitive to clock adjustments.

std::system_error is thrown if there is no associated mutex or if the mutex is already locked by this std::unique_lock.

Parameters
timeout_duration	-	maximum duration to block for
Return value
true if the ownership of the mutex has been acquired successfully, false otherwise.

Exceptions
Any exceptions thrown by mutex()->try_lock_for(timeout_duration)
If there is no associated mutex, std::system_error with an error code of std::errc::operation_not_permitted
If the mutex is already locked, std::system_error with an error code of std::errc::resource_deadlock_would_occur
*/

/*
template< class Clock, class Duration >
bool try_lock_until( const std::chrono::time_point<Clock,Duration>& timeout_time );
(since C++11)
Tries to lock (i.e., takes ownership of) the associated mutex. Blocks until specified timeout_time has been reached or the lock is acquired, whichever comes first. On successful lock acquisition returns true, otherwise returns false. May block for longer than timeout_time until has been reached.

Effectively calls mutex()->try_lock_until(timeout_time)

std::system_error is thrown if there is no associated mutex or if the mutex is already locked by the same thread.

Clock must meet the Clock requirements. The program is ill-formed if std::chrono::is_clock_v<Clock> is false. (since C++20)

Parameters
timeout_time	-	maximum time point to block until
Return value
true if the ownership of the mutex has been acquired successfully, false otherwise.

Exceptions
Any exceptions thrown by mutex()->try_lock_until(timeout_time)
If there is no associated mutex, std::system_error with an error code of std::errc::operation_not_permitted
If the mutex is already locked, std::system_error with an error code of std::errc::resource_deadlock_would_occur
*/


#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>
using namespace std;

timed_mutex m1,m2;

void LockTheMutex()
{
 m2.lock();
 cout<<"Lock is acquired by the thread"<<endl;
 this_thread::sleep_for(10s);
 m2.unlock();
}

int main()
{
 unique_lock<timed_mutex> ulock(m1); // blockable call
 // ulock.lock(); // resource_deadlock_would_occur std::system_error
 
 // if the unique_lock object is not associated with any mutex then
 // lock will result in std::system_error with operation not permitted error
 
 if(ulock.owns_lock())
  cout<<"ulock has locked the associated mutex m1"<<endl;
 else
  cout<<"m1 is not locked"<<endl;
  
 unique_lock<timed_mutex> ulock2(m2,defer_lock); // unique_lock owns the mutex m2 and not locked
 
 if(!ulock2.owns_lock())
 {
  cout<<"m2 is not locked"<<endl;
  if(ulock2.try_lock())
   cout<<"m2 is locked "<<endl;
  else
   cout<<"m2 is not locked "<<endl;
 }
 
 ulock2.unlock(); // unlock the assoiated mutex
 
 thread t1(LockTheMutex);
 this_thread::sleep_for(2s);
 ulock2.try_lock_for(chrono::seconds(3s));
 
 if(!ulock2.owns_lock())
 {
  cout<<"Lock is not acquired by ulock2"<<endl;
  cout<<"Waiting for the lock"<<endl;
  while(!ulock2.try_lock())
  {
   cout<<".";
   this_thread::sleep_for(10ms);
  }
   
 }
 else
  cout<<"Lock is acquired by the ulock2"<<endl;
 cout<<endl;
 cout<<"Lock is acquired"<<endl;
 t1.join();
 return 0;
}
