#include <cstdint>
#include <functional>
#include <iostream>
#include <string>

using namespace std;

class Worker {
public:
    virtual ~Worker();
    int          InitWorker();
    virtual void Routine() = 0;

protected:
    Worker(const char *name, int priority);

private:
    void        InternalRoutine();
    std::string name_;
    int         priority_;
};

class VSyncWorker : public Worker {
public:
    VSyncWorker();
    ~VSyncWorker() override = default;
    auto Init(std::function<void(uint64_t)> callback) -> int;
    void Routine();
    void ChangeNum(int64_t val_1, int64_t val_2) {
        param1 = val_1;
        param2 = val_2;
        cout << "param1 = " << param1 << endl;
        cout << "param2 = " << param2 << endl;
    }

private:
    std::function<void(uint64_t /*timestamp*/)> callback_;
    uint64_t                                    param1{0};
    uint64_t                                    param2{1};
};

class hwcDisplay {
public:
    void Init();

private:
    VSyncWorker vsync_worker_;
};

auto VSyncWorker::Init(std::function<void(uint64_t)> callback) -> int {
    callback_ = std::move(callback);
    if (callback_) cout << "callback_ moved" << endl;
    // callback_会因为在栈空间而释放掉，因此Routine()放这里,
    // 右值引用和std::move被广泛用于在STL和自定义类中实现移动语义，避免拷贝，从而提升程序性能
    Routine();
    return 0;
}

void VSyncWorker::Routine() {
    uint64_t timestamp = 100;
    if (callback_) {
        cout << "callback_ entered" << endl;
        callback_(timestamp);
    }
}
void hwcDisplay::Init() {
    cout << "hwcDisplay::Init" << endl;
    int ret = vsync_worker_.Init([this](uint64_t timestamp) {
        cout << "timestamp:" << timestamp << endl;
        vsync_worker_.ChangeNum(timestamp, timestamp + 100);
    });
}
Worker::Worker(const char *name, int priority) : name_(name), priority_(priority) {}
Worker::~Worker() {
    cout << "Worker::~Worker()" << endl;
}
void Worker::InternalRoutine() {
    Routine();
}

VSyncWorker::VSyncWorker() : Worker("vsync", 123){};
int main(void) {
    hwcDisplay *display = new hwcDisplay;
    display->Init();
    if (display) delete display;
    return 0;
}