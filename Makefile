all: peak

peak:
	g++ -o peak main.cpp -O3 -std=c++17

clean:
	rm -f peak
