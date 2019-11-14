#include <iostream>
#include "thread"
#include "mutex"
#include "string"
#include "condition_variable"
#include <unistd.h>

std::mutex Mutex;
bool readyFlag = false;
std::condition_variable readyCondition;

void First(const std::string &s)
{
    std::unique_lock<std::mutex> Lock(Mutex);
    std::cout << "First" << std::endl;
    for(int i = 0; i < 3; i++)
    {
        sleep(1);
        std::cout << "wait..." << std::endl;
    }
	readyFlag = true;
	readyCondition.notify_one();
    std::cout << "Fisrt Over" << std::endl;
}
void Second()
{
	std::unique_lock<std::mutex> Lk(Mutex);
    std::cout << "Second" << std::endl;
	readyCondition.wait(Lk, []{return readyFlag;});
    std::cout << "Hello World" << std::endl;
}

int main()
{
    std::thread thread2(Second);
	std::thread thread1(First, "First");
	thread1.join(); //调用它的线程即main线程会被block阻塞
	thread2.join();

	return 0;
}

