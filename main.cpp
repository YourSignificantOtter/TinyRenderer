#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#include "tgaimage.h"
#include "geometry.h"
#include "model.h"

#define IMAGE_WIDTH 1920
#define IMAGE_HEIGHT 1080

int main(int argc, char *argv[])
{
	TGAImage myImage(IMAGE_WIDTH, IMAGE_HEIGHT, TGAImage::RGB);
	Model *model = nullptr;	
	if(argc >= 2)
		model = new Model(argv[1]);
	else
		model = new Model("african_head.obj");
	
	int numFaces = model->GetNumFace();
	Vec3f light_dir(0,0,-1);
	for(int i = 0; i < numFaces; i++)
	{
		std::vector<int> thisFace = model->GetFace(i);
		Vec2i screen_coords[3];
		Vec3f world_coords[3];
		for(int j = 0; j < 3; j++)
		{
			Vec3f v = model->GetVert(thisFace[j]);
			screen_coords[j] = Vec2i((v.x+1.)*IMAGE_WIDTH/2., (v.y+1.)*IMAGE_HEIGHT/2.);
			world_coords[j] = v;
		}
		Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
		n.normalize();
		float intensity = n*light_dir;
		unsigned char val = intensity * 255; //avoids warnings in TGAColor ctor
		if(intensity > 0)
			FilledTriangle(screen_coords[0], screen_coords[1], screen_coords[2], myImage, TGAColor{val, val, val, 255});
	}	
	
	myImage.flip_vertically();
	if(argc >= 2)
	{
		std::string saveFileName = argv[1];
		saveFileName = saveFileName.substr(0, saveFileName.find("."));
		saveFileName += ".tga";
		myImage.write_tga_file(saveFileName.c_str());
	}
	else
		myImage.write_tga_file("test.tga");
	
	delete model;
	
	return 1;
}