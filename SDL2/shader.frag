#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform bool hasTexture = false;

uniform vec4 color = vec4(1.0);
uniform sampler2D texture01;


void main()
{
	if(!hasTexture){
		FragColor = color;
	}
	else{
		FragColor = texture(texture01, TexCoord);
	}
	
}