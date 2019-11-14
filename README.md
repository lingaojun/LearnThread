# LearnThread
LearnThread

# 11.14
修改文件名  
增加Makefile
学习std::condition_variable相关知识：  
  ## 1 std::condition_variable::wait()
   wait()有两种表达形式，一种是只有一个形参，另一种的两个形参。先解释后者，第一个形参是一个互斥量(mutex)，第二个形参是一个lamba函数。  
   当程序执行到wait()函数时，会**先对第一个互斥量解锁，再去判断第二个lamba函数的返回值。若返回值为真，则重新上锁，继续执行下去。
   若返回值为假时，则会一直阻塞在这行代码。** 
  ## 2 std::condition_variable::notify_one(); 
  
  ## 3 std::condition_variable::notify_all();
