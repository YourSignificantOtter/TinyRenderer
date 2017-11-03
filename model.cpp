#include "model.h"


Model::Model(std::string fileName)
{
	m_numFace = 0;
	m_numVert = 0;
	std::ifstream inputFile;
	inputFile.open(fileName);
	
	if(inputFile.fail())
	{
		std::cerr << "failed to open " << fileName << "!\n";
	}
	else
	{
		std::string line;
		std::string delim = " ";
		std::string faceDelim = "/";
		std::string token;
		size_t pos;
		while(!inputFile.eof())
		{
			std::getline(inputFile, line);
			if(!line.compare(0, 2, "v "))
			{
				Vec3f vec;
				line.erase(line.begin(), line.begin() + 2);
				pos = 0;
				for(int i = 0; i < 3; i++)
				{
					pos = line.find(delim);
					token = line.substr(0, pos);
					vec.raw[i] = std::stof(token);
					line.erase(0, pos + delim.length());
				}
				m_vertices.push_back(vec);
				m_numVert++;
			}
			else if(!line.compare(0, 2, "f "))
			{
				line.erase(line.begin(), line.begin() + 2);
				std::vector<int> vec;
				int index;
				
				for(int i = 0; i < 3; i++)
				{
					pos = line.find(faceDelim);
					token = line.substr(0, pos);
					vec.push_back(std::stoi(token) - 1);
					pos = line.find(delim);
					line.erase(0, pos + delim.length());
				}
				m_faces.push_back(vec);
				m_numFace++;
			}
		}
		
		inputFile.close();
	}
}

Model::~Model()
{

}

Vec3f Model::GetVert(int i)
{
	return m_vertices[i];
}

std::vector<int> Model::GetFace(int i)
{
	return m_faces[i];
}

int Model::GetNumVert()
{
	return m_numVert;
}

int Model::GetNumFace()
{
	return m_numFace;
}