# Tinotenda Muzambi
# MZMTIN002

default:
	@g++ -I /Eigen/Dense main.cpp pca.cpp -o pca

main.run: main.o pca.o
	g++ main.run main.o pca.o
main.o: main.cpp pca.h
	g++ -c -o main.o main.cpp
pca.o: pca.cpp pca.h
	g++ -c -o pca.o pca.cpp

clean:
	@rm -f ./pca *.o

run:
	@./pca
