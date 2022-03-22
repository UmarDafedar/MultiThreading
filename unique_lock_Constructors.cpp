 #include<iostream>
#include<mutex>
#include<shared_mutex>
#include<thread>

using namespace std;

// Following mutexes are created and are in unlocked status
mutex m1;
timed_mutex tm1;
recursive_mutex rm1;
recursive_timed_mutex rtm1;
shared_mutex sm1;
shared_timed_mutex stm1;

void LockingFunction()
{
 cout<<"LockingFunction is called "<<endl;
 m1.lock();
 tm1.lock();
 rm1.lock();
 cout<<"Lock is acquired in LockingFunction"<<endl;
 m1.unlock();
 tm1.unlock();
 rm1.unlock();
 cout<<"Lock is released in LockingFunction"<<endl;
}

int main()
{
 {
  unique_lock<mutex> ulock(m1);// Blocking call to acquire the lock i,e m1.lock()
  cout<<"lock has been acquired by ulock for m1"<<endl;
  cout<<"Releasing the lock in Main Thread"<<endl;
 }
 
 unique_lock<mutex> ulock2(m1,adopt_lock);
 /*It assume that the thread has already owns the lock and 
 hence, it owns the mutes but does not lock it
 ulock2.lock(); // This will result in deadlock system_error
 
 Error : terminate called after throwing an instance of 'std::system_error'
  what():  Resource deadlock avoided
 */
 ulock2.unlock();
 
 unique_lock<timed_mutex> ulock3(tm1,defer_lock); 
 /*
 defer_lock does indicate the unique_lock object to acquire the ownership of the mutex
 but it does not lock the mutex
 */
 ulock3.lock();// Can be locked
 ulock3.unlock(); // Unlocked
 
 unique_lock<recursive_mutex> ulock4(rm1,try_to_lock);
 /*
 try_to_lock indicates the unique_lock to acquire the ownership of the mutex
 However, it tries to lock the mutex using try_lock() and continues even if the mutex is not locked
 */
 if(!ulock4.owns_lock())
 {
  cout<<"Lock is not acquired by the ulock4"<<endl;
  ulock4.lock();
 }
 if(ulock4.owns_lock())
 {
  cout<<"Lock is already acquired by the ulock4"<<endl;
  ulock4.unlock();
 }
 
 //unique_lock<mutex> ulock5(m1,try_lock_for(chrono::seconds(10)));
 
 thread t1(LockingFunction);
 cout<<"is Lock acquired by main thread"<<endl;
 this_thread::sleep_for(10s);
 t1.join();

 return 0;
}
