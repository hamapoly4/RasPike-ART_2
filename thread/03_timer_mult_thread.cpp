#include <iostream>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

void* timer_thread_30ms(void* arg) {
    std::cout << "30ms スレッドが実行されています\n";
    return nullptr;
}

void* timer_thread_10ms(void* arg) {
    std::cout << "10ms スレッドが実行されています\n";
    return nullptr;
}

void timer_handler_30ms(union sigval sv) {
    pthread_t thread;
    pthread_create(&thread, nullptr, timer_thread_30ms, nullptr);
    pthread_detach(thread); // スレッドの終了を待たずにデタッチ
}

void timer_handler_10ms(union sigval sv) {
    pthread_t thread;
    pthread_create(&thread, nullptr, timer_thread_10ms, nullptr);
    pthread_detach(thread); // スレッドの終了を待たずにデタッチ
}

int main() {
    struct sigevent sev_30ms, sev_10ms;
    struct itimerspec timer_30ms, timer_10ms;
    timer_t timerid_30ms, timerid_10ms;

    // 30msタイマーの設定
    sev_30ms.sigev_notify = SIGEV_THREAD;
    sev_30ms.sigev_value.sival_ptr = &timerid_30ms;
    sev_30ms.sigev_notify_function = timer_handler_30ms;
    sev_30ms.sigev_notify_attributes = nullptr;

    timer_create(CLOCK_REALTIME, &sev_30ms, &timerid_30ms);

    timer_30ms.it_value.tv_sec = 0;  // 初回のタイマー発火までの時間（秒）
    timer_30ms.it_value.tv_nsec = 1;
    timer_30ms.it_interval.tv_sec = 0;  // 以降の周期（秒）
    timer_30ms.it_interval.tv_nsec = 30 * 1000 * 1000;

    timer_settime(timerid_30ms, 0, &timer_30ms, nullptr);

    // 10msタイマーの設定
    sev_10ms.sigev_notify = SIGEV_THREAD;
    sev_10ms.sigev_value.sival_ptr = &timerid_10ms;
    sev_10ms.sigev_notify_function = timer_handler_10ms;
    sev_10ms.sigev_notify_attributes = nullptr;

    timer_create(CLOCK_REALTIME, &sev_10ms, &timerid_10ms);

    timer_10ms.it_value.tv_sec = 0;  // 初回のタイマー発火までの時間（秒）
    timer_10ms.it_value.tv_nsec = 1;
    timer_10ms.it_interval.tv_sec = 0;  // 以降の周期（秒）
    timer_10ms.it_interval.tv_nsec = 10 * 1000 * 1000;

    timer_settime(timerid_10ms, 0, &timer_10ms, nullptr);

    while (true) {
        pause();  // シグナルを待機
    }

    return 0;
}
