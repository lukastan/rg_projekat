#version 330 core

in vec3 outColor;
in vec2 outTexCoords;

out vec4 fragColor;
uniform sampler2D t0;

void main() {
    fragColor = texture(t0, outTexCoords) * vec4(outColor, 1.0f);
}