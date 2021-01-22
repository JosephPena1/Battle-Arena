#include "Player.h"
#include "Game.h"
#include "raylib.h"
#include "Sprite.h"
#include "Bullet.h"
#include <cmath>

Player::Player(float x, float y, float health, float collisionRadius, const char* spriteFilePath, float maxSpeed) : Actor(x, y, health, collisionRadius, spriteFilePath, maxSpeed)
{
    m_globalTransform = new MathLibrary::Matrix3();
    m_localTransform = new MathLibrary::Matrix3();
    m_rotation = new MathLibrary::Matrix3();
    m_translation = new MathLibrary::Matrix3();
    m_scale = new MathLibrary::Matrix3();

    setLocalPosition(MathLibrary::Vector2(x, y));
    m_velocity = MathLibrary::Vector2();
    m_maxSpeed = maxSpeed;
    m_health = health;
}

void Player::update(float deltaTime)
{
    if (!Game::getWin() && !Game::getLose())
    {
        if (m_health <= 0)
            Game::setLose(true);
        else
        {
            updateFacing(); //fix

            /*if (checkCollision(m_target) == true)
            return false;*/

            //controls for player
            int xDirection = -Game::getKeyDown(KEY_A) + Game::getKeyDown(KEY_D);
            int yDirection = -Game::getKeyDown(KEY_W) + Game::getKeyDown(KEY_S);

            setAcceleration(MathLibrary::Vector2(xDirection, yDirection));

            /*if (getVelocity().getMagnitude() > 0)
                lookAt(getWorldPosition() + getVelocity().getNormalized());*/

            //if left control is pressed down, slow down acceleration \WIP
            if (Game::getKeyDown(KEY_LEFT_CONTROL) == true)
            {
                setAcceleration(getAcceleration() / 1.50f);
                setVelocity(getVelocity() / 1.50f);
            }
          
            //if space is pressed once, shoot bullet \WIP
            if (Game::getKeyPressed(KEY_SPACE))
                Game::getCurrentScene()->addActor(new Bullet(getWorldPosition().x, getWorldPosition().y, 2, "Images/bullettest.png", 10, getVelocity() * 10));

            if (m_immuneFrames >= 70)
            {
                m_immuneTime++;
                m_immuneFrames = 0;
            }
            else
                m_immuneFrames++;
        }
    }

    else
    {
        if (Game::getKeyDown(KEY_ENTER))
        {
            Game::setGameOver(true);
        }

        setVelocity(MathLibrary::Vector2(0, 0));
        setAcceleration(MathLibrary::Vector2(0, 0));
    }
    Actor::update(deltaTime);
}

void Player::debug()
{
}

void Player::draw()
{
    if (!Game::getWin() && !Game::getLose())
    {
        if (m_immuneTime < 1)
        {
            Actor::draw();
        }
        else
        {
            setSprite("Images/Player.png");
            Actor::draw();
        }
    }
    else
        Actor::draw();
}

void Player::onCollision(Actor* other)
{
    Actor::onCollision(other);
}

void Player::takeDamage()
{
    if (GetTime() > 2 && m_immuneTime > 1)
    {
        m_health -= 1;
        m_immuneTime = 0;
        setSprite("Images/PlayerHurt.png");
    }
}

//updates the player's current facing
void Player::updateFacing()
{
    if (m_velocity.getMagnitude() != 0)
        setRotation(-(float)atan2(m_velocity.y, m_velocity.x));

    Actor::updateFacing();
}