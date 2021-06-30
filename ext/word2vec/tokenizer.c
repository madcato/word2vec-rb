#include "common.h"

void word2vec_tokenize(char* train_file, char* vocab_file, char* output_file) {
  long long word;
  vocab = (struct vocab_word *)calloc(vocab_max_size, sizeof(struct vocab_word));
  vocab_hash = (long long *)calloc(vocab_hash_size, sizeof(long long));
  strcpy(train_file, train_file);
  strcpy(read_vocab_file, vocab_file);
  ReadVocab();
  FILE *fi = fopen(train_file, "rb");
  FILE *fo = fopen(output_file, "wb");
  while (1) {
    word = ReadWordIndex(fi);
    if (feof(fi)) break;
    fwrite(&word, sizeof(word), 1, fo);
  }
  fclose(fi);
  fclose(fo);
}