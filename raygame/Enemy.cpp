#include "Enemy.h"
#include "Game.h"
#include "raylib.h"
#include "Sprite.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed)
{
    m_globalTransform = new MathLibrary::Matrix3();
    m_localTransform = new MathLibrary::Matrix3();
    m_rotation = new MathLibrary::Matrix3();
    m_translation = new MathLibrary::Matrix3();
    m_scale = new MathLibrary::Matrix3();

    setLocalPosition(MathLibrary::Vector2(x, y));
    m_velocity = MathLibrary::Vector2();
    m_maxSpeed = maxSpeed;
}

//Returns true if target is in sight, false if not
bool Enemy::detectTarget(float maxAngle, float maxDistance)
{
    if (m_target == nullptr)
        return false;

    MathLibrary::Vector2 getDot;

    MathLibrary::Vector2 direction = m_target->getLocalPosition() - getLocalPosition();

    float distance = direction.getMagnitude();

    float angle = (float)acos(getDot.dotProduct(getForward(), direction.getNormalized()));

    if (angle <= maxAngle && distance <= maxDistance)
        return true;

    return false;
}

void Enemy::update(float deltatime)
{
    updateFacing();

    // [if] target is in range, follow
    if (detectTarget(5, 5) == true)
    {
        setAcceleration(m_target->getLocalPosition() - getLocalPosition());
    }

    // [else] slow to a stop \WIP
    /*else
    {
        if ((getAcceleration().x || getAcceleration().y > 0) || (getAcceleration().x || getAcceleration().y < 0))
            setAcceleration(MathLibrary::Vector2(0, 0));

        if ((getVelocity().x || getVelocity().y > 0) || (getVelocity().x || getVelocity().y < 0))
            setVelocity(MathLibrary::Vector2(0, 0));
        
    }*/

    Actor::update(deltatime);
}

void Enemy::debug()
{

}

void Enemy::draw()
{
    DrawText(TextFormat("%f", getVelocity().x), 5, 5, 20, BLACK);
    DrawText(TextFormat("%f", getVelocity().y), 5, 20, 20, BLACK);

    Actor::draw();
}


void Enemy::setTarget(Actor* target)
{
    m_target = target;
}

void Enemy::updateFacing()
{
    

    if (m_velocity.getMagnitude() != 0)
        setRotation(-(float)atan2(m_velocity.y, m_velocity.x));

    Actor::updateFacing();
}
