/*
Works with Standard C++ 11 and 14. Compiler TDM-GCC 4.8.1 64-bit release for C++


Each class's renderShapetoScreen takes the help of the leaf's(i.e. line) renderShapeToScreen to draw an actual figure but to indicate
that an algorithm is running for Triangle, Arrow etc. I have used cout statments to show the printing of figure. 
The explodeShape will return the lines that make up the figure and those individual components too are getting printed after the pseudo figure. 
*/

#include<iostream>


class Shape{
	public:
	virtual void renderShapeToScreen() = 0; // draw this shape on screen 
	virtual Shape ** explodeShape() =0;		// return the list of all basic shapes forming this shape
	//virtual void showbasic(void)=0;
	
};

class Line: public Shape{
	
	/*Leaf class that can be used to compose other staright-line shapes such as triangle, arrow-head, rectangle etc.
	*/
	
	private:	
		int startx;			
		int starty;
		int endx;
		int endy;
		Shape *s[1];
	public:
		Line(int startX, int startY, int endX, int endY)
		{	/*Constructor that initializes the line*/
			startx=startX;
			starty=startY;
			endx=endX;
			endy=endY;
			
		}
		
		void renderShapeToScreen(void);		//Draw single line on screen
		Shape ** explodeShape(void); 		//explode the individual line objects and return them
		//void showbasic(void);						
	
};
void Line::renderShapeToScreen(){
	struct LineDraw{
	int xs;		//start: x
	int xe;		//start: y
	int ys;		//end: x
	int ye;		//end: y

	};
	struct LineDraw ld;
	ld.xs = startx;	//assigning a data structure to draw single line on screen
	ld.xe = endx;
	ld.ys = starty;
	ld.ye = endy;
	struct LineDraw arr[] ={ld
	};	
	
	
	int minx=arr[0].xs;			//get minimum and max co-ordinates to init array for holding line
	int maxx=0;
	int miny=arr[0].ys;
	int maxy=0;
	int row=0;					//how many row and columns is the line
	int column=0;
	for(int i=0;i<1;i++)        //iterate a single time only!
		//----------------------x-------------------------
	{	
		if(arr[i].xs<minx)
		minx = arr[i].xs;
		if(arr[i].xe<minx)
		minx=arr[i].xe;
		if(arr[i].xs>maxx)
		maxx = arr[i].xs;
		if(arr[i].xe>maxx)
		maxx=arr[i].xe;
		//---------------------y--------------------------------
		if(arr[i].ys<miny)
		miny = arr[i].ys;
		if(arr[i].ye<miny)
		miny=arr[i].ye;
		if(arr[i].ys>maxy)
		maxy = arr[i].ys;
		if(arr[i].ye>maxy)
		maxy=arr[i].ye;
	
	
	 row = maxy-miny+1;			//no. of rows
	 column = maxx-minx+1;		//no. of columns
	char frame[row][column];	//init. char array to hold line
	
	for(int i = 0;i<row;i++)
	for(int j=0;j<column;j++)
	{
		frame[i][j]='\0';		//init. to zero
	}
	int temp=0;

	
	
	
	if(arr[i].xs==arr[i].xe)		//if straight line in horizontal direction then,
		{	temp = arr[i].ys>arr[i].ye?arr[i].ys:arr[i].ye;
			arr[i].ys =  arr[i].ys<arr[i].ye?arr[i].ys:arr[i].ye;
			temp = temp-miny;		//position statements to position the drawing of line
			arr[i].ys-=miny;
			arr[i].xs-=minx;
			arr[i].xe=arr[i].xs;
			while(arr[i].ys<=temp)
			{
				frame[arr[i].ys][arr[i].xs]='.';			//store line!
				arr[i].ys++;
			}
			
		}
		else if(arr[i].ys==arr[i].ye)		//else - if straight line in vertical direction then,
		{	
			temp = arr[i].xs>arr[i].xe?arr[i].xs:arr[i].xe;
			arr[i].xs = arr[i].xs<arr[i].xe?arr[i].xs:arr[i].xe;
			temp-=minx;
			arr[i].xs-=minx;	//position statements to position the drawing of line
			arr[i].ys-=miny;
			arr[i].ye = arr[i].ys;
			while(arr[i].xs<=temp)
			{
				frame[arr[i].ys][arr[i].xs]='.';		//store line
				arr[i].xs++;
			}
			
			
		}
		else{				//else line at angle of 45 degrees.
			struct Coord{
				int x;
				int y;		//struct to make decision as to which co-ordinate is the start co-ordinate based on the smallest row number i.e. y
			};
			struct Coord c1, c2, t;
			c1.x = arr[i].xs;		//init.
			c1.y = arr[i].ys;
			c2.x = arr[i].xe;
			c2.y = arr[i].ye;
			
			t = arr[i].ys>arr[i].ye?c1:c2;
			c1 = arr[i].ys<arr[i].ye?c1:c2;			
			
			int sign=1;			//is horizontal direction decreasing or increasing?? Assume it is increasing
			if(c1.x>t.x)		
			sign=-1;			//horizontal direction is decreasing thus as row increases we have to decrease column number every iteration
			t.x-=minx;
			c1.x-=minx;
			t.y-=miny;
			c1.y-=miny;
			arr[i].xs-=minx;
			arr[i].xe-=minx;
			arr[i].ys-=miny;
			arr[i].ys-=miny;
			while(c1.y<=t.y)
			{
				frame[c1.y][c1.x]='.';   //draw!
				c1.x+=sign;				//increase or decrease x co-ordinate based on sign
				c1.y++;
			}
			
		
			
		
		
		}
		
	
	/*
	The statements below will print the entire line as per the co-ordinates defined within the 
	constructor of Line
	*/
	
	for(int i=0;i<=miny;i++)
	std::cout<<std::endl;
	for(int i=0;i<=minx;i++)
	std::cout<<" ";
	for(int i = 0;i<row;i++)
	{
	for(int j=0;j<column;j++)		//print line if cell has '.' character else null gets printed
	{	
		std::cout<<frame[i][j];
	
	}
	std::cout<<std::endl;
		
		{	
			for(int k=0;k<=minx;k++)
			std::cout<<" ";	
		}
	}
}

	
}


Shape ** Line::explodeShape(){
	
s[0]= this;
return s;	
	
}
/*
void Line::showbasic(void)
{
	
	std::cout<<"Start X: "<<startx<<" "<<"Start Y: "<<starty<<" "<<"End X: "<<endx<<" "<<"End Y: "<<endy<<std::endl;
	
	
}

*/
class Triangle: public Shape{

	private:
		Shape *s[3];			//Array to hold individual lines
	public:
		Triangle(void){}
		
		void renderShapeToScreen(); // draw this shape on screen 
		Shape ** explodeShape();		// return the list of all basic shapes forming this shape
		//void showbasic(void);
		void addLines(Shape *, Shape *, Shape *);		//Triangle is made up of three lines

};



void Triangle::renderShapeToScreen(){
	std::cout<<"\nPrinting Triangle: "<<std::endl;
	for(int i=0;i<3;i++)						//Since 3 lines make a triangle
	{
	std::cout<<"\nPrinting line: "<<(i+1)<<std::endl;
	(*(s+i))->renderShapeToScreen();			//Call line's rederShapeToScreen
	}
	std::cout<<"\nEnd of Triangle"<<std::endl;
}


Shape ** Triangle::explodeShape(){
	return s;
}

void Triangle::addLines(Shape *x, Shape *y, Shape *z)
{
	s[0] = x;				//Add lines to array of pointers
	s[1] = y;
	s[2] = z;
}
/*
void Triangle::showbasic(){
	
	
}
*/
class Arrow: public Shape{

	private:
		Shape *s[2];			//Arrow is made up of 2 figures
		Shape *s1[4];
	public:
		Arrow(void){}
		
		void renderShapeToScreen(); // draw this shape on screen 
		Shape ** explodeShape();		// return the list of all basic shapes forming this shape
		void showbasic(void);
		void addLines(Shape *, Shape *);

};

void Arrow::renderShapeToScreen(){
	std::cout<<"\nPrinting Arrow: "<<std::endl;			
	for(int i=0;i<2;i++)						//Since 4 lines make up an Arrow
	{std::cout<<"\nPrinting line: "<<(i+1)<<std::endl;
	(*(s+i))->renderShapeToScreen();			//Draw individual lines by calling line's rendertoscreen function.
	}
	std::cout<<"\nEnd of Arrow"<<std::endl;
	
	}


Shape ** Arrow::explodeShape(){
	return s1;
}

void Arrow::addLines(Shape *w, Shape *x)
{	s[0] = w;			//Store addresses of 2 figures in an array of pointers
	s[1]= x;
	s1[0] = w;
	Shape **ptr = x->explodeShape();
	s1[1] = ptr[0];
	s1[2] = ptr[1];
	s1[3] = ptr[2];
}
/*
void Arrow::showbasic(){
	
	
}
*/

class Rectangle: public Shape{

	private:
		Shape *s[4];				//4 lines make a rectangle
	public:
		Rectangle(void){}
		
		void renderShapeToScreen(); // draw this shape on screen 
		Shape ** explodeShape();		// return the list of all basic shapes forming this shape
		void showbasic(void);
		void addLines(Shape *, Shape *, Shape *, Shape *);

};

void Rectangle::renderShapeToScreen(){
	std::cout<<"\nPrinting Rectangle: "<<std::endl;
	for(int i=0;i<4;i++)						//Since rectangle is made up of 4 lines
	{std::cout<<"\nPrinting line: "<<(i+1)<<std::endl;
	(*(s+i))->renderShapeToScreen();			//Draw individual lines that will make up rectangle
	}
	std::cout<<"\nEnd of Rectangle"<<std::endl;
}


Shape ** Rectangle::explodeShape(){
	return s;
}

void Rectangle::addLines(Shape *w, Shape *x, Shape *y, Shape *z)
{	s[0] = w;
	s[1] = x;
	s[2] = y;			//Store the address of the 4 lines in an array of pointers!
	s[3] = z;
}
/*
void Rectangle::showbasic(){
	
	
}
*/
int main()
{

//Printing Line----------------	
Line l(2,2,10,2);
Shape *ptr = &l;	
std::cout<<"Printing Line "<<std::endl;		
ptr->renderShapeToScreen();						//Print line to screen
Shape **ptr1 = ptr->explodeShape();				//Get individual line component
		
std::cout<<"\nPrinting Individual Line "<<std::endl;		
(*ptr1)->renderShapeToScreen();
//Printing Triangle---------------------------------	
Triangle t;	
ptr= &t;
Line l1(6,2,2,6);
Line l2(2,6,10,6);
Line l3(6,2,10,6);
t.addLines(&l1, &l2, &l3);
ptr->renderShapeToScreen();
ptr1 = ptr->explodeShape();						//Gets the individual components i.e. lines that make up Triangle
std::cout<<"Printing individual lines that make up Triangle\n\n";
for(int i=0;i<3;i++)
(*(ptr1+i))->renderShapeToScreen();				//Printing individual lines that make up the figure

//Printing Arrow----------------------------------

Arrow a;	
Line l4(3,2,8,2);								//Create 4 lines as Arrow is made up of 4 line objects i.e. 1 line and 1 triangle
Line l5(8,1,8,3);	
Line l6(8,1,9,2);
Line l7(8,3,9,2);
Triangle t1;									//Creating triangle object as Arrow is made up of Line + Triangle
t1.addLines(&l5,&l6,&l7);						//Add individual lines to triangle 

ptr = &a;							
a.addLines(&l4,&t1);							//Add address of single horizontal line and triangle to Arrow method 
ptr->renderShapeToScreen();						//Render shape will call the line's render method and Triangle method recursively! 
ptr1 = ptr->explodeShape();						//Gets the individual components i.e. lines and triangle that make up Arrow
std::cout<<"Printing individual lines that make up Arrow\n\n";
for(int i=0;i<4;i++)
{
(*(ptr1+i))->renderShapeToScreen();				//Printing individual lines that make up the figure

}
	
//Printing Rectangle	
Line l8(2,2,2,6);
Line l9(2,6,10,6);
Line l10(10,6,10,2);
Line l11(2,2,10,2);	
Rectangle r;
ptr = &r;
r.addLines(&l8, &l9, &l10, &l11);
ptr->renderShapeToScreen();
ptr1 = ptr->explodeShape();						//Gets the individual components i.e. lines that make up Rectangle
std::cout<<"Printing individual lines that make up Rectangle\n\n";
for(int i=0;i<4;i++)
(*(ptr1+i))->renderShapeToScreen();				//Printing individual lines that make up the figure

	
return 0;
	
	
}
