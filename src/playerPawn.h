#ifndef PLAYER_PAWN_H
#define PLAYER_PAWN_H

#include <sp2/scene/node.h>
#include "pipeEntrance.h"
class InputController;
class PlayerPawn : public sp::Node
{
public:
    enum class State
    {
        Falling,
        Jumping,
        Walking,
        Swimming,
        EnterPipe,
        Death,
        Finish
    };
    
    PlayerPawn(sp::P<sp::Node> parent, InputController& controller, sp::string animation_name);
    virtual void onUpdate(float delta);
    virtual void onFixedUpdate();
    virtual void onCollision(sp::CollisionInfo& info);

    double getBottomPosition();

    void didHeadBump();
    void trampolineFire();
    bool takeDamage();
    void gotFlagpole(double x);
    
    bool upgrade();
    int getUpgradeLevel();
    bool setInvincibilityTime(float time, bool auto_kill);
    bool isInWater();
    
    void finish();
    bool isFinished();
    
    State getState() { return state; }
    sp::string getAnimationName() { return animation_name; }
    
    bool enterPipe(PipeEntrance::Type type);

    static sp::P<PlayerPawn> getClosestTo(sp::Vector2d);
    static sp::PList<PlayerPawn> all;

    InputController& controller;
private:
    void die();
    void setupCollisionShape();

    State state;
    enum class FinishSubState
    {
        GlidingDownPole,
        Walking,
        Stopped
    } finish_state;
    double finish_final_x;
    double jump_start_velocity_x = 0.0;
    double death_velocity = 0.0;
    bool skidding = false;
    bool left = false;
    bool wants_to_jump = false;
    float invincibility_time = 0;
    bool invincibility_auto_kill = false;
    int still_running_timeout = 0;
    sp::string animation_prefix;
    
    sp::string animation_name;
};

#endif//PLAYER_PAWN_H
