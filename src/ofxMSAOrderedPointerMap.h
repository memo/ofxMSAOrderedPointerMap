#pragma once

//#include <vector>
//#include <map>
//#include <string>
#include "ofMain.h"

namespace msa {
    
    template<typename T>
    class OrderedPointerMap {
    public:
        
        virtual ~OrderedPointerMap();
        
        // get size
        int size() const;
        
        // add new item
        // item will be cloned, stored internally and added to an stl::map and stl::vector as a pointer
        // pointer will be owned and deleted by this class
        // returns a reference to the new pointer added
        T& push_back(string name, const T& t);
        
        // add new item
        // this pointer will be added directly to the stl::map and stl::vector
        // pointer will be owned and deleted by this class
        // returns a reference to the (same) pointer
        T& push_back(string name, T* t);

        
        // return reference to the stored object
        // throws an exception of the index or name doesn't exist
        T& at(int index) const;         // get by index
        T& at(string name) const;       // get by name
        
        // [] operator overloads for above
        // these also throw an exception if the index or name doesn't exist
        T& operator[](int index) const;
        T& operator[](string name) const;
        T& operator[](const char* name) const;
        
        // get the name for item at index
        string nameAt(int index) const;
        
        // see if name exists
        bool exists(string name) const;
        
        // clear, and delete pointers
        void clear();
        
    private:
        map<string, T*> _map;
        vector< pair<string, T*> >	_vector;
    };
    
    
    //--------------------------------------------------------------
    template<typename T>
    OrderedPointerMap<T>::~OrderedPointerMap() {
        clear();
    }
    
    //--------------------------------------------------------------
    template<typename T>
    void OrderedPointerMap<T>::clear() {
        for(int i=0; i<_vector.size(); i++) delete _vector[i].second;
        _vector.clear();
        _map.clear();
    }
    
    //--------------------------------------------------------------
    template<typename T>
    int OrderedPointerMap<T>::size() const {
        return _map.size();
    }
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::push_back(string name, const T& t) {
        if(exists(name)) {
            ofLogError() << "msa::ControlFreak::OrderedPointerMap<T>::push_back: " << name << " - name already exists, returning existing";
            return *_map[name];
        } else {
            return push_back(name, new T(t));
        }
    }
    
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::push_back(string name, T* t) {
        if(exists(name)) {
            ofLogError() << "msa::ControlFreak::OrderedPointerMap<T>::push_back: " << name << " - name already exists, returning existing";
            return *_map[name];
        } else {
            _map[name] = t;
            _vector.push_back(pair<string, T*>(name, t));
            size();	// to check if correctly added to both containers, should be ok
            return *t;
        }
    }
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::at(int index) const {
        // make sure there is something in the array, and index is within the range
//        return _vector.size() && ofInRange(index, 0, _vector.size()-1) ? *_vector[index].second : T();
        return *_vector.at(index).second;
    }
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::at(string name) const {
        // make sure the name exists (don't add it by mistake)
//        return exists(name) ? *_map.at(name) : T();
        return *_map.at(name);
    }
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::operator[](int index) const {
        return at(index);
    }
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::operator[](string name) const {
        return at(name);
    }
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::operator[](const char* name) const {
        return at(name);
    }
    
    //--------------------------------------------------------------
    template<typename T>
    string OrderedPointerMap<T>::nameAt(int index) const {
        return _vector.size() && ofInRange(index, 0, _vector.size()-1) ? _vector[index].first : "";
    }
    
    //--------------------------------------------------------------
    template<typename T>
    bool OrderedPointerMap<T>::exists(string name) const {
        return _map.find(name) != _map.end();
    }


    
}