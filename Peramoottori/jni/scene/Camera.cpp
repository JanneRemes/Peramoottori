#include <scene\Camera.h>
#include <core\Application.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

pm::Camera::Camera()
{
	origin = glm::vec2(	Application::GetInstance()->window.GetResolution().x, 
						Application::GetInstance()->window.GetResolution().y);

	origin *= 0.5;

	cameraPosition	= glm::vec2(0.0f,0.0f);
	cameraRotation	= 0.0f;
	cameraZoom		= 1.0f;
	
	CalculateMatrix();
}

void pm::Camera::MoveCamera(float x, float y)
{
	cameraPosition += glm::vec2(x, y);
	CalculateMatrix();
}

void pm::Camera::MoveCamera(glm::vec2 moveXY)
{
	cameraPosition += moveXY;
	CalculateMatrix();
}

void pm::Camera::RotateCamera(float rotation)
{
	cameraRotation += rotation;
	CalculateMatrix();
}

void pm::Camera::ZoomCamera(float zoom)
{
	cameraZoom += zoom;
	CalculateMatrix();
}

void pm::Camera::SetCameraMatrix(glm::mat4 newCameraMatrix)
{
	cameraMatrix = newCameraMatrix;
	CalculateMatrix();
}

void pm::Camera::SetCameraPosition(float xPosition, float yPosition)
{
	cameraPosition = glm::vec2(xPosition, yPosition);
	CalculateMatrix();
}

void pm::Camera::SetCameraPosition(glm::vec2 newPosition)
{
	cameraPosition = newPosition;
	CalculateMatrix();
}

void pm::Camera::SetCameraRotation(float newRotation)
{
	cameraRotation = newRotation;
	CalculateMatrix();
}

void pm::Camera::SetCameraZoom(float newZoom)
{
	cameraZoom = newZoom;
	CalculateMatrix();
}

void pm::Camera::CalculateMatrix()
{
	cameraMatrix = glm::mat4(1);

	cameraMatrix = glm::translate(glm::vec3(-origin, 0.0f)) * cameraMatrix;
	cameraMatrix = glm::translate(glm::vec3(-cameraPosition, 0.0f)) * cameraMatrix;
	cameraMatrix = glm::scale(glm::vec3(cameraZoom, cameraZoom, 0.0f)) * cameraMatrix;
	cameraMatrix = glm::rotate(cameraRotation * 3.14f / 180.0f, glm::vec3(0, 0, 1)) * cameraMatrix;
	cameraMatrix = glm::translate(glm::vec3(origin, 0.0f)) * cameraMatrix;
}
glm::mat4 pm::Camera::GetCameraMatrix()
{
	return cameraMatrix;
}

glm::vec2 pm::Camera::GetCameraLocation()
{
	return cameraPosition;
}

float pm::Camera::GetCameraRotation()
{
	return cameraRotation;
}

float pm::Camera::GetCameraZoom()
{
	return cameraZoom;
}

glm::mat4 pm::Camera::GetInverseCameraMatrix()
{
	glm::mat4 inverse = glm::mat4(1);

	inverse = glm::translate(glm::vec3(-origin, 0.0f)) * inverse;
	inverse = glm::translate(glm::vec3(cameraPosition, 0.0f)) * inverse;
	inverse = glm::scale(glm::vec3(1.0 / cameraZoom, 1.0 / cameraZoom, 0.0f)) * inverse;
	inverse = glm::rotate(-cameraRotation * 3.14f / 180.0f, glm::vec3(0, 0, 1)) * inverse;
	inverse = glm::translate(glm::vec3(origin, 0.0f)) * inverse;

	return inverse;
}