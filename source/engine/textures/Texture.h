#include <Renderer.h>
#include <stb_image/stb_image.h>	

class Texture
{
private:
	unsigned int m_RendererID;
	std::vector<std::string> m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(std::vector<std::string> &filepath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

};