#include "common.h"

// Find nearest words in the model
size_t word2vec_model_distance(word2vec_model* model, char* word, WordSimilarity word_list[]) {
  if (strlen(word) >= max_size) {
    rb_raise(rb_eArgError, "word must be %lu character max size", max_size);
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