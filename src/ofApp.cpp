#include "ofApp.h"

std::string catedral[7] = {"catedral","catedral2","catedral_frente", "campanario", "catedral_noche", "catedral_noche_luces", "catedral_frente_personas"}; //c
std::string tiendas[6] = {"tienda_peatonal_chucherias", "tienda_peatonal_frente_pilchas","tienda_peatonal_celulares", "verduleria","bombachas", "ferreteria"}; //t
std::string lugares[8] = {"terminal", "estacionamiento", "panaderia","gym","veterinaria" ,"faro", "fabrica", "pintura_auto"}; //l
std::string diver[1] = {"zona_zoo_cba"}; //d panoramicas
std::string bizarra[5] = {"maquina_rara_medica","sala_hospital", "bizarra","zoo_cba_peces", "rockero"}; //n
//std::string otrasIglesias[4] = {"auxiliadora", "iglesia"}; //i
std::string facu[4] = {"estudiantes_comunicacion", "arquitectura", "teatrino", "psico"}; //i

std::string * current_image_category = lugares;
std::string * second_current_category = lugares;

int OF_KEY_C = 99;
int OF_KEY_T = 116;
int OF_KEY_N = 110;
int OF_KEY_B = 98;
int OF_KEY_I = 105;
int OF_KEY_F = 102;
int OF_KEY_L = 108;
int OF_KEY_D = 100;
int OF_KEY_M = 109;
int OF_KEY_R = 114;
int OF_KEY_1 = 49;
int OF_KEY_2 = 50;
int OF_KEY_3 = 51;
int OF_KEY_4 = 52;
int OF_KEY_MINUS_NUMPAD = 45;
int OF_KEY_PLUS_NUMPAD = 43;
int OF_KEY_STAR_NUMPAD = 42;

//-------------------------------------------------------------
void ofApp::setup(){
    count = 0;
	//just set up the openFrameworks stuff
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    exaggerate_depth = true;
    exaggerate_bright = true;
    //loadMesh2(sphere,"terminal.png",1000);
    multi_mode = true;
    exaggerate_depth_factor =0.;
    exaggerate_bright_factor =0.;
    transp = false;
    radius_mod = 0.;
    fast_spin = false;
    ultra_fast_spin = false;
    loadMeshes(current_image_file,1000);
    
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
        
    ofBackground(180, 180, 180);

//Set a gradient background from white to gray
ofBackgroundGradient( ofColor( 0 ), ofColor( 1 ) );
ofPushMatrix();
//Store the coordinate system
//Move the coordinate center to screen's center
ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
//Calculate the rotation angle
float time = ofGetElapsedTimef();
//Get time in seconds
 angle = 0.;
//Compute angle. We rotate at speed
//20 degrees per second
//ofRotate( 30, 1, 0, 0 );
//Rotate coordinate system
//ofRotate( angle, 0, 0, 1 );
//Draw mesh
//Here ofSetColor() does not affects the result of drawing,
//because the mesh has its own vertices' colors

	//cam.setGlobalPosition({ 0,0,cam.getImagePlaneDistance(ofGetCurrentViewport()) });
    cam.begin();
        texture.bind();
        //light.setPosition(ofGetWidth() / 2, ofGetHeight()/2, 600);
        //light.enable();
        //material.begin();
        ofEnableDepthTest();
        ofPushStyle();
        ofSetColor(ofColor::white);
        sphere.draw();
        sphere2.draw();
        ofSetColor(ofColor::black);
		ofNoFill();
		ofSetColor(0, 0, 0);
        ofPopStyle();
        //sphere2.draw();
        //sphere2.drawWireframe();
        sphere.rotateDeg(angle, 0, 1, 0);
        sphere2.rotateDeg(angle, 0, 1, 0);
     
        ofDisableDepthTest();
        //material.end();
        //light.disable();
        //ofDisableLighting();
        texture.unbind();
        //draw3d();
        ofPopMatrix();
        //Restore the coordinate system
    cam.end();
}

//--------------------------------------------------------------
void ofApp::loadMeshes(std::string path, int radius){
    if (transp) {
        path = path + "_transp.png";
    } else {
        path = path + ".png";
    }

    ofLog(OF_LOG_NOTICE, ">>>>>>"+path);
    sphere.setRadius(radius);
    sphere.setResolution(100);
    sphere2.setRadius(radius/1.5);
    sphere2.setResolution(100);
    ofLoadImage(texture,path);
    cam.enableMouseInput();
    
    float w = texture.getWidth();
    float h = texture.getHeight();
    sphere.mapTexCoords(0, h, w, 0);
    sphere2.mapTexCoords(0, h, w, 0);
    
     vector<glm::vec<3, float, glm::packed_highp>>& vertices = sphere.getMesh().getVertices();
     vector<glm::vec<3, float, glm::packed_highp>>& vertices2 = sphere2.getMesh().getVertices();
     extrude_factor = 1.; 
     ofPixels pixels;
     texture.readToPixels(pixels);
     for (int i=0; i<vertices.size(); i++) {
         ofVec2f t = sphere.getMesh().getTexCoords()[i];
         t.x = ofClamp( t.x, 0, pixels.getWidth()-1 );
         t.y = ofClamp( t.y, 0, pixels.getHeight()-1 );
         float br = pixels.getColor(t.x, t.y).getBrightness();
         if (exaggerate_depth) {
            vertices[i] *= exaggerate_depth_factor;
         } else if (exaggerate_bright) {
            vertices[i] *= ofNoise(sin(ofGetFrameNum())*exaggerate_bright_factor);
        } else {
             vertices[i] *= 1 + br / 255.0  * extrude_factor;
        }
     }
     for (int i=0; i<vertices2.size(); i++) {
         ofVec2f t = sphere2.getMesh().getTexCoords()[i];
         t.x = ofClamp( t.x, 0, pixels.getWidth()-1 );
         t.y = ofClamp( t.y, 0, pixels.getHeight()-1 );
         float br = pixels.getColor(t.x, t.y).getBrightness();
         vertices2[i] *= 1. + br / 255.0  * extrude_factor;
    }
}
//--------------------------------------------------------------

void ofApp::draw3d(){

}
void ofApp::keyPressed(int key){
    if( key == OF_KEY_UP){
        extrude_factor = extrude_factor + .1;
    } else if (key == OF_KEY_DOWN){
        extrude_factor = extrude_factor - .1;
    } else if (key == OF_KEY_RIGHT){
        //loadMesh("tienda_peatonal_chucherias.png",1000);
    } else if (key == OF_KEY_LEFT){
        //loadMesh("terminal.png",1000);
    //galeria
    } else if (key == OF_KEY_C) { 
        current_image_category = catedral;
        current_image_file = catedral[count];
        loadMeshes(current_image_file,1000);
        count = (count+1) % (sizeof(catedral)/sizeof(catedral[0]));
    } else if (key == OF_KEY_T) { 

        current_image_category=tiendas;
        current_image_file = tiendas[count];
        loadMeshes(current_image_file,1000);
        count = (count+1) % (sizeof(tiendas)/sizeof(tiendas[0]));

    } else if (key == OF_KEY_B) { 
        current_image_category=bizarra;
        current_image_file = bizarra[count];
        loadMeshes(current_image_file,1000);
        count = (count+1) % (sizeof(bizarra)/sizeof(bizarra[0]));

    } else if (key == OF_KEY_L) { 
        current_image_category=lugares;
        current_image_file = lugares[count];
        loadMeshes(current_image_file,1000);
        count = (count+1) % (sizeof(lugares)/sizeof(lugares[0]));

    } else if (key == OF_KEY_D) { 
        current_image_category = diver;
        current_image_file = diver[count];
        loadMeshes(current_image_file,1000);
        count = (count+1) % (sizeof(diver)/sizeof(diver[0]));
    } else if (key == OF_KEY_F) { 
        current_image_category = facu;
        current_image_file = facu[count];
        loadMeshes(current_image_file,1000);
        count = (count+1) % (sizeof(facu)/sizeof(facu[0]));

    } else if (key == OF_KEY_M) { 
        multi_mode = true;
        loadMeshes(current_image_file, 1000);
        
    } else if (key == OF_KEY_R) { 
        ofApp::setup();
    //efectos
    } else if (key == OF_KEY_1) { //1
        exaggerate_depth = !exaggerate_depth;
        exaggerate_depth_factor -= .001;
        if (exaggerate_depth_factor >= -.003){
            exaggerate_depth_factor = 0.;
        }
        loadMeshes(current_image_file,1000);
        ofLog(OF_LOG_NOTICE, ofToString(exaggerate_depth_factor) + " " + ofToString(key));

    } else if (key == OF_KEY_2) { //1
        exaggerate_bright = !exaggerate_bright;
        exaggerate_bright_factor += .001;
        loadMeshes(current_image_file,1000);
        ofLog(OF_LOG_NOTICE, ofToString(exaggerate_bright_factor) + " " + ofToString(key));
    } else if(key==OF_KEY_3){
        float speed_modifier = .3;
        if (fast_spin) {
            speed_modifier = ofRandom(1.,10.);
        }
        if (ultra_fast_spin) {
            speed_modifier = ofRandom(50.,100.);
        }
        angle = angle+speed_modifier;
        
        if (mouseX < ofGetScreenWidth()/3){
            sphere2.rotateDeg(angle, 0, 0, 1);
        } else if (mouseX < ofGetScreenWidth()*2/3) {
            sphere2.rotateDeg(angle, 0, 1, 0);
        } else {
            sphere2.rotateDeg(angle, 1, 0, 0);
        }
    } else if(key==OF_KEY_4){ //perfect sphere?
        exaggerate_depth_factor = -.005;
        loadMeshes(current_image_file,1000);
    } else if (key == OF_KEY_MINUS_NUMPAD){
        transp= !transp;
    } else if (key == OF_KEY_PLUS_NUMPAD){
        fast_spin = !fast_spin;
    } else if (key == OF_KEY_STAR_NUMPAD){
        ultra_fast_spin = !ultra_fast_spin;
    }
    ofLog(OF_LOG_NOTICE, ofToString(count) + " " + ofToString(key));
}

