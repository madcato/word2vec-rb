#include "common.h"

// Output the analog accuracy of the model 
void word2vec_model_accuracy(word2vec_model* model, char* file_name) {
  FILE *f;
  char st1[max_size], st2[max_size], st3[max_size], st4[max_size], bestw[N][max_size];
  float dist, bestd[N], vec[max_size];
  long long aa, b, c, d, b1, b2, b3;
  unsigned long a;
  int TCN, CCN = 0, TACN = 0, CACN = 0, SECN = 0, SYCN = 0, SEAC = 0, SYAC = 0, QID = 0, TQ = 0, TQS = 0;
  TCN = 0;

  f = fopen(file_name, "r");
  if (f == NULL) {
    rb_raise(rb_eArgError, "Input file not found: %s", file_name);
    return;
  }
  long long words = model->word_count;
  long long size = model->vector_dim;
  
  while (1) {
    for (aa = 0; aa < N; aa++) bestd[aa] = 0;
    for (aa = 0; aa < N; aa++) bestw[aa][0] = 0;
    fscanf(f, "%s", st1);
    for (a = 0; a < strlen(st1); a++) st1[a] = tolower(st1[a]);
    if ((!strcmp(st1, ":")) || feof(f)) {
      if (TCN == 0) TCN = 1;
      if (QID != 0) {
        printf("ACCURACY TOP1: %.2f %%  (%d / %d)\n", CCN / (float)TCN * 100, CCN, TCN);
        printf("Total accuracy: %.2f %%   Semantic accuracy: %.2f %%   Syntactic accuracy: %.2f %% \n", CACN / (float)TACN * 100, SEAC / (float)SECN * 100, SYAC / (float)SYCN * 100);
      }
      QID++;
      fscanf(f, "%s", st1);
      if (feof(f)) break;
      printf("%s:\n", st1);
      TCN = 0;
      CCN = 0;
      continue;
    }
    fscanf(f, "%s", st2);
    for (a = 0; a < strlen(st2); a++) st2[a] = tolower(st2[a]);
    fscanf(f, "%s", st3);
    for (a = 0; a<strlen(st3); a++) st3[a] = tolower(st3[a]);
    fscanf(f, "%s", st4);
    for (a = 0; a < strlen(st4); a++) st4[a] = tolower(st4[a]);
    for (b = 0; b < words; b++) if (!strcmp(&model->vocabulary[b * max_w], st1)) break;
    b1 = b;
    for (b = 0; b < words; b++) if (!strcmp(&model->vocabulary[b * max_w], st2)) break;
    b2 = b;
    for (b = 0; b < words; b++) if (!strcmp(&model->vocabulary[b * max_w], st3)) break;
    b3 = b;
    for (aa = 0; aa < N; aa++) bestd[aa] = 0;
    for (aa = 0; aa < N; aa++) bestw[aa][0] = 0;
    TQ++;
    if (b1 == words) continue;
    if (b2 == words) continue;
    if (b3 == words) continue;
    for (b = 0; b < words; b++) if (!strcmp(&model->vocabulary[b * max_w], st4)) break;
    if (b == words) continue;
    for (aa = 0; aa < size; aa++) vec[aa] = (model->vectors[aa + b2 * size] - model->vectors[aa + b1 * size]) + model->vectors[aa + b3 * size];
    TQS++;
    for (c = 0; c < words; c++) {
      if (c == b1) continue;
      if (c == b2) continue;
      if (c == b3) continue;
      dist = 0;
      for (aa = 0; aa < size; aa++) dist += vec[aa] * model->vectors[aa + c * size];
      for (aa = 0; aa < N; aa++) {
        if (dist > bestd[aa]) {
          for (d = N - 1; d > aa; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[aa] = dist;
          strcpy(bestw[aa], &model->vocabulary[c * max_w]);
          break;
        }
      }
    }
    if (!strcmp(st4, bestw[0])) {
      CCN++;
      CACN++;
      if (QID <= 5) SEAC++; else SYAC++;
    }
    if (QID <= 5) SECN++; else SYCN++;
    TCN++;
    TACN++;
  }
  printf("Questions seen / total: %d %d   %.2f %% \n", TQS, TQ, TQS/(float)TQ*100);
  return;
}
