#include "camera.h"
#include "playerPawn.h"
#include "main.h"
#include "pipeEntrance.h"

Camera::Camera(sp::P<sp::Node> parent)
: sp::Camera(parent)
{
    setOrtographic(8.0, Direction::Horizontal);
    setPosition(sp::Vector2d(8, 0));
}

void Camera::onUpdate(float delta)
{
    if (PipeEntrance::active_entrance)
        return;
    
    std::vector<double> position_x;
    for(auto player : PlayerPawn::all)
        position_x.push_back(player->getPosition2D().x);
    std::sort(position_x.begin(), position_x.end());
    
    if (position_x.size() > 0)
    {
        double target;
        if (position_x.size() > 1)
        {
            double max_x = position_x.back();
            double average = 0;
            for(unsigned int n=0; n<position_x.size() / 2; n++)
                average += position_x[n + position_x.size() / 4];
            average /= position_x.size() / 2;
            
            target = std::max(max_x - max_forward_distance, average);
        }
        else
        {
            target = position_x[0];
        }
        
        target = std::min(target, global_area_data.view_limit - 8.0);
        target = std::max(target, getPosition2D().x);
        if (init)
            init = false;
        else
            target = std::min(target, getPosition2D().x + delta * maximum_move_speed);
        setPosition(sp::Vector2d(target, 6.5));
    }
}
