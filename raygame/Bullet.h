#pragma once
#include "Actor.h"

class Bullet : public Actor
{
public:
	Bullet() : Actor() {};
	Bullet(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, MathLibrary::Vector2 velocity);
	void update(float deltaTime) override;
	void draw() override;

protected:
	void updateFacing() override;
};