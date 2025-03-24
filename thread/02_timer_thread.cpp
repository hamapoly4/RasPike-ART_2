#include <iostream>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

void* timer_thread(void* arg) {
    std::cout << "スレッドが実行されています\n";
    return nullptr;
}

void timer_handler(int signum) {
    pthread_t thread;
    pthread_create(&thread, nullptr, timer_thread, nullptr);
    pthread_detach(thread); // スレッドの終了を待たずにデタッチ
}

int main() {
    struct sigaction sa;
    struct itimerspec timer;
    timer_t timerid;

    sa.sa_handler = timer_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, nullptr);

    timer_create(CLOCK_REALTIME, nullptr, &timerid);

    timer.it_value.tv_sec = 1;  // 初回のタイマー発火までの時間（秒）
    timer.it_value.tv_nsec = 0;
    timer.it_interval.tv_sec = 1;  // 以降の周期（秒）
    timer.it_interval.tv_nsec = 0;

    timer_settime(timerid, 0, &timer, nullptr);

    while (true) {
        pause();  // シグナルを待機
    }

    return 0;
}
