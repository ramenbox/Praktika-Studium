/* Author : ramenbox */

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex letMutex;

//Thread 1
void kleinbuchstabe()
{
	//std::unique_lock<std::mutex> m(letMutex);
	letMutex.lock();
	for (int i = 0; i < 26; i++)
	{
		cout << "T1: " << (char)('a' + i) << endl;
	}
	letMutex.unlock();
}

//Thread 2
void zahl()
{
	//std::unique_lock<std::mutex> m(letMutex);
	letMutex.lock();
	for (int i = 0; i < 33; i++)
	{
		cout << "T2: " << i << endl;
	}
	letMutex.unlock();
}

//Thread 3
void grossbuchstabe()
{
	//std::unique_lock<std::mutex> m(letMutex);
	letMutex.lock();
	for (int i = 0; i < 26; i++)
	{
		cout << "T3: " << (char)('A' + i) << endl;
	}
	letMutex.unlock();
}

int main()
{
	thread T1(kleinbuchstabe);
	thread T2(zahl);
	thread T3(grossbuchstabe);

	T1.join();
	T2.join();
	T3.join();

	cout << endl;
	cin.get();
	return 0;
}