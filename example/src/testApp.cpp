#include "testApp.h"
#include "ofxMSAOrderedPointerMap.h"

stringstream outputStream;

//--------------------------------------------------------------
void testApp::setup() {

    // Ordered pointer map of ofVec3f's
    msa::OrderedPointerMap<ofVec3f> a;
    
    
    // add some data
    outputStream << "adding data..." << endl;
    a.push_back("memo", ofVec3f(37, 175, 70));  // age (years), height (cm), weight (kg)
    a.push_back("jane", ofVec3f(27, 165, 55));
    a.push_back("pearl", ofVec3f(2, 15, 0.52));
    a.push_back("bruce", ofVec3f(3, 12, 0.45));
    
    outputStream << "memo's info: " << a["memo"] << endl;
    outputStream << "jane's info: " << a["jane"] << endl;
    outputStream << "pearl's info: " << a["pearl"] << endl;
    outputStream << "bruce's info: " << a["bruce"] << endl;
    
    // i know this one doesn't exist, so checking first to avoid an exception
    if(a.exists("blufo")) outputStream << "blufo's info: " << a["blufo"] << endl;
    else outputStream << "blufo doesn't exist!" << endl;
    
    
    // accessing via name
    outputStream << endl << endl << "accessing and modifying via names (make 1 year older)..." << endl;
    // various different ways of modifying:
    a["memo"].x = 38;
    a["jane"].x = a["jane"].x + 1;
    a["pearl"] = a["pearl"] + ofVec3f(1, 0, 0);
    a["bruce"].x++;
    outputStream << "memo's info: " << a["memo"] << endl;
    outputStream << "jane's info: " << a["jane"] << endl;
    outputStream << "pearl's info: " << a["pearl"] << endl;
    outputStream << "bruce's info: " << a["bruce"] << endl;

    
    // accessing via index
    outputStream << endl << endl << "accessing and modifying via index (make 1 year older).." << endl;
    for(int i=0; i<a.size(); i++) {
        a[i].x += 1;
        outputStream << a.nameAt(i) << "'s info: " << a[i] << endl;
    }
    
}

//--------------------------------------------------------------
void testApp::draw() {
    ofBackground(0);
    ofDrawBitmapString(outputStream.str(), 20, 30);
}

