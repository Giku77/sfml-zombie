#pragma once
#include "GameObject.h"

class Player;
class Zombie : public GameObject
{
public:
	enum class Types
	{
		Bloater,
		Chase,
		Crawler,
	};
	
	static const int TotalTypes = 3;

protected:
	Types type = Types::Bloater;
	Player* player = nullptr;


	sf::Sprite body;
	std::string texId;

	sf::Vector2f dir;

	int maxHp = 0;
	int hp = 0;
	int damage = 0;
	float attackInterval = 0.f;

	float speed = 0.f;

public:
	Zombie(const std::string& name = "");
	virtual ~Zombie() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetType(Types type);
};

