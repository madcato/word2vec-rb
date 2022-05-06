# word2vec-rb

Gem using word2vec functionality from https://code.google.com/archive/p/word2vec/

This gem was developed using the `.c` files of the Google word2vec as base. Mostly by applying copy-and-paste.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'word2vec-rb'
```

And then execute:

    $ bundle install

Or install it yourself as:

    $ gem install word2vec-rb

## Usage

### Distance arithmetic: to find the nearest words, try:

```ruby
require 'word2vec'

model = Word2vec::Model.load("./data/minimal.bin")
words = model.distance("from")
words.each do |w| 
  puts "#{w.first} #{w.last}"
end
```

### Analogy arithmetic: to find the analogy with three words, try:

```ruby
require 'word2vec'

model = Word2vec::Model.load("./data/minimal.bin")
words = model.analogy("spain", "madrid", "france")
# In a well prepared vectors file (high quality), first word would be "Paris"
words.each do |w| 
  puts "#{w.first} #{w.last}"
end
```

### Accuray: test accuracy of the vectors:

Define a file with the analogies to test, format:
: section heading
Word1 Word2 Word3 Word4

Sample:

    : capital-common-countries
    Athens Greece Baghdad Iraq
    Athens Greece Bangkok Thailand

```ruby
require 'word2vec'

model = Word2vec::Model.load(file_name)
model.accuracy("./data/questions-words.txt")

# Outputs the results on terminal
```

### Vocabulary: create a vocabulary file from a train file:

```ruby
require 'word2vec'

Word2vec::Model.build\_vocab("./data/text7", "./data/vocab.txt")
```

The output file will have a list of words and its number of appearances separated by line break.

### Tokenizer: create a binary file by tokenizing an input file

This method requires a vocabulary file precreated.

```ruby
require 'word2vec'

Word2vec::Model.tokenize("./data/text7", "./data/vocab.txt", "./data/tokenized.bin")
```

The output file will contain a sequence of binary identificators of each word of the input file.

Read output file with:

    long long id;
    fread(&id, sizeof(id), 1, fi);

### Load the **word2vec** output bin file (*vectors.bin*), into ruby array

```ruby
require 'word2vec'

vector_array = Word2vec::load_vectors("./data/minimal.bin")
```

The `vector_array` variable will contain an array of pairs with the vocab and the vector the float values of each word.

Set parameter `normalize: true` to normalize the vectors.

```ruby
require 'word2vec'

vector_array = Word2vec::Model.load_vectors("./data/minimal.bin", normalize: true)
```

## Development

After checking out the repo, run `bin/setup` to install dependencies. Then, run `rake spec` to run the tests. You can also run `bin/console` for an interactive prompt that will allow you to experiment.

To install this gem onto your local machine, run `bundle exec rake install`. To release a new version, update the version number in `version.rb`, and then run `bundle exec rake release`, which will create a git tag for the version, push git commits and tags, and push the `.gem` file to [rubygems.org](https://rubygems.org).

### Build extension 

    $ rake build

### Launch tests

    $ rake spec

### Build extension 

    $ rake compile

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/madcato/word2vec-rb
