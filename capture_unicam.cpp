#include <libcamera/libcamera.h>
#include <libcamera/camera_manager.h>
#include <libcamera/framebuffer_allocator.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/mman.h> // mmapおよび関連定数のためのヘッダーを追加

using namespace libcamera;
using namespace std;

int main() {
    // Libcameraの初期化
    CameraManager cm;
    cm.start();

    if (cm.cameras().empty()) {
        cerr << "カメラが見つかりません" << endl;
        return -1;
    }

    // 最初のカメラデバイスを取得
    shared_ptr<Camera> camera = cm.get(cm.cameras()[0]->id());
    if (!camera) {
        cerr << "カメラを取得できません" << endl;
        return -1;
    }

    // カメラを開く
    if (camera->acquire()) {
        cerr << "カメラを開けません" << endl;
        return -1;
    }

    // カメラ設定
    unique_ptr<CameraConfiguration> config = camera->generateConfiguration({StreamRole::Viewfinder});
    if (!config) {
        cerr << "カメラ設定の生成に失敗しました" << endl;
        return -1;
    }
    config->at(0).pixelFormat = formats::BGR888;
    config->at(0).size = {640, 480};

    CameraConfiguration::Status validation = config->validate();
    if (validation == CameraConfiguration::Invalid) {
        cerr << "カメラ設定が無効です" << endl;
        return -1;
    }

    if (camera->configure(config.get())) {
        cerr << "カメラ設定に失敗しました" << endl;
        return -1;
    }

    // バッファの割り当て
    FrameBufferAllocator allocator(camera);
    if (allocator.allocate(config->at(0).stream())) {
        cerr << "バッファの割り当てに失敗しました" << endl;
        return -1;
    }

    std::vector<std::shared_ptr<FrameBuffer>> buffers;
    for (auto &buffer : allocator.buffers(config->at(0).stream())) {
        buffers.push_back(std::shared_ptr<FrameBuffer>(std::move(buffer)));
    }

    // カメラストリームの開始
    if (camera->start()) {
        cerr << "カメラの起動に失敗しました" << endl;
        return -1;
    }

    cout << "カメラが起動しました" << endl;

    // フレームをキャプチャして表示
    for (int i = 0; i < 100; i++) {
        unique_ptr<Request> request = camera->createRequest();
        if (!request) {
            cerr << "リクエストの作成に失敗しました" << endl;
            break;
        }

        // バッファをリクエストにバインド
        for (auto &buffer : buffers) {
            if (request->addBuffer(config->at(0).stream(), buffer.get())) {
                cerr << "リクエストにバッファを追加することに失敗しました" << endl;
                break;
            }
        }

        if (camera->queueRequest(request.get())) {
            cerr << "リクエストのキューイングに失敗しました" << endl;
            break;
        }

        // フレームの取得待ち
        const Request::BufferMap &buffers_map = request->buffers();
        if (buffers_map.empty()) {
            cerr << "フレームの取得に失敗しました" << endl;
            break;
        }

        // OpenCVでフレームを表示
        for (const auto &bufferPair : buffers_map) {
            const FrameBuffer &buffer = *bufferPair.second;
            const FrameBuffer::Plane &plane = buffer.planes()[0];
            void *data = mmap(NULL, plane.length, PROT_READ, MAP_SHARED, plane.fd.get(), 0);
            if (data == MAP_FAILED) {
                cerr << "フレームバッファのマップに失敗しました" << endl;
                break;
            }
            cv::Mat frame(config->at(0).size.height, config->at(0).size.width, CV_8UC3, data, cv::Mat::AUTO_STEP);
            cv::imshow("Camera", frame);
            if (cv::waitKey(30) == 'q') {
                break;
            }
            munmap(data, plane.length);
        }
    }

    // カメラの停止
    camera->stop();

    // カメラのリリース
    camera->release();

    // Libcameraのシャットダウン
    cm.stop();

    return 0;
}
