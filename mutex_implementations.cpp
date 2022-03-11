 #include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;
using namespace chrono_literals;

int counter=20;// Critical Variable

mutex m1; // Unlock

void FunctnPrint()
{
 cout<<"FunctnPrint"<<endl;
 //Critical Section
 this_thread::sleep_for(3s);
 if(m1.try_lock())
 {
  while(counter>0)
  {
   this_thread::sleep_for(1s);
   cout<<"FunctnPrint "<<counter<<endl;
   counter--; 
  }
  counter=20;
  m1.unlock();
 }
 else
 {
  cout<<"Did not acquire the lock and hence not doing anything"<<endl;
  return;
 }
  //Critical Section
}

void CriticalExecution()
{
 cout<<"CriticalExecution"<<endl;
 //Critical Section
 m1.lock();
 while(counter>0)
 {
  this_thread::sleep_for(1s);
  cout<<"CriticalExecution "<<counter<<endl;
  counter--;
 }
 counter=20;
 m1.unlock();
 //Critical Section
 
}

int main()
{
 thread t1(FunctnPrint),t2(CriticalExecution);
 t1.join();
 t2.join();
 return 0;
}
