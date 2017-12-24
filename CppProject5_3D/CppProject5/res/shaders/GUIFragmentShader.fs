#version 330 core

in vec2 passTextureCoords;

out vec4 outColor;

uniform sampler2D guiModelTexture;

void main(){
    outColor = texture(guiModelTexture, passTextureCoords);
}
