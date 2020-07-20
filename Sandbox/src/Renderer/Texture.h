#pragma once

class Texture
{
public:
	virtual ~Texture() = default;
	
	virtual void Bind(uint32_t slot) = 0;
	virtual void Unbind() = 0;
};

class Texture2D : public Texture
{
public:
	Texture2D(const char* filePath);
	~Texture2D();

	virtual void Bind(uint32_t slot) override;
	virtual void Unbind() override;
private:
	uint32_t m_ID;
};