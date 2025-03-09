#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"
#include <time.h>


//kv pair
typedef struct {
    char pair[2];
} Pair;

//frequency of pairs
typedef struct {
    Pair key;
    size_t value;
} Freq;

//dynamic array of frequency counts
#define INITIAL_CAPACITY 4  
typedef struct {
    Freq *items;
    size_t length;
    size_t capacity;
} Freqs;


// Initialize the dynamic array
void init_freqs(Freqs *arr) {
    arr->length = 0;
    arr->capacity = INITIAL_CAPACITY;
    arr->items = (Freq *)malloc(arr->capacity * sizeof(Freq));
    if (!arr->items) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
}

void append_freq(Freqs *arr, Freq value) {
    if (arr->length >= arr->capacity) {
        arr->capacity *= 2;
        arr->items = (Freq *)realloc(arr->items, arr->capacity * sizeof(Freq));
        if (!arr->items) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
    }
    arr->items[arr->length++] = value; // Append the item
}

void free_freqs(Freqs *arr) {
    free(arr->items);
    arr->items = NULL;
    arr->length = 0;
    arr->capacity = 0;
}

Freq *freq = NULL;

int compare(const void *a, const void *b) {
    const Freq *freq1 = a;
    const Freq *freq2 = b;
    return (int)freq1->value - (int)freq2->value;
}

int main() {
    const char *text = "If you're visiting this page, you're likely here because you're searching for a random sentence. Sometimes a random word just isn't enough, and that is where the random sentence generator comes into play. By inputting the desired number, you can make a list of as many random sentences as you want or need. Producing random sentences can be helpful in a number of different ways.";

    int length = strlen(text);
    
    for (int i = 0; i < length - 1; ++i) { 
        Pair pair = {{ text[i], text[i + 1] }};
        ptrdiff_t index = hmgeti(freq, pair);
        if (index < 0) 
            hmput(freq, pair, 1);
        else 
            freq[index].value += 1;
    }

    Freqs sorted_freqs;
    init_freqs(&sorted_freqs);  

    // Copy values from hashmap to dynamic array
    for (ptrdiff_t i = 0; i < hmlen(freq); ++i) {
        append_freq(&sorted_freqs, freq[i]); 
    }

    qsort(sorted_freqs.items, sorted_freqs.length, sizeof(*sorted_freqs.items), compare);

    for (size_t i = 0; i < sorted_freqs.length; i++) {
        printf("%c%c: %zu\n", sorted_freqs.items[i].key.pair[0], sorted_freqs.items[i].key.pair[1], sorted_freqs.items[i].value);
    }

    free_freqs(&sorted_freqs);
    return 0;
}
