#include "testApp.h"
#include "ofxMSAOrderedPointerMap.h"


// an arbitrary class to hold some data
class PersonData {
public:
    float age;
    float height;
    
    PersonData(float age, float height) {
        this->age = age;
        this->height = height;
    }
    
    string toString() {
        return "[ age: " + ofToString(age) + ", height: " + ofToString(height) + "cm ]";
    }
};


// create an ordered named map of PersonData pointers
msa::OrderedPointerMap<string, PersonData> a;


// this will store our output
stringstream outputStream;


//--------------------------------------------------------------
void testApp::setup() {

    
    // add some data
    outputStream << "adding data..." << endl;
    a.push_back("memo", PersonData(37, 175));  // age (years), height (cm), weight (kg)
    a.push_back("jane", PersonData(27, 165));
    a.push_back("pearl", PersonData(2, 15));
    a.push_back("bruce", PersonData(3, 12));
    
    outputStream << "memo - " << a["memo"].toString() << endl;
    outputStream << "jane - " << a["jane"].toString() << endl;
    outputStream << "pearl - " << a["pearl"].toString() << endl;
    outputStream << "bruce - " << a["bruce"].toString() << endl;
    
    // i know this one doesn't exist, so checking first to avoid an exception
    if(a.exists("blufo")) outputStream << "blufo - " << a["blufo"].toString() << endl;
    else outputStream << "blufo doesn't exist!" << endl;
    
    
    // accessing via name
    outputStream << endl << endl << "accessing and modifying via names (make 1 year older)..." << endl;
    // various different ways of modifying:
    a["memo"].age = 38;
    a["jane"].age = a["jane"].age + 1;
    a["pearl"].age += 1;
    a["bruce"].age++;
    outputStream << "memo - " << a["memo"].toString() << endl;
    outputStream << "jane - " << a["jane"].toString() << endl;
    outputStream << "pearl - " << a["pearl"].toString() << endl;
    outputStream << "bruce - " << a["bruce"].toString() << endl;

    
    // accessing via index
    outputStream << endl << endl << "accessing and modifying via index (make 1 year older)..." << endl;
    for(int i=0; i<a.size(); i++) {
        a[i].age ++;
        outputStream << a.keyFor(i) << " - " << a[i].toString() << endl;
    }
    
    // getting index for name
    outputStream << endl << endl << "accessing and modifying via index (make 1 year older)..." << endl;
    outputStream << "memo - " << a.indexFor("memo") << endl;
    outputStream << "jane - " << a.indexFor("jane") << endl;
    outputStream << "pearl - " << a.indexFor("pearl") << endl;
    outputStream << "bruce - " << a.indexFor("bruce") << endl;

    // erase by index
    outputStream << endl << endl << "erase by index... erase(1)" << endl;
    a.erase(1); // erasing jane
    for(int i=0; i<a.size(); i++) {
        outputStream << a.keyFor(i) << " - " << a[i].toString() << endl;
    }
    
    // erase by key
    outputStream << endl << endl << "erase by key... erase('bruce') " << endl;
    a.erase("bruce"); // erasing bruce
    for(int i=0; i<a.size(); i++) {
        outputStream << a.keyFor(i) << " - " << a[i].toString() << endl;
    }

    
    
}

//--------------------------------------------------------------
void testApp::draw() {
    ofBackground(0);
    ofDrawBitmapString(outputStream.str(), 20, 30);
}

