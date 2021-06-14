require_relative 'lib/word2vec/version'

Gem::Specification.new do |spec|
  spec.name          = "word2vec-rb"
  spec.version       = Word2vec::VERSION
  spec.authors       = ["Dani Vela"]
  spec.email         = ["veladan@me.com"]

  spec.summary       = %q{Ruby interface to use word2vec arithmetic.}
  spec.description   = %q{To use this gem is required the file`vectors.bin` where is stored the output of the Google algorithm called `word2vec`. This gem doesn't produce this file. Once produced, this can can load it and use it to calculate some arithmetic operations like distance between words or to calculate the relations between them.'}
  spec.homepage      = "https://github.com/madcato/word2vec-rb"
  spec.required_ruby_version = Gem::Requirement.new(">= 2.7.1")

  spec.metadata["homepage_uri"] = spec.homepage
  spec.metadata["source_code_uri"] = "https://github.com/madcato/word2vec-rb"
  spec.metadata["changelog_uri"] = "http://github.com/macato/word2vec-rb/CHANGELOG"

  # Specify which files should be added to the gem when it is released.
  # The `git ls-files -z` loads the files in the RubyGem that have been added into git.
  spec.files         = Dir.chdir(File.expand_path('..', __FILE__)) do
    `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.license       = 'MIT'
  
  spec.extensions = %w[ext/word2vec/extconf.rb]
  
  spec.add_development_dependency "bundler", "~> 2.1.0"
  spec.add_development_dependency "rake", "~> 12.0"
  spec.add_development_dependency "rake-compiler", "~> 1.0"
  spec.add_development_dependency "rspec", "~> 3.0"
end
