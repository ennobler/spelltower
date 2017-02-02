%.o : %.cc
	g++ -g -c -std=c++11 -O0 $< -o $@

all: test_board test_trie

test_trie: test_trie.o trie.o
	g++ -g -std=c++11 -o test_trie $^

test_board: test_board.o board.o trie.o
	g++ -g -std=c++11 -o test_board $^

clean:
	rm *.o test_trie test_board

