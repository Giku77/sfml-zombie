#include "stdafx.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "Zombie.h"

SceneGame::SceneGame()
	:Scene(SceneIds::Game)
{
}

void SceneGame::Init() {
	texIds.push_back("graphics/player.png");
	texIds.push_back("graphics/background_sheet.png");

	texIds.push_back("graphics/bloater.png");
	texIds.push_back("graphics/chaser.png");
	texIds.push_back("graphics/crawler.png");
	texIds.push_back("graphics/crosshair.png");

	AddGameObject(new TileMap("TileMap"));

	player = (Player*)AddGameObject(new Player("Player"));

	for (int i = 0; i < 100; i++) {
		Zombie* zombie = (Zombie*)AddGameObject(new Zombie());
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}

	Scene::Init();
}

void SceneGame::Exit() {
	FRAMEWORK.GetWindow().setMouseCursorVisible(true);

	for (auto zombie : zombieList) {
		//RemoveGameObject(zombie);
		zombie->SetActive(false);
		zombiePool.push_back(zombie);
	}
	zombieList.clear();

	std::cout << "zombiePool의 사이즈 : " << zombiePool.size() << std::endl;

	Scene::Exit();
}

void SceneGame::Enter() {

	FRAMEWORK.GetWindow().setMouseCursorVisible(false);

	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);


	Scene::Enter();

	cursor.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	Utils::SetOrigin(cursor, Origins::MC);
}

void SceneGame::Update(float dt) 
{
	cursor.setPosition(ScreenToUi(InputMgr::GetMousePosition()));

	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space)) {
		SpawnZombies(10);
		std::cout << "남아 있는 좀비 수 : " << zombieList.size() << std::endl;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter)) {
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneGame::SpawnZombies(int count)
{
	for (int i = 0; i < count; i++) {
		Zombie* zombie = nullptr;
		if (zombiePool.empty()) {
			zombie = (Zombie*)AddGameObject(new Zombie());
			zombie->Init();
		}
		else {
			zombie = zombiePool.front();
			zombiePool.pop_front();
			zombie->SetActive(true);
		}


		zombie->SetType((Zombie::Types)Utils::RandomRange(0, Zombie::TotalTypes));

		zombie->Reset();

		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);

		zombieList.push_back(zombie);
	}
}

void SceneGame::Draw(sf::RenderWindow& window) {
	Scene::Draw(window);

	window.setView(uiView);
	window.draw(cursor);
}
