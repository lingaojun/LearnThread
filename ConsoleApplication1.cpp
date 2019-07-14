#include <iostream>
#include "thread"
#include "mutex"
#include "string"

std::mutex Mutex;
bool readyFlag;
std::condition_variable readyCondition;

void First(const std::string &s)
{
	std::lock_guard<std::mutex> Lock(Mutex);
	readyFlag = true;
	readyCondition.notify_one();
}
void Second()   
{
	std::cout << "Hello World! " << std::endl;
	std::unique_lock<std::mutex> Lk(Mutex);
	readyCondition.wait(Lk, []{return readyFlag;});
}

int main()
{
	std::thread thread1(First,"Hello World");
	std::thread thread2(Second);
	std::cout << thread1.get_id() << std::endl; //线程ID 且每次运行程序值都会改变
	std::cout << thread2.get_id() << std::endl;
	thread1.join(); //调用它的线程即main线程会被block阻塞
	thread2.join();

	return 0;
}

