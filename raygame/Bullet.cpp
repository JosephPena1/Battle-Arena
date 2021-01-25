#include "Bullet.h"
#include "Game.h"
#include "Sprite.h"
#include "raylib.h"
#include <typeinfo>

Bullet::Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, MathLibrary::Vector2 velocity) : Actor(x, y, collisionRadius, spriteFilePath, maxSpeed, velocity)
{
	setVelocity(velocity);
}

void Bullet::update(float deltaTime)
{
	Actor::update(deltaTime);

	if (getWorldPosition().x < 0 || getWorldPosition().x > 50 || getWorldPosition().y < 0 || getWorldPosition().y > 30)
		Game::destroy(this);
}

void Bullet::draw()
{
	Actor::draw();
}

void Bullet::onCollision(Actor* other)
{
	if (typeid(other) == typeid(Enemy()))
	{
		other->takeDamage();
		Actor::onCollision(other);
	}
}
