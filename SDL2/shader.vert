#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model = mat4(1.0);
uniform mat4 view;
uniform mat4 projection;

uniform bool isInstanced = false;
uniform mat4 models[100];

out vec2 TexCoord;

void main()
{
	TexCoord = aTexCoord;

	if(isInstanced){
		gl_Position = projection * view * models[gl_InstanceID] * vec4(aPos,0.0, 1.0);
	}
	else{
		gl_Position = projection * view * model * vec4(aPos,0.0, 1.0);
	}
	
}