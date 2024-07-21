#version 450 core
in vec4 fColor;
in vec3 fTexCoords;

out vec4 FragColor;

uniform sampler2D Textures[16];

void main()
{
	// round is used, because the float sometimes goes from 1.0f to 0.999..f for example
	// when cast to an int, it will turn from the intended 1 to a 0.
	// the round fixes this by rounding to the nearest integer.
	int Index = int(round(fTexCoords.z));
	FragColor = texture(Textures[Index], vec2(fTexCoords.x, fTexCoords.y)) * fColor;
}
