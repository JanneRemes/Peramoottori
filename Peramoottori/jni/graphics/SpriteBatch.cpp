#include "SpriteBatch.h"
#include "Drawable.h"
#include "Color.h"
#include "Shape.h"
#include "scene\Texture.h"
#include "scene\Transformable.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"
#include <algorithm>
#include <core\Passert.h>
#include <core\Log.h>
#include <core\Memory.h>


using namespace pm;


SpriteBatch* SpriteBatch::instance = nullptr;

SpriteBatch::SpriteBatch()
{

}

SpriteBatch* SpriteBatch::GetInstance()
{
	if (instance == nullptr)
	{
		instance = NEW SpriteBatch();
	}
	return instance;
}

void SpriteBatch::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void SpriteBatch::Update()
{
	for (int i = 0; i < gameEntityVector.size(); i++)
	{

	}
}

void SpriteBatch::AddGameEntityToVector(GameEntity *gameEntity)
{
	gameEntityVector.push_back(gameEntity);
}

bool SpriteBatch::CheckIfDrawable(GameEntity *gameEntity)
{
	if (gameEntity->GetComponent<Drawable>() == nullptr)
		return false;
	else
		return gameEntity->GetComponent<Drawable>()->GetDrawState();
}

Sprite GatherDataFromComponents(GameEntity *gameEntity)
{

	glm::mat4 translationMatrix;
	std::vector<GLfloat> vertexPos;
	GLfloat depth;
	std::vector<GLfloat> vertexTexPos;
	glm::vec4 vertexColor;
	std::vector<GLuint> indices;

	GLuint textureID;

	if (gameEntity->GetComponent<Shape>() == nullptr)
	{
		//NO SHAPE
		vertexPos = NULL;
		indices = NULL;
	}
	else
	{
		vertexPos = gameEntity->GetComponent<Shape>()->GetVertices();
		indices = gameEntity->GetComponent<Shape>()->GetIndices();
	}

	if (gameEntity->GetComponent<Transformable>() == nullptr)
	{
		translationMatrix = glm::mat4();
		depth = NULL;
	}
	else
	{
		Transformable* transform = gameEntity->GetComponent<Transformable>();
		// !
		translationMatrix = glm::translate(glm::vec3(transform->GetPosition(), 0.0f));
		translationMatrix *= glm::rotate(transform->GetRotation(), glm::vec3(0, 0, 1));
		translationMatrix *= glm::scale(glm::vec3(transform->GetScale(), 0.0f));
		depth = transform->GetDepth();
	}

	if (gameEntity->GetComponent<Texture>() == nullptr)
	{
		vertexTexPos = NULL;
		textureID = NULL;
	}
	else
	{
		vertexTexPos = gameEntity->GetComponent<Texture>()->GetTextureVertices();
		textureID = gameEntity->GetComponent<Texture>()->GetId();
	}

	if (gameEntity->GetComponent<Color>() == nullptr)
	{
		//NO COLOR
		vertexColor = glm::vec4(255, 50, 150, 1);
	}
	else
	{
		vertexColor = gameEntity->GetComponent<Color>()->GetColor();
	}

	// TEXTURECOMPONENT WIP
	
	std::vector<GLfloat> vertexData;
	vertexData = CreateVertexData(vertexPos, depth, vertexTexPos, vertexColor);

	Sprite sprite(vertexData, indices, translationMatrix, textureID);
	return sprite;
}

void SpriteBatch::AddSpriteToBatch(Sprite sprite)
{
	for (unsigned i = 0; i < batchVector.size(); i++)
	{
			// If there is a texture with same index as new one, add data to batch.
		if (batchVector[i].textureIndex == sprite.GetTextureIndex());
		{
			batchVector[i].AddData(sprite.GetVertexData(), sprite.GetIndexData(), sprite.GetTransformMatrix());
			return;
		}
	}
			// If no batches with same texture were found, create new batch and add data to it.
	Batch newBatch(sprite.GetVertexData(), sprite.GetIndexData(), sprite.GetTransformMatrix(), sprite.GetTextureIndex());
	batchVector.push_back(newBatch);
}

std::vector<GLfloat> SpriteBatch::CreateVertexData(std::vector<GLfloat> vertexPos
	GLfloat depth, glm::vec4 vertexTexPos, glm::vec4 vertexColor)
{
	std::vector<GLfloat> vertexData;
	for (int i = 0; i < 4; i++)
	{
		vertexData.push_back(vertexPos[i * 2]);
		vertexData.push_back(vertexPos[i * 2 + 1]);
		vertexData.push_back(depth);

		vertexData.push_back(vertexColor.x);
		vertexData.push_back(vertexColor.y);
		vertexData.push_back(vertexColor.z);

		vertexData.push_back(vertexTexPos[]);
		vertexData.push_back(vertexTexPos[])
	}
}