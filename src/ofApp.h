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
        float exaggerate_depth_factor;
        bool exaggerate_bright;
        float exaggerate_bright_factor;
        std::string current_image_file = "terminal";
        bool multi_mode;
        bool transp;
        float radius_mod;
        bool fast_spin;
        bool ultra_fast_spin;
        
};
