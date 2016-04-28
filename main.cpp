#include<iostream> 
#include<fstream>
#include<math.h>
using namespace std;


class ImaginaryNumber {
	private:	
		float imaginary,real;

	public:
		ImaginaryNumber(float realvalue, float imagvalue){
			imaginary = imagvalue;
			real = realvalue;
		}

		ImaginaryNumber(){
			imaginary=0;
			real = 0;
		}

		ImaginaryNumber operator +(ImaginaryNumber &imaginaryNumber2){
			return ImaginaryNumber(imaginaryNumber2.real+real,imaginaryNumber2.imaginary+imaginary);
		}

		ImaginaryNumber operator *(ImaginaryNumber &imaginaryNumber2){
			float newReal;
			float newImag;
			// (a+jb)*(c+jd) = (a.c - b.d) + j(a.d + b.c)
			newReal = (real*imaginaryNumber2.real - imaginary*imaginaryNumber2.imaginary);
			newImag = (real*imaginaryNumber2.imaginary + imaginary*imaginaryNumber2.real);
			return ImaginaryNumber(newReal,newImag);
		}

		float modulus(void){
			return (imaginary*imaginary*1.0) + (real*real*1.0);

		}

		void display(void){
			cout << real << "+j" <<imaginary << endl;
		}

};


class Queue {
	private:
		struct Node {
			float data;
			Node *next;
		};

		Node *HEAD = NULL;
		Node *TAIL = NULL;

	public:

		Queue(float data){
			Node* node = new Node;
			node->data = data;
			node->next = NULL;
			HEAD = node;
			TAIL = node;
		}

		Queue(){
			Node* node = new Node;
			node->data = 0;
			node->next = NULL;
			HEAD = node;
			TAIL = node;
		}

		void addToQueue(float data){
			Node* node = new Node;
			
			node->data = data;
			node->next = NULL;

			(*TAIL).next = node;
			TAIL = node;

		}

		void display(void){
			Node * current;
			current = HEAD;
			cout << " Value "<< endl;
			while(current!=NULL){
				cout << (*current).data << endl;
				current = (*current).next;
			}
		}

		void printToPPMFile(int maxiter){
			/*ToDo: Restructure this and take this out of this class*/
			ofstream myfile;
			myfile.open("test.ppm");
			myfile << "P3 \n" ;
			myfile << "1032 688 \n 255 255 255 \n";

			int i=0,j=0;

			Node * current;
			current = (*HEAD).next;
		
			while(current!=NULL){

				int depth = ((float((*current).data)/float(maxiter))*16777216.0);

				int blue = depth % 256 ;
				depth = depth / 256;
				int green = depth % 256;
				depth = depth / 256;
				int red = depth % 256;


				myfile << blue << " " << red << " " << green << " \t" ;

				i++;
				if(i%1031==0)
				myfile << " \n";

				current = (*current).next;
			}
			myfile.close();
		}
};

class Mandelbrot:public ImaginaryNumber{
	private:
		const int MAXITER = 6000;
		Queue q;
	public:
		Mandelbrot(){
			float zoom;
			float x,y;
			cout << "Enter the zoom,x,y details"<<endl;
			cin >> zoom >> x >> y ;
			cout << "Calculating" <<endl;
			for(int j=0;j<688;j++){
				for(int i=0;i<1032;i++){
					ImaginaryNumber z(i*((3.0*zoom)/1032.0)-x,y-j*((2.0*zoom)/688.0)); 
					q.addToQueue(checkIfMandelbrot(z));
				}
			}
		}

		float checkIfMandelbrot(ImaginaryNumber c){
			ImaginaryNumber z ;
			int iter;
			for(iter=1; iter<=MAXITER; iter++){	
				 z = (z*z)+c;
				 if(z.modulus()>4.0){ 
				 	z = (z*z)+c;
				 	z = (z*z)+c;
				 	float nsmooth = iter+2 + 1 - log(log(sqrt(z.modulus())))/log(2);
				 	return nsmooth; // This is not a mandelbrot
				 }	
			}

			return 0; //This is a mandelbrot point
		}

		void printImage (void){
			q.printToPPMFile(MAXITER);
		}
};




int main(){	
	Mandelbrot m;
	
	m.printImage();

	return 0;
} 	