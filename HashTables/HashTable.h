//
//  HashTable.h
//  HashTables
//
//  Created by A Philipeit on 24/11/2016.
//

#pragma once
#include <string.h>

#include "HashFunctions.h"

typedef enum HashFunction {
    HashFunction1,
    HashFunction2,
    HashFunction3,
    HashFunction4,
    HashFunction4_2
}HashFunction;

struct HashTable{
    char ** entries;
    int M;
    HashFunction hashFunction;
};

typedef struct HashTable * HashTableRef;

HashTableRef createHashTable(int M, HashFunction hashFunction);
void deleteHashTable(HashTableRef table);

void addToHashTable(HashTableRef table, char * entry);
void addToHashTable(HashTableRef table, char * entry, int &collisions);
bool searchHashTable(HashTableRef table, char * entry);
bool searchHashTable(HashTableRef table, char * entry, int &collisions);
