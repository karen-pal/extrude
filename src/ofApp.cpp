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
    loadMesh("terminal.png",200 );
    
}

//--------------------------------------------------------------
void ofApp::update() {
     //vector<glm::vec<3, float, glm::packed_highp>>& vertices = sphere.getMesh().getVertices();
     //ofPixels pixels;
     //texture.readToPixels(pixels);
     //for (int i=0; i<vertices.size(); i++) {
     //    ofVec2f t = sphere.getMesh().getTexCoords()[i];
     //    t.x = ofClamp( t.x, 0, pixels.getWidth()-1 );
     //    t.y = ofClamp( t.y, 0, pixels.getHeight()-1 );
     //    float br = pixels.getColor(t.x, t.y).getBrightness();
     //    vertices[i] *= 1  + br / 255.0 ;// * extrude_factor;
     //}

}

//--------------------------------------------------------------
void ofApp::draw() {
        
    ofBackground(180, 180, 180);

    cam.begin();
    draw3d();
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
    sphere.rotate(180, 0, 1, 0);
    
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

}
void ofApp::keyPressed(int key){
    if( key == OF_KEY_UP){
        extrude_factor = extrude_factor + .1;
    } else if (key == OF_KEY_DOWN){
        extrude_factor = extrude_factor - .1;
    } else if (key == OF_KEY_RIGHT){
        loadMesh("tienda_peatonal_chucherias.png",1000);
    } 
    ofLog(OF_LOG_NOTICE, ofToString(key));
}

