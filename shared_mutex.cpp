#include<iostream>
#include<thread>
#include<mutex>
#include<shared_mutex>

using namespace std;

int counter=100;
shared_mutex m1;

void DisplayOdds()
{
 this_thread::sleep_for(2s);
 m1.lock_shared();
 while(counter>0)
 {
  this_thread::sleep_for(1s);
  if(counter%2==1)
   cout<<"********************Odd "<<counter<<"************************"<<endl;
  counter--;
 }
 m1.unlock_shared();
 
}

void DisplayEvens()
{
 this_thread::sleep_for(1s);
 m1.lock_shared();
 while(counter>0)
 {
  // m1.lock();
 this_thread::sleep_for(1s);
  if(counter%2==0)
   cout<<"********************Even "<<counter<<"************************"<<endl;
  counter--;
 // m1.unlock();
 }
 m1.unlock_shared();
}

void ExclusiveLock()
{
 m1.lock();
 cout<<"Exclusive Lock is acquired by ExclusiveLock"<<endl;
 m1.unlock();
}

int main()
{
 cout<<"Main Thread"<<endl;
 thread t1(DisplayEvens),t2(DisplayOdds),t3(ExclusiveLock);
 t1.join();t2.join();t3.join();
 return 0;
}
