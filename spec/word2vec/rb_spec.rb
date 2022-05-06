require "matrix"

RSpec.describe Word2vec do
  file_name = "./data/minimal.bin"
  train_file = "./data/text7"
  vocab_file = "./data/vocab.txt"
  output_file = "./data/tokenized.bin"

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
    # words.each { |word| p word }
  end
  
  it "check word analogy" do
    model = Word2vec::Model.load(file_name)
    words = model.analogy("from", "that", "international")
    expect(words.count).to eq(7)
    expect(words.first.first).to eq("is")
  end
  
  it "check accuracy" do
    model = Word2vec::Model.load(file_name)
    model.accuracy("./data/questions-words.txt")
    expect(true).to eq(true)
  end
  
  it "build vocab" do
    File.delete(vocab_file) if File.exist?(vocab_file)
    Word2vec::Model.build_vocab(train_file, vocab_file)
    expect(File.exist?(vocab_file)).to eq(true)
  end

  it "tokenizer" do
    File.delete(vocab_file) if File.exist?(vocab_file)
    Word2vec::Model.build_vocab(train_file, vocab_file)
    Word2vec::Model.tokenize(train_file, vocab_file, output_file)
    expect(File.exist?(output_file)).to eq(true)
  end

  it "load vectors" do
    vectors = Word2vec::load_vectors(file_name)
    expect(vectors.count).to eq(66)
    expect(vectors.last.first).to eq("including")
    expect(vectors.last.last).to eq(Vector[0.01026306115090847, 0.00774459820240736, -0.0038772583939135075, -0.015581512823700905, 0.01217040978372097, 0.020333100110292435, -0.02079315111041069, -0.017226409167051315, -0.01868591271340847, -0.013318633660674095, -0.0028945922385901213, 0.000904083251953125, -0.01902465894818306, 0.0044456482864916325, -0.005650329403579235, -0.0072837830521166325, -0.013064575381577015, -0.016217803582549095, -0.02202911302447319, 0.024616241455078125])
  end

  it "load vectors normalized" do
    vectors = Word2vec::load_vectors(file_name, normalize: true)
    expect(vectors.count).to eq(66)
    expect(vectors.last.first).to eq("including")
    expect(vectors.last.last).to eq(Vector[0.15759230123573748, 0.11892056715997408, -0.0595364349678772, -0.23925867989238472, 0.18688019652194574, 0.31222069034967886, -0.31928490781154406, -0.2645165436263346, -0.28692764681963323, -0.20451150948424313, -0.044447309171313176, 0.013882462365662724, -0.29212919418333994, 0.06826422776316728, -0.08676245813571738, -0.11184461594904518, -0.20061037041255825, -0.2490291103192797, -0.33826346395700707, 0.37798957656380405])
  end
end
