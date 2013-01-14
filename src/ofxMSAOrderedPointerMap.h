#pragma once

//#include <vector>
//#include <map>
//#include <string>
#include "ofMain.h"

namespace msa {
    
    template<typename keyType, typename T>
    class OrderedPointerMap {
    public:
        
        virtual ~OrderedPointerMap();
        
        // get size
        int size() const;
        
        // add new item
        // item will be cloned, stored internally and added to an stl::map and stl::vector as a pointer
        // pointer will be owned and deleted by this class
        // returns a reference to the new pointer added
        T& push_back(keyType key, const T& t);
        
        // add new item
        // this pointer will be added directly to the stl::map and stl::vector
        // pointer will be owned and deleted by this class
        // returns a reference to the (same) pointer
        T& push_back(keyType key, T* t);

        
        // return reference to the stored object
        // throws an exception of the index or key doesn't exist
        T& at(int index) const;         // get by index
        T& at(keyType key) const;       // get by key
        
        // [] operator overloads for above
        // these also throw an exception if the index or key doesn't exist
        T& operator[](int index) const;
        T& operator[](keyType key) const;
        T& operator[](const char* key) const;
        
        // get the key for item at index. returns "" if doesn't exist
        keyType nameFor(int index) const;
        
        // get the index for item with key. returns -ve if doesn't exist
        int indexFor(keyType key) const;
        
        // see if key exists
        bool exists(keyType key) const;
        
        // clear, and delete pointers
        void clear();
        
    private:
        map<keyType, pair<int, T*> > _map;
        vector< pair<keyType, T*> >	_vector;
    };
    
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    OrderedPointerMap<keyType, T>::~OrderedPointerMap() {
        clear();
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    void OrderedPointerMap<keyType, T>::clear() {
        for(int i=0; i<_vector.size(); i++) delete _vector[i].second;
        _vector.clear();
        _map.clear();
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    int OrderedPointerMap<keyType, T>::size() const {
        return _vector.size();
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    T& OrderedPointerMap<keyType, T>::push_back(keyType key, const T& t) {
        if(exists(key)) {
            ofLogError() << "msa::ControlFreak::OrderedPointerMap<keyType, T>::push_back: " << key << " - key already exists, returning existing";
            return *_map[key].second;
        } else {
            return push_back(key, new T(t));
        }
    }
    
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    T& OrderedPointerMap<keyType, T>::push_back(keyType key, T* t) {
        if(exists(key)) {
            ofLogError() << "msa::ControlFreak::OrderedPointerMap<keyType, T>::push_back: " << key << " - key already exists, returning existing";
            return at(key);
        } else {
            _vector.push_back(pair<keyType, T*>(key, t));
            _map[key] = pair<int, T*>(_vector.size()-1, t);
            size();	// to check if correctly added to both containers, should be ok
            return *t;
        }
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    T& OrderedPointerMap<keyType, T>::at(int index) const {
        // make sure there is something in the array, and index is within the range
//        return _vector.size() && ofInRange(index, 0, _vector.size()-1) ? *_vector[index].second : T();
        return *_vector.at(index).second;
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    T& OrderedPointerMap<keyType, T>::at(keyType key) const {
        // make sure the key exists (don't add it by mistake)
//        return exists(key) ? *_map.at(key) : T();
        return *_map.at(key).second;
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    T& OrderedPointerMap<keyType, T>::operator[](int index) const {
        return at(index);
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    T& OrderedPointerMap<keyType, T>::operator[](keyType key) const {
        return at(key);
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    T& OrderedPointerMap<keyType, T>::operator[](const char* key) const {
        return at(key);
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    keyType OrderedPointerMap<keyType, T>::nameFor(int index) const {
        return _vector.size() && ofInRange(index, 0, _vector.size()-1) ? _vector[index].first : "";
    }
    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    int OrderedPointerMap<keyType, T>::indexFor(keyType key) const {
        return exists(key) ? _map.at(key).first : -1;
    }

    
    //--------------------------------------------------------------
    template<typename keyType, typename T>
    bool OrderedPointerMap<keyType, T>::exists(keyType key) const {
        return _map.find(key) != _map.end();
    }


    
}