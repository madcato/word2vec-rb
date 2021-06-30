#include "common.h"

const int vocab_hash_size = 30000000;  // Maximum 30 * 0.7 = 21M words in the vocabulary

struct vocab_word *vocab;
int debug_mode = 2, min_count = 5, min_reduce = 1;
long long vocab_max_size = 1000, vocab_size = 0;
long long *vocab_hash;
long long train_words = 0, file_size = 0;

void SaveVocab(char* save_vocab_file) {
  long long i;
  FILE *fo = fopen(save_vocab_file, "wb");
  for (i = 0; i < vocab_size; i++) fprintf(fo, "%s %lld\n", vocab[i].word, vocab[i].cn);
  fclose(fo);
}

// Build vocabulary file
void word2vec_build_vocab(char* train, char* save_vocab_file) {
  strcpy(train_file, train);
  vocab = (struct vocab_word *)calloc(vocab_max_size, sizeof(struct vocab_word));
  vocab_hash = calloc(vocab_hash_size, sizeof(long long));
  LearnVocabFromTrainFile();
  SaveVocab(save_vocab_file);
}