#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m1,m2;
int counter=0;

int main()
{
 cout<<"Main Thread"<<endl;
 m1.lock();
 while(try_lock(m1,m2)!=-1)
 {
  counter++;
  this_thread::sleep_for(1s);
  cout<<counter<<endl;
  if(counter>25)
   m1.unlock();
 }
 
 cout<<"Lock is acquired"<<endl;
 cout<<"Processing...."<<endl;
 this_thread::sleep_for(5s);
 cout<<"completed!!!"<<endl;
 m1.unlock();
 m2.unlock();
 
 return 0;
}
