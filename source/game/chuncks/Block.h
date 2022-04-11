#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


class Block
{
private:
	unsigned int _index;
	float _positions[24] =
	{
		-100.0f, -100.0f, 100.0f,  //0
		 100.0f, -100.0f, 100.0f,  //1
		 100.0f,  100.0f, 100.0f,  //2
		-100.0f,  100.0f, 100.0f,  //3

		-100.0f, -100.0f,-100.0f,  //4
		 100.0f, -100.0f,-100.0f,  //5
		 100.0f,  100.0f,-100.0f,  //6
		-100.0f,  100.0f,-100.0f	//7
	};


	unsigned int _indices[36] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
		1, 0, 4,
		1, 4, 5,
		1, 5, 6,
		2, 1, 6,
		3, 2, 6,
		3, 6, 7,
		4, 3, 7,
		5, 4, 7,
		6, 5, 7
	};

public:
	Block(unsigned int index);
	~Block();

	inline float* getPosition()			  { return &_positions[0];}
	inline unsigned int* getIndices()	  { return &_indices[0]; }
	inline unsigned int getPositionSize() { return (24 * sizeof(float)); }
	inline unsigned int getIndicesSize()  { return (36 * sizeof(int)); }
};

