#include "ofApp.h"
#include <regex>

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0,0,0);
    wiki.setup("http://en.wikipedia.org/w/api.php", PORT, "HelveticaNeue-Medium.otf", 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    wiki.oscUpdateMessage("/result");
    wiki.TextUpdatePosition(2.0);
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    wiki.drawTextAnimation(130, 25, 0);
}

void ofApp::exit() {
    printf("exit()\n");
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == ' '){
        wiki.postWiki("coffee");
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
