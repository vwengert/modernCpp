#include <modernLibrary.h>
#include <thread>

class BackgroundTask {
public:
    void operator()() const {
        doWork();
    }
};

auto main() -> int {
    BackgroundTask task;
    std::thread th1(task);
    th1.join();
    return 0;
}
