#version 330 core

out vec4 FragColor;

uniform bool hasTexture = false;

uniform vec4 color = vec4(1.0);

void main()
{
	if(!hasTexture){
		FragColor = color;
	}
	
}