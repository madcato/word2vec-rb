# word2vec-rb

Gem for using word2vec functionality from https://code.google.com/archive/p/word2vec/


Welcome to your new gem! In this directory, you'll find the files you need to be able to package up your Ruby library into a gem. Put your Ruby code in the file `lib/word2vec`. To experiment with that code, run `bin/console` for an interactive prompt.

This gem was developed using the `.c` files of the Google word2vec as base. Mostly by applying copy-and-paste legendary technique.

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

To find the nearest words, try:

    require 'word2vec'
    
    model = Word2vec::Model.load("./data/minimal.bin")
    words = model.distance("from")
    words.each do |w| 
      puts "#{w.first} #{w.last}"
    end

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

Bug reports and pull requests are welcome on GitHub at https://github.com/madcato/word2vec-rb.
