#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; 
uniform sampler2D tex0;

in vec2 TexCoord;

void main()
{
   FragColor = texture(tex0, TexCoord);
}