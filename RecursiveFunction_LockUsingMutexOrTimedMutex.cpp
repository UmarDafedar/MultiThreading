 #include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<ctime>

using namespace std;
using namespace std::chrono_literals;

mutex m1;
// lock()
// unlock()
// try_lock()

#define COUNTER_LIMIT 20
int counter=COUNTER_LIMIT;

void PrintFunction(int i)
{
 if(m1.try_lock())
 {
  cout<<"Lock is acquired"<<endl;
  if(i<=0)
   return;
  else  if(i==1)
   cout<<i<<endl;
  else
  {
   PrintFunction(i-1);
   cout<<i<<endl;
  }
  
  m1.unlock();
 }
 else
 {
  cout<<"The lock is not acquired"<<endl;
  return;
 }
}

int main()
{
 thread t1(PrintFunction,10);
 t1.join();
 return 0;
}
