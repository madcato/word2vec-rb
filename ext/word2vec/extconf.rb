require "mkmf"

## Check existence of functions before build
# abort "missing malloc()" unless have_func "malloc"
# abort "missing free()"   unless have_func "free"

create_makefile "word2vec/word2vec"