#include<iostream>
#include<mutex>
#include<shared_mutex>
#include<thread>

using namespace std;

void LockingFunctn()
{
 mutex* m1=new mutex;
 timed_mutex* tm1=new timed_mutex;
 this_thread::sleep_for(10s);
 m1->lock();
 tm1->lock();
 scoped_lock<mutex,timed_mutex> lockable(adopt_lock,*m1,*tm1);
 cout<<"Lock is acquired in Function1"<<endl;
 delete m1;
 delete tm1;
 cout<<"Lock is released in Function1"<<endl;
}

// void LockingFunctn2()
// {
//  this_thread::sleep_for(10s);
//  lock(*m1,*tm1);
//  cout<<"Lock is acquired in Function2"<<endl;
//  m1->unlock();
//  tm1->unlock();
//  cout<<"Lock is released in Function2"<<endl;
// }

int main()
{
 thread t1(LockingFunctn);
 //thread t2(LockingFunctn2);
 this_thread::sleep_for(2s);
 t1.join();
 //t2.join();
 return 0;
}
