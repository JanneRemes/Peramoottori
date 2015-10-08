#include "TextureFactory.h"
#include <resources\ResourceManager.h>
#include <resources\ImageResource.h>

#include <core\Log.h>
#include <core\Memory.h>
#include <GLES2\gl2.h>

#include <lodepng.h>
#include <graphics\Text.h>

pm::TextureStruct TS;
std::map<std::string, pm::TextureStruct> pm::TextureFactory::generatedTextures = { { "MapInit", TS } };

pm::Texture* pm::TextureFactory::CreateTexture(std::string fileName)
{
	pm::Texture* tempTexture = NEW pm::Texture;

	for (std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		if (it->first == fileName)
		{
			tempTexture->SetId(it->second.id);
			tempTexture->SetTextureSize(glm::uvec2(it->second.sx, it->second.sy));
			return tempTexture;
		}
	}


	CreateOGLTexture(fileName, tempTexture);

	pm::TextureStruct tempTS;
	tempTS.id = tempTexture->GetId();
	tempTS.sx = tempTexture->GetTextureSize().x;
	tempTS.sy = tempTexture->GetTextureSize().y;

	generatedTextures[fileName] = tempTS;

	return tempTexture;
}

void pm::TextureFactory::CreateOGLTexture(std::string fileName, Texture* pointer)
{
	if (fileName.empty() || pointer == nullptr)
	{
		DEBUG_WARNING(("TextureFactory failed to create texture (%s).", fileName.c_str()));
		return;
	}

	DEBUG_GL_ERROR_CLEAR();
	pm::ImageResource* decodedImage = (pm::ImageResource*)pm::ResourceManager::GetInstance()->LoadAsset(fileName);

	std::vector<unsigned char> img;
	unsigned int sx = 0;
	unsigned int sy = 0;

	unsigned error = lodepng::decode(img, sx, sy, decodedImage->GetImageData().data(), decodedImage->GetImageData().size());

	if (error) // display error to debugger
	{
		DEBUG_WARNING(("Texture Creation failed lodepng error #%u", error));
		return;
	}
	else
	{
		GLuint textureIndex;
		glGenTextures(1, &textureIndex);
		DEBUG_GL_ERROR();

		glBindTexture(GL_TEXTURE_2D, textureIndex);
		DEBUG_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		DEBUG_GL_ERROR();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		DEBUG_GL_ERROR();

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
			sx, sy,
			0, GL_RGBA, GL_UNSIGNED_BYTE,
			img.data());
		DEBUG_GL_ERROR();

		glBindTexture(GL_TEXTURE_2D, 0);
		DEBUG_GL_ERROR();

		pointer->SetTextureSize(glm::uvec2(sx, sy));
		pointer->SetId(textureIndex);
	}
}

void pm::TextureFactory::RecreateOGLTextures()
{
	pm::Texture* tempTexture = nullptr;
	if (!generatedTextures.empty())
	{
		for (std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
			CreateOGLTexture(it->first, tempTexture);
	}
}

						
void pm::TextureFactory::DestroyOGLTextures()
{

	DEBUG_GL_ERROR_CLEAR();
	/*
	for (std::map<std::string, Texture*>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		glDeleteTextures(1, &it->second->GetId());
		DEBUG_GL_ERROR();
	}*/

	/*
	for (GLuint i = 0; i < generatedTextures.size(); i++) // Bubblegum fix temporary!
	{
		glDeleteTextures(1, &i);
		DEBUG_GL_ERROR();
	}
	*/
}

pm::TextureFactory::~TextureFactory()
{
	DEBUG_GL_ERROR_CLEAR();
	for (std::map<std::string, pm::TextureStruct>::iterator it = generatedTextures.begin(); it != generatedTextures.end(); it++)
	{
		GLuint reference = it->second.id;
		glDeleteTextures(1, &reference);
		DEBUG_GL_ERROR();
		//delete it->second;
		//it->second = nullptr;
	}
	generatedTextures.clear();
}