RSpec.describe Word2vec do
  file_name = "./data/minimal.bin"

  it "has a version number" do
    expect(Word2vec::VERSION).not_to be nil
  end

  it "does something useful" do
    expect(true).to eq(true)
  end
  
  it 'raises an file not found error' do
    expect { Word2vec::Model.load('invalid.bin') }.to raise_error(ArgumentError, 'file not found')
  end

  it "check file size and words" do
    model = Word2vec::Model.load(file_name)
    expect(model.word_count).to eq(66)
    expect(model.vector_dim).to eq(20)
  end
  
  it "check word distance" do
    model = Word2vec::Model.load(file_name)
    words = model.distance("from")
    expect(words.count).to eq(10)
    expect(words.first.first).to eq("that")
  end
end
