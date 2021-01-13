#pragma once

#include "Actor.h"

class Player : Actor
{

public:
	Player() {}

	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
	/// <param name="icon">The symbol that will appear when drawn</param>
	/// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
	Player(float x, float y, float collisionRadius, char icon, float maxSpeed);

	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
	/// <param name="sprite">That sprite that will be drawn in this actors draw function.</param>
	Player(float x, float y, float collisionRadius, Sprite* sprite, float maxSpeed);

	/// <param name="x">Position on the x axis</param>
	/// <param name="y">Position on the y axis</param>
	/// <param name="collisionRadius">The size of the circle surrounding the actor that will be used to detect collisions.</param>
	/// <param name="sprite">That path for the sprite that will be drawn in this actors draw function.</param>
	/// <param name="maxSpeed">The largest the magnitude of the actors velocity can be.</param>
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed);

	void onCollision(Actor* other) override;

	void start() override;
	void update(float deltaTime) override;
	void draw() override;
	void debug() override;
	void end() override;

protected:
	void updateFacing() override;

private:


public:

private:
	float m_health;
	float m_damage;
	Sprite* m_sprite;

};