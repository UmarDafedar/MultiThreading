#include<iostream>
#include<mutex>
#include<shared_mutex>
#include<thread>

using namespace std;

mutex m1;
timed_mutex tm1;

void LockingFunctn()
{
 this_thread::sleep_for(10s);
 lock(tm1,m1);
 cout<<"Lock is acquired in Function1"<<endl;
 m1.unlock();
 tm1.unlock();
 cout<<"Lock is released in Function1"<<endl;
}

void LockingFunctn2()
{
 this_thread::sleep_for(10s);
 lock(m1,tm1);
 cout<<"Lock is acquired in Function2"<<endl;
 m1.unlock();
 tm1.unlock();
 cout<<"Lock is released in Function2"<<endl;
}

int main()
{
 thread t1(LockingFunctn);
 thread t2(LockingFunctn2);
 this_thread::sleep_for(2s);
 t1.join();
 t2.join();
 return 0;
}
