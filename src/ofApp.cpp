#include "ofApp.h"

std::string catedral[3] = {"catedral.png","catedral2.png","catedral_frente.png"};
std::string tiendas[3] = {"tienda_peatonal_chucherias.png", "tienda_peatonal_frente_pilchas.png","tienda_peatonal_celulares.png"};
std::string terminal[1] = {"terminal.png"};
std::string diver[2] = {"zona_zoo_cba.png","zoo_cba_peces.png"};
std::string noche[1] = {"faro.png"};
std::string otrasIglesias[1] = {"auxiliadora.png"};

//--------------------------------------------------------------
void ofApp::setup(){
    count = 0;
	//just set up the openFrameworks stuff
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    exaggerate_depth = false;
    //sphere.setRadius(200);
    //sphere.setResolution(100);

    //ofLoadImage(texture,"terminal.png");
    //cam.enableMouseInput();
    //
    //float w = texture.getWidth();
    //float h = texture.getHeight();
    //sphere.mapTexCoords(0, h, w, 0);
    //sphere.rotate(180, 0, 1, 0);
    //
    // vector<glm::vec<3, float, glm::packed_highp>>& vertices = sphere.getMesh().getVertices();
    // extrude_factor = 1.; 
    // ofPixels pixels;
    // texture.readToPixels(pixels);
    // for (int i=0; i<vertices.size(); i++) {
    //     ofVec2f t = sphere.getMesh().getTexCoords()[i];
    //     t.x = ofClamp( t.x, 0, pixels.getWidth()-1 );
    //     t.y = ofClamp( t.y, 0, pixels.getHeight()-1 );
    //     float br = pixels.getColor(t.x, t.y).getBrightness();
    //     vertices[i] *= 1 + br / 255.0  * extrude_factor;
    // }
    

    //loadMesh("terminal.png",1000 );
    loadMesh("terminal.png",1000);
    current_image_file = "terminal.png";
    
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
 angle = time;
//Compute angle. We rotate at speed
//20 degrees per second
//ofRotate( 30, 1, 0, 0 );
//Rotate coordinate system
//ofRotate( angle, 0, 0, 1 );
//Draw mesh
//Here ofSetColor() does not affects the result of drawing,
//because the mesh has its own vertices' colors


    cam.begin();
    texture.bind();
    //light.setPosition(ofGetWidth() / 2, ofGetHeight()/2, 600);
    //light.enable();
    //material.begin();
    ofEnableDepthTest();
    ofSetColor(ofColor::white);
    sphere.draw();
    sphere.drawWireframe();
 
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
void ofApp::loadMesh(std::string path, int radius){
    sphere.setRadius(radius);
    sphere.setResolution(100);
    ofLoadImage(texture,path);
    cam.enableMouseInput();
    
    float w = texture.getWidth();
    float h = texture.getHeight();
    sphere.mapTexCoords(0, h, w, 0);
    //sphere.rotateDeg(angle, 0, 1, 0);
    
     vector<glm::vec<3, float, glm::packed_highp>>& vertices = sphere.getMesh().getVertices();
     extrude_factor = 1.; 
     ofPixels pixels;
     texture.readToPixels(pixels);
     for (int i=0; i<vertices.size(); i++) {
         ofVec2f t = sphere.getMesh().getTexCoords()[i];
         t.x = ofClamp( t.x, 0, pixels.getWidth()-1 );
         t.y = ofClamp( t.y, 0, pixels.getHeight()-1 );
         float br = pixels.getColor(t.x, t.y).getBrightness();
         if (exaggerate_depth) {
             if (br <.5){
                vertices[i] *= -2.;
             } else {
                 vertices[i] *= 1 + br / 255.0  * extrude_factor;
             }
         } else {

         vertices[i] *= 1 + br / 255.0  * extrude_factor;
         }
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
        loadMesh("tienda_peatonal_chucherias.png",1000);
    } else if (key == OF_KEY_LEFT){
        loadMesh("terminal.png",1000);
    } else if (key == 99) { //c

        current_image_file = catedral[count];
        loadMesh(current_image_file,1000);
        count = count+1 % (sizeof(catedral)/sizeof(catedral[0]));

    } else if (key == 49) { //1
        exaggerate_depth = !exaggerate_depth;
        loadMesh(current_image_file,1000);
    }
    ofLog(OF_LOG_NOTICE, ofToString(key));
}

