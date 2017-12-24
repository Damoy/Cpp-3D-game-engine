#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoords;

out vec2 passTexCoords;

uniform vec2 windowSize;

void main(){
	
	passTexCoords = textureCoords;

	vec2 windowSizeD2 = windowSize / 2;
	vec2 posHomogSpace = (position - windowSizeD2) / windowSizeD2;
	gl_Position = vec4(posHomogSpace, 0, 1);
}