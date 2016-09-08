#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //This is just a way to read in API key from text file (currently in a gitignore) - feel free to just put it directly in your code, but be careful about pushing to github
    
    ifstream ifile;
    ifile.open(ofToDataPath("apikey.txt").c_str(), ios::in );
    string apiKey;
    if (ifile.is_open()) {
        ifile >> apiKey;
        cout << "API Key: " << apiKey << endl;
    }
    
    float latitude = 0;
    float longitude = 0;
    
    locationData temp;
    
    temp.latitude = 40.7028816;
    temp.longitude= -73.99043340000003;
    temp.locName = "Brooklyn USA";
    locData.push_back(temp);
    
    temp.latitude = 37.5407246;
    temp.longitude= -77.4360481;
    temp.locName = "Richmond, VA USA";
    locData.push_back(temp);
    
    temp.latitude = -34.60368440000001;
    temp.longitude= -58.381559100000004;
    temp.locName = "Buenos Aires, Argentina";
    locData.push_back(temp);
    
    temp.latitude = 36.5322649;
    temp.longitude= -116.93254079999997;
    temp.locName = "Death Valley, CA USA";
    locData.push_back(temp);
    
    temp.latitude = 25.2716565;
    temp.longitude= 91.73080329999993;
    temp.locName = "Cherrapunji India";
    locData.push_back(temp);
    
    temp.latitude = 61.01370970000001;
    temp.longitude= -99.1966559;
    temp.locName = "Siberia Russia";
    locData.push_back(temp);
    
    
    //Get gps coords from google maps addresses here: http://www.gps-coordinates.net
    
    currentLoc = 0;
    forecast.setup(locData[currentLoc].latitude, locData[currentLoc].longitude, apiKey);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    forecast.drawDebug();
    ofDrawBitmapString("Currently Showing: " + locData[currentLoc].locName, 20, 20);
    ofDrawBitmapString("Press r to request updated data. Press space to change location",20,40);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='r'){
        forecast.requestUpdate();
    }
    
    if(key==' '){
        currentLoc++;
        currentLoc = ofWrap(currentLoc,0,locData.size());
        forecast.setNewLocation(locData[currentLoc].latitude, locData[currentLoc].longitude);
        forecast.requestUpdate();
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
