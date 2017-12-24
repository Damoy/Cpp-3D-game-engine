#version 330 core

in vec2 passTextureCoords;

// normals / lights
in vec3 passSurfaceNormal;

out vec4 outColor;

uniform sampler2D modelTexture;
uniform vec3 lightColor;

void main(){
    outColor = texture(modelTexture, passTextureCoords);
    //outColor = vec4(lightDiffusion, 1.0) * texture(modelTexture, passTextureCoords);
    // outColor = texture(modelTexture, passTextureCoords);
}
