#pragma once

#include "ofMain.h"
class ofApp : public ofBaseApp{
	public:
        bool flag_tan;
        bool flag;
        int amount;

		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
        void draw3d();
        void loadMesh(std::string path, int radius);
        void loadMeshes(std::string path, int radius);

	    ofSpherePrimitive sphere;
	    ofSpherePrimitive sphere2;

	    ofMaterial material;
	    ofTexture texture;
	    ofEasyCam cam;
        float extrude_factor;
        float angle;
        ofLight light;
        int count;
        bool exaggerate_depth;
        bool exaggerate_bright;
        std::string current_image_file;
        bool multi_mode;
	bool bWireframe;
        
};
