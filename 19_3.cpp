#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>


/**
 * 19.3 std thread와 멀티쓰레딩 기초
 */

using namespace std;

// mutual exclusion
mutex mtx;

int main() 
{
    // const int num_pro = std::thread::hardware_concurrency();

    // cout << std::this_thread::get_id() << endl;

    // vector<std::thread> my_threads;
    // my_threads.resize(num_pro);

    // for (auto &e : my_threads)
    //     e = std::thread([]() {
    //                 cout << std::this_thread::get_id() << endl;
    //                 while (true) {/* code */}});

    // for (auto &e : my_threads)
    //     e.join();

    auto work_func = [](const string & name)
    {
        for (int i = 0; i < 5; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
            mtx.lock();
            cout << name << " " << std::this_thread::get_id() << " is working" << i << endl;
            mtx.unlock();
        }
    };

    std::thread t1 = std::thread(work_func, "JackJack");
    std::thread t2 = std::thread(work_func, "Dash");

    t1.join();
    t2.join();

    return 0;
}