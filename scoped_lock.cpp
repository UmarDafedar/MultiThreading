#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

int value=0;
mutex m1,m2;

void DisplayValue()
{
 cout<<"Display Function is called "<<endl;
 cout<<"Display Function is trying to get m1,m2 lock"<<endl;
 scoped_lock lock(m1,m2);
 cout<<"Display Function has acquired m1 and m2 lock"<<endl;
 
 while(value<100)
 {
  cout<<value<<endl;
  this_thread::sleep_for(1s);
  value++;
 }
}

void ModifyValue()
{
 cout<<"Modify Function is called "<<endl;
 cout<<"Modify Function is trying to get m1,m2 lock"<<endl;
 scoped_lock lock(m1,m2);
 cout<<"Modify Function has acquired m1 and m2 lock"<<endl;
 
 for(int i=0;i<=50;i++)
 {
  value=i;
  this_thread::sleep_for(1s);
 }
}

int main()
{
 thread t1(ModifyValue),t2(DisplayValue);
 t1.join();t2.join();
 return 0;
}
