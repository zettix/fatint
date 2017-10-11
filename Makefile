# (C) Sean Brennan 2017
# MIT License
ALL: fatint_test

fatint.o: fatint.cc fatint.h
	g++ -c -g -std=c++11 fatint.cc

fatint_test: fatint.o fatint_test.cc
	g++ -g -std=c++11 fatint_test.cc fatint.o -o fatint_test
  
