#ifndef READWRITEPIECES_H
#define READWRITEPIECES_H

#include <string>

#include "Vector.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace engine {
	
	class ReadWritePiece{

	public:
		PiecePosition bigLPiecePos;
		PiecePosition smallLPiecePos;
		PiecePosition tPiecePos;
		PiecePosition snakePiecePos;
		PiecePosition strangePiece1Pos;
		PiecePosition strangePiece2Pos;
		PiecePosition cornerPiecePos;

		std::string Convert (float number){
			std::ostringstream buff;
			buff << number;
			return buff.str();
		}

		ReadWritePiece(){}
		~ReadWritePiece(){}

		XMLNode* insertPosition(XMLDocument* doc, XMLNode* node, std::string nodeName, Vec3 values){
			XMLNode* result = node->InsertEndChild( doc->NewElement( nodeName.c_str() ) );
			XMLNode* x = result->InsertEndChild( doc->NewElement( "x" ) );
			x->InsertFirstChild( doc->NewText( Convert(values.x).c_str()));
			XMLNode* y = result->InsertEndChild( doc->NewElement( "y" ) );
			y->InsertFirstChild( doc->NewText( Convert(values.y).c_str()));
			XMLNode* z = result->InsertEndChild( doc->NewElement( "z" ) );
			z->InsertFirstChild( doc->NewText( Convert(values.z).c_str()));
			return result;
		}

		void WriteFile(const std::string filename){

			XMLDocument* doc = new XMLDocument();
			XMLNode* root = doc->InsertEndChild( doc->NewElement( filename.c_str() ) );
			XMLNode* position0;
			XMLNode* position1;
			XMLNode* position2;
			XMLNode* position3;
			

			XMLNode* bigLPiecePosition = root->InsertEndChild( doc->NewElement( "bigLPiecePosition" ) );
			position0 = insertPosition(doc, bigLPiecePosition, "Position0", bigLPiecePos.pos[0]);
			position1 = insertPosition(doc, bigLPiecePosition, "Position1", bigLPiecePos.pos[1]);
			position2 = insertPosition(doc, bigLPiecePosition, "Position2", bigLPiecePos.pos[2]);
			position3 = insertPosition(doc, bigLPiecePosition, "Position3", bigLPiecePos.pos[3]);

			XMLNode* smallLPiecePosition = root->InsertEndChild( doc->NewElement( "smallLPiecePosition" ) );
			position0 = insertPosition(doc, smallLPiecePosition, "Position0", smallLPiecePos.pos[0]);
			position1 = insertPosition(doc, smallLPiecePosition, "Position1", smallLPiecePos.pos[1]);
			position2 = insertPosition(doc, smallLPiecePosition, "Position2", smallLPiecePos.pos[2]);
			
			XMLNode* tPiecePosition = root->InsertEndChild( doc->NewElement( "tPiecePosition" ) );
			position0 = insertPosition(doc, tPiecePosition, "Position0", tPiecePos.pos[0]);
			position1 = insertPosition(doc, tPiecePosition, "Position1", tPiecePos.pos[1]);
			position2 = insertPosition(doc, tPiecePosition, "Position2", tPiecePos.pos[2]);
			position3 = insertPosition(doc, tPiecePosition, "Position3", tPiecePos.pos[3]);

			XMLNode* snakePiecePosition = root->InsertEndChild( doc->NewElement( "snakePiecePosition" ) );
			position0 = insertPosition(doc, snakePiecePosition, "Position0", snakePiecePos.pos[0]);
			position1 = insertPosition(doc, snakePiecePosition, "Position1", snakePiecePos.pos[1]);
			position2 = insertPosition(doc, snakePiecePosition, "Position2", snakePiecePos.pos[2]);
			position3 = insertPosition(doc, snakePiecePosition, "Position3", snakePiecePos.pos[3]);

			XMLNode* strangePiece1Position = root->InsertEndChild( doc->NewElement( "strangePiece1Position" ) );
			position0 = insertPosition(doc, strangePiece1Position, "Position0", strangePiece1Pos.pos[0]);
			position1 = insertPosition(doc, strangePiece1Position, "Position1", strangePiece1Pos.pos[1]);
			position2 = insertPosition(doc, strangePiece1Position, "Position2", strangePiece1Pos.pos[2]);
			position3 = insertPosition(doc, strangePiece1Position, "Position3", strangePiece1Pos.pos[3]);

			XMLNode* strangePiece2Position = root->InsertEndChild( doc->NewElement( "strangePiece2Position" ) );
			position0 = insertPosition(doc, strangePiece2Position, "Position0", strangePiece2Pos.pos[0]);
			position1 = insertPosition(doc, strangePiece2Position, "Position1", strangePiece2Pos.pos[1]);
			position2 = insertPosition(doc, strangePiece2Position, "Position2", strangePiece2Pos.pos[2]);
			position3 = insertPosition(doc, strangePiece2Position, "Position3", strangePiece2Pos.pos[3]);

			XMLNode* cornerPiecePosition = root->InsertEndChild( doc->NewElement( "cornerPiecePosition" ) );
			position0 = insertPosition(doc, cornerPiecePosition, "Position0", cornerPiecePos.pos[0]);
			position1 = insertPosition(doc, cornerPiecePosition, "Position1", cornerPiecePos.pos[1]);
			position2 = insertPosition(doc, cornerPiecePosition, "Position2", cornerPiecePos.pos[2]);
			position3 = insertPosition(doc, cornerPiecePosition, "Position3", cornerPiecePos.pos[3]);

			std::string str = "xml/" + filename + ".xml";
			doc->SaveFile(str.c_str());
		}

		Vec3 readPosition(XMLDocument *dxml, std::string pieceName, std::string positionName){
			float x, y, z;
			XMLElement* position = dxml->FirstChildElement()->FirstChildElement(pieceName.c_str())->FirstChildElement(positionName.c_str());
			position->FirstChildElement( "x" )->QueryFloatText( &x );
			position->FirstChildElement( "y" )->QueryFloatText( &y );
			position->FirstChildElement( "z" )->QueryFloatText( &z );

			return Vec3(x, y, z);
		}

		void ReadFile(const std::string filename){
			XMLDocument *dxml  = new XMLDocument();
			std::string str = "xml/" + filename + ".xml";
			dxml->LoadFile(str.c_str());

			bigLPiecePos.pos[0] = readPosition(dxml, "bigLPiecePosition", "Position0");
			bigLPiecePos.pos[1] = readPosition(dxml, "bigLPiecePosition", "Position1");
			bigLPiecePos.pos[2] = readPosition(dxml, "bigLPiecePosition", "Position2");
			bigLPiecePos.pos[3] = readPosition(dxml, "bigLPiecePosition", "Position3");

			smallLPiecePos.pos[0] = readPosition(dxml, "smallLPiecePosition", "Position0");
			smallLPiecePos.pos[1] = readPosition(dxml, "smallLPiecePosition", "Position1");
			smallLPiecePos.pos[2] = readPosition(dxml, "smallLPiecePosition", "Position2");

			tPiecePos.pos[0] = readPosition(dxml, "tPiecePosition", "Position0");
			tPiecePos.pos[1] = readPosition(dxml, "tPiecePosition", "Position1");
			tPiecePos.pos[2] = readPosition(dxml, "tPiecePosition", "Position2");
			tPiecePos.pos[3] = readPosition(dxml, "tPiecePosition", "Position3");

			snakePiecePos.pos[0] = readPosition(dxml, "snakePiecePosition", "Position0");
			snakePiecePos.pos[1] = readPosition(dxml, "snakePiecePosition", "Position1");
			snakePiecePos.pos[2] = readPosition(dxml, "snakePiecePosition", "Position2");
			snakePiecePos.pos[3] = readPosition(dxml, "snakePiecePosition", "Position3");

			strangePiece1Pos.pos[0] = readPosition(dxml, "strangePiece1Position", "Position0");
			strangePiece1Pos.pos[1] = readPosition(dxml, "strangePiece1Position", "Position1");
			strangePiece1Pos.pos[2] = readPosition(dxml, "strangePiece1Position", "Position2");
			strangePiece1Pos.pos[3] = readPosition(dxml, "strangePiece1Position", "Position3");

			strangePiece2Pos.pos[0] = readPosition(dxml, "strangePiece2Position", "Position0");
			strangePiece2Pos.pos[1] = readPosition(dxml, "strangePiece2Position", "Position1");
			strangePiece2Pos.pos[2] = readPosition(dxml, "strangePiece2Position", "Position2");
			strangePiece2Pos.pos[3] = readPosition(dxml, "strangePiece2Position", "Position3");

			cornerPiecePos.pos[0] = readPosition(dxml, "cornerPiecePosition", "Position0");
			cornerPiecePos.pos[1] = readPosition(dxml, "cornerPiecePosition", "Position1");
			cornerPiecePos.pos[2] = readPosition(dxml, "cornerPiecePosition", "Position2");
			cornerPiecePos.pos[3] = readPosition(dxml, "cornerPiecePosition", "Position3");

			//std::cerr << cornerPiecePos.pos[3] << std::endl;
		}
	};
}


#endif //READWRITEPIECES_H