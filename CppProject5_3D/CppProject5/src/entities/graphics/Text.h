#pragma once

#include "models\TexturedModel.h"
#include "loaders\ModelLoader.h"

/*
	The Text class.
	Tried to use for rendering text but failed.
*/
class Text{
private:
	const char* text;
	unsigned short size;
	const static TexturedModel* POLICY;

public:
	Text(const char* text, unsigned short size);
	~Text();
};

