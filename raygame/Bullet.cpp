#include "Bullet.h"
#include "Game.h"
#include <cmath>

Bullet::Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, MathLibrary::Vector2 velocity) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed, velocity)
{
	setVelocity(velocity);
	setScale(MathLibrary::Vector2(2,2));
}

void Bullet::update(float deltaTime)
{
	Actor::update(deltaTime);

	if (getWorldPosition().x < 0 || getWorldPosition().x > 50
		|| getWorldPosition().y < 0 || getWorldPosition().y > 30)

		Game::destroy(this);
}

void Bullet::draw()
{
	Actor::draw();
}

void Bullet::updateFacing()
{
	if (m_velocity.getMagnitude() != 0)
		setRotation(-(float)atan2(m_velocity.y, m_velocity.x));

	Actor::updateFacing();
}
