#include "Enemy.h"
#include "Game.h"
#include "raylib.h"
#include "Sprite.h"
#include <random>
#include <typeinfo>
#include <cmath>

Enemy::Enemy(float x, float y, float health,float collisionRadius, const char* spriteFilePath, float maxSpeed, Actor* target) : Actor(x, y, health, collisionRadius, spriteFilePath, maxSpeed)
{
    m_globalTransform = new MathLibrary::Matrix3();
    m_localTransform = new MathLibrary::Matrix3();
    m_rotation = new MathLibrary::Matrix3();
    m_translation = new MathLibrary::Matrix3();
    m_scale = new MathLibrary::Matrix3();

    setLocalPosition(MathLibrary::Vector2(x, y));
    m_velocity = MathLibrary::Vector2();
    m_maxSpeed = maxSpeed;
    m_target = target;
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
    if (!Game::getWin() && !Game::getLose())
    {
        updateFacing();

        //if player was hit, make immune for 1 second.
        //if collision = true and time is > 3; call onCollision
        if (checkCollision(m_target) == true && GetTime() > 3)
            onCollision(m_target);

        setAcceleration(m_target->getLocalPosition() - getLocalPosition());

        // [if] target is in range, follow
        /*if (detectTarget(20, 20) == true)
        {
            setAcceleration(m_target->getLocalPosition() - getLocalPosition());
        }*/

        // [else] slow to a stop \WIP
        /*else
        {
            if ((getAcceleration().x || getAcceleration().y > 0) || (getAcceleration().x || getAcceleration().y < 0))
                setAcceleration(MathLibrary::Vector2(0, 0));

            if ((getVelocity().x || getVelocity().y > 0) || (getVelocity().x || getVelocity().y < 0))
                setVelocity(MathLibrary::Vector2(0, 0));

        }*/
    }

    else
    {
        setVelocity(MathLibrary::Vector2(0, 0));
        setAcceleration(MathLibrary::Vector2(0, 0));
    }
    

    Actor::update(deltatime);
}

void Enemy::debug()
{

}

void Enemy::draw()
{
    //DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, 50, RED);
    ////Draws the actor and a line indicating it facing to the raylib window
    //DrawLine(
    //    (int)(getWorldPosition().x * 32),
    //    (int)(getWorldPosition().y * 32),
    //    (int)((getWorldPosition().x + getForward().x) * 32),
    //    (int)((getWorldPosition().y + getForward().y) * 32),
    //    WHITE
    //);

    //if (m_sprite)
    //    m_sprite->draw(*m_globalTransform);

    Actor::draw();
}

void Enemy::createEnemies(int enemyCount, Actor* target)
{
    Enemy** enemies = new Enemy*[enemyCount];
    Scene* currentScene = Game::getCurrentScene();

    for (int i = 0; i < enemyCount; i++)
    {
        enemies[i] = new Enemy(GetRandomValue(0, -15), GetRandomValue(0, 30), 2, 1.5f, "Images/enemy.png", 2, target);
        enemies[i]->setScale(MathLibrary::Vector2(2, 2));
        currentScene->addActor(enemies[i]);
    }
}

void Enemy::setTarget(Actor* target)
{
    m_target = target;
}

void Enemy::onCollision(Actor* other)
{
    //for future reference
    /*if (typeid(other) == typeid(Enemy()))
    {

    }*/

    //setLocalPosition(MathLibrary::Vector2(2, 2));

    other->takeDamage();

    Actor::onCollision(other);
}

void Enemy::updateFacing()
{
    if (m_velocity.getMagnitude() != 0)
        setRotation(-(float)atan2(m_velocity.y, m_velocity.x));

    Actor::updateFacing();
}