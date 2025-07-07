#pragma once
#include "Scene.h"

class Player;
class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
public:
	SceneGame();
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
};

