//
//  Tests.cpp
//  HashTables
//
//  Created by Arne Philipeit on 23/11/2016.
//

#include "Tests.h"

void testCustomImplementation() {
    for (int h = 1; h <= 5; h++) {
        if (h >= 1 && h <= 4) {
            printf("hashIndex%i\n", h);
        }else{
            printf("hashIndex4+2\n");
        }
        
        HashFunction hashFunction = (HashFunction)(h - 1);
        
        for (int d = 1; d <= 2; d++) {
            printf("TestStrings%i.txt\n", d);
            
            string testStringsFilePath;
            if (d == 1) {
                testStringsFilePath = "/Users/Philipeit/Documents/College/HashTables/HashTables/TestStrings1.txt";
            }else{
                testStringsFilePath = "/Users/Philipeit/Documents/College/HashTables/HashTables/TestStrings2.txt";
            }
            
            fstream testStringsFile;
            testStringsFile.open(testStringsFilePath);
            
            if (!testStringsFile) {
                exit(1);
            }
            
            for (int l = 1; l <= 2; l++) {
                printf("Load: %i%%\n", (l == 1) ? 50 : 80);
                
                for (int M = 5; M <= 1000; M++) {
                    HashTableRef table = createHashTable(M, hashFunction);
                    
                    if (!table) {
                        exit(2);
                    }
                    
                    int totalCollisions = 0;
                    int nEntries = M * ((l == 1) ? 0.5 : 0.8);
                    
                    for (int i = 0; i < nEntries; i++) {
                        char * testString = (char *) malloc(21 * sizeof(char));
                        
                        testStringsFile.getline(testString, 21);
                        
                        int collisions;
                        
                        addToHashTable(table, testString, collisions);
                        
                        totalCollisions += collisions;
                    }
                    
                    printf("%f ", (double)totalCollisions / (double)nEntries);
                    
                    delete[] table;
                    testStringsFile.clear();
                    testStringsFile.seekg(0, ios::beg);
                }
                printf("\n\n");
                fflush(stdout);
            }
            
            testStringsFile.close();
        }
    }
}

void testReviewedImplementation() {
    for (int d = 1; d <= 2; d++) {
        printf("TestStrings%i.txt\n", d);
        
        string testStringsFilePath;
        if (d == 1) {
            testStringsFilePath = "/Users/Philipeit/Documents/College/HashTables/HashTables/TestStrings1.txt";
        }else{
            testStringsFilePath = "/Users/Philipeit/Documents/College/HashTables/HashTables/TestStrings2.txt";
        }
        
        fstream testStringsFile;
        testStringsFile.open(testStringsFilePath);
        
        if (!testStringsFile) {
            exit(1);
        }
        
        hash_t table;
        
        hash_init(&table, 5);
        
        for (int i = 0; i < 1000; i++) {
            char * testString = (char *) malloc(21 * sizeof(char));
            
            testStringsFile.getline(testString, 21);
            
            hash_insert(&table, testString, 0);
            
            if (i >= 4) {
                printf("%s\n", hash_stats(&table));
            }
        }
        
        hash_destroy(&table);
    }
}
