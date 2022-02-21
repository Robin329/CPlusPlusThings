//
// Created by renbin jiang on 2022/2/22.
//
#include <future>
#include <iostream>
#include <thread>

int futureExample1() {
    // future from a packaged_task
    std::packaged_task<int()> task([] { return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();          // get a future
    std::thread t(std::move(task));                   // launch on a thread

    // future from an async()
    std::future<int> f2 = std::async(std::launch::async, [] { return 8; });

    // future from a promise
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread([&p] { p.set_value_at_thread_exit(9); }).detach();

    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: " << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
    t.join();
}

int futureExample2() {
    std::promise<int> p;
    std::future<int> f = p.get_future();

    std::thread t([&p] {
        try {
            // code that may throw
            throw std::runtime_error("Example");
        } catch (...) {
            try {
                // store anything thrown in the promise
                p.set_exception(std::current_exception());
            } catch (...) {
            } // set_exception() may throw too
        }
    });

    try {
        std::cout << f.get();
    } catch (const std::exception& e) {
        std::cout << "Exception from the thread: " << e.what() << '\n';
    }
    t.join();
}

int main() {
    futureExample1();
    futureExample2();

    return 0;
}