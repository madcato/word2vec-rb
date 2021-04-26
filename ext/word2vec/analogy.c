#include "common.h"

// Find the analog word 
size_t word2vec_model_analogy(word2vec_model* model, char* wordx1, char* wordy1, char* wordx2, WordSimilarity word_list[]) {
  if (strlen(wordx1) >= max_size) {
    rb_raise(rb_eArgError, "First parameter word must be %lu character max size", max_size);
    return 0;
  }

  if (strlen(wordy1) >= max_size) {
    rb_raise(rb_eArgError, "Second parameter word must be %lu character max size", max_size);
    return 0;
  }
  
  if (strlen(wordx2) >= max_size) {
    rb_raise(rb_eArgError, "Third parameter word must be %lu character max size", max_size);
    return 0;
  }
  
  float bestd[N];
  char bestw[N][max_size];
  size_t besti[N];
  long long words = model->word_count;
  long long size = model->vector_dim;
  long a = 0;
  long b = 0;
  for (a = 0; a < N; a++) bestd[a] = 0;
  for (a = 0; a < N; a++) bestw[a][0] = 0;

  char st[100][max_size];
  long long bi[100];
  long cn = 3;
  strcpy(st[0], wordx1);
  strcpy(st[1], wordy1);
  strcpy(st[2], wordx2);
  for (a = 0; a < cn; a++) {
    for (b = 0; b < words; b++) if (!strcmp(&model->vocabulary[b * max_w], st[a])) break;
    if (b == words) b = 0;
    bi[a] = b;

    if (b == 0) {
      rb_raise(rb_eArgError, "%s: out of dictionary word!", st[a]);
      break;
    }
  }
  float vec[max_size];
  for (a = 0; a < size; a++) vec[a] = model->vectors[a + bi[1] * size] - model->vectors[a + bi[0] * size] + model->vectors[a + bi[2] * size];
  float len = 0;
  for (a = 0; a < size; a++) len += vec[a] * vec[a];
  len = sqrt(len);
  long long c;
  long long d;
  float dist;
  for (a = 0; a < size; a++) vec[a] /= len;
  for (a = 0; a < N; a++) bestd[a] = 0;
  for (a = 0; a < N; a++) bestw[a][0] = 0;
  for (c = 0; c < words; c++) {
    if (c == bi[0]) continue;
    if (c == bi[1]) continue;
    if (c == bi[2]) continue;
    a = 0;
    for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
    if (a == 1) continue;
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
  return N;
}
