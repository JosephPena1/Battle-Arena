#pragma once

#include "Actor.h"

class Player : public Actor
{

public:
	Player() : Actor() {}
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed);
	void update(float deltatime) override;
	void debug() override;
	void draw() override;

	void onCollision(Actor* other) override;
	void takeDamage();

protected:
	void updateFacing() override;

private:
	float m_health;
	float m_collisionRadius;
	Actor** m_actors;
	int m_actorCount;
	Sprite* m_sprite;

};