#include "Texture.h"

#include <stb_image/stb_image.h>
std::vector<unsigned int> goof::TextureManager::Texture_2D_ID;

void goof::Texture2D::Init( const char* file_name)
{

	glGenTextures(1, &ID);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//transperency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	stbi_set_flip_vertically_on_load(true);

	int height;
	int width;
	int nRChannels;

	unsigned char* data = stbi_load(file_name, &width, &height,
		&nRChannels, 0);

	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		if(nRChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	Texture_2D_ID.push_back(ID);
	manager_ID = Texture_2D_ID.size();
}

void goof::Texture2D::use(Shader& sha)
{
	sha.setBool("isTexture", true);
	glBindTexture(GL_TEXTURE_2D, ID);
}

goof::Texture2D::Texture2D() : ID(0),manager_ID(0)
{
	
	
}

goof::Texture2D::~Texture2D()
{
	ID = 0;
	if(manager_ID != 0)
	Texture_2D_ID.erase(std::next(Texture_2D_ID.begin(),manager_ID - 1));
	manager_ID = 0;
	glBindTexture(GL_TEXTURE_2D, 0);
}
