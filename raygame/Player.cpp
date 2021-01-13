#include "Player.h"
#include "raylib.h"
#include "Sprite.h"

Player::Player(float x, float y, float health, float damage, float collisionRadius, char icon, float maxSpeed)
{
    m_globalTransform = new MathLibrary::Matrix3();
    m_localTransform = new MathLibrary::Matrix3();
    m_rotation = new MathLibrary::Matrix3();
    m_translation = new MathLibrary::Matrix3();
    m_scale = new MathLibrary::Matrix3();

    m_icon = icon;
    setLocalPosition(MathLibrary::Vector2(x, y));
    m_velocity = MathLibrary::Vector2();
    m_maxSpeed = maxSpeed;
}

Player::Player(float x, float y, float health, float damage, float collisionRadius, Sprite* sprite, float maxSpeed)
{
    m_sprite = sprite;
}

Player::Player(float x, float y, float health, float damage, float collisionRadius, const char* spriteFilePath, float maxSpeed)
{
    m_sprite = new Sprite(spriteFilePath);
}

void Player::onCollision(Actor* other)
{
    Actor::onCollision(other);
}

void Player::start()
{
	Actor::start();
}

void Player::update(float deltaTime)
{
	updateFacing();

	//controls for player below here

	Actor::update(deltaTime);
}

void Player::draw()
{
    DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, 50, BLUE);

    //Draws the actor and a line indicating it facing to the raylib window
    DrawLine(
        (int)(getWorldPosition().x * 32),
        (int)(getWorldPosition().y * 32),
        (int)((getWorldPosition().x + getForward().x) * 32),
        (int)((getWorldPosition().y + getForward().y) * 32),
        WHITE
    );

    if (m_sprite)
        m_sprite->draw(*m_globalTransform);
    Actor::draw();
}

void Player::debug()
{

}

void Player::end()
{
    Actor::end();
}

//updates the player's current facing
void Player::updateFacing()
{

}