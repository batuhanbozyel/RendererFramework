#type vertex
#version 460 core

layout(location = 0) in vec4  a_Position;
layout(location = 1) in vec3  a_Normal;
layout(location = 2) in vec4  a_Color;
layout(location = 3) in vec2  a_TexCoord;
layout(location = 4) in uvec2 a_TexHandle;

out vec3 v_Normal;
out vec4 v_Color;
out vec2 v_TexCoord;
flat out uvec2 v_TexHandle;

out vec3 v_FragPos;

uniform mat4 u_ViewProjection;

void main()
{
	v_FragPos = vec3(a_Position);
	v_Normal = a_Normal;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexHandle = a_TexHandle;
	gl_Position = u_ViewProjection * a_Position;
}

#type fragment
#version 460 core
#extension GL_ARB_bindless_texture : require

struct Material
{
	vec3  Ambient;
	vec3  Diffuse;
	vec3  Specular;
	float Shininess;
};

struct Light
{
	vec3 Position;

	vec3  Ambient;
	vec3  Diffuse;
	vec3  Specular;
};

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec4 v_Color;
in vec2 v_TexCoord;
flat in uvec2 v_TexHandle;

in vec3 v_FragPos;

uniform vec3 u_CameraPos;

uniform Material u_Material;
uniform Light u_Light;

void main()
{
	// Ambient Lighting
	vec3 ambient = u_Light.Ambient * u_Material.Ambient;

	// Diffuse Lighting
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.Position - v_FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.Diffuse * (diff * u_Material.Diffuse);

	// Specular Lighting
	vec3 viewDir = normalize(u_CameraPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
	vec3 specular = u_Light.Specular * (spec * u_Material.Specular);

	color = vec4(ambient + diffuse + specular, 1.0) * v_Color * texture(sampler2D(v_TexHandle), v_TexCoord);
}