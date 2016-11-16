//Sanele Mpangalala

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Image.h"
using namespace MPNSAN005;
using namespace std;
int main(int argc, char** argv){
    if (argc < 2) {
        cout << "Too few arguments." << endl;
        return 0;
    }
    
    if (string(argv[1]).compare("-a")==0){
    	std::string image1 = argv[2];
    	Image A(image1);
    	std::string image2 = argv[3];
    	Image B(image2);
	Image output = A + B;//Addition
	output.saveImage("addition.pgm");
    }else if (string(argv[1]).compare("-s")==0){ 
    	std::string image1 = argv[2];
    	Image A(image1);
    	std::string image2 = argv[3];
    	Image B(image2);
	Image output = A - B;//Subtraction
	output.saveImage("subtraction.pgm");
    }else if (string(argv[1]).compare("-i")==0){ 
    	std::string image1 = argv[2];
    	Image A(image1);
        Image output = !A; //Inversion
	output.saveImage("inverted.pgm");
    }else if(string(argv[1]).compare("-l")==0){
    	std::string image1 = argv[2];
    	Image A(image1);
    	std::string image2 = argv[3];
    	Image B(image2);
        Image output = A/B; //Mask
	output.saveImage("maskOutput.pgm");
    }else if(string(argv[1]).compare("-t")==0) { // Threshold
	std::string image1 = argv[2];
	Image A(image1);
        int threshold = std::stoi(argv[3]);
        Image output = A*threshold;
	output.saveImage("thresholdOutput.pgm");
    }else{
        cout << "Incorrect command"<<endl;
        return 0;
    }
    return 0;
}
