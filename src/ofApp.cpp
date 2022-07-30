#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
    
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
        
    ofBackground(180, 180, 180);

//Set a gradient background from white to gray
ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
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
    loadMesh("terminal.png",1000);
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
    sphere.rotateDeg(angle, 0, 1, 0);
    
     vector<glm::vec<3, float, glm::packed_highp>>& vertices = sphere.getMesh().getVertices();
     extrude_factor = 1.; 
     ofPixels pixels;
     texture.readToPixels(pixels);
     for (int i=0; i<vertices.size(); i++) {
         ofVec2f t = sphere.getMesh().getTexCoords()[i];
         t.x = ofClamp( t.x, 0, pixels.getWidth()-1 );
         t.y = ofClamp( t.y, 0, pixels.getHeight()-1 );
         float br = pixels.getColor(t.x, t.y).getBrightness();
         vertices[i] *= 1 + br / 255.0  * extrude_factor;
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
    } 
    ofLog(OF_LOG_NOTICE, ofToString(key));
}

