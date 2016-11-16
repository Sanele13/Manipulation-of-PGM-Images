//Sanele Mpangalala

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "Image.h"
namespace MPNSAN005{
MPNSAN005::Image::Image(){
	width=height=0;
	fileName="";
}

MPNSAN005::Image::Image(std::string filename){
	std::cout<<"image creating"<<std::endl;
	this->loadImage(filename);
}

Image::~Image(){
	data = nullptr;
	width=height=0;
}
//Copy constructor
MPNSAN005::Image::Image(const Image& rhs){
	this->fileName = rhs.fileName;
	this->height = rhs.height;
	this->width = rhs.width;
	this->loadImage(this->fileName);
}
//Move constructor
MPNSAN005::Image::Image(Image&& rhs){
	this->fileName = rhs.fileName;
	this->height = rhs.height;
	this->width = rhs.width;
	this->data = std::move(rhs.data);
}
//Copy assignment operator
Image& Image::operator=(const Image& rhs){
	this->height = rhs.height;
	this->width = rhs.width;
	this->loadImage(rhs.fileName);
	return *this;
}
//move assignment operator
Image& Image::operator=(Image&& rhs){
	this->height = rhs.height;
	this->width = rhs.width;
	this->data = std::move(rhs.data);
	return *this;
}
//load and save an image
    void Image::loadImage(std::string file) {
        this->fileName = file;
        std::ifstream img(file, std::ios::binary);
        if (!img.is_open()) {
            std::cout << "File not found" << std::endl;
            exit(0);
        }
        std::string line;
        while (!img.eof()) { //end of file not reached
            getline(img, line);
            if (line.at(0)=='#'|| line.compare("P5")==0) {
                continue;
            } else if (line == "255"){ // the last line of the header information
                break;
            } else {
                std::stringstream ss(line);
                std::string number;
                getline(ss, number, ' ');
		//std::cout<<number<<std::endl;
                width = stoi(number);
                getline(ss, number, ' ');
                height = stoi(number);
            }
        }
	unsigned char* bytes = new unsigned char [width*height];
	img.read((char*) bytes, height*width);
	img.close();
	data = std::unique_ptr<unsigned char []>(bytes);
}

void Image::saveImage(std::string file ){
	std::cout<<"Saving image"<<std::endl;
	std::cout<<this->fileName<<" "<<this->width<<" "<<this->height<<std::endl;
	std::ofstream outputFile(file, std::ios::out|std::ios::binary);
   if(outputFile){
      outputFile<<"P5"<<std::endl;
      outputFile<<"#result"<<std::endl;
      outputFile<< height<<" "<< width<< std::endl;
      outputFile<<"255"<<std::endl;
      std::cout<<width<<" "<<height<<std::endl;
      Image::iterator it = this->begin();
      while(it!=this->end()){
		outputFile.write((char*)&(*it),1);
		it++;
	} 
      
      
    
      outputFile.close();
   }
   else{
      std::cout<<"Unable to open the file"<<std::endl;
   }


     
   
}

//Adding two images
Image Image::operator+(const Image &rhs){
   if(rhs.height != height || rhs.width != width ){
      std::cout<<height<<" "<<rhs.height<<std::endl;
      std::cout<< "Dimensions don't match, so can't add images."<<std::endl;
      return *this;
   }
    Image temp(*this);//copy constructor
   
   Image::iterator beg = temp.begin(), end = temp.end();
   Image::iterator inStart = rhs.begin();
   int sum = (*beg + *inStart);
   while ( beg != end) { 
   	if(sum>255){
		*beg = 255;
	}
	else{
		//std::cout<<*beg<<std::endl;
		*beg = sum;
	} 
   ++beg;
   ++inStart;
   } 
   return temp;  
}
//subtracting two images
Image Image::operator-(const Image& rhs ){
   Image temp(*this);
   if(rhs.height != height || rhs.width != width ){
      std::cout<< "Dimensions don't match!"<<std::endl;
      return *this;
   }
   
   Image::iterator beg = temp.begin(), end = temp.end();
   Image::iterator inStart = rhs.begin();

   while (beg != end) { 
   
      int diff = (*beg - *inStart);
      if(diff < 0){
         diff = 0;
      }  
      *beg = diff; 
      ++beg;
      ++inStart;
   }
   return temp;
}
//Threshold
Image Image::operator*(const int threshold ){

   Image temp(*this);
   Image::iterator beg = temp.begin(), end = temp.end();
   while ( beg != end) {      
      if(*beg>threshold){
         *beg = 255 ;
      }
      else{
         *beg = 0 ;
      }
      ++beg;
   } 
   return temp;
}
//invert
Image Image::operator!(){
   Image temp(*this);
   Image::iterator beg = temp.begin(), end = temp.end();
   while ( beg != end) { 
      *beg = 255 - *beg;
       ++beg;
   } 
   return temp;
}
//mask
Image Image::operator/(const Image& rhs ){
   Image temp(*this);
   if(rhs.height != height || rhs.width != width ){
      std::cout<< "Can't operate on the given args"<< std::endl;
      return *this;
   }
   Image::iterator beg = temp.begin(), end = temp.end();
   Image::iterator inStart = rhs.begin();
   while ( beg != end) { 
      if(!(*inStart==255)){
         *beg = 0;
      }  
   ++beg;
   ++inStart;
   } 
   return temp;
}
}
