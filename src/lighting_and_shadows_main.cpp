#include <chrono>

#include "lighting_and_shadows.h"

int main(int argc, char *argv[])
{
    LightingAndShadows *render = new LightingAndShadows(1920, 1080);
    int result = render->LoadGeometry("models/CornellBox-Original.obj");
    if (result)
    {
        return result;
    }
    render->SetCamera(float3{0.f, 1.f, 3.f}, float3{0, 1.f, 0}, float3{0, 1, 0});
    render->AddLight(new Light(float3{0, 1.98f, -0.06f}, float3{0.78f, 0.78f, 0.78f}));
    render->Clear();
    render->DrawScene();
    result = render->Save("results/lighting.png");
    return result;
}