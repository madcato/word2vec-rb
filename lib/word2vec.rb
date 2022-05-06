require "word2vec/version"
require "matrix"

module Word2vec
  class Error < StandardError; end
  # Your code goes here...
  
  def self.load_vectors(binary_file_path, normalize = false)
    raise Error, "File not found: #{binary_file_path}" unless File.exists?(binary_file_path)
    
    first_line = File.open(binary_file_path, &:readline)
    values = first_line.scan(/\w+/)
    words = values[0].to_i
    size = values[1].to_i

    float_size = 4

    result = []

    File.open(binary_file_path, "rb") do |file|
      header = file.read(first_line.size)  # words size

      until words == 0
        vocab = ""
        loop do
          c = file.read(1)
          break if c == ' '
          vocab << c  
        end

        vector = file.read(size * float_size).unpack("f*")
        vector = Vector.elements(vector)

        if normalize
          vector = vector.normalize
        end

        file.read(1)  # \n
        words -= 1

        result << [vocab, vector]
      end
    end

    return result
  end
end

require "word2vec/word2vec"