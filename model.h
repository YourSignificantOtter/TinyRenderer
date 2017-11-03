#ifndef __model_h_
#define __model_h_

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "geometry.h"


class Model
{
	public:
		Model(std::string fileName);
		~Model();
		int GetNumVert();
		int GetNumFace();
		
		Vec3f GetVert(int i);
		std::vector<int> GetFace(int i);
		
	private:
		std::vector<Vec3f> m_vertices;
		std::vector<std::vector<int>> m_faces;
		int m_numVert;
		int m_numFace;
};


#endif