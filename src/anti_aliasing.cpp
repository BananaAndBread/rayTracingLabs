#include "anti_aliasing.h"

AntiAliasing::AntiAliasing(short width, short height) : AccelerationStructures(width, height)
{
    camera.SetRenderTargetSize(width * 2, height * 2);
}

AntiAliasing::~AntiAliasing() {}

void AntiAliasing::DrawScene()
{
    for (int x = 0; x < width; x++)
    {
#pragma omp parallel for
        for (int y = 0; y < height; y++)
        {
            Ray camera_ray_1 = camera.GetCameraRay(2 * x, 2 * y);
            Payload payload_1 = TraceRay(camera_ray_1, raytracing_depth);

            Ray camera_ray_2 = camera.GetCameraRay(2 * x + 1, 2 * y);
            Payload payload_2 = TraceRay(camera_ray_2, raytracing_depth);
            
            Ray camera_ray_3 = camera.GetCameraRay(2 * x, 2 * y + 1);
            Payload payload_3 = TraceRay(camera_ray_3, raytracing_depth);
            
            Ray camera_ray_4 = camera.GetCameraRay(2 * x + 1, 2 * y + 1);
            Payload payload_4 = TraceRay(camera_ray_4, raytracing_depth);

            SetPixel(x, y, (payload_1.color + payload_2.color + payload_3.color + payload_4.color) / 4);
        }
    }
}
