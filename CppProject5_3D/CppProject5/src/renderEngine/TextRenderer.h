#pragma once

#include "Renderer.h"
#include "entities\graphics\Camera.h"
#include "shaders\TextShader.h"
#include "loaders\TextureLoader.h"

/*
	[UNUSED]
	Yes, absence of text is bad.
	I tried to couple glut for glutbitmapcharacter method thing with current recent opengl
	but it is old code and it can't be coupled.
	I also tried font images, but it was taking too much time and as I failed,
	I abandoned it.
	So the below does not work and is in a big part not mine, but it took time, I prefered to let it.

*/
class TextRenderer : public Renderer{
private:
	const static char* POLICY_PATH;

	ModelTexture* texture;
	TextShader* shader;
	Camera* playerCamera;

	unsigned int Text2DTextureID;
	unsigned int Text2DVertexBufferID;
	unsigned int Text2DUVBufferID;
	unsigned int Text2DShaderID;
	unsigned int Text2DUniformID;


public:
	TextRenderer(TextShader* shader, Camera* playerCamera);
	~TextRenderer();

	void render() const;
	void renderText(const char* text, float x, float y, float size) const;

	static std::string fToStr(float f);
	// NOT MINE
	static GLuint loadDDS(const char* path);

	// libGraph's drawText
	static void renderText(const char* text, float x, float y, float r, float g, float b, float a);
	static void renderText(const char* text, float x, float y, float r, float g, float b);
};

