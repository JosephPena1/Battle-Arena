#pragma once

#include "Actor.h"

class Enemy
	: public Actor
{

public:
	Enemy() : Actor() {};
	Enemy(float x, float y, float health, float collisionRadius, const char* spriteFilePath, float maxSpeed, Actor* target);
	bool detectTarget(float maxAngle, float maxDistance);
	void update(float deltatime) override;
	void debug() override;
	void draw() override;

	/// <summary>
	/// Creates the given number of enemies and adds them to the scene. 
	/// </summary>
	/// <param name="enemyCount">The amount of enemies created.</param>
	/// <param name="target">The collision target</param>
	static void createEnemies(int enemyCount, Actor* target);

	//sets collision target for enemy
	void setTarget(Actor* target);
	void onCollision(Actor* other) override;
	void takeDamage();

protected:
	void updateFacing() override;

private:
	Actor* m_target;
};