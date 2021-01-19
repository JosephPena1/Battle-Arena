#include "Player.h"
#include "Game.h"
#include "raylib.h"
#include "Sprite.h"
#include <cmath>

Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed)
{
    m_globalTransform = new MathLibrary::Matrix3();
    m_localTransform = new MathLibrary::Matrix3();
    m_rotation = new MathLibrary::Matrix3();
    m_translation = new MathLibrary::Matrix3();
    m_scale = new MathLibrary::Matrix3();

    setLocalPosition(MathLibrary::Vector2(x, y));
    m_velocity = MathLibrary::Vector2();
    m_maxSpeed = maxSpeed;
    m_health = 3;
}

void Player::update(float deltaTime)
{
	//updateFacing(); //fix

    /*if (checkCollision(m_target) == true)
        return false;*/

	//controls for player
    int xDirection = -Game::getKeyDown(KEY_A) + Game::getKeyDown(KEY_D);
    int yDirection = -Game::getKeyDown(KEY_W) + Game::getKeyDown(KEY_S);

    setAcceleration(MathLibrary::Vector2(xDirection, yDirection));

    if (getVelocity().getMagnitude() > 0)
        lookAt(getWorldPosition() + getVelocity().getNormalized());

    //if left control is pressed down, slow down acceleration \WIP
    if (Game::getKeyDown(KEY_LEFT_CONTROL) == true)
        setAcceleration(getAcceleration() / 10);

    Actor::update(deltaTime);
}

void Player::debug()
{

}

void Player::draw()
{
    //DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, 50, DARKBLUE);
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

void Player::onCollision(Actor* other)
{

    Actor::onCollision(other);
}

void Player::takeDamage()
{
    m_health -= 1;
}

//updates the player's current facing
void Player::updateFacing()
{
    if (m_velocity.getMagnitude() != 0)
        setRotation(-(float)atan2(m_velocity.y, m_velocity.x));

    Actor::updateFacing();
}