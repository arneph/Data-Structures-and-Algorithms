//
//  HashTable.cpp
//  HashTables
//
//  Created by A Philipeit on 24/11/2016.
//

#include "HashTable.h"

int getIndexForKey(HashTableRef table, char * key, int &collisions);

HashTableRef createHashTable(int M, HashFunction hashFunction) {
    if (M < 1) {
        return NULL;
    }
    
    HashTableRef table = (HashTableRef) malloc(sizeof(HashTable));
    
    if (!table) {
        return NULL;
    }
    
    table->M = M;
    table->hashFunction = hashFunction;
    table->entries = (char **) calloc(M, sizeof(char *));
    
    if (!(table->entries)) {
        free(table);
        return NULL;
    }
    
    return table;
}

void deleteHashTable(HashTableRef table) {
    if (table == NULL) {
        return;
    }
    
    for (int i = 0; i < table->M; i++) {
        if (table->entries[i] != NULL) {
            free(table->entries[i]);
        }
    }
    
    free(table->entries);
    free(table);
}

void addToHashTable(HashTableRef table, char * entry) {
    int collisions;
    int index = getIndexForKey(table, entry, collisions);
    
    if (index == -1) {
        return;
    }
    
    if (table->entries[index] == NULL) {
        table->entries[index] = entry;
    }
}

void addToHashTable(HashTableRef table, char * entry, int &collisions) {
    int index = getIndexForKey(table, entry, collisions);
    
    if (index == -1) {
        return;
    }
    
    if (table->entries[index] == NULL) {
        table->entries[index] = entry;
    }
}

bool searchHashTable(HashTableRef table, char * entry) {
    int collisions;
    int index = getIndexForKey(table, entry, collisions);
    
    if (index == -1) {
        return false;
    }else if (table->entries[index] == NULL) {
        return false;
    }else{
        return true;
    }
}

bool searchHashTable(HashTableRef table, char * entry, int &collisions) {
    int index = getIndexForKey(table, entry, collisions);
    
    if (index == -1) {
        return false;
    }else if (table->entries[index] == NULL) {
        return false;
    }else{
        return true;
    }
}

int getIndexForKey(HashTableRef table, char * key, int &collisions) {
    collisions = 0;
    
    int index = 0;
    
    if (table->hashFunction == HashFunction1) {
        index = hashIndex1(key, table->M);
    }else if (table->hashFunction == HashFunction2) {
        index = hashIndex2(key, table->M);
    }else if (table->hashFunction == HashFunction3) {
        index = hashIndex3(key, table->M);
    }else if (table->hashFunction == HashFunction4 ||
              table->hashFunction == HashFunction4_2){
        index = hashIndex4(key, table->M);
    }
    
    bool * encounteredIndexes = (bool *) calloc(table->M, sizeof(bool));
    encounteredIndexes[index] = true;
    
    while (table->entries[index] != NULL &&
           strcmp(key, table->entries[index]) != 0) {
        collisions++;
        
        if (table->hashFunction == HashFunction4_2) {
            index += hashIndex2(key, table->M);
        }else{
            index++;
        }
        index %= table->M;
        
        if (encounteredIndexes[index] == false) {
            encounteredIndexes[index] = true;
        }else{
            free(encounteredIndexes);
            
            return -1;
        }
    }
    
    free(encounteredIndexes);
    
    return index;
}
