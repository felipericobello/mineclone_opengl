#include "Block.h"

Block::Block(unsigned int index) 
	: _index(index)
{
}

Block::~Block()
{
}

std::vector<std::string> Block::getPath()
{
	if (_index == 0)
	{
        std::vector<std::string> texPath =
        {
            "res/textures/grass.png",
            "res/textures/grass.png",
            "res/textures/grass_top.png",
            "res/textures/bottom_grass.png",
            "res/textures/grass.png",
            "res/textures/grass.png"
        };
        return texPath;
	}
    else if (_index == 1)
    {
        std::vector<std::string> texPath =
        {
            "res/textures/cobblestone.png",
            "res/textures/cobblestone.png",
            "res/textures/cobblestone.png",
            "res/textures/cobblestone.png",
            "res/textures/cobblestone.png",
            "res/textures/cobblestone.png"
        };
        return texPath;
    }
    else if (_index == 2)
    {
        std::vector<std::string> texPath =
        {
            "res/textures/sand.png",
            "res/textures/sand.png",
            "res/textures/sand.png",
            "res/textures/sand.png",
            "res/textures/sand.png",
            "res/textures/sand.png"
        };
        return texPath;
    }
    else if (_index == 3)
    {
        std::vector<std::string> texPath =
        {
            "res/textures/wood.png",
            "res/textures/wood.png",
            "res/textures/top_wood.png",
            "res/textures/top_wood.png",
            "res/textures/wood.png",
            "res/textures/wood.png"
        };
        return texPath;
    }
    else
    {
        std::vector<std::string> texPath =
        {
            "res/textures/0.png",
            "res/textures/0.png",
            "res/textures/0.png",
            "res/textures/0.png",
            "res/textures/0.png",
            "res/textures/0.png"
        };
        return texPath;
    }
}