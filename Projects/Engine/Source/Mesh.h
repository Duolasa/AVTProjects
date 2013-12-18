#ifndef MESH_H
#define MESH_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "Entity.h"

namespace engine {

	class Mesh {
	private:

		std::vector<Vertex> vertexs;	// list of vertexs
		Entity meshEntity;				// Entity of mesh
		
		std::vector<std::string> explode(std::string aStr, char aDelim){
		  std::vector<std::string> res;
		  std::string str = aStr.substr(0, aStr.find(aDelim));

		  while(str.size() < aStr.size())
		  {
			res.push_back(str);
			aStr = aStr.substr(aStr.find(aDelim) + 1);
			str = aStr.substr(0, aStr.find(aDelim));
		  }

		  res.push_back(str);

		  return res;
		}

		void loadObjMesh(std::string filename){

			std::string line;
			std::vector<float> verts, textures, norms; 
			std::vector<int> faces;

			std::vector<float> finalVerts, finalNorms, finalTextures;
			std::vector<int> finalFaces;

			std::map<std::string, int> faceHash;
			int hashIndex = 0;

			// Open file
			std::ifstream objFile(filename.c_str());

			if(objFile.fail()){
				std::cout << "Error: could not open file <" << filename << ">" << std::endl;
			}

			// Visit each line of the obj file
			while(getline(objFile, line)){

				// Extract vertex
				// Line starts with v[space]...
				if(line[0] == 'v' && line[1] == ' '){
					std::string lineVals = line.substr(2);
					float val;

					std::string val0 = lineVals.substr(0, lineVals.find(' '));
					val = (float)atof(val0.c_str());
					verts.push_back(val);

					std::string val1 = lineVals.substr(val0.length() + 1, lineVals.find(' '));
					val = (float)atof(val1.c_str());
					verts.push_back(val);

					std::string val2 = lineVals.substr(lineVals.find_last_of(' ') + 1);
					val = (float)atof(val2.c_str());
					verts.push_back(val);
				}

				// Extract textures
				// Line starts with vt[space]...
				else if(line[0] == 'v' && line[1] == 't' && line[2] == ' '){
					std::string lineVals = line.substr(3);
					float val;

					std::string val0 = lineVals.substr(0, lineVals.find(' '));
					val = (float)atof(val0.c_str());
					textures.push_back(val);

					std::string val1 = lineVals.substr(val0.length() + 1, 
										lineVals.find(' '));
					val = (float)atof(val1.c_str());
					textures.push_back(val);
				}

				// Extract normals
				// Line starts with vn[space]...
				else if(line[0] == 'v' && line[1] == 'n' && line[2] == ' '){
					std::string lineVals = line.substr(3);
					float val;

					std::string val0 = lineVals.substr(0, lineVals.find(' '));
					val = (float)atof(val0.c_str());
					norms.push_back(val);

					std::string val1 = lineVals.substr(val0.length() + 1, 
										lineVals.find(' '));
					val = (float)atof(val1.c_str());
					norms.push_back(val);

					std::string val2 = lineVals.substr(lineVals.find_last_of(' ') + 1);
					val = (float)atof(val2.c_str());
					norms.push_back(val);
				}

				// Extract faces
				// Line starts with f[space]...
				else if(line[0] == 'f' && line[1] == ' '){
					std::string lineVals = line.substr(2);

					std::string val0 = lineVals.substr(0, lineVals.find_first_of(' '));

					// If the value for this face includes texture and/or 
					// normal, parse them out
					if(val0.find('/') >= 0){
						// Get first group of values
						std::string g1 = val0.substr(0, val0.find(' '));
        
						// Get second group of values
						std::string g2 = line.substr(line.find(' ') + 2);
						g2 = g2.substr(g2.find(' ') + 1);
						g2 = g2.substr(0, g2.find(' '));

						std::string g3 = line.substr(line.find_last_of(' ') + 1);

					
						//std::cout << "Face: (" << g1 << ") (" << g2 << ") (" << g3 << ")" << std::endl;

						// Just stick all the unique values in this hash and give each key a 
						// unique, increasing value
						std::map<std::string,int>::iterator itr;

						//
						// Add key's position to the faces list
						//

						itr = faceHash.find(g1);
						// If key not in map
						if(itr == faceHash.end()){
							faceHash[g1] = hashIndex++;
						}
						itr = faceHash.find(g1);
						faces.push_back(itr->second);

						itr = faceHash.find(g2);
						// If key not in map
						if(itr == faceHash.end()){
							faceHash[g2] = hashIndex++;
						}
						itr = faceHash.find(g2);
						faces.push_back(itr->second);

						itr = faceHash.find(g3);
						// If key not in map
						if(itr == faceHash.end()){
							faceHash[g3] = hashIndex++;
						}
						itr = faceHash.find(g3);
						faces.push_back(itr->second);
					}

						// Only verts in file
					else{
						// Push faces straight up -- converting to 
						// base zero in the process
					}
				}
			}
			/** /
			std::cout  << "Finished extracting values from file" << std::endl
            << "\tVerts = " << verts.size() << std::endl
            << "\tNorms = " << norms.size() << std::endl
            << "\tTexts = " << textures.size() << std::endl
            << "\tFaces = " << faces.size() << std::endl;
			/**/
			objFile.close();

			for(int i = 0; i < (faceHash.size() * 2); i++)
				finalTextures.push_back(0.0f);

			for(int i = 0; i < (faceHash.size() * 3); i++){
				finalVerts.push_back(0.0f);
				finalNorms.push_back(0.0f);
			}
			/** /
			std::cout << "Hashing list of unique vertices" << std::endl;

			std::cout << faceHash.size() << " unique vertices found" << std::endl;
			/**/
			
			std::map<std::string, int>::iterator hashItr = faceHash.begin();
			int faceCounter = 0;
			while(hashItr != faceHash.end()){
				std::string faceHashKey = hashItr->first;
				int faceHashVal = hashItr->second;
				/** /
				std::cout << "Unique Vert #" << faceHashVal 
							<< " = " << faceHashKey << std::endl;
				/**/
				// Default values
				float v0 = (float)0.0f;
				float v1 = (float)0.0f;
				float v2 = (float)0.0f;

				float t0 = (float)0.0f;
				float t1 = (float)0.0f;

				float n0 = (float)0.0f;
				float n1 = (float)0.0f;
				float n2 = (float)0.0f;
				/**/
				std::vector<std::string> vals = explode(faceHashKey, '/');

				v0 = (float)verts[(atoi(vals[0].c_str()) - 1) * 3];
				v1 = (float)verts[(atoi(vals[0].c_str()) - 1) * 3 + 1];
				v2 = (float)verts[(atoi(vals[0].c_str()) - 1) * 3 + 2];

				if(vals.size() > 1 && vals[1].size() > 0)
				{
					t0 = (float)textures[(atoi(vals[1].c_str()) - 1) * 2];
					t1 = (float)textures[(atoi(vals[1].c_str()) - 1) * 2 + 1];
				}

				if(vals.size() > 2 && vals[2].size() > 0)
				{
					n0 = (float)norms[(atoi(vals[2].c_str()) - 1) * 3];
					n1 = (float)norms[(atoi(vals[2].c_str()) - 1) * 3 + 1];
					n2 = (float)norms[(atoi(vals[2].c_str()) - 1) * 3 + 2];
				}


				finalVerts.at(faceHashVal * 3) = v0;
				finalVerts.at(faceHashVal * 3 + 1) = v1;
				finalVerts.at(faceHashVal * 3 + 2) = v2;

				finalTextures.at(faceHashVal * 2) = t0;
				finalTextures.at(faceHashVal * 2 + 1) = t1;

				finalNorms.at(faceHashVal * 3) = n0;
				finalNorms.at(faceHashVal * 3 + 1) = n1;
				finalNorms.at(faceHashVal * 3 + 2) = n2;

				/** /
				std::cout  << "  Vert: " << finalVerts.at(faceHashVal * 3) 
								<< " " << finalVerts.at(faceHashVal * 3 + 1) 
								<< " " << finalVerts.at(faceHashVal * 3 + 2)
								<< "  Text: " << finalTextures.at(faceHashVal * 2) 
								<< " " << finalTextures.at(faceHashVal * 2 + 1)
								<< "  Norm: " << finalNorms.at(faceHashVal * 3) 
								<< " " << finalNorms.at(faceHashVal * 3 + 1) 
								<< " " << finalNorms.at(faceHashVal * 3 + 2)
							<< std::endl;
				/**/
				hashItr++;
				
			}

			

			for(std::vector<int>::iterator it = faces.begin(); it != faces.end();it = it + 3){
				
				/** /
				std::cout << "FACE "<< *it << " " <<*(it+1) << " " << *(it+2) << std::endl;
				std::cout << "Vert #"<< *it << " " << finalVerts.at((*it) * 3) << " " <<finalVerts.at((*it) * 3 + 1) << " " << finalVerts.at((*it) * 3 + 2)<< std::endl;
				std::cout << "Vert #"<< *(it+1) << " " << finalVerts.at((*(it+1)) * 3) << " " <<finalVerts.at((*(it+1)) * 3 + 1) << " " << finalVerts.at((*(it+1)) * 3 + 2)<< std::endl;
				std::cout << "Vert #"<< *(it+2) << " " << finalVerts.at((*(it+2)) * 3) << " " <<finalVerts.at((*(it+2)) * 3 + 1) << " " << finalVerts.at((*(it+2)) * 3 + 2)<< std::endl;
				/**/
				Vertex v1 = {{finalVerts.at((*it) * 3),finalVerts.at((*it) * 3 + 1),finalVerts.at((*it) * 3 + 2),1.0f},{0.0f,0.0f,0.0f,1.0f},{finalNorms.at((*it) * 3),finalNorms.at((*it) * 3 + 1),finalNorms.at((*it) * 3 + 2),0.0f},{finalTextures.at((*it) * 2),finalTextures.at((*it) * 2 + 1)}};
				Vertex v2 = {{finalVerts.at((*(it+1)) * 3),finalVerts.at((*(it+1)) * 3 + 1),finalVerts.at((*(it+1)) * 3 + 2),1.0f},{0.0f,0.0f,0.0f,1.0f},{finalNorms.at((*(it+1)) * 3),finalNorms.at((*(it+1)) * 3 + 1),finalNorms.at((*(it+1)) * 3 + 2),0.0f},{finalTextures.at((*(it+1)) * 2),finalTextures.at((*(it+1)) * 2 + 1)}};
				Vertex v3 = {{finalVerts.at((*(it+2)) * 3),finalVerts.at((*(it+2)) * 3 + 1),finalVerts.at((*(it+2)) * 3 + 2),1.0f},{0.0f,0.0f,0.0f,1.0f},{finalNorms.at((*(it+2)) * 3),finalNorms.at((*(it+2)) * 3 + 1),finalNorms.at((*(it+2)) * 3 + 2),0.0f},{finalTextures.at((*(it+2)) * 2),finalTextures.at((*(it+2)) * 2 + 1)}};

				vertexs.push_back(v1);
				vertexs.push_back(v2);
				vertexs.push_back(v3);
			}

			//std::cout << "Vertex size "<< vertexs.size() << std::endl;
		}

	public:
		Mesh(){}

		Mesh(std::string filename){
			loadObjMesh(filename);
		}

		~Mesh(){}

		Entity getMeshEntity(const GLuint UBO){
			int n = vertexs.size();
			Vertex *vertices = new Vertex[n];
			
			int i = 0;
			for(std::vector<Vertex>::iterator it = vertexs.begin(); it != vertexs.end();it++){
				vertices[i] = *it;
				i++;
			}

			meshEntity.createBufferObject(vertices,n,UBO);

			delete [] vertices;

			return meshEntity;
		}

	};
}

#endif //MESH_H