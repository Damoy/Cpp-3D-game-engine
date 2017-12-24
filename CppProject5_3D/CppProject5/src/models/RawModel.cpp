#include "RawModel.h"

RawModel::RawModel(unsigned int vao, unsigned int vertices, bool iRendering)
	: vaoID(vao), verticesNumber(vertices), indexedRendering(iRendering){
}

RawModel::~RawModel(){
}

unsigned int RawModel::getVaoID() const { return vaoID; }
unsigned int RawModel::getVerticesNumber() const { return verticesNumber; }
bool RawModel::indexed() const { return indexedRendering; }