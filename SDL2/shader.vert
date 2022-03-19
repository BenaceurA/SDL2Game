#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 modelPos;

uniform mat4 model = mat4(1.0);
uniform mat4 view;
uniform mat4 projection;

uniform bool isInstanced = false;

out vec2 TexCoord;

void main()
{
	TexCoord = aTexCoord;

	if(isInstanced){
		mat4 IModel = mat4(1.0);
		IModel[3] = IModel[0] * modelPos[0] + IModel[1] * modelPos[1] + IModel[3];
		gl_Position = projection * view * IModel * vec4(aPos,0.0, 1.0);
	}
	else{
		gl_Position = projection * view * model * vec4(aPos,0.0, 1.0);
	}
	
}