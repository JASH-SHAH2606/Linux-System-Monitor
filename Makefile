all:
	g++ src/*.cpp -o monitor -std=c++11

clean:
	rm -f monitor
