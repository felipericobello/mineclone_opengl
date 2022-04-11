#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 vTextureCoords;
uniform mat4 uMVP;

void main()
{
	vTextureCoords = position;
	gl_Position = uMVP * vec4(position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 vTextureCoords;

uniform samplerCube uTexture;

void main()
{
	vec4 texColor = texture(uTexture, vTextureCoords);
	color = texColor;
}