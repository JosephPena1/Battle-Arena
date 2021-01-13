#include "Player.h"
#include "raylib.h"
#include "Sprite.h"

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