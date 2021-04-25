#include "common.h"

/*
 * model_deallocate
 * clean model memory
 */
static void model_deallocate(word2vec_model *model) {
  if (model != NULL) {
    if (model->vocabulary != NULL) {
      xfree(model->vocabulary);
    }
    if (model->vectors != NULL) {
      xfree(model->vectors);
    }
    xfree(model);
  }
}

/*
 * model_load
 * load the vectors.bin file from disc
 * @param [String] rb_filename
 */
static VALUE model_load(VALUE mod, VALUE rb_filename) {
  word2vec_model* model = ZALLOC(word2vec_model);
  
  char* filename = StringValueCStr(rb_filename);
  
  word2vec_model_load(model, filename);

  return Data_Wrap_Struct(mod, NULL, model_deallocate, model);
}

/*
 * model vocabulary length
 * @return [Integer]
 */
static VALUE model_word_count(VALUE mod) {
  word2vec_model *model;

  Data_Get_Struct(mod, word2vec_model, model);

  return SIZET2NUM(model->word_count);
}

/*
 * model vector dimensionality
 * @return [Integer]
 */
static VALUE model_vector_dim(VALUE mod) {
  word2vec_model *model;

  Data_Get_Struct(mod, word2vec_model, model);

  return SIZET2NUM(model->vector_dim);
}

/*
 * model find the nearest distance words
 * @param [String] rb_word 
 * @return [Hash<String, Float>]
 */
static VALUE model_distance(VALUE mod, VALUE rb_word) {
  word2vec_model *model;
  Data_Get_Struct(mod, word2vec_model, model);
  char* word = StringValueCStr(rb_word);

  WordSimilarity word_list[N];
  
  size_t word_count = word2vec_model_distance(model, word, word_list);

  VALUE rb_ret = rb_hash_new();
  
  for (size_t i = 0 ; i < word_count ; i++) {
    size_t index = word_list[i].index;
    if (index >= 0) {
      VALUE rb_word = rb_str_freeze(rb_utf8_str_new_cstr(&model->vocabulary[index]));
      VALUE rb_score = DBL2NUM(word_list[i].score);
      rb_hash_aset(rb_ret, rb_word, rb_score);
    }
  }

  return rb_ret;
}

void Init_word2vec(void) {
  VALUE mWord2vec = rb_define_module("Word2vec");
  VALUE mWord2vecModel = rb_define_class_under(mWord2vec, "Model", rb_cObject);
  rb_define_singleton_method(mWord2vecModel, "load", model_load, 1);
  rb_define_method(mWord2vecModel, "word_count", model_word_count, 0);
  rb_define_method(mWord2vecModel, "vector_dim", model_vector_dim, 0);
  rb_define_method(mWord2vecModel, "distance", model_distance, 1);
}