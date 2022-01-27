/* Author : ramenbox */

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
using namespace std;

class Semaphore {

private:
	std::atomic<int> count;
	std::mutex letMutex;
	std::condition_variable cond_var;

public:
	Semaphore(int count)
	{
		this->count = count;
	}

	void wait()
	{	//Critical section
		std::unique_lock<std::mutex> m(letMutex);
		while (count == 0) {
			cond_var.wait(m);
		}
		count--;
	}	//End of critical section

	void release()
	{	//Critical section
		std::unique_lock<std::mutex> m(letMutex);
		count++;
		cond_var.notify_all();
	}	//End of critical section


	/*
	void wait()
    {    //Critical section
        std::unique_lock<std::mutex> m(letMutex);
        cond_var.wait(m, [&count](){ return count != 0; });
        count--;
        //End of critical section
    }

    void release()
    {    //Critical section
        std::unique_lock<std::mutex> m(letMutex);
        count++;
        cond_var.notify_all();
        //End of critical section
    }
	*/
};
Semaphore semaphore(1);

//Thread 1
void kleinbuchstabe()
{
	semaphore.wait();
	for (int i = 0; i < 26; i++)
	{
		cout << "T1: " << (char)('a' + i) << endl;
	}
	semaphore.release();
}

//Thread 2
void zahl()
{
	semaphore.wait();
	for (int i = 0; i < 33; i++)
	{
		cout << "T2: " << i << endl;
	}
	semaphore.release();
}

//Thread 3
void grossbuchstabe()
{
	semaphore.wait();
	for (int i = 0; i < 26; i++)
	{
		cout << "T3: " << (char)('A' + i) << endl;
	}
	semaphore.release();
}

int main()
{
	thread T1(kleinbuchstabe);
	thread T2(zahl);
	thread T3(grossbuchstabe);

	T1.join();
	T2.join();
	T3.join();

	cin.get();
	return 0;
}