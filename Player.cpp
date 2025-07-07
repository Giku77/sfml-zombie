#include "stdafx.h"
#include "Player.h"
#include "SceneGame.h"

Player::Player(const std::string& name)
	:GameObject(name)
{

}

void Player::SetPosition(const sf::Vector2f& pos) {
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}
void Player::SetRotation(float rot) {
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}
void Player::SetScale(const sf::Vector2f& s) {
	GameObject::SetScale(s);
	body.setScale(s);
}
void Player::SetOrigin(const sf::Vector2f& o) {
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}
void Player::SetOrigin(Origins preset) {
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom) Utils::SetOrigin(body, preset);
}


void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	SetOrigin(Origins::MC);
}

void Player::Release()
{
}

void Player::Reset()
{
	if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Game) {
		sceneGame = (SceneGame*)SCENE_MGR.GetCurrentScene();
	}
	else sceneGame = nullptr;

	body.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);
	SetPosition({ 0.f, 0.f });
	SetRotation(0.f);

	dir = { 0.f, 0.f };
	look = { 1.0f, 0.f };
}

void Player::Update(float dt)
{
	//Pos
	dir.x = InputMgr::GetAxis(Axis::Horizontal);
	dir.y = InputMgr::GetAxis(Axis::Vertical);

	if (Utils::Magnitude(dir) > 1.f) {
		Utils::Normalize(dir); //대각선 이동에서 정규화로 1로 크기 조절 필요
	}
	SetPosition(position + dir * speed * dt);

	//Rot
	sf::Vector2i mousePos = InputMgr::GetMousePosition();

	sf::Vector2f mouseWPos = sceneGame->ScreenToWorld(mousePos);
	look = Utils::GetNormal(mouseWPos - GetPosition());
	//look = Utils::GetNormal((sf::Vector2f)InputMgr::GetMousePosition() - GetPosition());
	SetRotation(Utils::Angle(look));
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
