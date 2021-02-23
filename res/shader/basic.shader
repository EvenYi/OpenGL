#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 pointColor;
layout(location = 3) in float texID;

out vec2 v_TexCoord;
out vec4 p_Color;
out float t_texID;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	p_Color = pointColor;
	t_texID = texID;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;
in vec4 p_Color;
in float t_texID;

uniform vec4 u_Color;
uniform sampler2D u_Texture[2];


void main()
{
	int texIndex = int(t_texID);
	vec4 textColor = texture(u_Texture[texIndex], v_TexCoord);
	color = textColor;
};