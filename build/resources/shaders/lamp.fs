#version 330 core

out vec4 color;
in vec2 vTexCoords;

uniform vec3 uLampColor;
uniform sampler2D uTexture;

void main() {
    color = vec4(uLampColor, 1.0) * texture(uTexture, vTexCoords);
}