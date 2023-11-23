

all := $(shell find ./ -iname "*.cc" -o -iname "*.h")
	
all: install 
	./build/untitled

install:
	-rm -rf ./build
	mkdir -p ./build
	cd ./build && cmake ..  && make

uninstall:
	rm -rf ./build

test: install
	./build/untitled_test

.PHONY: test
dvi:
	open readme.html

dist:
	git archive --format=tar.gz -o CPP4_3DViewer_v2.0-1.tar.gz --prefix=my-repo/ develop

cppcheck: $(all) 
	cppcheck  $^;

format: $(all)
	cp ../materials/linters/.clang-format .
	clang-format -i -style=google $^;
	rm .clang-format

clean: 
	-rm -rf *.o && rm -rf *.gcno
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./test && rm -rf ./cov-report
	-rm -rf ./report/ && rm -rf test.a.* && rm -rf main.a*
	-rm -rf *tar.gz
