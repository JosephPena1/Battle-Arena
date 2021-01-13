#include "Player.h"
#include "Game.h"
#include "raylib.h"
#include "Sprite.h"
#include <cmath>

Player::Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed)
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

void Player::update(float deltaTime)
{
	updateFacing();

    //setAcceleration(MathLibrary::Vector2());

	//controls for player
    int xDirection = -Game::getKeyDown(KEY_A) + Game::getKeyDown(KEY_D);
    int yDirection = -Game::getKeyDown(KEY_W) + Game::getKeyDown(KEY_S);

    if (getVelocity().getMagnitude() > 0)
        lookAt(getWorldPosition() + getVelocity().getNormalized());

    Actor::update(deltaTime);
}

//updates the player's current facing
void Player::updateFacing()
{
    if (m_velocity.getMagnitude() != 0)
        setRotation(-(float)atan2(m_velocity.y, m_velocity.x));

    Actor::updateFacing();
}