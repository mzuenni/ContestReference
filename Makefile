all:
	cd content; latexmk -pdf tcr -output-directory=.. -aux-directory=../build/ -usepretex="\newcommand{\gitorigin}{https://github.com/mzuenni/ContestReference/tree/$(shell git branch --show-current)/content/}"
clean:
	rm -r build/*
