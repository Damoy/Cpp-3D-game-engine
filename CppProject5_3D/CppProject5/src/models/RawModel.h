#pragma once
/*
	Simple raw model class.
*/
class RawModel{
private:
	unsigned int vaoID;
	unsigned int verticesNumber;
	// Don't want to create 2 classes
	// for only a boolean.
	bool indexedRendering;

public:
	RawModel(unsigned int vaoID, unsigned int verticesNb, bool indexedRendering);
	~RawModel();
	// getters
	unsigned int getVaoID() const;
	unsigned int getVerticesNumber() const;
	bool indexed() const;
};

