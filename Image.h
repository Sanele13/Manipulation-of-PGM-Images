//Sanele Mpangalala
#ifndef IMAGE_H
#define IMAGE_H
#include <string>
#include <iostream>
#include <memory>

namespace MPNSAN005{
class Image
{
	private:
		int width, height;
		std::unique_ptr<unsigned char[]> data;
 	public:
		std::string fileName;
		Image(); 				//constructor		
		Image(std::string fileName);	
		Image(const Image& rhs);		//Copy Constructor
		Image(Image&& rhs);			//Move constructor
		Image& operator=(const Image& rhs ); 	//Copy assignment operator
		Image& operator=(Image&& rhs);		//Move assignment operator
		~Image();				//Destructor
		
		//read image file
		void loadImage(std::string fileName);
		void saveImage(std::string fileName);

		//operator overloading

		//image addition
		Image operator+(const Image &rhs);
		//image subtraction
		Image operator-(const Image &rhs);
		//mask
		Image operator/(const Image &rhs);
		//invert
		Image operator!();
		//threshold
		Image operator*(const int threshold);
		//comparing images
		bool operator==(const Image rhs);
		//saving image		
		void operator>>(const std::string fileName){
			this->saveImage(fileName);		
		}
		//loading image
		void operator<<(const std::string fileName){
			this->loadImage(fileName);		
		}
		
 	class iterator
 	{
 		private:
 			unsigned char *ptr;
			// construct only via Image class (begin/end)
			friend class Image;
 			iterator(u_char *p) : ptr(p) {}

 		public:
 			//copy construct is public
 			iterator( const iterator & rhs) : ptr(rhs.ptr) {}
		
 			// define overloaded ops: *, ++, --, =
 			iterator & operator=(const iterator & rhs){
				this->ptr = std::move(rhs.ptr);
				return *this;
			}
			bool operator!=(const iterator & rhs){
				return (this->ptr!=rhs.ptr);
			}
			bool operator==(const iterator & rhs){
				return (rhs.ptr==ptr);
			}
			iterator& operator++(){
				++ptr;
				return *this;
			}
			iterator operator++(int parameter){
				iterator oldCopy(*this);
				operator++();
				return oldCopy;
			}
			iterator operator--(){
				if(ptr!=NULL){
					ptr=ptr--;
				}
				return *this;
			}
			iterator operator--(int parameter){
				iterator oldCopy(*this);
				--(*this);
				return oldCopy;
			}
			unsigned char& operator*(){
				return *ptr;
			}
 	};
 	// define begin()/end() to get iterator to start and
 	// "one-past" end.
 	iterator begin(void) const{ return iterator(data.get());}
	iterator end(void) { return iterator(data.get()+(width*height)-1);}
};
}

#endif
