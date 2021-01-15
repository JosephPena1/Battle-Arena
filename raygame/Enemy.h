#pragma once

#include "Actor.h"

class Enemy : public Actor
{

public:
	Enemy() :Actor() {}
	Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed);
	bool detectTarget(float maxAngle, float maxDistance);
	void update(float deltatime) override;
	void debug() override;
	void draw() override;

	void setTarget(Actor* target);

protected:
	void updateFacing() override;

private:
	Actor* m_target;
};