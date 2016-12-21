//
//  HashFunctions.cpp
//  HashTables
//
//  Created by A Philipeit on 23/11/2016.
//

#include "HashFunctions.h"

//hashIndex1
//Hash function (extremely simple)
int hashIndex1(const char * string, int M) {
    size_t l = strlen(string);
    
    return l % M;
}

//hashIndex2
//Hash function using more data from the string
int hashIndex2(const char * string, int M) {
    size_t l = strlen(string);
    
    long index = 0;
    
    for (int i = 0; i < l; i++) {
        index += string[i] * (l - i);
    }
    
    return index % M;
}

//hashIndex3
//Hash function which adds the differences between characters
int hashIndex3(const char * string, int M) {
    size_t l = strlen(string);
    
    long index = 0;
    
    for (int i = 0; i < l; i++) {
        index += abs(string[(i + 1) % l] - string[i]);
    }
    
    return index % M;
}

//hashIndex4
//Hash function using bitwise operators
int hashIndex4(const char * string, int M) {
    size_t l = strlen(string);
    
    int index = 0;
    
    for (int i = 0; i < l; i++) {
        index = index ^ (((int) string[i]) << (i % 25));
    }
    
    return index % M;
}
