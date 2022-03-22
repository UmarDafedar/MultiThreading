#include<iostream>
#include<mutex>
#include<shared_mutex>
#include<thread>

using namespace std;

mutex m1;
timed_mutex tm1;

void LockingFunctn()
{
 {
  m1.lock();
  tm1.lock();
  cout<<"trying to lock the mutexes with adopt_lock strategy"<<endl;
  scoped_lock<mutex,timed_mutex> lockable(adopt_lock,m1,tm1);
  cout<<"Lock is acquired in Function1"<<endl;
  this_thread::sleep_for(10s);
  cout<<"Lock is released in Function1"<<endl;
 }
 
 {
  cout<<"trying to lock the mutexes with lock strategy"<<endl;
  scoped_lock<mutex,timed_mutex> lockable(m1,tm1);
  cout<<"Lock is acquired again in Function1"<<endl;
  this_thread::sleep_for(10s);
  cout<<"Lock is released again in Function1"<<endl;
 }
 
  
}

int main()
{
 thread t1(LockingFunctn);
 t1.join();
 this_thread::sleep_for(2s);
 return 0;
}
