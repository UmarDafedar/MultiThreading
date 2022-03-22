#include<iostream>
#include<mutex>
#include<shared_mutex>
#include<thread>

using namespace std;

mutex m1;

void LockingFunctn()
{
 m1.lock();
 cout<<"Lock is acquired in thread"<<endl;
 this_thread::sleep_for(10s);
 m1.unlock();
 cout<<"Lock is released in thread"<<endl;
}

int main()
{
 // thread t1(LockingFunctn);
 // this_thread::sleep_for(2s);
 //m1.lock();
 lock_guard<mutex> lock(m1,std::adopt_lock);// does not lock
 cout<<"Lock is not acquried as I am using adopt_lock strategy"<<endl;
 this_thread::sleep_for(2s);
 // lock_guard<mutex> lock2(m1);
 thread t1(LockingFunctn);
 // lock2=move(lock);
 cout<<"Lock is acquried"<<endl;
 t1.join();
 return 0;
}
