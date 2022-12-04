CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra -g3 
SOURCES=r_polish_notation.c
OBJECTS=$(SOURCES:.c=.o) 
OS = $(shell uname)
TEST_FILE_NAME = tests.c
TEST_RAND_FILE_NAME = tests_rand.c

ifeq ($(OS), Darwin)
	TEST_LIBS=-lcheck
else
	TEST_LIBS=-lcheck -lsubunit -pthread -lrt -lm 
endif

all: clean gcov_report

install: build
	cd s21_calc; make

build: s21_smart_calc.a
	rm -rf s21_calc
	mkdir s21_calc
	cd s21_calc; cmake ../../calc

uninstall:
	rm -rf s21_calc

exec:
ifeq ($(OS), Darwin)
	cd s21_calc/calc.app/Contents/MacOS; ./calc
else
	cd s21_calc; ./calc
endif
	

dist: build
	tar --totals -cvf s21_calc.tar s21_calc

s21_smart_calc.a: clean $(OBJECTS)
	ar -rcs s21_smart_calc.a $(OBJECTS)
	rm -f *.o

tests: $(TEST_FILE_NAME) s21_smart_calc.a
	$(CC) $(CFLAGS) $(TEST_FILE_NAME) $(SOURCES) -o test $(TEST_LIBS) -L. --coverage
	./test

testsrand: $(TEST_RAND_FILE_NAME) s21_smart_calc.a
		$(CC) $(CFLAGS) $(TEST_RAND_FILE_NAME) $(SOURCES) -o test_rand $(TEST_LIBS) -L. --coverage
		sh tests_rand.sh
    # number=1 ; while [[ $$number -le 1000 ]] ; do \
	# 	$(CC) $(CFLAGS) $(TEST_RAND_FILE_NAME) $(SOURCES) -o test_rand $(TEST_LIBS) -L. --coverage ; \
	# 	./test_rand ; \
    # done

lint: 
	sh linter.sh 

gcov_report: tests
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
ifeq ($(OS), Darwin)
	open report/index.html
else
	xdg-open ./report/index.html
endif

dvi:
	cp pics/s21_calc.pdf .
	xdg-open ./s21_calc.pdf

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch *.pdf *.tar rep.info *.html *.css test.info test.dSYM report

# install lcov:
# 	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
# 	brew install lcov

check: tests
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c r_polish_notation.c
	rm -rf CPPLINT.cfg
	make test
ifeq ($(OS), Darwin)
	leaks --atExit -- ./test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
