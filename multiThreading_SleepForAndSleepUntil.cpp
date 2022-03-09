#include<iostream>
#include<thread>
#include<ctime>
#include<chrono>

using namespace std;
using namespace std::chrono_literals;

void Fnctn()
{
 cout<<"Fnctn is called "<<endl;
 cout<<"waiting...."<<endl;
 this_thread::sleep_for(5s);
}

void Sleep_For()
{
 cout<<"Sleep_For function is called"<<endl;
 auto now=chrono::system_clock::now();
 std::time_t end_time = std::chrono::system_clock::to_time_t(now);
 cout<<ctime(&end_time)<<endl;
  //cout<<end_time<<endl;
 now=now+20s;
 cout<<"waiting ..."<<endl;
 this_thread::sleep_until(now);
 now=chrono::system_clock::now();
 end_time=chrono::system_clock::to_time_t(now);
 cout<<ctime(&end_time)<<endl;
}

int main()
{
 cout<<"Main Thread is called "<<endl;
 // thread t1(Fnctn); 
 // t1.join();
 // cout<<"Fnctn is returned"<<endl;
 thread t2(Sleep_For);
 t2.join();
 cout<<"Main thread is resumed "<<endl;
 cout<<"And finished"<<endl;
 
 return 0;
}
