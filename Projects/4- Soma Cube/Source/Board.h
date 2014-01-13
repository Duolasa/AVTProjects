#ifndef BOARD_H
#define BOARD_H

#include "Entity.h"

namespace engine {

	class Board {
	private:
		int _dimensions;					// dimensions of board
		int _extra;							// board center is at 0,0,0
		unsigned int board[17][17][17];
		unsigned int boardSolution[17][17][17];
	public:
		bool solutionExists;

		Board(){
			for(int i = 0; i < 17 ; i++)
				for(int j = 0; j < 17 ; j++)
					for(int k = 0; k < 17 ; k++)
						board[i][j][k] = 0;
			_extra = (17-1)/2;
			solutionExists = false;
		}
		Board(int dm){ 
			for(int i = 0; i < 17 ; i++)
				for(int j = 0; j < 17 ; j++)
					for(int k = 0; k < 17 ; k++)
						board[i][j][k] = 0;
			_dimensions = dm;
			_extra = (dm-1)/2;
			solutionExists = false;
		}
		~Board(){}

		bool checkWinningCondition(){
			//bool check = true;
			for(int i = 0; i < 17 ; i++){
				for(int j = 0; j < 17 ; j++){
					for(int k = 0; k < 17 ; k++){ //TODO....
						if(boardSolution[i][j][k] == 0 && board[i][j][k]==0){
							//check &= true;
						}else if(boardSolution[i][j][k] == 1 && board[i][j][k] != 0){
							//check &= true;
						}else{
							//check &= false;
							return false;
						}
					}
				}
			}
			return true;
		}

		void setSolutionBoard(PiecePosition piecePositions, int size){
			for(int i = 0; i<size ;i++){
				Vec3 boardPos = piecePositions.pos[i] - Vec3((float)-_extra,(float)-_extra,(float)-_extra);
				boardSolution[(int)boardPos.x][(int)boardPos.y][(int)boardPos.z] = 1;
			}
			solutionExists = true;
		}

		bool inBoardBoundaries(Vec3 boardPosition){
			//std::cerr << boardPosition << std::endl;
			return boardPosition.x >= 0 && boardPosition.y >= 0 && boardPosition.z >= 0 &&
				boardPosition.x <= (_dimensions-1) && boardPosition.y <= (_dimensions-1) && boardPosition.z <= (_dimensions-1);
		}

		bool canSetPiece(PiecePosition piecePositions, int size, int id){
			//std::cerr << piecePositions[0] - Vec3(-_extra,0,-_extra) << " "
				//<< piecePositions[1] - Vec3(-_extra,0,-_extra) << " "
				//<< piecePositions[2] - Vec3(-_extra,0,-_extra) << " " << std::endl;
			bool canSet = true;
			for(int i = 0; i<size ;i++){
				Vec3 boardPos = piecePositions.pos[i] - Vec3((float)-_extra,(float)-_extra,(float)-_extra);
				canSet &= inBoardBoundaries(boardPos);
				if(!canSet) return false;
				if(board[(int)boardPos.x][(int)boardPos.y][(int)boardPos.z] == 0 
					|| board[(int)boardPos.x][(int)boardPos.y][(int)boardPos.z] == (unsigned int)id){
					canSet &= true;
				}else{
					canSet = false;
				}
			}

			return canSet;
		}

		void setPiece(PiecePosition piecePositions,int size, int id){
			for(int i = 0; i<size ;i++){
				Vec3 boardPos = piecePositions.pos[i] - Vec3((float)-_extra,(float)-_extra,(float)-_extra);
				board[(int)boardPos.x][(int)boardPos.y][(int)boardPos.z] = id;
			}
		}

		void erasePiece(PiecePosition piecePositions,int size){
			for(int i = 0; i<size ;i++){
				Vec3 boardPos = piecePositions.pos[i] - Vec3((float)-_extra,(float)-_extra,(float)-_extra);
				board[(int)boardPos.x][(int)boardPos.y][(int)boardPos.z] = 0;
			}
		}

		bool canMove(PiecePosition newPiecePositions, int size, int id){
			return canSetPiece(newPiecePositions, size, id);

		}

	};
}

#endif //BOARD_H