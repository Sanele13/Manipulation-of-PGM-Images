#Sanele Mpangalala

imageops:  Image.o Driver.o
	g++ -std=c++11 Driver.o Image.o -o imageops
   
Image.o : Image.cpp Image.h
	g++ -std=c++11 -o Image.o -c Image.cpp  
     
Driver.o : Driver.cpp
	g++ -std=c++11 -o Driver.o -c Driver.cpp

tests: unitTest.cpp
	g++ -std=c++11 -o unitTest.o -c unitTest.cpp

clean:
	rm -rf *.o
