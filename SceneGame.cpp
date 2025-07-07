#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init() {
	texIds.push_back("graphics/player.png");

	player = (Player*)AddGameObject(new Player("Player"));
	Scene::Init();
}

void SceneGame::Enter() {

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);



	Scene::Enter();
}
