#include "Node.h"


engine::Node::Node(int i){
	id = i;
}

void engine::Node::AddNode(Node * n){
	childs.push_back(n);
}

void engine::Node::RemoveNode(Node * n){
	for (std::vector<Node*>::iterator it = childs.begin(); it != childs.end(); it++){
		if (*it == n){
				childs.erase(it);
		}
	}
}

void engine::Node::Draw(){
	std::cout << id << " - ";
	for (std::vector<Node*>::iterator it = childs.begin(); it != childs.end(); it++){
		std::cout << (*it)->id << " ";
	}
	std::cout << std::endl;
}
