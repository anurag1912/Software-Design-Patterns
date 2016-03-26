
/*Works with Standard C++ 11 and 14. Compiler GCC 4.9.2 for C++ (g++)
Compile and run with www.cpp.sh
Assumption: Stock market works for 7 hours be it any stock market (NYSE or NASDAQ). I have taken two stock markets: NYSE and NASDAQ
and assume that both of them work for 7 hours from Monday to Friday 0900 to 1600

*/



#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct stockstoexchange{				
	/* This is a data structure maintained to fetch the exchange where the stock is traded.
	This is further encapsulated in a Vector to allow for other stocks and exchanges to be added.
	*/
	string stock;
	string exchange;
};
struct exchangetotimings{
	/* This is a data structure maintained to fetch the working hours of the exchange.
	This is further encapsulated in a Vector to allow for other exchanges to be added in future.
	*/
	string exchange;			    // Name of exchange
	unsigned int start, end;       //start timing; end timing
	
	
};

class Command;					  // Forward declaration

struct stock{
	/* This is a data structure that stores the exchange for the stock request object. This data structure is maintained
	by the invoker.
	*/
	string exchange;			//Name of exchange
	Command *cmd;				//Request encapsulated in object
};

/*------------------------------------------Interface of the Command Pattern-----------------------------------*/
class Command{
	/*Abstract class command that implements the interface for the command pattern*/
	
	public:
	//Pure virtual function to implement dynamic binding and achieve run-time polymorphism and is part of an abstract class.
		virtual void execute() = 0;			
	
	
	
};

/*-------------------------------------------------------------------------------------------------------------*/


/*---------------------------------------Stock Trade-----------------------------------------------------------*/



class StockTrade{
	/*The "Receiver" in command pattern terminology. The interface is as below:*/
	public:
		void buy(string symbol, unsigned long amount) {
        std::cout<<"Buy " <<amount << " " << symbol << " stocks"<<std::endl;	//buy 'x' amount of stocks
    }
   		 void sell(string symbol, unsigned long amount) {
        std::cout<<"Sell " <<amount << " " << symbol << " stocks"<<std::endl;	//sell 'y' amount of stocks
    }
		
	
	
	
};


/*-------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------Buystocks - Concrete command class---------------------------------*/

class Buystocks: public Command{		//Inheriting from abstract class, the virtual function execute()
/* This is a concrete command that encapsulates a specific request from the client and is then passed on to the
"invoker" */ 	
	private:
	StockTrade st;						//Object of receiver.	
	unsigned long no;    				//Number of stock
	string name;						//Name of stock
	public:
	Buystocks(string, unsigned long, StockTrade s);	//Constructor: Takes the name and amount of the stock as an argument and assigns it to the private variables
	void execute();						//Overloaded execute for buying
	
	
};

/*-------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------Sellstocks - Concrete command class--------------------------------*/

class Sellstocks: public Command{
/* This is a concrete command that encapsulates a specific request from the client and is then passed on to the
"invoker" */ 	
	private:
	StockTrade st;						//Object of receiver.
	unsigned long no;					//Number of stock
	string name;						//Name of stock
	public:
	
	Sellstocks(string, unsigned long, StockTrade s);	//Constructor: Takes the name and amount of the stock as an argument and assigns it to the private variables
	void execute();						//Overloaded execute for selling
	
	
};

/*-------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Broker--------------------------------------------------------*/

class Broker{
/* Broker acts as the invoker which takes the request encapslated as an object and executes it. The Agent encapsulates
the request.
*/	
	private:
		vector<stock> orders;                  //Data structure to store requests if market is closed or hours are beyond the working hours for the request to be executed.
		vector<exchangetotimings> v;		   //Data structure that maps the stock exchange to its hours of operation.	
		
	public:
	Broker(void);								//Constructor that initializes the data structure vector<exchangetotimings>
	
	void executeorder(struct stock,long,int);	//execute function!
	
	
	
};
Broker::Broker(void){
/*Initializes struct of exchangetotimings and adds to the vector the exchange and its start and end hour*/
struct exchangetotimings etot;					
etot.exchange="NYSE";
etot.start= 900;
etot.end=1600;
v.push_back(etot);
etot.exchange="NASDAQ";
etot.start= 900;
etot.end=1600;
v.push_back(etot);
		
}
void Broker::executeorder(struct stock s,long hour,int day)
{/* Execute order based on day and time. If day falls out of the working days do not execute irrespective of the timing,
else if day falls in the range from Monday...Friday, check the hour when the request was received, if within the working
hours of the stock market execute! else store in data structure for processing it later.
*/
int start,end;
start=end=0;
for(int i=0; i<v.size();i++)
{	/*What are the start and end hours of the stock market?*/
	if(v[i].exchange==s.exchange)
	{
		start = v[i].start;
		end = v[i].end;
		
		break;
	}
	
}

if(day<3)
{	//if day is saturday or sunday do not execute.
cout<<s.exchange<<" closed on Saturday and Sunday. Order stored for processing the next business day!"<<endl;
orders.push_back(s);
}
else if(hour<start || hour>end)
{
cout<<s.exchange<<" closed for now. Order stored for processing the next business day!"<<endl;
orders.push_back(s);
}
else
{
if (orders.size()!=0)
cout<<"Processing all orders...!"<<endl;
orders.push_back(s);
for(int i=0;i<orders.size();i++)
{
cout<<orders[i].exchange<<":  ";			//which exchange the stock is traded at
orders[i].cmd->execute();					//execute the derived class execute using the base class pointer.
delete orders[i].cmd;						//delete from the heap.
}
orders.clear();								//clear data structure 
}		
	
}

/*-------------------------------------------------------------------------------------------------------------*/



/*------------------------------------------------------Agent---------------------------------------------------------------*/
/*
The Agent class is the actual "Client" in the command pattern. It accepts the order from the user and does some
processing and packages the request as an object. 
*/


class Agent{
	
private:
Buystocks *bs;			//The concrete object buystocks
Sellstocks *ss;			//The concrete object sellstocks
string name;			//name of stock
unsigned long no;		//amount of stock
vector<stockstoexchange> v;		//which exchange the stock is traded at
public:
string getSE(void);				//get the exchange where stock is traded in a string
Agent();
void buy(string, unsigned long, StockTrade);		//request to buy
void sell(string, unsigned long, StockTrade);		//request to sell
	
Command * address_of_request(void)		//This function returns address of request object after receiving request from client.
{	if(bs!=NULL)                       //Send the address to buy stock or sell stock one at a time. The logic below does that.
	{
	Command *temp = bs;
	bs=NULL;
	return temp;
	
}
	else 
	{
	Command *temp = ss;
	ss=NULL;
	return temp;
	
}
}
struct stock request(void){
/*	This data structure binds the stock exchange and the requestor object in one struct and passes it on to the invoker i.e.
the Broker.
*/
	struct stock s;
	s.exchange=getSE();
	s.cmd = address_of_request(); 
	return s;}
};
/*--------------------------------------------------------------------------------*/




Buystocks::Buystocks(string name, unsigned long no,StockTrade s)
{	st=s;
	this->name=name;				//Buy stock of name "name"
	this->no=no;					//The amount to buy
}
Sellstocks::Sellstocks(string name, unsigned long no, StockTrade s)
{	st=s;
	this->name=name;				//Sell stock of name "name"
	this->no=no;					//The amount to sell
}
void Buystocks::execute(){
	
	st.buy(name, no);				//Call to stocktrade for buying
}

void Sellstocks::execute(){
	
	st.sell(name, no);				//Call to stocktrade for selling
}
Agent::Agent(){
	bs=NULL;						//Set buystock pointer to null
	ss=NULL;						//Set sellstock pointer to null
	/*Initialize & map the stock with the appropriate exchange
	*/
	stockstoexchange s;				
	s.exchange="NYSE";
	s.stock="Google";
	v.push_back(s);
	s.stock="Microsoft";
	v.push_back(s);
	s.exchange="NASDAQ";
	s.stock="Yahoo";
	v.push_back(s);
}
string Agent::getSE(void){
	/*Return the exchange where the stock is traded!
	*/
	int i=0;
	for(i=0;i<v.size();i++)
	{	if(v[i].stock==name)
		return v[i].exchange;
	}
	if(i==v.size())
	{
		return "NASDAQ";
	}
	
}
void Agent::buy(string name, unsigned long no, StockTrade s){
	 bs = new Buystocks(name, no, s);				//Construct object of type Buystocks from heap and assign to bs
	 this->name=name;
	 this->no=no;
	
}
void Agent::sell(string name, unsigned long no, StockTrade s){
	 ss = new Sellstocks(name, no,s);			//Construct object of type Sellstocks from heap and assign to ss
	 this->name=name;
	 this->no=no;
	}
int main(){
	/*
	This simulation covers the weekends when the markets are closed and it covers the cases where the order is placed
	before or after the working hours of the stock market. The simulation covers an entire week where many stocks which
	were queued in the data structure when the markets were closed are executed during the normal hours of operation
	AND it covers the cases where the requests were placed within the normal hours of operation.
	*/
/* 1 = Saturday, 2= Sunday, 3= Monday, 4 = Tuesday, 5= Wednesday, 6 = Thursday, 7 = Friday */	
	Agent ag;					//Agent object that receives request from client and encapsulates that request in object and passes it on to the Invoker.
	Broker b;					//The Broker acts as the Invoker which "executes" the instruction in the object that Agent passes
	StockTrade st;				//Create receiver
	long hour=800;				//The hour in 24 hour format.
	for(int i=1;i<=7;i++){		//Loop 7 times for the 7 days of the week.
		cout<<"\n\n";
								//Display the days of the week, starting from Saturday.	
	switch(i){
		case 1:
			cout<<"\t\tSaturday\n"<<endl;
			break;
		case 2:
			cout<<"\t\tSunday\n"<<endl;
			break;
		case 3:
			cout<<"\t\tMonday\n"<<endl;
			break;
		case 4:
			cout<<"\t\tTuesday\n"<<endl;
			break;
		case 5:
			cout<<"\t\tWednesday\n"<<endl;
			break;
		case 6:
			cout<<"\t\tThursday\n"<<endl;
			break;
		case 7:
			cout<<"\t\tFriday\n"<<endl;
			break;
	}
	hour=800; //8:00 AM			//Beginning of day when the client places order to agent irrespective of the hour of the market  
	
	ag.buy("Google", 35,st);							//Buy Google shares from some market, amount: 35
	b.executeorder(ag.request(),hour,i);			//Agent makes a request and sends it as a object to the Invoker
	hour+=200;										//10:00 AM - Beginning of trade
	ag.sell("Google", 25,st);							//Sell!
	b.executeorder(ag.request(),hour,i);			
	hour+=200;										//12:00 PM
	ag.buy("Microsoft", 55,st);						//Buy Microsoft shares from some market, amount: 55
	b.executeorder(ag.request(),hour, i);
	hour+=200;										//2:00 PM
	ag.sell("Microsoft", 75,st);						
	b.executeorder(ag.request(),hour,i);
	hour+=200;										//4:00 PM - closing, last trade...!
	ag.buy("Yahoo", 105,st);
	b.executeorder(ag.request(),hour,i);
	hour+=200;										//6:00 PM - beyond trading hours!
	ag.sell("Yahoo", 110,st);
	b.executeorder(ag.request(),hour,i);			//Agent encapsulates request in object and sends it to Invoker (Broker)	

	}
	return 0;
}
