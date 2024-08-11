#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aTexCoord;

out vec4 fColor;
out vec3 fTexCoords;

uniform int windowWidth;
uniform int windowHeight;

void main()
{
	fColor = aColor;
	fTexCoords = aTexCoord;
	// OpenGL defines the viewspace between -1.0 and 1.0
	// vec2 transformedPos = (vec2(aPos.x, aPos.y) - vec2(0.5, 0.5))* 2.0 to make it between 0.0 and 1.0
	vec2 transformedPos = (vec2(aPos.x, aPos.y) - vec2(0.5, 0.5))* 2.0;
	gl_Position = vec4(transformedPos, aPos.z, 1.0); 
	// gl_Position = vec4(aPos, 1.0);
}
