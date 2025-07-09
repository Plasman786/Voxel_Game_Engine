#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec2 TexCoord;
out vec2 v_TexCoord;

void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
   v_TexCoord = TexCoord;
}

#shader fragment
#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 TexColour = texture(u_Texture, v_TexCoord);
	FragColor = TexColour;
}