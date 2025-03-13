#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    // Pythonで指定した共有メモリの名前
    const char* shm_name = "yuta";  // Pythonで出力された名前を入力

    // 共有メモリを開く
    int fd = shm_open(shm_name, O_RDONLY, 0666);
    if (fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    // 共有メモリのマッピング
    size_t data_size = 4 * sizeof(int);  // int型4つ分
    void* ptr = mmap(0, data_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    // データの読み取り
    int* data = static_cast<int*>(ptr);
    for (size_t i = 0; i < 4; ++i) {
        std::cout << "Data[" << i << "]: " << data[i] << std::endl;
    }

    // 後処理
    munmap(ptr, data_size);
    close(fd);

    return 0;
}
