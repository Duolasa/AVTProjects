#ifndef LIST_MANAGER_H
#define LIST_MANAGER_H

#include <map>
#include <string>

namespace engine {

	template<class T>
	class ListManager {
	private: 
		std::map<std::string, T*> _list;
		static ListManager* _instance;
		ListManager(){}
	public:
		static ListManager* instance(){
			if (_instance == 0) { _instance = new ListManager(); }
			return _instance; 
		}
		~ListManager(){}
		void cleanup(){
			if (_instance != 0) { delete _instance; }
		}
		void add(std::string name, T* t){
			_list.insert(std::pair<std::string,T*>(name,t));
		}
		void remove(std::string name){
			std::map<std::string, T*>::iterator it;
			it=_list.find(name);
			_list.erase(it);
		}
		T* get(std::string name){
			std::map<std::string, T*>::iterator it;
			it=_list.find(name);
			return it->second;
		}
	};

}

#endif // LIST_MANAGER_H