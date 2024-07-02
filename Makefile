all:
	cd content; latexmk -pdf tcr -output-directory=.. -aux-directory=../build/
clean:
	rm -r build/*
