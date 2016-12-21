//
//  main.cpp
//  Sorting
//
//  Created by Arne Philipeit on 05/12/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

//Global variable to count probes (long long to avoid overflow)
long long n_probes;

//All functions assume that numc is the size of a valid array nums

void random_numbers(int numc, int nums[], int max);
void print_numbers(int numc, int nums[]);

void insertion_sort(int numc, int nums[]);
void randomized_quick_sort(int numc, int nums[]);
void quick_sort(int numc, int nums[]);

bool is_sorted(int numc, int nums[]);

int main(int argc, const char * argv[]) {
    {//Small test to see if functions work correctly:
        int test1a[] = {2,4,5,4,7};
        int test1b[] = {2,4,5,4,7};
        int test1c[] = {2,4,5,4,7};
        
        insertion_sort(5, test1a);
        quick_sort(5, test1b);
        randomized_quick_sort(5, test1c);
        
        assert(is_sorted(5, test1a));
        assert(is_sorted(5, test1b));
        assert(is_sorted(5, test1c));
        
        printf("Insertion sort: ");
        print_numbers(5, test1a);
        printf("\n");
        
        printf("Quick sort: ");
        print_numbers(5, test1b);
        printf("\n");
        
        printf("Randomized Quick sort: ");
        print_numbers(5, test1c);
        printf("\n");
    }
    
    {//Examine performance for large array sizes with different input:
        for (int i = 1; i <= 100; i++) {
            //Set up test case for n elements:
            int n = 1000 * i;
            
            //Test 2 (already sorted):
            int * test2a = (int *) malloc(n * sizeof(int));
            int * test2b = (int *) malloc(n * sizeof(int));
            int * test2c = (int *) malloc(n * sizeof(int));
            //Test 3 (reverse order):
            int * test3a = (int *) malloc(n * sizeof(int));
            int * test3b = (int *) malloc(n * sizeof(int));
            int * test3c = (int *) malloc(n * sizeof(int));
            //Test 4 (random order):
            int * test4a = (int *) malloc(n * sizeof(int));
            int * test4b = (int *) malloc(n * sizeof(int));
            int * test4c = (int *) malloc(n * sizeof(int));
            
            for (int j = 0; j < n; j++) {
                test2a[j] = test2b[j] = test2c[j] = j;
                test3a[j] = test3b[j] = test3c[j] = n - j - 1;
            }
            
            random_numbers(n, test4a, n);
            
            for (int j = 0; j < n; j++) test4c[j] = test4b[j] = test4a[j]; //I do not trust memcpy, this is also easier to understand
            
            //Count the number of probes each algorithm performs:
            n_probes = 0;
            insertion_sort(n, test2a);
            long long n_probes_insertion_sort_test2 = n_probes;
            
            n_probes = 0;
            quick_sort(n, test2b);
            long long n_probes_quick_sort_test2 = n_probes;
            
            n_probes = 0;
            randomized_quick_sort(n, test2c);
            long long n_probes_randomized_quick_sort_test2 = n_probes;
            
            n_probes = 0;
            insertion_sort(n, test3a);
            long long n_probes_insertion_sort_test3 = n_probes;
            
            n_probes = 0;
            quick_sort(n, test3b);
            long long n_probes_quick_sort_test3 = n_probes;
            
            n_probes = 0;
            randomized_quick_sort(n, test3c);
            long long n_probes_randomized_quick_sort_test3 = n_probes;
            
            n_probes = 0;
            insertion_sort(n, test4a);
            long long n_probes_insertion_sort_test4 = n_probes;
            
            n_probes = 0;
            quick_sort(n, test4b);
            long long n_probes_quick_sort_test4 = n_probes;
            
            n_probes = 0;
            randomized_quick_sort(n, test4c);
            long long n_probes_randomized_quick_sort_test4 = n_probes;
            
            //Check results (optional, slows down program):
            assert(is_sorted(n, test2a));
            assert(is_sorted(n, test2b));
            assert(is_sorted(n, test2c));
            assert(is_sorted(n, test3a));
            assert(is_sorted(n, test3b));
            assert(is_sorted(n, test3c));
            assert(is_sorted(n, test4a));
            assert(is_sorted(n, test4b));
            assert(is_sorted(n, test4c));
            
            //Print results:
            printf("%i %lli %lli %lli %lli %lli %lli %lli %lli %lli\n", n,
                   n_probes_insertion_sort_test2, n_probes_quick_sort_test2, n_probes_randomized_quick_sort_test2,
                   n_probes_insertion_sort_test3, n_probes_quick_sort_test3, n_probes_randomized_quick_sort_test3,
                   n_probes_insertion_sort_test4, n_probes_quick_sort_test4, n_probes_randomized_quick_sort_test4);
             
            //Memory:
            free(test2a);
            free(test2b);
            free(test2c);
            free(test3a);
            free(test3b);
            free(test3c);
            free(test4a);
            free(test4b);
            free(test4c);
        }
    }
    
    return 0;
}

//Helping function
//Fills a given array with random number values up to max (inclusive)
void random_numbers(int numc, int nums[], int max) {
    srand((unsigned int) time(NULL));
    
    for (int i = 0; i < numc; i++) {
        nums[i] = rand() % (max + 1);
    }
}

//Helping function
//Prints an array of integers without a line break
void print_numbers(int numc, int nums[]) {
    for (int i = 0; i < numc; i++) {
        printf("%i ", nums[i]);
    }
}

//Helping function
//Simply switches values pointed to by a and b
void swap(int * a, int * b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

//Iterates throught the array looking at elements
//If an element I is smaller than the element before it,
//it needs to be swapped left continually until it is "inserted" in the right position.
void insertion_sort(int numc, int nums[]) {
    //Iterate through the array, looking at the element at index j:
    for (int i = 1; i < numc; i++) {
        int j = i;//Keep track of the element at index j (for insertion), called I (for commenting)
        
        //While the element to be inserted I, found at index j, is not in the correct position,
        //at the start of the array,
        //or after an element that is smaller than or equal to I...
        while (j > 0 && nums[j] < nums[j - 1]) {
            n_probes++;
            swap(&(nums[j]), &(nums[j - 1]));//Swap I with the element to its left
            j--;//Update j to keep track of I
        }
        if (j > 0) n_probes++;
    }
}
//Note: i starts at 1 because the first element can not be inserted anywhere in the (empty)
//subarray before it. The loop condition that all elements left of i are sorted already holds
//for i = 1.

void randomized_quick_sort(int p, int q, int nums[]);
void quick_sort(int p, int q, int nums[]);
int quick_sort_partition(int p, int q, int nums[]);

//Convenience function to start randomized quick sort for a whole array
void randomized_quick_sort(int numc, int nums[]) {
    randomized_quick_sort(0, numc - 1, nums);
}

//Convenvience function to start quick sort for a whole array
void quick_sort(int numc, int nums[]) {
    quick_sort(0, numc - 1, nums);
}

//Actual randomized quick sort function
//Sorts the array nums between indices p and q inclusive
void randomized_quick_sort(int p, int q, int nums[]) {
    if (p == q) return;
    
    //Randomize pivot:
    srand((unsigned int) time(NULL));
    
    int a = p + rand() % (q - p + 1); //Random index in array
    
    swap(&(nums[a]), &(nums[q])); //Swap random element with last element
    //Last element will be used as pivot
    
    //Carry out quick sort as usual:
    int r = quick_sort_partition(p, q, nums); //Partition array, remember pivot index
    
    //Sort the two partitions (recursively), if their size is greater than 1:
    if (r > p) randomized_quick_sort(p, r - 1, nums);
    if (r < q) randomized_quick_sort(r + 1, q, nums);
}

//Actual quick sort function
//Sorts the array nums between indices p and q inclusive
void quick_sort(int p, int q, int nums[]) {
    if (p == q) return; //Array of size 1: No need to sort,
    
    int r = quick_sort_partition(p, q, nums); //Partition array, remember pivot index
    
    //Sort the two partitions (recursively), if their size is greater than 1:
    if (r > p) quick_sort(p, r - 1, nums);
    if (r < q) quick_sort(r + 1, q, nums);
}

//Helping function for quick sort
//Partitions the array nums between indices p and q inclusive
//Returns the pivot index
//
//Choose the last element as pivot,
//then go through the array, swapping each element smaller than the pivot
//with the first element greater than or equal to the pivot
int quick_sort_partition(int p, int q, int nums[]) {
    int pivot = nums[q]; //Choose the last element as pivot
    int j = p - 1; //Keep track of the largest index of elements known to be smaller than the pivot
    //j is also the largest index (inclusive) of the first partition
    
    
    //Go through every element in the array (except the pivot):
    for (int i = p; i < q; i++) {
        
        //Decide which partition (< pivot or >= pivot) nums[i] belongs to:
        if (nums[i] < pivot) {
            n_probes++;
            //nums[i] should be part of the first partition (< pivot)
            
            j++; //Increase the size of the first partition
            swap(&(nums[i]), &(nums[j])); //Add nums[i] to its last position
            //nums[i] will be swapped with an element (nums[j]) that is known to be >= pivot,
            //expect if i = j, in which case it is swapped with itself
        }
    }
    
    
    //Swap the first element in the second partition (>= pivot)
    //with the pivot element in the last position.
    swap(&(nums[j + 1]), &(nums[q]));
    
    
    //Array is now partitioned:
    //Elements < pivot | pivot | Elements >= pivot
    
    //Return the pivot index:
    return j + 1;
}

//Checks if a given array nums is sorted (O(n))
//If an element is smaller than the element before it,
//the function returns false
bool is_sorted(int numc, int nums[]) {
    for (int i = 1; i < numc; i++) {
        if (nums[i] < nums[i - 1]) {
            return false;
        }
    }
    
    return true;
}
