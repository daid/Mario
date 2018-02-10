#ifndef CAMERA_H
#define CAMERA_H

#include <sp2/scene/camera.h>

class Camera : public sp::Camera
{
public:
    Camera(sp::P<sp::Node> parent);
    
    virtual void onUpdate(float delta) override;
    
    static constexpr double max_forward_distance = 4.0;
    static constexpr double default_forward_view = 2.0;
    static constexpr double maximum_move_speed = 12.0;

private:
    bool init=true;
};

#endif//CAMERA_H
