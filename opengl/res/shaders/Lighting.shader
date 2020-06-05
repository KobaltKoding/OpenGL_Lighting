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
	gl_Position = u_Projection * u_View * u_Model * position;
	//gl_Position = transform *position;
	v_TexCoord = texCoord;
};


#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0); // set alle 4 vector values to 1.0
}