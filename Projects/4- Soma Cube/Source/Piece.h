#ifndef PIECE_H
#define PIECE_H

#include "Entity.h"

namespace engine{
	///////////////////////////////

	class Cube{
	public:
		Vertex Vertices[36];
		
		int size(){
			return 36;
		}

		Cube(float side, Vec3 frontColor, Vec3 rightColor, Vec3 topColor, Vec3 backColor, Vec3 leftColor, Vec3 bottomColor){
			Vertex Verts[] =
			{
				{{-side/2,-side/2, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 0 - TOP
				{{ side/2,-side/2, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 1
				{{ side/2, side/2, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 2
				{{ side/2, side/2, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 2	
				{{-side/2, side/2, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 3
				{{-side/2,-side/2, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 0

				{{-side/2,-side/2,-side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 4 - FRONT
				{{ side/2,-side/2,-side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 5
				{{ side/2,-side/2, side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 1
				{{ side/2,-side/2, side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 1
				{{-side/2,-side/2, side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 0
				{{-side/2,-side/2,-side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 4

				{{ side/2,-side/2,-side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 5 - RIGHT
				{{ side/2, side/2,-side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 6
				{{ side/2, side/2, side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 2
				{{ side/2, side/2, side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 2
				{{ side/2,-side/2, side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 1
				{{ side/2,-side/2,-side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 5

				{{ side/2, side/2,-side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 6 - BACK
				{{-side/2, side/2,-side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 7
				{{-side/2, side/2, side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 3
				{{-side/2, side/2, side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 3
				{{ side/2, side/2, side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 2
				{{ side/2, side/2,-side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 6

				{{-side/2, side/2,-side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 7 - LEFT
				{{-side/2,-side/2,-side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 4
				{{-side/2,-side/2, side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 0
				{{-side/2,-side/2, side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 0
				{{-side/2, side/2, side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 3
				{{-side/2, side/2,-side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 7

				{{-side/2, side/2,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 7 - BOTTOM
				{{ side/2, side/2,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 6
				{{ side/2,-side/2,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 5
				{{ side/2,-side/2,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 5
				{{-side/2,-side/2,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 4
				{{-side/2, side/2,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}  // 7
				
				
			};

			memcpy(Vertices, Verts, sizeof(Verts)+1);
		}
	};

	class BoardPiece{
	public:
		Vertex Vertices[36];

		BoardPiece(float side, Vec3 frontColor, Vec3 rightColor, Vec3 topColor, Vec3 backColor, Vec3 leftColor, Vec3 bottomColor){
			Vertex Verts[] =
			{
				{{-side/2,-.05f, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 0 - TOP
				{{ side/2,-.05f, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 1
				{{ side/2, .05f, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 2
				{{ side/2, .05f, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 2	
				{{-side/2, .05f, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 3
				{{-side/2,-.05f, side/2, 1.0f }, { topColor.x, topColor.y, topColor.z, 1.0f }}, // 0

				{{-side/2,-.05f,-side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 4 - FRONT
				{{ side/2,-.05f,-side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 5
				{{ side/2,-.05f, side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 1
				{{ side/2,-.05f, side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 1
				{{-side/2,-.05f, side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 0
				{{-side/2,-.05f,-side/2, 1.0f }, { frontColor.x, frontColor.y, frontColor.z, 1.0f }}, // 4

				{{ side/2,-.05f,-side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 5 - RIGHT
				{{ side/2, .05f,-side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 6
				{{ side/2, .05f, side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 2
				{{ side/2, .05f, side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 2
				{{ side/2,-.05f, side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 1
				{{ side/2,-.05f,-side/2, 1.0f }, { rightColor.x, rightColor.y, rightColor.z, 1.0f }}, // 5

				{{ side/2, .05f,-side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 6 - BACK
				{{-side/2, .05f,-side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 7
				{{-side/2, .05f, side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 3
				{{-side/2, .05f, side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 3
				{{ side/2, .05f, side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 2
				{{ side/2, .05f,-side/2, 1.0f }, { backColor.x, backColor.y, backColor.z, 1.0f }}, // 6

				{{-side/2, .05f,-side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 7 - LEFT
				{{-side/2,-.05f,-side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 4
				{{-side/2,-.05f, side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 0
				{{-side/2,-.05f, side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 0
				{{-side/2, .05f, side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 3
				{{-side/2, .05f,-side/2, 1.0f }, { leftColor.x, leftColor.y, leftColor.z, 1.0f }}, // 7

				{{-side/2, .05f,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 7
				{{ side/2, .05f,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 6
				{{ side/2,-.05f,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 5 - BOTTOM
				{{ side/2,-.05f,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 5
				{{-side/2,-.05f,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}, // 4
				{{-side/2, .05f,-side/2, 1.0f }, { bottomColor.x, bottomColor.y, bottomColor.z, 1.0f }}  // 7
				
				
			};

			memcpy(Vertices, Verts, sizeof(Verts)+1);
		}
	};

	}

#endif