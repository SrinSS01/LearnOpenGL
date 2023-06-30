#version 330 core

out vec4 color;
in vec3 vNormal;
in vec3 vFragPos;
in vec2 vTexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material uMaterial;
uniform Light uLight;
uniform vec3 uViewPos;

void main() {
    // ambient
    vec3 ambient =  uLight.ambient * vec3(texture(uMaterial.diffuse, vTexCoords));

    // diffuse
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLight.position - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uLight.diffuse * diff * vec3(texture(uMaterial.diffuse, vTexCoords));

    // specular
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = uLight.specular * spec * (vec3(1.0) - vec3(texture(uMaterial.specular, vTexCoords)));

    color = vec4(ambient + diffuse + specular, 1.0);
}