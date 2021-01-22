#pragma once

#include "Actor.h"

class Player
	: public Actor
{

public:
	Player() : Actor() {}
	Player(float x, float y, float health, float collisionRadius, const char* spriteFilePath, float maxSpeed);
	void update(float deltatime) override;
	void debug() override;
	void draw() override;

	void onCollision(Actor* other) override;
	void takeDamage();

protected:
	void updateFacing() override;

private:
	float m_immuneFrames;
	float m_immuneTime;
};