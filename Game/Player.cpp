#include "Player.h"
#include "Input.h"
#include "Transform.h"
#include "GTime.h"

void Player::Update()
{
	GEngine::Transform* transform = gameObject()->transform();

	auto dist = _speed * GEngine::Time::deltaTime();

	if (GEngine::Input::GetKey(GEngine::KeyCode::W))
	{
		transform->position().y -= dist;
	}
	if (GEngine::Input::GetKey(GEngine::KeyCode::S))
	{
		transform->position().y += dist;
	}
	if (GEngine::Input::GetKey(GEngine::KeyCode::A))
	{
		transform->position().x -= dist;
	}
	if (GEngine::Input::GetKey(GEngine::KeyCode::D))
	{
		transform->position().x += dist;
	}
}

void Player::LateUpdate()
{
}

void Player::Render(HDC hdc)
{
	auto& v3 = gameObject()->transform()->position();
	Rectangle(hdc, v3.x, v3.y, 100 + v3.x, 100 + v3.y);
}
