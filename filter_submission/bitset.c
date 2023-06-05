#include "bitset.h"

// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int universe_size) {
    struct bitset * result;
    result = malloc(sizeof(struct bitset));
    float word_size = sizeof(uint64_t)*8;
    int words = ceil(universe_size/word_size);
    result-> size_in_words = words;
    result->universe_size = universe_size;
    result->bits = malloc(sizeof(uint64_t)*words);
    for(int i = 0; i<words; i++)
    {
        result->bits[i] = 0;
    }
    return result;

}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {

    return this->universe_size;

}

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int the_number_of_items = 0; 
    for(int i=0; i<this->universe_size; i++)
        if ( bitset_lookup(this, i) == 1 ) // count the number when bitset_lookup found an item
        the_number_of_items++;
        
        return the_number_of_items;

}    

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){
    
    int word_size = sizeof(uint64_t)*8;
    int word = item / word_size;            //determine in which element an item is.
    int bit = item % word_size;             //determine in which index an item is.
    uint64_t the_item = this->bits[word];
    uint64_t mask = 1ULL << bit;
    if(((the_item) & (mask)) !=0)           
        return 1;
    else
        return 0;
        
}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {

    int word_size = sizeof(uint64_t)*8;
    int word = item / word_size;
    int bit = item % word_size;
    uint64_t old_val = this->bits[word];
    uint64_t mask = 1ULL << bit; 
    this->bits[word] = old_val | mask;

}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {

    int word_size = sizeof(uint64_t)*8;
    int word = item / word_size;
    int bit = item % word_size;
    uint64_t old_val = this->bits[word];
    uint64_t mask = 1ULL << bit; 
    old_val = old_val | mask;
    this->bits[word] = old_val ^ mask;

}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {

        for(int i = 0; i<dest->universe_size; i++) //universe_size or size_in_words? worked in both situation
        dest->bits[i] = src1->bits[i] | src2->bits[i]; 

}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {
        
        for(int i = 0; i<dest->universe_size; i++)//universe_size or size_in_words?
        dest->bits[i] = src1->bits[i] & src2->bits[i];
        
}

  /*if(this->bits[i] !=0 )
        {
        the_number_of_items++;
        }*/

  /*  int i=sizeof(this->bits);
    int j=0;
    for(; i>0; i--)
    {
        if(this->bits[i] != 0)
        {
          the_number_of_items = the_number_of_items + 2^j;
        }
        j++;
    }*/


    /*if(this->bits[item] != 0)
    {
        return 1;
    }else
    {
        return 0;
    }*/


    /* int i=0;
    for(; i<this->size_in_words; i++)//maybe universe_size?
    {
        if(this->bits[i]== '\0')
            this->bits[i] = item;
    }*/
