#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono_literals;

timed_mutex m1;
// lock()
// unlock()
// try_lock()
// try_lock_for(Duration)
// try_lock_until(Time until which the thread has to wait to acquire a lock)

#define COUNTER_LIMIT 20
int counter=COUNTER_LIMIT;

void PrintFunction()
{
 cout<<"PrintFunction"<<" ";
 this_thread::sleep_for(1s);
 if(m1.try_lock_for(10s))
 {
  cout<<"Lock was acquired for PrintFunction"<<endl;
  while(counter>0)
  {
   this_thread::sleep_for(1s); 
   cout<<counter<<endl;
   counter--;
  }
  counter=COUNTER_LIMIT;
  m1.unlock();
 }
 else
 {
  cout<<"Lock was not acquired for PrintFunction"<<endl;
 }
}

void MultiplyFunction(int i)
{
 cout<<"MultiplyFunction"<<endl;
 
 if(m1.try_lock())
 {
  cout<<"Lock was acquired for MultiplyFunction"<<endl;
  while(counter>0)
  {
   this_thread::sleep_for(1s);
   cout<<counter*i<<endl;
   counter--;
  }
  counter=COUNTER_LIMIT;
 
  m1.unlock();
 }
 else
 {
  cout<<"Lock was not acquired for MultiplyFunction"<<endl;
 }
}

void InOrOut()
{
 cout<<"InOrOut"<<endl;
 this_thread::sleep_for(1s);
 
 auto start=chrono::system_clock::now();
 
 start=start+chrono::seconds(30);
 
 if(m1.try_lock_until(start))
 {
  cout<<"Lock was acquired for InOrOut"<<endl;
  while(counter>0)
  {
   this_thread::sleep_for(1s);
   cout<<(counter%2==0?0:1)<<endl;
   counter--;
  }
  counter=COUNTER_LIMIT;
 
  m1.unlock();
 }
 else
 {
  cout<<"Lock was not acquired for InOrOut"<<endl;
 }
}

int main()
{
 thread t1(PrintFunction);
 thread t2(MultiplyFunction,10);
 thread t3(InOrOut);
 t1.join();
 t2.join();
 t3.join();
 
 // auto start=chrono::system_clock::to_time_t(chrono::system_clock::now());
 // cout<<ctime(&start)<<endl;
 // start=start+10;
 // cout<<ctime(&start)<<endl;
 return 0;
} 
