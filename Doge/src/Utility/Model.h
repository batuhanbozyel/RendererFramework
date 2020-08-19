#pragma once
#include "Mesh.h"

#include <assimp/scene.h>

enum class TextureType;

class Model
{
public:
	Model(const std::string& filePath);

private:
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	void AddTexturePath(std::vector<std::pair<std::string, TextureType>>& texturePaths, aiMaterial* material, aiTextureType type, TextureType textureType);
private:
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;
};