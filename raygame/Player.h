#pragma once

#include "Actor.h"

class Player : Actor
{

public:
	Player() {}

	void onCollision(Actor* other) override;

	void start() override;
	void update(float deltaTime) override;
	void draw() override;
	void debug() override;
	void end() override;

private:

public:

private:
	float m_health;
	float m_damage;

};