#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include "Vector.h"
#include "Quaternion.h"

namespace engine{


	class Node
	{
	public:

		int id;
		std::vector<Node*> childs;
		engine::Vec3 translation;
		engine::Vec3 scale;
		engine::Quaternion rotation;

		/*
		Shader shader;
		Piece piece;

		*/
		Node(int i);
		void AddNode(Node * n);
		void RemoveNode(Node * n);
		void Draw();

	};

}

#endif //NODE_H