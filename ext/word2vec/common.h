#ifndef _WORD2VEC_COMMON_H
#define _WORD2VEC_COMMON_H

#include <ruby.h>
#include <ruby/io.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

extern const long long N;  // number of closest words that will be shown
  
typedef struct word2vec_model_s {
  long long word_count;
  char *vocabulary;  // char *[word_count]
  long long vector_dim;
  float *vectors;  // float[word_count][vector_dim]
} word2vec_model;

typedef struct WordSimilarity_s {
  size_t index;
  float score;
} WordSimilarity;

void word2vec_model_load(word2vec_model* model, char* file_name);
size_t word2vec_model_distance(word2vec_model* model, char* word, WordSimilarity word_list[]);

#endif /* _WORD2VEC_COMMON_H */