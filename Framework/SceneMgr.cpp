#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "SceneGame.h"

void SceneMgr::Init()
{
	scenes[SceneIds::Game] = new SceneGame();
	scenes[SceneIds::Dev1] = new SceneDev1();
	scenes[SceneIds::Dev2] = new SceneDev2();


	for (auto& pair : scenes)
	{
		pair.second->Init();
	}

	currentScene = startScene;
	auto it = scenes.find(currentScene);
	if (it != scenes.end())
	{
		it->second->Enter();
	}
}

void SceneMgr::Release()
{
	auto it = scenes.find(currentScene);
	if (it != scenes.end())
	{
		it->second->Exit();
	}

	for (auto& pair : scenes)
	{
		pair.second->Release();
		delete pair.second;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		auto itExit = scenes.find(currentScene);
		if (itExit != scenes.end())
			itExit->second->Exit();

		currentScene = nextScene;
		nextScene = SceneIds::None;

		auto itEnter = scenes.find(currentScene);
		if (itEnter != scenes.end())
			itEnter->second->Enter();
	}

	auto itUpdate = scenes.find(currentScene);
	if (itUpdate != scenes.end())
		itUpdate->second->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	auto itDraw = scenes.find(currentScene);
	if (itDraw != scenes.end())
		itDraw->second->Draw(window);
}
