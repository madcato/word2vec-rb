#ifndef _WORD2VEC_COMMON_H
#define _WORD2VEC_COMMON_H

#include <ruby.h>
#include <ruby/io.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>

#define MAX_STRING 100
#define MAX_CODE_LENGTH 40

// max length of strings
extern const unsigned long max_size;
// number of closest words that will be shown
extern const long long N;
// max length of vocabulary entries
extern const long long max_w;
// Maximum 30 * 0.7 = 21M words in the vocabulary
extern const int vocab_hash_size;
extern long long *vocab_hash;
extern struct vocab_word *vocab;

extern char train_file[];
extern char read_vocab_file[];
extern long long vocab_max_size, vocab_size;
extern long long train_words, file_size ;
extern int debug_mode, min_count, min_reduce;

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

struct vocab_word {
  long long cn;
  int *point;
  char *word, *code, codelen;
};

void ReadWord(char *word, FILE *fin);
unsigned long long GetWordHash(char *word);
unsigned long long SearchVocab(char *word) ;
unsigned long long ReadWordIndex(FILE *fin);

void LearnVocabFromTrainFile();
void ReadVocab();

/// main functions
void word2vec_model_load(word2vec_model* model, char* file_name);
size_t word2vec_model_distance(word2vec_model* model, char* word, WordSimilarity word_list[]);
size_t word2vec_model_analogy(word2vec_model* model, char* wordx1, char* wordy1, char* wordx2, WordSimilarity word_list[]);
void word2vec_model_accuracy(word2vec_model* model, char* file_name);
void word2vec_build_vocab(char* train_file, char* save_vocab_file);
void word2vec_tokenize(char* train_file, char* vocab_file, char* output_file);

#endif /* _WORD2VEC_COMMON_H */