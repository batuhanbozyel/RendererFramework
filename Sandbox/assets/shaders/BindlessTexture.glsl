#type vertex
#version 460 core

layout(location = 0) in vec4  a_Position;
layout(location = 1) in vec4  a_Color;
layout(location = 2) in vec2  a_TexCoord;
layout(location = 3) in uvec2 a_TexHandle;

out vec4 v_Color;
out vec2 v_TexCoord;
flat out uvec2 v_TexHandle;

uniform mat4 u_ViewProjection;

void main()
{
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexHandle = a_TexHandle;
	gl_Position = u_ViewProjection * a_Position;
}

#type fragment
#version 460 core
#extension GL_ARB_bindless_texture : require

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TexCoord;
flat in uvec2 v_TexHandle;

void main()
{
	color = v_Color * texture(sampler2D(v_TexHandle), v_TexCoord);
}