#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

void Fnction()
{
 cout<<"Thread Function called"<<endl;
 this_thread::sleep_for(chrono::seconds(10));
 cout<<"Returning to main thread"<<endl;
}

int main()
{
 cout<<"Main Thread"<<endl;
 thread t1;// t1 is thread object which does not represent a thread
 //t1.join();// System Error as t1 is not assocciated with any thread
 if(t1.joinable())
  cout<<"t1 is joinable"<<endl;
 else
  cout<<"t1 is not joinable"<<endl;
  
 thread t2(Fnction);// t2 is a thread object associated with Fnction() which is a callable
 //t2.detach();
 //if the thread object is not joined/detached then it completes with terminate called without an active exception
 if(t2.joinable())
 {
  cout<<"t2 is joinable "<<endl;
  t2.join(); // Waits for the child thread to complete its processing
  // t2.detach(); //Main thread does not wait for child thread to complete its procesing
  
 }
 else
 {
  cout<<"t2 is not joinable "<<endl;
 }
 
 cout<<"Main Thread is progressing"<<endl;
 this_thread::sleep_for(chrono::seconds(3));
 cout<<"Main thread completed"<<endl;
 
 
 return 0;
}
