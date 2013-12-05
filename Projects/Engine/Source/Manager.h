#ifndef MANAGER_H
#define MANAGER_H



namespace engine {
	class Manager {

	public:
		Manager();
		~Manager();

		void createPieces();
		void destroyPieces();
		void drawPieces();
		void setCamera();
	};
}

#endif //MANAGER_H