#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aTexCoord;

out vec4 OutColor;
out vec3 OutTexCoord;

void main()
{
	OutColor = aColor;
	OutTexCoord = aTexCoord;
	gl_Position = vec4(aPos, 1.0);
}
