#ifndef PHYSICS_H
#define PHYSICS_H
#include <scene\Component.h>
#include <core\Memory.h>
#include <glm\common.hpp>
class Physics :public pm::Component
{
public:

	Physics(glm::vec2 speed);
	Physics();
	~Physics();
	void SetParent(pm::GameEntity* entity);
	glm::vec2 speed;
};
#endif
