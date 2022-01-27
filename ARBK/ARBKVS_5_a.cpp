/* Author : ramenbox */

#include <iostream>
#include <thread>
using namespace std;

//Thread 1
void kleinbuchstabe()
{
	for (int i = 0; i < 26; i++)
	{
		cout << "T1: " << (char)('a' + i) << endl;
		//this_thread::sleep_for(1s);
	}
}

//Thread 2
void zahl()
{
	for (int i = 0; i < 33; i++)
	{
		cout << "T2: " << i << endl;
		//this_thread::sleep_for(1s);
	}
}

//Thread 3
void grossbuchstabe()
{
	for (int i = 0; i < 26; i++)
	{
		cout << "T3: " << (char)('A' + i) << endl;
		//this_thread::sleep_for(1s);
	}
}

int main()
{
	thread T1(kleinbuchstabe);
	thread T2(zahl);
	thread T3(grossbuchstabe);

	T1.join();
	T2.join();
	T3.join();

	//wait for exit
	//also, cin.get() wird nicht ausgeführt bis thread fertig ist

	cout << endl;
	cin.get();
	return 0;
}