#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
mutex m; 
void taskA()
{
	for(int i=0;i<10;i++)
	{
		{
			lock_guard<mutex> lock(m); 
			cout << "i " << i << endl; 
		}
	   
		this_thread::sleep_for(chrono::milliseconds(5)); 
	}
}
void taskB()
{
	for(int j=0;j<10;j++)
	{
		{
			lock_guard<mutex> lock(m); 
		    cout << "j " << j << endl;
		}
		
		this_thread::sleep_for(chrono::milliseconds(5)); 
	}
}
int main()
{
	unsigned int c = std::thread::hardware_concurrency(); 
	cout << "Number of threads " << c << endl;
	thread t1(taskA);
	thread t2(taskB);
	t1.join();
	t2.join();
	return 0;
}
