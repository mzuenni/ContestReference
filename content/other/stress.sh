for i in {1..1000}; do
	printf "\r$i"
	python3 gen.py > input      # generate test with gen.py
	./a.out < input > out       # execute ./a.out
	./b.out < input > out2      # execute ./b.out
	diff out out2 || break
done
