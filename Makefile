# (C) Sean Brennan 2017
# MIT License
ALL: fatint_test examples
.PHONY: examples

fatint.o: fatint.cc fatint.h
	g++ -fPIC -c -g -std=c++11 fatint.cc

dynamic/libfatint.so: fatint.o
	gcc -shared fatint.o -o dynamic/libfatint.so

static/libfatint.a: fatint.o
	ar rcs static/libfatint.a fatint.o

fatint_test_dynamic: dynamic/libfatint.so fatint_test.cc
	g++ -g -std=c++11 fatint_test.cc -L dynamic -l fatint -o fatint_test_dynamic

fatint_test_static: static/libfatint.a fatint_test.cc
	g++ -g -std=c++11 fatint_test.cc -L static -l fatint -o fatint_test_static

fatint_test: fatint_test_dynamic fatint_test_static
	@echo OK

examples:
	$(MAKE) -C examples

clean:
	@rm -f fatint.o dynamic/libfatint.so fatint_test_static fatint_test_dynamic static/libfatint.a examples/lehmer_rng
