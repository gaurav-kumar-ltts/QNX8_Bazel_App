#include <atomic>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <vector>

namespace {

// Keeps one core busy for `percentage` out of every 100ms period until
// `stop` is set, so the requested CPU load is approximated regardless of
// how long the process runs.
void cpu_worker(std::atomic<bool> &stop, int percentage) {
    constexpr auto period = std::chrono::milliseconds(100);

    const auto busy_time = period * percentage / 100;
    const auto idle_time = period - busy_time;

    while (!stop.load()) {
        const auto start = std::chrono::high_resolution_clock::now();

        while (std::chrono::high_resolution_clock::now() - start < busy_time) {
            asm volatile("" ::: "memory");
        }

        if (idle_time.count() > 0) {
            std::this_thread::sleep_for(idle_time);
        }
    }
}

}  // namespace

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <duration_seconds> <cpu_percentage>\n";
        return 1;
    }

    const int duration = std::atoi(argv[1]);
    const int percentage = std::atoi(argv[2]);

    if (percentage < 0 || percentage > 100) {
        std::cerr << "CPU percentage must be between 0 and 100.\n";
        return 1;
    }

    unsigned int cores = std::thread::hardware_concurrency();
    if (cores == 0) {
        cores = 1;
    }

    std::cout << "Using " << cores << " threads\n";

    std::atomic<bool> stop(false);
    std::vector<std::thread> workers;

    for (unsigned int i = 0; i < cores; ++i) {
        workers.emplace_back(cpu_worker, std::ref(stop), percentage);
    }

    std::this_thread::sleep_for(std::chrono::seconds(duration));

    stop = true;

    for (auto &t : workers) {
        t.join();
    }

    std::cout << "Finished.\n";
    return 0;
}
