#include<iostream>
#include<mutex>

using namespace std;

mutex m1,m2,m3;

int main()
{
 unique_lock<mutex> lock(m1); // lock owns the mutex m1 and locks it
 unique_lock<mutex> lock2(move(lock)); // ownership is transfered to lock2 and 
 // lock does not own any mutex
 
 lock=move(lock2); // now lock owns the mutes m1 again and lock2 does not own the mutex
 //m1 is locked
 /*
 unique_lock<mutex> lock3;
 lock.lock(); -- exception as the associated mutex is already locked
 lock3.lock(); -- exception as the unique_lock object lock3 does not own any mutex
 
 Exceptions
 Any exceptions thrown by mutex()->lock()
 If there is no associated mutex, std::system_error with an error code of std::errc::operation_not_permitted
 If the mutex is already locked by this unique_lock (in other words, owns_lock is true), 
 std::system_error with an error code of std::errc::resource_deadlock_would_occur
 */
 
 unique_lock<mutex> lock4(m2,try_to_lock); //Not locked assuming it is already locked [_M_owns will be set to true]
 //lock4.lock(); // std::system_error with an error code of std::errc::resource_deadlock_would_occur
 m2.lock();
 
 unique_lock<mutex> lock5(m3,defer_lock); // owns the mutex, but not locked and _M_owns set to FALSE
 lock5.lock();
 

 return 0;
}
