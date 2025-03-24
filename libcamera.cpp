#include <libcamera/libcamera.h>
#include <libcamera/camera.h>
#include <libcamera/camera_manager.h>
#include <libcamera/framebuffer_allocator.h>
#include <iostream>
#include <memory>

using namespace libcamera;

int main() 
{
    std::shared_ptr<CameraManager> camera_manager = std::make_shared<CameraManager>();
    if (camera_manager->start()) 
    {
        std::cerr << "Failed to start camera manager" << std::endl;
        return -1;
    }

    std::shared_ptr<Camera> camera = camera_manager->get("imx219 10-0010");
    if (!camera) 
    {
        std::cerr << "Failed to get camera" << std::endl;
        return -1;
    }

    if (camera->acquire()) 
    {
        std::cerr << "Failed to acquire camera" << std::endl;
        return -1;
    }

    std::unique_ptr<CameraConfiguration> config = camera->generateConfiguration({ StreamRole::Viewfinder });
    if (!config || config->size() == 0) 
    {
        std::cerr << "Failed to generate configuration" << std::endl;
        camera->release();
        return -1;
    }

    config->at(0).size.width = 640;
    config->at(0).size.height = 480;
    config->at(0).pixelFormat = formats::RGB888;

    if (camera->configure(config.get())) 
    {
        std::cerr << "Failed to configure camera" << std::endl;
        camera->release();
        return -1;
    }

    // フレームバッファの割り当て
    FrameBufferAllocator allocator(camera);
    if (allocator.allocate(config->at(0).stream()))
    {
        std::cerr << "Failed to allocate frame buffer" << std::endl;
        camera->release();
        return -1;
    }

    if (camera->start()) 
    {
        std::cerr << "Failed to start camera" << std::endl;
        camera->release();
        return -1;
    }

    std::cout << "Camera started successfully" << std::endl;
    
    // Implement frame capture and display logic here

    camera->stop();
    camera->release();
    camera_manager->stop();

    return 0;
}
