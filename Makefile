# Tinotenda Muzambi
# MZMTIN002

default:
	@g++ -I /Eigen/Dense main.cpp -o pca

main.run: main.o pca.o
	g++ main.run main.o pca.o

clean:
	@rm -f ./pca *.o

run:
	@./pca
