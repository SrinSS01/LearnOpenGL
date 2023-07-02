#version 330 core

out vec4 color;
in vec2 vTexCoords;

uniform sampler2D uTexture_diffuse;

void main() {
    color = texture(uTexture_diffuse, vTexCoords);
}