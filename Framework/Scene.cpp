#include "stdafx.h"
#include "Scene.h"

Scene::Scene(SceneIds id)
	: Id(id)
{
}

void Scene::Init()
{
	for (auto obj : gameObjects)
	{
		obj->Init();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Init();
	}
}

void Scene::Release()
{
	ApplyPendingChanges();
	
	for (auto obj : gameObjects)
	{
		obj->Release();
		delete obj;
	}
	gameObjects.clear();
}

void Scene::Enter()
{
	TEXTURE_MGR.Load(texIds);
	FONT_MGR.Load(fontIds);
	SOUNDBUFFER_MGR.Load(soundIds);

	for (auto obj : gameObjects)
	{
		obj->Reset();
	}

	for (auto obj : objectsToAdd)
	{
		obj->Reset();
	}
}

void Scene::Exit()
{
	ApplyPendingChanges();
	
	TEXTURE_MGR.Unload(texIds);
	FONT_MGR.Unload(fontIds);
	SOUNDBUFFER_MGR.Unload(soundIds);
}

void Scene::Update(float dt)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}



void Scene::Draw(sf::RenderWindow& window)
{
	std::list<GameObject*> sortedObjects(gameObjects);

	sortedObjects.sort(DrawOrderComparer());

	window.setView(worldView);
	bool isUiVeiw = false;

	for (auto obj : sortedObjects)
	{
		if (obj->sortingLayer >= SortingLayers::UI && !isUiVeiw) {
			window.setView(uiView);
			isUiVeiw = true;
		}


		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}

	ApplyPendingChanges();
}

void Scene::ApplyPendingChanges()
{
	for (GameObject* go : objectsToAdd)
	{
		if (std::find(gameObjects.begin(), gameObjects.end(), go) == gameObjects.end())
		{
			gameObjects.push_back(go);
		}
	}
	objectsToAdd.clear();

	for (GameObject* go : objectsToRemove)
	{
		gameObjects.remove(go);
		if (go != nullptr)
		{
			go->Release();
			delete go;
		}
	}
	objectsToRemove.clear();
}

GameObject* Scene::AddGameObject(GameObject* go)
{
	objectsToAdd.push_back(go);
	return go;
}

void Scene::RemoveGameObject(GameObject* go)
{
	go->SetActive(false);
	objectsToRemove.push_back(go);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	
	return nullptr;
}

std::vector<GameObject*> Scene::FindGameObjects(const std::string& name)
{
	std::vector<GameObject*> results;
	
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	return results;
}

void Scene::FindGameObjects(const std::string& name, std::vector<GameObject*>& results)
{
	for (auto obj : gameObjects)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
	
	for (auto obj : objectsToAdd)
	{
		if (obj->GetName() == name)
		{
			results.push_back(obj);
		}
	}
}

sf::Vector2f Scene::ScreenToWorld(sf::Vector2i s)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(s, worldView);
	//ÇÈ¼¿ = ½ºÅ©¸° ÁÂÇ¥°è
}

sf::Vector2i Scene::WorldToScreen(sf::Vector2f s)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(s, worldView);
}

sf::Vector2f Scene::ScreenToUi(sf::Vector2i s)
{
	return FRAMEWORK.GetWindow().mapPixelToCoords(s, uiView);
}

sf::Vector2i Scene::UiToScreen(sf::Vector2f s)
{
	return FRAMEWORK.GetWindow().mapCoordsToPixel(s, uiView);
}
