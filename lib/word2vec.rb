require "word2vec/version"

module Word2vec
  class Error < StandardError; end
  # Your code goes here...
  
  class Hola
    # Say hi to the world!
    #
    # Example:
    #   >> Hola.hi("spanish")
    #   => hola mundo
    #
    # Arguments:
    #   language: (String)
    def self.hi(language = "english")
      translator = Translator.new(language)
      puts translator.hi
    end
  end
end

require "word2vec/word2vec"