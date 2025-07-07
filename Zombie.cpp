#include "stdafx.h"
#include "Zombie.h"
#include "Player.h"

Zombie::Zombie(const std::string& name)
	: GameObject(name)
{
}

void Zombie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Zombie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Zombie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Zombie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Zombie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Zombie::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetType(type);
}

void Zombie::Release()
{
}

void Zombie::Reset()
{
	player = (Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Player");

	body.setTexture(TEXTURE_MGR.Get(texId));

	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);
	SetScale({ 1.f, 1.f });
}

void Zombie::Update(float dt)
{
	//std::cout << "°Å¸® : " << Utils::Distance(player->GetPosition(), GetPosition()) << std::endl;
	if (Utils::Distance(player->GetPosition(), GetPosition()) <= 5) {
		//speed = 0.f;
		dir = { 0.f, 0.f };
		///*if (Utils::CheckCollision(player->getBody(), body)) {
		//	dir = Utils::GetNormal(player->GetPosition() - GetPosition());
		//	dir.x *= -1.f;
		//	dir.y *= -1.f;
		//	SetRotation(Utils::Angle(dir));
		//	SetPosition(GetPosition() + dir * speed * dt);
		//}*/
	}
	else {
		dir = Utils::GetNormal(player->GetPosition() - GetPosition());
		SetRotation(Utils::Angle(dir));
		SetPosition(GetPosition() + dir * speed * dt);
	}
}

void Zombie::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Zombie::SetType(Types type)
{
	this->type = type;
	switch (this->type)
	{
	case Types::Bloater:
		texId = "graphics/bloater.png";
		maxHp = 200;
		speed = 50.f;
		damage = 100.f;
		attackInterval = 1.f;
		break;
	case Types::Chase:
		texId = "graphics/chaser.png";
		maxHp = 100;
		speed = 100.f;
		damage = 100.f;
		attackInterval = 1.f;
		break;
	case Types::Crawler:
		texId = "graphics/crawler.png";
		maxHp = 50;
		speed = 200.f;
		damage = 100.f;
		attackInterval = 1.f;
		break;
	default:
		break;
	}

}
