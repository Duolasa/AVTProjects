#ifndef BOARD_H
#define BOARD_H

#include "Entity.h"

namespace engine {

	class Board {
	private:
		int _dimensions;					// dimensions of board
		int _extra;							// board center is at 0,0,0
		unsigned int board[17][17][17];
		unsigned int boardAux[17][17][17];
	public:

		Board(){
			for(int i = 0; i < 17 ; i++)
				for(int j = 0; j < 17 ; j++)
					for(int k = 0; k < 17 ; k++)
						board[i][j][k] = 0;
			_extra = (17-1)/2;
		}
		Board(int dm){ 
			for(int i = 0; i < 17 ; i++)
				for(int j = 0; j < 17 ; j++)
					for(int k = 0; k < 17 ; k++)
						board[i][j][k] = 0;
			_dimensions = dm;
			_extra = (dm-1)/2;
		}
		~Board(){}

		void setBoardToAux(){
			for(int i = 0; i < 17 ; i++)
				for(int j = 0; j < 17 ; j++)
					for(int k = 0; k < 17 ; k++)
						boardAux[i][j][k] = board[i][j][k];
		}

		void setAuxToBoard(){
			for(int i = 0; i < 17 ; i++)
				for(int j = 0; j < 17 ; j++)
					for(int k = 0; k < 17 ; k++)
						board[i][j][k] = boardAux[i][j][k];
		}

		bool inBoardBoundaries(Vec3 boardPosition){
			//std::cerr << boardPosition << std::endl;
			return boardPosition.x >= 0 && boardPosition.y >= 0 && boardPosition.z >= 0 &&
				boardPosition.x <= (_dimensions-1) && boardPosition.y <= (_dimensions-1) && boardPosition.z <= (_dimensions-1);
		}

		bool canSetPiece(Vec3 * piecePositions, int size, int id){
			//std::cerr << piecePositions[0] - Vec3(-_extra,0,-_extra) << " "
				//<< piecePositions[1] - Vec3(-_extra,0,-_extra) << " "
				//<< piecePositions[2] - Vec3(-_extra,0,-_extra) << " " << std::endl;
			bool canSet = true;
			for(int i = 0; i<size ;i++){
				Vec3 boardPos = piecePositions[i] - Vec3((float)-_extra,0.0f,(float)-_extra);
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

		void setPiece(Vec3 * piecePositions,int size, int id){
			for(int i = 0; i<size ;i++){
				Vec3 boardPos = piecePositions[i] - Vec3((float)-_extra,0,(float)-_extra);
				board[(int)boardPos.x][(int)boardPos.y][(int)boardPos.z] = id;
			}
		}

		void erasePiece(Vec3 * piecePositions,int size){
			for(int i = 0; i<size ;i++){
				Vec3 boardPos = piecePositions[i] - Vec3((float)-_extra,0,(float)-_extra);
				board[(int)boardPos.x][(int)boardPos.y][(int)boardPos.z] = 0;
			}
		}

		bool canMove(Vec3 * newPiecePositions, int size, int id){
			return canSetPiece(newPiecePositions, size, id);

		}

	};
}

#endif //BOARD_H