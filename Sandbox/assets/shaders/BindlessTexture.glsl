#type vertex
#version 460 core

layout(location = 0) in vec4  a_Position;
layout(location = 1) in vec3  a_Normal;
layout(location = 2) in vec2  a_TexCoord;
layout(location = 3) in uint a_TexIndex;

out vec3 v_Normal;
out vec2 v_TexCoord;
flat out uint v_TexIndex;

out vec3 v_FragPos;

uniform mat4 u_ViewProjection;

void main()
{
	v_FragPos = vec3(a_Position);
	v_Normal = a_Normal;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = u_ViewProjection * a_Position;
}

#type fragment
#version 460 core
#extension GL_ARB_bindless_texture : require

layout(location = 0) out vec4 color;

struct TextureMap
{
	uvec2 Diffuse;
	uvec2 Specular;
};

layout(std430, binding = 0) readonly buffer TextureMaps
{
	TextureMap textures[];
} textureBuffer;

struct Material
{
	vec3 Color;
	float Shininess;
};

struct Light
{
	vec3 Position;

	vec3  Ambient;
	vec3  Diffuse;
	vec3  Specular;
};

in vec3 v_Normal;
in vec2 v_TexCoord;
flat in uint v_TexIndex;

in vec3 v_FragPos;

uniform Material u_Material;
uniform vec3 u_CameraPos;
uniform Light u_Light;

void main()
{
	// Ambient Lighting
	vec3 ambient = u_Light.Ambient * vec3(texture(sampler2D(textureBuffer.textures[v_TexIndex].Diffuse), v_TexCoord));

	// Diffuse Lighting
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.Position - v_FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.Diffuse * diff * vec3(texture(sampler2D(textureBuffer.textures[v_TexIndex].Diffuse), v_TexCoord));

	// Specular Lighting
	vec3 viewDir = normalize(u_CameraPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.Shininess);
	vec3 specular = u_Light.Specular * spec * vec3(texture(sampler2D(textureBuffer.textures[v_TexIndex].Specular), v_TexCoord));

	color = vec4(ambient + diffuse + specular, 1.0);
}