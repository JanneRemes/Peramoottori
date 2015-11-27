#include <scene\Hitbox.h>

bool pm::Hitbox::CheckCollision(glm::vec2 touchCoordinates)
{
	glm::vec4 tempTouch = glm::vec4(touchCoordinates, 1, 1);
	std::vector<float> tempVertices = parent->GetComponent<Rectangle>()->GetVertices();
	
	float left, top, right, bot;
	left = tempVertices[0];
	top = tempVertices[1];
	right = tempVertices[6];
	bot = tempVertices[7];
	
	glm::mat4 tempCamMat = CameraSystem::GetInstance()->GetActiveCamera()->GetCameraMatrix();
	tempTouch = tempCamMat * tempTouch;

	Transformable* tempTrans = parent->GetComponent<Transformable>();
	if (tempTrans != nullptr)
	{
		glm::mat4 tempTransformMat = tempTrans->GetInverseMatrix();
		tempTouch = tempTransformMat * tempTouch;
	}

	if ((tempTouch.x > left) && (tempTouch.x < right) && (tempTouch.y > top) && (tempTouch.y < bot))
		return true;
	else
		return false;

}