#ifndef NODEGRAPH_H
#define NODEGRAPH_H

#include <list>
#include <string>
#include "Quaternion.h"
#include "Shader.h"
#include "Entity.h"

namespace engine {

	class NodeGraph {
	private:
		std::string _name;

		Shader* _shader;
		Position _pos;
		Entity _entity;
		bool _hasEntity;
		Mat4 transforms;

		std::list<NodeGraph*> _nodes;

	public:
		NodeGraph(std::string name){ _name = name; _hasEntity = false; }
		~NodeGraph(){}

		std::string getName(){ return _name;}

		void attachNode(NodeGraph* node){
			_nodes.push_front(node);
		}

		void detachNode(std::string name){
			//TODO
		}

		void detachAll(){
			for(std::list<NodeGraph*>::iterator it = _nodes.begin(); it != _nodes.end();it++){
				(*it)->detachAll();
			}
			_nodes.clear();
		}

		void setPosition(Position pos){
			_pos = pos;
		}

		void setTranslation(float x, float y, float z){
			_pos.translation.x = x;
			_pos.translation.y = y;
			_pos.translation.z = z;
		}

		void setRotation(Quaternion q){
			_pos.rotation = q;
		}

		//void setScale(float sx, float sy, float sz);
		//void setScale(float s);

		void setShader(Shader* shader){
			_shader = shader;
		}

		void setEntity(Entity entity){
			if(_nodes.size() == 0 && !_hasEntity){
				_entity = entity;
				_hasEntity = true;
			}
		}

	};

	typedef ListManager<NodeGraph> NODEGRAPH;
	ListManager<NodeGraph>* ListManager<NodeGraph>::_instance = 0;
}

#endif //NODEGRAPH_H