#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position= u_Projection * u_View * u_Model * position;
	//gl_Position = transform *position;
	v_TexCoord = texCoord;
};


#shader fragment
#version 330 core

layout(location=0 ) out vec4 color;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform sampler2D u_Texture1;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord);
	
	color = mix(texture(u_Texture, v_TexCoord), texture(u_Texture1, v_TexCoord), 0.8);
	//color = texColor*u_Color;
	//color = u_Color;
};
