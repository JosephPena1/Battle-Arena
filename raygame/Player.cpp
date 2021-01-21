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

//updates the player's current facing
void Player::updateFacing()
{
    if (IsCursorOnScreen(true))



    Actor::updateFacing();
}