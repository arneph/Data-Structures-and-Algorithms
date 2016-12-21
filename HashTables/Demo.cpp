//
//  Demo.cpp
//  HashTables
//
//  Created by A Philipeit on 23/11/2016.
//

#include "Demo.h"

void demo() {
    fstream testStringsFile;
    testStringsFile.open("/Users/Philipeit/Documents/College/HashTables/HashTables/TestStrings2.txt");
    
    if (!testStringsFile) {
        exit(3);
    }
    
    HashTableRef table = createHashTable(1200, HashFunction4_2);
    
    if (!table) {
        exit(4);
    }
    
    for (int i = 0; i < 1000; i++) {
        char * testString = (char *) malloc(21 * sizeof(char));
        
        testStringsFile.getline(testString, 21);
        
        addToHashTable(table, testString);
    }
    
    
//    {//Print table:
//        for (int i = 0; i < 2000; i++) {
//            printf("%s\n", table->entries[i]);
//        }
//    }
    
    {//Search demo:
        char searchTerm1[] = "soup";
        char searchTerm2[] = "truth";
        
        if (searchHashTable(table, searchTerm1)) {
            printf("Found soup!\n");
        }else{
            printf("Did not find soup!\n");
        }
        
        if (searchHashTable(table, searchTerm2)) {
            printf("Found truth!\n");
        }else{
            printf("Did not find truth!\n");
        }
    }
    
    deleteHashTable(table);
    
    testStringsFile.close();
}
