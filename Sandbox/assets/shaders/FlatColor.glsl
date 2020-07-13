#type vertex
#version 330 core
layout(location = 0) in vec3 a_Pos;

out vec3 v_Position;

uniform mat4 u_ViewProjection;

void main()
{
	v_Position = a_Pos;
	gl_Position = u_ViewProjection * vec4(a_Pos, 1.0);
}
#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec3 v_Position;

void main()
{
	color = vec4(v_Position * 0.5 + 0.5, 1.0);
}