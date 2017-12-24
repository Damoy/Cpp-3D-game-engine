#pragma once

/*
	A model texture.
	Used as a container after openGL texture loading.
*/
class ModelTexture {
private:
	unsigned int textureID;
	unsigned int width;
	unsigned int height;

public:
	ModelTexture(unsigned int textureID, unsigned int width, unsigned int height);
	ModelTexture(unsigned int textureID);
	~ModelTexture();

	unsigned int getID() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
};

