//
// Created by renbin jiang on 2022/2/22.
//

#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

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

void futureExample3(void) {
    auto f1 = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::seconds(9));
        return 42;
    });

    auto f2 = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 13;
    });

    auto f3 = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::seconds(6));
        return 666;
    });

    auto timeout = std::chrono::milliseconds(10);

    while (f1.valid() || f2.valid() || f3.valid()) {
        if (f1.valid() && f1.wait_for(timeout) == std::future_status::ready) {
            std::cout << "Task1 is done! " << f1.get() << std::endl;
        }

        if (f2.valid() && f2.wait_for(timeout) == std::future_status::ready) {
            std::cout << "Task2 is done! " << f2.get() << std::endl;
        }

        if (f3.valid() && f3.wait_for(timeout) == std::future_status::ready) {
            std::cout << "Task3 is done! " << f3.get() << std::endl;
        }

        std::cout << "I'm doing my own work!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "I'm done with my own work!" << std::endl;
    }

    std::cout << "Everything is done, let's go back to the tutorial" << std::endl;
}

void futureExample4() {
    {
        auto future = std::async(std::launch::async, []() {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            return 42;
        });

        // Do something else ?

        std::cout << future.get() << std::endl;
    }
}

void futureExample5() {
    std::vector<std::future<size_t>> futures;

    for (size_t i = 0; i < 10; ++i) {
        futures.emplace_back(std::async(
                std::launch::async,
                [](size_t param) {
                    std::this_thread::sleep_for(std::chrono::seconds(param));
                    return param;
                },
                i));
    }

    std::cout << "Start querying" << std::endl;

    for (auto& future : futures) {
        std::cout << future.get() << std::endl;
    }
}

int main() {
    std::cout << "------------------------" << std::endl;
    futureExample1();
    std::cout << "------------------------" << std::endl;
    futureExample2();
    std::cout << "------------------------" << std::endl;
    futureExample3();
    std::cout << "------------------------" << std::endl;
    futureExample4();
    std::cout << "------------------------" << std::endl;
    futureExample5();

    return 0;
}