#include <iostream>
#include "p_4_header.hpp"
#include <fstream>
#include <cassert>

std::size_t length (char const *a);
int compare(char const *str1, char const *str2);
void assign( char *str1, char const *str2);
unsigned int distance(char const *str1, char const *str2);
std::size_t is_sorted( char *array[], std::size_t capacity );
void insert( char *array[], std::size_t capacity );
void insertion_sort( char *array[], std::size_t capacity );
std::size_t remove_duplicates( char *array[], std::size_t capacity );
std::size_t find( char *array[], std::size_t capacity, char const *str );
void read_words_from_file( char const *filename, char **&word_array, std::size_t &num_words, std::size_t max_length );
void free_word_array( char** word_array );

std::size_t length( char const *a)
{
    char stop = '\0';
    std::size_t count = 0;
    int i = 0;
    while(a[i] != stop){
        count++;
        i++;
    }
    return count;
}


int compare(char const *str1, char const *str2){// -1 str1 is before the in the dictionary
    int i = 0;                                  // 0 str1 & str2 are the same
    if(str2[0] == '\0' && str1[0] != '\0'){     // 1 str2 is before in the dictionary
        return 1;  
    }
    else if(str1[0] == '\0' && str2[0] != '\0'){
        return -1;
    }
    else{
        while(str1[i] != '\0' || str2[i] != '\0'){
            if(str1[i] == '\0' &&  str2[i] == '\0'){//if both null situation
                break;
            }
            else if(str1[i] == str2[i]){//if the same they are the same value
                i++;
            }
            else if(str2[i] == '\0' || str1[i] > str2[i]){//if string1 is greater return 1 meaning str1 is later in dictionary
                return 1;
            }
            else if(str1[i] == '\0' || str1[i] < str2[i]){// if string2 is greater returns -1 meaning str2 later in dictionary
                return -1;
            }
        }
    }
    return 0;
}


void assign( char *str1, char const *str2){
    int i = 0;
    while(str2[i] != '\0'){
        str1[i] = str2[i];//replaces the values of str1
        i++;
    }
    str1[i] = str2[i];//sets the null variable back in place
}

unsigned int distance(char const *str1, char const *str2){
    int i = 0;
    if(str1[0] == '\0' && str2[0] == '\0'){//base case when it gets to the end it will return 0 and add up all the values
        return 0;
    }
    else if(str1[0] == '\0'){// if the first string is not equal to anything it will be counting how many adds it needs
       return 1 + distance(str1, str2 + 1);

    }
    else if(str2[0] == '\0'){//if the second string is not equal to anything it will be counting how many adds it needs
       return 1 + distance(str1 + 1, str2);
    }
    else if(str1[0] == str2[0])//if they are equal dont increase count bc you didnt change
    {
        return distance(str1 + 1, str2 + 1);
    }
    else if (str1[0] != str2[0]){// first dist = delete & middle/last dist = switches(embedded min statement)
        unsigned int min = std::min(distance(str1 + 1, str2 + 1), std::min(distance(str1 + 1, str2), distance(str1, str2 + 1)));
        return 1 + min;//counts everytime it calls the fastest way to change it 
    }
    return -1;
}

std::size_t is_sorted( char *array[], std::size_t capacity ){
    for(int i = 0; i < capacity - 1; i++){
        if(compare(array[i], array[i + 1]) > 0){//compare 2 strings if they aren't sorted it returns where it wasn't sorted
            return i + 1;
        }
    }
    return capacity;
}

void insert( char *array[], std::size_t capacity ){//array holds multiple strings
    char *value = new char[length(array[capacity - 1]) + 1]{};
    assign(value, array[capacity - 1]);
    std::size_t i{};
    for( i = capacity - 1; i > 0; i--){
        int check = compare(value, array[i - 1]);//compares if its the same or larger
        if(check == -1){//if the value of the array infront of last variable move the variable over 
            array[i] = array[i - 1];
        } 
        else{
            break;
        }
    }
    array[i] = value;//add the final value saved to spot it should be at
}

void insertion_sort( char *array[], std::size_t capacity ){
    for(int k = 1; k <= capacity ; k++){
        insert(array, k);
    }
}

std::size_t remove_duplicates( char *array[], std::size_t capacity ){
   int cap_change = capacity;
   for(int i = 0; i < cap_change - 1; i++){
      if(compare(array[i],array[i + 1]) == 0)
      {
        for(int j = i; j < cap_change - 1; j++){
            array[j] = array[j + 1];
        }
        cap_change--;
        i--;//bc it moves everything over so you have to move it back so it checks the same location
      }
   }
   return cap_change;
}

std::size_t find( char *array[], std::size_t capacity, char const *str ){
    int smallD = distance(array[0], str);
    std::size_t smallD_ind = 0;
    for(int i = 0; i < capacity; i++){
        if(compare(array[i], str) == 0){//compares if they are the same string
            return i;//returns index where it found it
        }
        //check the smallest distance 
        else{
            int size = distance(array[i],str);
            if(smallD < size){//if its the new smallest index save it's value
                smallD = size;
                smallD_ind = i;
            }
        }
    }
    return smallD_ind;
}

void free_word_array( char** word_array ){//only need 2 deletes because there are only two allocated uses of allocating memory
    delete[] word_array[0];               //in the read words from file function
    delete[] word_array;
}