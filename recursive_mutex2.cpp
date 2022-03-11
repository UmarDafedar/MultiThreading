#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono_literals;

recursive_timed_mutex m1;
// lock()
// unlock()
// try_lock()

#define COUNTER_LIMIT 20
int counter=COUNTER_LIMIT;

void PrintFunction(int i)
{
 if(m1.try_lock())
 {
  this_thread::sleep_for(1s);
  cout<<"Lock is acquired "<<i<<endl;
  if(i==0)
   return;
  else
  {
   PrintFunction(i-1);
  }
  cout<<"unlocking "<<i<<endl;
  m1.unlock();
 }
 else
 {
  cout<<"The lock is not acquired"<<endl;
  return;
 }
}

void Waiting(int i)
{
 this_thread::sleep_for(1s);
 if(i==0)
  return;
  
 if(m1.try_lock())
 {
  cout<<"Waiting "<<i<<endl;
  cout<<"Lock acquired"<<endl;
  Waiting(i-1);
  m1.unlock();
  cout<<"unlock "<<i<<endl;
 }
 else
 {
  cout<<"Waiting :: did not acquire the lock"<<endl;
 }
}

int main()
{
 thread t1(PrintFunction,10);
 this_thread::sleep_for(1s);
 thread t2(Waiting,10);
 t1.join();
 t2.join();
 return 0;
}
