#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m1;

void PrintNumbers()
{
 cout<<"PrintNumbers is called "<<endl;
 
 lock_guard<mutex> lock(m1); // Scoped Lock
 for(int i=0;i<20;i++)
 {
  this_thread::sleep_for(1s);
  cout<<i<<endl;
 }
 cout<<endl;
}

void PrintCharacters()
{
 this_thread::sleep_for(1s);
 cout<<"PrintCharacters is called "<<endl;
 m1.lock();
 for(int i=65;i<100;i++)
 {
  this_thread::sleep_for(1s);
  cout<<(char)i<<endl;
 }
 cout<<endl;
 m1.unlock();
}



/********************** Main Function ************************/
int main()
{
 thread t1(PrintNumbers),t2(PrintCharacters);
 t1.join();
 t2.join();
 return 0;
}
