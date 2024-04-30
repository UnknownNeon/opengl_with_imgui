#version 330 core
out vec4 FragColor;

uniform vec4 myColor;
uniform sampler2D myTexture;
uniform bool isTexture;

in vec3 Normal;
in vec3 fragmentPosition;
in vec2 TexCoord;

void main()
{
vec4 texColor = texture(myTexture, TexCoord) * myColor;

if(isTexture == true){
FragColor = texColor;
}
else
{
FragColor = myColor;
}
}