#include "Game.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <core/Log.h>
#include <core/Passert.h>
#include <core/Memory.h>
#include "resources\TextureFactory.h"
using namespace pm;
using namespace std;

Game* Game::instance = nullptr;

Game* Game::GetInstance()
{
	if (instance == nullptr) // If instance has not been initialized yet.
		instance = NEW Game;
	return instance;
}

void Game::DestroyInstance()
{
	delete instance;
	instance = nullptr;
	DEBUG_INFO(("Game instance deleted."));
}

bool Game::Initialize(android_app* application)
{
	Application::Initialize(application);
	
	if (this->androidApplication != nullptr)
	{
		initialized = true;
		return true;
	}
	else
		return false;
}

bool Game::IsReady()
{
	if (androidApplication != nullptr && window.HasContext()) // If Game has been initialized and device context is ready.
		return true;
	else
		return false;
}

Vector2<int> Game::GetResolution()
{
	return window.GetResolution();
}

void Game::Clear()
{
	if (!IsReady())
		return;

	Application::ClearScreen();
}

void Game::SetClearColor(float red, float green, float blue)
{
	glClearColor(red, green, blue, 1.0f);
}

bool Game::Update()
{
	return Application::Update();
}

void Game::Draw()
{
	if (!IsReady()) // Prematurely end function if everything is not prepared.
		return;

	Application::SwapBuffers();
}

void Game::InitializeGame()
{
	gameEntity.AddComponent(new Rectangle(100, 200));
	
	gameEntity.AddComponent(new Transformable());
	gameEntity.GetComponent<Transformable>()->SetPosition(400, 200);

	gameEntity.AddComponent(new Drawable());
	gameEntity.GetComponent<Drawable>()->SetDrawState(true);

	gameEntity.AddComponent(TextureFactory::CreateTexture("test.png"));
}
void Game::UpdateGame()
{

}
