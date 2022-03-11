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
 m1.lock();
 while(counter>0)
 {
  this_thread::sleep_for(1s);
  cout<<"FunctnPrint "<<counter<<endl;
  counter--;
 }
 counter=20;
 m1.unlock();
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

/* Result
FunctnPrint
CriticalExecution
FunctnPrint 20
FunctnPrint 19
FunctnPrint 18
FunctnPrint 17
FunctnPrint 16
FunctnPrint 15
FunctnPrint 14
FunctnPrint 13
FunctnPrint 12
FunctnPrint 11
FunctnPrint 10
FunctnPrint 9
FunctnPrint 8
FunctnPrint 7
FunctnPrint 6
FunctnPrint 5
FunctnPrint 4
FunctnPrint 3
FunctnPrint 2
FunctnPrint 1
CriticalExecution 20
CriticalExecution 19
CriticalExecution 18
CriticalExecution 17
CriticalExecution 16
CriticalExecution 15
CriticalExecution 14
CriticalExecution 13
CriticalExecution 12
CriticalExecution 11
CriticalExecution 10
CriticalExecution 9
CriticalExecution 8
CriticalExecution 7
CriticalExecution 6
CriticalExecution 5
CriticalExecution 4
CriticalExecution 3
CriticalExecution 2
CriticalExecution 1

*/
