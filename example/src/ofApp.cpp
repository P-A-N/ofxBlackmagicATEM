#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	atem.setup("10.0.0.91");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{

	case '1':
		atem.changePgOut(ofxBlackmagicATEM::NO1);
		break;

	case '2':
		atem.changePgOut(ofxBlackmagicATEM::NO2);
		break;


	case '3':
		atem.changePgOut(ofxBlackmagicATEM::NO3);
		break;


	case '4':
		atem.changePgOut(ofxBlackmagicATEM::NO4);
		break;


	case '5':
		atem.changePgOut(ofxBlackmagicATEM::NO5);
		break;


	case '6':
		atem.changePgOut(ofxBlackmagicATEM::NO6);
		break;


	case '7':
		atem.changePgOut(ofxBlackmagicATEM::NO7);
		break;


	case '8':
		atem.changePgOut(ofxBlackmagicATEM::NO8);
		break;
	default:
		break;
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
