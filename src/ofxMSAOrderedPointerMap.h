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
        // pointer will be owned and deleted by this class
        // returns the pointer added
        T& push_back(string name, const T& t);
        
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
        void clear(bool bDeletePointers = true);
        
    private:
        map<string, T*> _map;
        vector< pair<string, T*> >	_vector;
    };
    
    
    //--------------------------------------------------------------
    template<typename T>
    OrderedPointerMap<T>::~OrderedPointerMap() {
        clear(true);
    }
    
    //--------------------------------------------------------------
    template<typename T>
    void OrderedPointerMap<T>::clear(bool bDeletePointers) {
        if(bDeletePointers) for(int i=0; i<_vector.size(); i++) delete _vector[i].second;
        _vector.clear();
        _map.clear();
    }
    
    //--------------------------------------------------------------
    template<typename T>
    int OrderedPointerMap<T>::size() const {
//        assert(_vector.size() == _map.size());	// probably tried to add with the same name
        return _map.size();
    }
    
    //--------------------------------------------------------------
    template<typename T>
    T& OrderedPointerMap<T>::push_back(string name, const T& t) {
        if(exists(name)) {
            ofLogError() << "msa::ControlFreak::OrderedPointerMap<T>::push_back: " << name << " - name already exists, returning existing";
            return *_map[name];
        } else {
            T* tt = new T(t);
            _map[name] = tt;
            _vector.push_back(pair<string, T*>(name, tt));
            size();	// to check if correctly added to both containers, should be ok
            return *tt;
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