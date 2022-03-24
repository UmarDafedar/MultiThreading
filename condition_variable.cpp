/*class condition_variable;
(since C++11)
The condition_variable class is a synchronization primitive that can be used to block a thread, or multiple threads at the same time, until another thread both modifies a shared variable (the condition), and notifies the condition_variable.

The thread that intends to modify the shared variable has to

acquire a std::mutex (typically via std::lock_guard)
perform the modification while the lock is held
execute notify_one or notify_all on the std::condition_variable (the lock does not need to be held for notification)
Even if the shared variable is atomic, it must be modified under the mutex in order to correctly publish the modification to the waiting thread.

Any thread that intends to wait on std::condition_variable has to

acquire a std::unique_lock<std::mutex>, on the same mutex as used to protect the shared variable
either
check the condition, in case it was already updated and notified
execute wait, wait_for, or wait_until. The wait operations atomically release the mutex and suspend the execution of the thread.
When the condition variable is notified, a timeout expires, or a spurious wakeup occurs, the thread is awakened, and the mutex is atomically reacquired. The thread should then check the condition and resume waiting if the wake up was spurious.
or
use the predicated overload of wait, wait_for, and wait_until, which takes care of the three steps above
std::condition_variable works only with std::unique_lock<std::mutex>; this restriction allows for maximal efficiency on some platforms. std::condition_variable_any provides a condition variable that works with any BasicLockable object, such as std::shared_lock.

Condition variables permit concurrent invocation of the wait, wait_for, wait_until, notify_one and notify_all member functions.

The class std::condition_variable is a StandardLayoutType. It is not CopyConstructible, MoveConstructible, CopyAssignable, or MoveAssignable.


Constructor
-----------
condition_variable(); (1)	(since C++11)
condition_variable(const condition_variable&) = delete; (2)	(since C++11)
1) Constructs an object of type std::condition_variable.
2) Copy constructor is deleted.

Parameters
(none)

Exceptions
1) May throw std::system_error with std::error_condition equal to std::errc::operation_not_permitted if the thread has no privilege to create a condition variable, 
std::errc::resource_unavailable_try_again if a non-memory resource limitation prevents this initialization, or another implementation-defined value.

Destrutor:
---------
~condition_variable();
(since C++11)
Destroys the object of type std::condition_variable.

It is only safe to invoke the destructor if all threads have been notified. It is not required that they have exited their respective wait functions: 
some threads may still be waiting to reacquire the associated lock, or may be waiting to be scheduled to run after reacquiring it.

The programmer must ensure that no threads attempt to wait on *this once the destructor has been started, 
especially when the waiting threads are calling the wait functions in a loop or are using the overloads of the wait functions that take a predicate.


void notify_one() noexcept;
(since C++11)
If any threads are waiting on *this, calling notify_one unblocks one of the waiting threads.

Parameters
(none)

Return value
(none)

Notes
The effects of notify_one()/notify_all() and each of the three atomic parts of wait()/wait_for()/wait_until() (unlock+wait, wakeup, and lock) take place in a 
single total order that can be viewed as modification order of an atomic variable: the order is specific to this individual condition variable. 
This makes it impossible for notify_one() to, for example, be delayed and unblock a thread that started waiting just after the call to notify_one() was made.

The notifying thread does not need to hold the lock on the same mutex as the one held by the waiting thread(s); in fact doing so is a pessimization, 
since the notified thread would immediately block again, waiting for the notifying thread to release the lock. However, some implementations 
(in particular many implementations of pthreads) recognize this situation and avoid this "hurry up and wait" scenario by transferring the waiting thread from the 
condition variable's queue directly to the queue of the mutex within the notify call, without waking it up.

Notifying while under the lock may nevertheless be necessary when precise scheduling of events is required, e.g. if the waiting thread would exit the program if 
the condition is satisfied, causing destruction of the notifying thread's condition variable. A spurious wakeup after mutex unlock but before notify would result 
in notify called on a destroyed object.
*/


#include<iostream>
#include<mutex>
#include<condition_variable>
#include<thread>


using namespace std;

condition_variable cv;
mutex m;
bool PrintABool=true,PrintBBool=false;

void PrintA(int i=0)
{
 cout<<"PrintA is called " <<endl;
 unique_lock<mutex> ulock(m);
 this_thread::sleep_for(2s);
 while(i>0)
 {
  cv.wait(ulock,[]{return PrintABool;});
  cout<<"A";
  --i;
  PrintABool=false;
  PrintBBool=true;
  cv.notify_one();
 }
}

void PrintB(int j=0)
{
 cout<<"PrintB is called " <<endl;
 
 unique_lock<mutex> ulock(m);
 this_thread::sleep_for(2s);
 while(j>0)
 {
  cv.wait(ulock,[]{return PrintBBool;});
  cout<<"B";
  --j;
  PrintABool=true;
  PrintBBool=false;
  cv.notify_one();
 }
}

int main()
{
 cout<<"Main thread is called"<<endl;
 thread t1(PrintA,10),t2(PrintB,10);
 t1.join();
 t2.join();
 return 0;
}
