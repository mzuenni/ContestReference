all:
	latexmk -pdf tcr
clean:
	latexmk -c tcr
	rm -f *.thm
