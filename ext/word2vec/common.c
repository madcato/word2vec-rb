#include "common.h"

// max length of strings
const long long max_size = 2000;
// number of closest words that will be shown
const long long N = 40;
// max length of vocabulary entries
const long long max_w = 50;

// Load the binary vector file generated by word2vec project
void word2vec_model_load(word2vec_model* model, char* file_name) {
  FILE *f;
  f = fopen(file_name, "rb");
  if (f == NULL) {
    rb_raise(rb_eArgError, "file not found");
    return;
  }
  
  long long words, size;
  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);
  model->word_count = words;
  model->vector_dim = size;
  
  model->vocabulary = ZALLOC_N(char, (long long)words * max_w);
  model->vectors = ALLOC_N(float, model->word_count * model->vector_dim);
  if (model->vectors == NULL) {
    rb_raise(rb_eNoMemError, "Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return;
  }

  for (long long b = 0; b < words; b++) {
    long long a = 0;
    while (true) {
      model->vocabulary[b * max_w + a] = fgetc(f);
      if (feof(f) || (model->vocabulary[b * max_w + a] == ' ')) break;
      if ((a < max_w) && (model->vocabulary[b * max_w + a] != '\n')) a++;
    }
    model->vocabulary[b * max_w + a] = 0;
    for (a = 0; a < size; a++) fread(&model->vectors[a + b * size], sizeof(float), 1, f);
    float len = 0;
    for (a = 0; a < size; a++) len += model->vectors[a + b * size] * model->vectors[a + b * size];
    len = sqrt(len);
    for (a = 0; a < size; a++) model->vectors[a + b * size] /= len;
  }
  fclose(f);
}

// Find nearest words in the model
size_t word2vec_model_distance(word2vec_model* model, char* word, WordSimilarity word_list[]) {
  if (strlen(word) >= max_size) {
    rb_raise(rb_eArgError, "word must be %lld character max size", max_size);
    return 0;
  }
  
  long long size = model->vector_dim;
  long long a;
  char *bestw[N];
  float bestd[N];
  size_t besti[N];
  for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));
  a = 0;

  long long b = 0;
  long long c = 0;

  long long words = model->word_count;
  for (b = 0; b < words; b++) { 
    if (!strcmp(&model->vocabulary[b * max_w], word)) break;
  }
  if (b == words) b = -1;
  long long bi = b;
  if (b == -1) {
    rb_raise(rb_eArgError, "Out of dictionary word!");
    return 0;
  }

  float vec[max_size];
  float dist;
  long long d;
  for (a = 0; a < size; a++) vec[a] = 0;
  for (a = 0; a < size; a++) vec[a] += model->vectors[a + bi * size];
  float len = 0;
  for (a = 0; a < size; a++) len += vec[a] * vec[a];
  len = sqrt(len);
  for (a = 0; a < size; a++) vec[a] /= len;
  for (a = 0; a < N; a++) bestd[a] = -1;
  for (a = 0; a < N; a++) bestw[a][0] = 0;
  for (c = 0; c < words; c++) {
    a = 0;
    if (bi == c) continue;
    dist = 0;
    for (a = 0; a < size; a++) dist += vec[a] * model->vectors[a + c * size];
    for (a = 0; a < N; a++) {
      if (dist > bestd[a]) {
        for (d = N - 1; d > a; d--) {
          bestd[d] = bestd[d - 1];
          strcpy(bestw[d], bestw[d - 1]);
          besti[d] = d - 1;
        }
        bestd[a] = dist;
        strcpy(bestw[a], &model->vocabulary[c * max_w]);
        besti[a] = c * max_w;
        break;
      }
    }
  }

  for (a = 0; a < N; a++) {
    word_list[a].index = besti[a];
    word_list[a].score = bestd[a];
  }
 
  for (a = 0; a < N; a++) free(bestw[a]);
  
  return N;
}