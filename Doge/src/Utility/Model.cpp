#include "pch.h"
#include "Model.h"

#include "Renderer/Renderer.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Model::Model(const std::string& filePath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_ERROR("ASSIMP: {0}", importer.GetErrorString());
		return;
	}
	m_Directory = filePath.substr(0, filePath.find_last_of('/') + 1);

	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint32_t i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	std::vector<TextureHandle> textures;

	for (uint32_t i = 0; i < mesh->mNumVertices; i++)
	{
		// Process Vertex Positions, Normals and Texture Coordinates
		glm::vec3 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;

		glm::vec3 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		glm::vec2 texCoord;
		if (mesh->mTextureCoords[0])
		{
			
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			texCoord = glm::vec2(0.0f);
		}
		vertices.push_back(Vertex(position, normal, texCoord));
	}
	// Process Indices
	for (uint32_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint32_t j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	// Process Material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<TextureHandle> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<TextureHandle> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<TextureHandle> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, TextureType textureType)
{
	std::vector<TextureHandle> textures;
	for (uint32_t i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		TextureHandle texture;
		texture.Handle = Renderer::CreateTexture((m_Directory + str.C_Str()).c_str());
		texture.Type = textureType;
		textures.push_back(texture);
	}
	return textures;
}