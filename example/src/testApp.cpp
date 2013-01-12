#include "testApp.h"
#include "ofxMSAOrderedPointerMap.h"

stringstream str;

//--------------------------------------------------------------
void testApp::setup() {
    msa::OrderedPointerMap<ofVec3f> a;
    
    a.push_back("memo", ofVec3f(37, 175, 70));  // age, height, weight
    a.push_back("jane", ofVec3f(27, 165, 60));
    a.push_back("pearl", ofVec3f(2, 15, 55));
    a.push_back("bruce", ofVec3f(3, 12, 48));
    
    str << "memo: " << a["memo"] << endl;
    str << "jane: " << a["jane"] << endl;
    str << "pearl: " << a["pearl"] << endl;
    str << "bruce: " << a["bruce"] << endl;
    
    // i know this one doesn't exist, so checking first to avoid an assert
    if(a.exists("blufo")) {
        str << "blufo: " << a["blufo"] << endl;
    } else {
        str << "blufo: doesn't exist!" << endl;
    }
    
    
    str << endl << "modifying via names (1 year older)..." << endl;
    a["memo"].x = 38;
    a["jane"].x = a["jane"].x + 1;
    a["pearl"] = a["pearl"] + ofVec3f(1, 0, 0);
    a["bruce"].x++;
    str << "memo: " << a["memo"] << endl;
    str << "jane: " << a["jane"] << endl;
    str << "pearl: " << a["pearl"] << endl;
    str << "bruce: " << a["bruce"] << endl;
    
    str << endl << "iterating and modifying via index (1 year older).." << endl;
    for(int i=0; i<a.size(); i++) {
        a[i].x += 1;
        str << a.nameAt(i) << ": " << a[i] << endl;
    }
    
}

//--------------------------------------------------------------
void testApp::draw() {
    ofBackground(0);
    ofDrawBitmapString(str.str(), 10, 30);
}

