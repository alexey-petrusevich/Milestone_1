.PHONY: test
compile:
	g++ -g -Wall -pedantic -std=c++11 test/test_serialization.cpp -o test/test_serialization
	g++ -g -Wall -pedantic -std=c++11 test/test_sorer.cpp -o test/test_sorer
	
test:
	test/test_serialization
	test/test_sorer
	
clean:
	rm test/test_serialization
	rm test/test_sorer
	