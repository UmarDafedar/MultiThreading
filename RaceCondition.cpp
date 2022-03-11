#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;
using namespace chrono_literals;

int counter=100;

mutex m1;

void FunctnPrint()
{
 cout<<"FunctnPrint"<<endl;
 while(counter>0)
 {
  this_thread::sleep_for(1s);
  cout<<"FunctnPrint "<<counter<<endl;
  counter--;
 }
 counter=100;
}

void CriticalExecution()
{
 cout<<"CriticalExecution"<<endl;
 while(counter>0)
 {
  this_thread::sleep_for(1s);
  cout<<"CriticalExecution "<<counter<<endl;
  counter--;
 }
 counter=100;
}

int main()
{
 thread t1(FunctnPrint),t2(CriticalExecution);
 t1.join();
 t2.join();
 return 0;
}


/* Output
CriticalExecution
FunctnPrint
FunctnPrint 100
CriticalExecution 99
FunctnPrint 98
CriticalExecution 97
FunctnPrint 96
CriticalExecution 95
FunctnPrint 94
CriticalExecution 93
FunctnPrint 92
CriticalExecution 91
FunctnPrint 90
CriticalExecution 89
FunctnPrint 88
CriticalExecution 87
FunctnPrint 86
CriticalExecution 85
FunctnPrint 84
CriticalExecution 83
FunctnPrint 82
CriticalExecution 81
FunctnPrint 80
CriticalExecution 79
FunctnPrint 78
CriticalExecution 77
FunctnPrint 76
CriticalExecution 75
FunctnPrint 74
CriticalExecution 73
FunctnPrint 72
CriticalExecution 71
FunctnPrint 70
CriticalExecution 69
FunctnPrint 68
CriticalExecution 67
FunctnPrint 66
CriticalExecution 65
FunctnPrint 64
CriticalExecution 63
FunctnPrint 62
CriticalExecution 61
FunctnPrint 60
CriticalExecution 59
FunctnPrint 58
CriticalExecution 57
FunctnPrint 56
CriticalExecution 55
FunctnPrint 54
CriticalExecution 53
FunctnPrint 52
CriticalExecution 51
FunctnPrint 50
CriticalExecution 49
FunctnPrint 48
CriticalExecution 47
FunctnPrint 46
CriticalExecution 45
FunctnPrint 44
CriticalExecution 43
FunctnPrint 42
CriticalExecution 41
FunctnPrint 40
CriticalExecution 39
FunctnPrint 38
CriticalExecution 37
FunctnPrint 36
CriticalExecution 35
FunctnPrint 34
CriticalExecution 33
FunctnPrint 32
CriticalExecution 31
FunctnPrint 30
CriticalExecution 29
FunctnPrint 28
CriticalExecution 27
FunctnPrint 26
CriticalExecution 25
FunctnPrint 24
CriticalExecution 23
FunctnPrint 22
CriticalExecution 21
FunctnPrint 20
CriticalExecution 19
FunctnPrint 18
CriticalExecution 17
FunctnPrint 16
CriticalExecution 15
FunctnPrint 14
CriticalExecution 13
FunctnPrint 12
CriticalExecution 11
FunctnPrint 10
CriticalExecution 9
FunctnPrint 8
CriticalExecution 7
FunctnPrint 6
CriticalExecution 5
FunctnPrint 4
CriticalExecution 3
FunctnPrint 2
CriticalExecution 1
FunctnPrint 100
FunctnPrint 99
FunctnPrint 98
FunctnPrint 97
FunctnPrint 96
FunctnPrint 95
FunctnPrint 94
FunctnPrint 93
FunctnPrint 92
FunctnPrint 91
FunctnPrint 90
FunctnPrint 89
FunctnPrint 88
FunctnPrint 87
FunctnPrint 86
FunctnPrint 85
FunctnPrint 84
FunctnPrint 83
FunctnPrint 82
FunctnPrint 81
FunctnPrint 80
FunctnPrint 79
FunctnPrint 78
FunctnPrint 77
FunctnPrint 76
FunctnPrint 75
FunctnPrint 74
FunctnPrint 73
FunctnPrint 72
FunctnPrint 71
FunctnPrint 70
FunctnPrint 69
FunctnPrint 68
FunctnPrint 67
FunctnPrint 66
FunctnPrint 65
FunctnPrint 64
FunctnPrint 63
FunctnPrint 62
FunctnPrint 61
FunctnPrint 60
FunctnPrint 59
FunctnPrint 58
FunctnPrint 57
FunctnPrint 56
FunctnPrint 55
FunctnPrint 54
FunctnPrint 53
FunctnPrint 52
FunctnPrint 51
FunctnPrint 50
FunctnPrint 49
FunctnPrint 48
FunctnPrint 47
FunctnPrint 46
FunctnPrint 45
FunctnPrint 44
FunctnPrint 43
FunctnPrint 42
FunctnPrint 41
FunctnPrint 40
FunctnPrint 39
FunctnPrint 38
FunctnPrint 37
FunctnPrint 36
FunctnPrint 35
FunctnPrint 34
FunctnPrint 33
FunctnPrint 32
FunctnPrint 31
FunctnPrint 30
FunctnPrint 29
FunctnPrint 28
FunctnPrint 27
FunctnPrint 26
FunctnPrint 25
FunctnPrint 24
FunctnPrint 23
FunctnPrint 22
FunctnPrint 21
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

*/
