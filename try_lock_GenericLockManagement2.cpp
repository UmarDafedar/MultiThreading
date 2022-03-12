#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m1,m2,m3;
int counter=0;

int main()
{
 cout<<"Main Thread"<<endl;
 //m1.lock(); -- try_lock returns 0 as it fails to lock m1 which is the first mutex
 //m2.lock(); --try_lock returns 1 as it fails to lock m2 which is the second mutex (m1 was locked and will be unlocked
              // the moment try_lock fails to lock m2)
 //m3.lock(); --try_lock returns 2 as it fails to lock m3 which is the third mutex (m1,m2 was locked and will be unlocked
              // the moment try_lock fails to lock m3)
 
 int result=try_lock(m1,m2,m3);
 cout<<result<<endl;
 if(result==-1)
 {
  cout<<"Lock is acquired"<<endl;
  cout<<"Processing...."<<endl;
  this_thread::sleep_for(5s);
  cout<<"completed!!!"<<endl;
  m1.unlock();
  m2.unlock();
  m3.unlock();
 }
 return 0;
}
