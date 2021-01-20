#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "raylib.h"

bool Game::m_gameOver = false;
bool Game::m_win = false;
bool Game::m_lose = false;
bool Game::m_playerChoice = true;
Scene** Game::m_scenes = new Scene*;
int Game::m_sceneCount = 0;
int Game::m_currentSceneIndex = 0;
float countDown;

Game::Game()
{
	m_gameOver = false;
	m_scenes = new Scene*;
	m_camera = new Camera2D();
	m_currentSceneIndex = 0;
	m_sceneCount = 0;
}

Game::~Game()
{
	delete m_scenes;
	delete m_camera;
}

void Game::start()
{
	int screenWidth = 1024;
	int screenHeight = 760;

	InitWindow(screenWidth, screenHeight, "Battle-Arena");
	m_camera->offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->target = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->zoom = 1;

	SetTargetFPS(60);

	player = new Player(10, 10, 3, 5, "Images/player.png", 5);
	enemy = new Enemy(10, 20, 2, 5, "Images/enemy.png", 2, player);
	enemy2 = new Enemy(5, 20, 2, 5, "Images/enemy.png", 2, player);

	Scene* scene = new Scene();

	player->setScale(MathLibrary::Vector2(3, 3));
	enemy->setScale(MathLibrary::Vector2(3, 3));
	enemy2->setScale(MathLibrary::Vector2(3, 3));

	scene->addActor(player);
	scene->addActor(enemy);
	scene->addActor(enemy2);
	addScene(scene);

	startingTime = 0; //default 5
	maxTime = 10 + startingTime; //default 60
}

void Game::update(float deltaTime)
{
	for (int i = 0; i < m_sceneCount; i++)
	{
		m_scenes[i]->update(deltaTime);
	}

	countDown = startingTime - GetTime();
	timeRemaining = maxTime - GetTime();

	//when time runs out, give lose message, then gameOver = true
	if (timeRemaining <= 0)
	{
		Game::m_lose = true;
		//Game::setGameOver(true);
	}
		
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(DARKGREEN);

	for (int i = 0; i < m_sceneCount; i++)
	{
		m_scenes[i]->draw();
	}

	//Draws the timer to the screen
	if (countDown > 0)
		DrawText(TextFormat("%f", countDown), 400, 1, 50, BLACK);
	else if (timeRemaining > 0)
		DrawText(TextFormat("%f", timeRemaining), 400, 1, 50, BLACK);
	
	EndMode2D();
	EndDrawing();
}

void Game::end()
{
	CloseWindow();
}

MathLibrary::Matrix3* Game::getWorld()
{
	return getCurrentScene()->getWorld();
}

void Game::run()
{
	start();

	while (!m_gameOver && !RAYLIB_H::WindowShouldClose())
	{
		float deltaTime = RAYLIB_H::GetFrameTime();
		update(deltaTime);
		draw();
	}
	/*if (m_playerChoice == true)
		restart();*/

	end();
}

Scene* Game::getScene(int index)
{
	if (index < 0 || index >= m_sceneCount)
		return nullptr;

	return m_scenes[index];
}

Scene* Game::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Game::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Game::addScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return -1;

	//Create a new temporary array that one size larger than the original
	Scene** tempArray = new Scene*[m_sceneCount + 1];

	//Copy values from old array into new array
	for (int i = 0; i < m_sceneCount; i++)
	{
		tempArray[i] = m_scenes[i];
	}

	//Store the current index
	int index = m_sceneCount;

	//Sets the scene at the new index to be the scene passed in
	tempArray[index] = scene;

	//Set the old array to the tmeporary array
	m_scenes = tempArray;
	m_sceneCount++;

	return index;
}

bool Game::removeScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return false;

	bool sceneRemoved = false;

	//Create a new temporary array that is one less than our original array
	Scene** tempArray = new Scene*[m_sceneCount];

	//Copy all scenes except the scene we don't want into the new array
	int j = 0;
	for (int i = 0; i < m_sceneCount; i++)
	{
		if (tempArray[i] != scene)
		{
			tempArray[j] = m_scenes[i];
			j++;
		}
		else
		{
			sceneRemoved = true;
		}
	}

	//If the scene was successfully removed set the old array to be the new array
	if (sceneRemoved)
	{
		m_scenes = tempArray;
		m_sceneCount--;
	}
		

	return sceneRemoved;
}

void Game::setCurrentScene(int index)
{
	//If the index is not within the range of the the array return
	if (index < 0 || index >= m_sceneCount)
		return;

	//Call end for the previous scene before changing to the new one
	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	//Update the current scene index
	m_currentSceneIndex = index;
}

bool Game::getKeyDown(int key)
{
	return RAYLIB_H::IsKeyDown((KeyboardKey)key);
}

bool Game::getKeyPressed(int key)
{
	return RAYLIB_H::IsKeyPressed((KeyboardKey)key);
}

void Game::setWin(bool value)
{
	m_win = value;
}

void Game::setLose(bool value)
{
	m_lose = value;
}

void Game::setPlayerChoice(bool value)
{
	m_playerChoice = value;
}

void Game::destroy(Actor* actor)
{
	getCurrentScene()->removeActor(actor);
	if (actor->getParent())
		actor->getParent()->removeChild(actor);
	actor->end();
	delete actor;
}

void Game::restart()
{
	m_playerChoice = false;
	m_gameOver = false;
	Scene* scene = getCurrentScene();

	scene->removeActor(player);
	scene->removeActor(enemy);
	scene->removeActor(enemy2);
	delete player;
	delete enemy;
	delete enemy2;

	end();
	run();
}

void Game::setGameOver(bool value)
{
	Game::m_gameOver = value;
}

bool Game::timer()
{
	if (GetTime() - maxTime == 0)
	{
		return true;
	}
	return false;
}