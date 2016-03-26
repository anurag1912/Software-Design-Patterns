/*
Works with Standard C++ 11 and 14. Compiler GCC 4.9.2 for C++ (g++)
(www.cpp.sh)
*/
#include<iostream>
#include<vector>
#include<cstdlib>		//to implement srand() and rand()
#include<ctime>			//for random number generation
struct mapping{
	
	/*Data structure that keeps track of which player is the next one to play if multiple positions are assigned*/
	std::vector<unsigned int> positions;
	
};

class Robot{
	/*The interface to the Field class. This class implements the functions that will receive the data that is broadcasted
	by the Field class
	*/
	public:				
	
		void rotate(std::vector<unsigned int> &); //Rotate the players priority such that if an area has multiple players each player will get a chance to play if ball is in the area
		virtual void display(void) = 0;			  //To display the players position
		//virtual void sleep(void) =0;				//Sensor API	
		//virtual void resume(char) = 0;				//Sensor API
		virtual void sensor(unsigned int) = 0;      //Ball's position is broadcasted via this function
		//virtual void play(char) = 0;				//Play function
		virtual void reassign(unsigned int, char, char)=0;	//BROADCAST function that will update internal data structures of all the players if a player is reassigned a new position
		virtual void assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer) =0; //BROADCAST function that allots a player multiple position if a player is down or given a red card.
};


class Field{
	
	/*
	Field class keeps track of ball AND broadcasts the position of the ball to all the observers.
	If there are any changes to the field the changes are also broadcasted via the reassign and assignmultiple functions.
	*/
	private:
		std::vector<Robot *> r;
	public:
		Field(Robot *r0, Robot *r1, Robot *r2, Robot *r3)
		{	//In constructor the vector holds the addresses of the various observers
			r.push_back(r0);
			r.push_back(r1);
			r.push_back(r2);
			r.push_back(r3);
		}
		void simul(void);			//Simulation function that will simulate the entire program.
		
	
};

void Field::simul(void){
srand((int)time(0));			//Function that will generate true random numbers
unsigned int a;
for(int i=0;i<4;i++)
r[i]->display();				//Display initial positions
	for(int i=1;i<=20;i++)
	{
		a=rand()%4;				//Generate random number
	
		if(a==0)
		{
	
		std::cout<<"Ball is in area covered by goalkeeper"<<std::endl;
		}
		else if(a==1)
		{std::cout<<"Ball is in area covered by defender"<<std::endl;
	
		}
		else if(a==2)
		{
		std::cout<<"Ball is in area covered by mid-fielder"<<std::endl;
	
		}
		else{
		std::cout<<"Ball is in area covered by forward"<<std::endl;
	
	}
		
		for(int j=0;j<r.size();j++)
		r[j]->sensor(a);				//Broadcast ball's position to every player/observer
		
		if(i==5)
		{	std::cout<<"Reassigning player 2's position.\nPlayer 2 is now a Forward\n";
		for(int j=0;j<r.size();j++)
		{r[j]->reassign(2,'F','M');			//Player number 2 that was initially midfield is being assigned forward position
		r[j]->display();					//At this point there is no player in midfield position
		}									
		}
		
		if(i==10)
		{	std::cout<<"Reassigning player 3's position.\nPlayer 3 is now a Midfielder\n";
		for(int j=0;j<r.size();j++)
		{r[j]->reassign(3,'M','F');			//Player number 2 that was initially midfield is being assigned forward position
		r[j]->display();					//At this point there is no player in midfield position
		}									
		}
		
		if(i==15)
		{
		std::cout<<"Player 1 is down/given a red card. Assigning player 3 to player 1's position\n";	
		r.erase(r.begin()+1);
		for(int j=0;j<r.size();j++)
		{r[j]->assignmultiple(1, 1, 3);			//Player 1 that was a defender is down and its position is assigned to player 3
		r[j]->display();						//Player 3 is thus a midfielder and defender.
		}
		}
	
	
	
	
	}
	
	
	
	
	
}
/*

The players inherit from the Robot interface and apply their own function definitions.
There are 4 players having their own data structures. I am designing 4 different classes as you might modify the players independent of the other players
For instance only Player0 can have a method that can enable him to perform a particular tackle or a particular move.
*/
class Player0 : public Robot{
	private:
		unsigned int player_no;	
		std::vector<char> positions;	//Keep track of multiple positions
		struct mapping m[4];			//Data structure that maps the positon to the players in that poition
	
	public:
		Player0(char ch){								
			 positions.push_back(ch);
			 player_no = 0;							//Assign unique id to each object instantiated
			 m[0].positions.push_back(0);			//Init data structure
			 m[1].positions.push_back(1);
			 m[2].positions.push_back(2);
			 m[3].positions.push_back(3);
		
		}
	void display(void);					//Display players position
	void sleep(void);					//Sensor API
	void resume(char);					//Sensor API
	void sensor(unsigned int);			//Broadcast function
	void play(char);					
	void reassign(unsigned int no, char fin, char init);  //Broadcast function that will make each player update its own data structure
	void assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer); //Broadcast function that will make each player update its own data structure
};

class Player1 : public Robot{
	private:
		unsigned int player_no;
		std::vector<char> positions;			//Keep track of multiple positions
		struct mapping m[4];					//Data structure that maps the positon to the players in that poition
	
	public:
		Player1(char ch){								
			 positions.push_back(ch);
			 player_no = 1;							//Assign unique id to each object instantiated
			 m[0].positions.push_back(0);
			 m[1].positions.push_back(1);
			 m[2].positions.push_back(2);
			 m[3].positions.push_back(3);
		
		}	
	void display(void);							//Display players position
	void sleep(void);							//Sensor API
	void resume(char);							//Sensor API	
	void sensor(unsigned int);					//Broadcast function
	void play(char);		
	void reassign(unsigned int no, char fin, char init);		////Broadcast function that will make each player update its own data structure
	void assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer);   //Broadcast function that will make each player update its own data structure
};
class Player2 : public Robot{
	
	private:
	unsigned int player_no;
	std::vector<char> positions;
	struct mapping m[4];

	
	public:
	Player2(char ch){								
	positions.push_back(ch);
	player_no = 2;							//Assign unique id to each object instantiated
	m[0].positions.push_back(0);
	m[1].positions.push_back(1);
	m[2].positions.push_back(2);
	m[3].positions.push_back(3);
		
	}	
	void display(void);
	void sleep(void);
	void resume(char);
	void sensor(unsigned int);
	void play(char);	
	void reassign(unsigned int no, char fin, char init);
	void assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer);
};

class Player3: public Robot{
	

	private:
	unsigned int player_no;
	std::vector<char> positions;
	struct mapping m[4];

	
	public:
	Player3(char ch){								
	positions.push_back(ch);
	player_no = 3;							//Assign unique id to each object instantiated
	m[0].positions.push_back(0);
	m[1].positions.push_back(1);
	m[2].positions.push_back(2);
	m[3].positions.push_back(3);
		
	}	
	void display(void);
	void sleep(void);
	void resume(char);
	void sensor(unsigned int);
	void play(char);	
	void reassign(unsigned int no, char fin, char init);
	void assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer);
	
};

void Player0::assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer){
	/*
	This function assigns multiple position if a player is given a red card or is down.
	It takes the player's no. who had been giving a red card or is down and the position it was initially in 
	and assigns the position to another player. The data structure is updated by everyoe when it receives these arguments
	This function implements this logic.	
	*/
	int i=0;
	for(i=0;i<m[initposn].positions.size();i++)
	{
	if(m[initposn].positions[i]==playerno)
	{
		break;
	}
	}
	if(i!=m[initposn].positions.size())
	m[initposn].positions.erase(m[initposn].positions.begin()+i);    //Remove player as it is down
	
	m[initposn].positions.push_back(destplayer);
	if(player_no==destplayer)
	{char ch;
	if(initposn==0)
	ch='G';
	else if(initposn==1)
	ch='D';
	else if(initposn==2)
	ch='M';
	else
	ch='F';
	positions.push_back(ch);				//Assign new player the postion 
}
}

void Player1::assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer){
	/*
	This function assigns multiple position if a player is given a red card or is down.
	It takes the player's no. who had been giving a red card or is down and the position it was initially in 
	and assigns the position to another player. The data structure is updated by everyoe when it receives these arguments
	This function implements this logic.	
	*/
	int i=0;
	for(i=0;i<m[initposn].positions.size();i++)
	{
	if(m[initposn].positions[i]==playerno)
	{
		break;
	}
	}
	if(i!=m[initposn].positions.size())
	m[initposn].positions.erase(m[initposn].positions.begin()+i);				//Remove player as it is down
	
	m[initposn].positions.push_back(destplayer);
	if(player_no==destplayer)
	{char ch;
	if(initposn==0)
	ch='G';
	else if(initposn==1)
	ch='D';
	else if(initposn==2)
	ch='M';
	else
	ch='F';
	positions.push_back(ch);					//Assign new player the postion 
}
}


void Player2::assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer){
	/*
	This function assigns multiple position if a player is given a red card or is down.
	It takes the player's no. who had been giving a red card or is down and the position it was initially in 
	and assigns the position to another player. The data structure is updated by everyoe when it receives these arguments
	This function implements this logic.	
	*/
	int i=0;
	for(i=0;i<m[initposn].positions.size();i++)
	{
	if(m[initposn].positions[i]==playerno)
	{
		break;
	}
	}
	if(i!=m[initposn].positions.size())
	m[initposn].positions.erase(m[initposn].positions.begin()+i);			//Remove player as it is down
	
	m[initposn].positions.push_back(destplayer);
	if(player_no==destplayer)
	{char ch;
	if(initposn==0)
	ch='G';
	else if(initposn==1)
	ch='D';
	else if(initposn==2)
	ch='M';
	else
	ch='F';
	positions.push_back(ch);				//Assign new player the postion 
}
}


void Player3::assignmultiple(unsigned int playerno, unsigned int initposn, unsigned int destplayer){
	/*
	This function assigns multiple position if a player is given a red card or is down.
	It takes the player's no. who had been giving a red card or is down and the position it was initially in 
	and assigns the position to another player. The data structure is updated by everyoe when it receives these arguments
	This function implements this logic.	
	*/
	int i=0;
	for(i=0;i<m[initposn].positions.size();i++)
	{
	if(m[initposn].positions[i]==playerno)
	{
		break;
	}
	}
	if(i!=m[initposn].positions.size())
	m[initposn].positions.erase(m[initposn].positions.begin()+i);		//Remove player as it is down
	
	m[initposn].positions.push_back(destplayer);
	if(player_no==destplayer)
	{char ch;
	if(initposn==0)
	ch='G';
	else if(initposn==1)
	ch='D';
	else if(initposn==2)
	ch='M';
	else
	ch='F';
	positions.push_back(ch);						//Assign new player the postion 
}
}
void Player0::display(void)
{/*
This function displays the positions the player is currently in.
It loops through the position vector and outputs the positions it is currently in.
*/
	std::cout<<"Player # "<<player_no<<" ";
	for(int i=0;i<positions.size();i++)
	{
		if(positions[i]=='G')
		std::cout<<"Goalkeeper ";
		else if(positions[i]=='D')
		std::cout<<"Defender ";
		else if(positions[i]=='M')
		std::cout<<"Midfielder ";
		else
		std::cout<<"Forward ";
	}
	
	std::cout<<std::endl;
}

void Player1::display(void)
{   /*
This function displays the positions the player is currently in.
It loops through the position vector and outputs the positions it is currently in.
*/
	std::cout<<"Player # "<<player_no<<" ";
	for(int i=0;i<positions.size();i++)
	{
		if(positions[i]=='G')
		std::cout<<"Goalkeeper ";
		else if(positions[i]=='D')
		std::cout<<"Defender ";
		else if(positions[i]=='M')
		std::cout<<"Midfielder ";
		else
		std::cout<<"Forward ";
	}
	
	std::cout<<std::endl;
}

void Player2::display(void)
{  /*
This function displays the positions the player is currently in.
It loops through the position vector and outputs the positions it is currently in.
*/
	std::cout<<"Player # "<<player_no<<" ";
	for(int i=0;i<positions.size();i++)
	{
		if(positions[i]=='G')
		std::cout<<"Goalkeeper ";
		else if(positions[i]=='D')
		std::cout<<"Defender ";
		else if(positions[i]=='M')
		std::cout<<"Midfielder ";
		else
		std::cout<<"Forward ";
	}
	
	std::cout<<std::endl;
}
void Player3::display(void)
{   /*
This function displays the positions the player is currently in.
It loops through the position vector and outputs the positions it is currently in.
*/
	std::cout<<"Player # "<<player_no<<" ";
	for(int i=0;i<positions.size();i++)
	{
		if(positions[i]=='G')
		std::cout<<"Goalkeeper ";
		else if(positions[i]=='D')
		std::cout<<"Defender ";
		else if(positions[i]=='M')
		std::cout<<"Midfielder ";
		else
		std::cout<<"Forward ";
	}
	
	std::cout<<std::endl;
}



void Player0::reassign(unsigned int no, char fin, char init){
/*
This function reassigns a player to a new position. A player could be occupying this position and in that case multiple players 
will now occupy this position. This function takes the player no as an argument and its destination position and its old postion.
G=Goalkeeper
D=Defender
M=Midfielder
F=Forward
*/

	if(no==player_no)
	{
	positions.push_back(fin);
	int i=0;
	for(i=0;i<positions.size();i++)
	{
		if(positions[i] == init)
		break;
	}
	if(i!=positions.size())
	positions.erase(positions.begin()+i);
}
	
	
	unsigned int a;
	if(init=='G')
	{a=0;
	int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='D')
	{
		a=1;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='M')
	{
		a=2;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else
	{a=3;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}

	
	
	if(fin=='G')
	{
		a=0;
		m[a].positions.push_back(no);
	}
	else if(fin=='D')
	{
		a=1;
		m[a].positions.push_back(no);
	}
	else if(fin=='M')
	{
		a=2;
		m[a].positions.push_back(no);
	}
	else
	{
		a=3;
		m[a].positions.push_back(no);
		
	}
	
}

void Player1::reassign(unsigned int no, char fin, char init){

/*
This function reassigns a player to a new position. A player could be occupying this position and in that case multiple players 
will now occupy this position. This function takes the player no as an argument and its destination position and its old postion.
G=Goalkeeper
D=Defender
M=Midfielder
F=Forward
*/

	if(no==player_no)
	{
	positions.push_back(fin);
	int i=0;
	for(i=0;i<positions.size();i++)
	{
		if(positions[i] == init)
		break;
	}
	if(i!=positions.size())
	positions.erase(positions.begin()+i);
}
	
	unsigned int a;
	if(init=='G')
	{a=0;
	int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='D')
	{
		a=1;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='M')
	{
		a=2;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else
	{a=3;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}

	
	
	if(fin=='G')
	{
		a=0;
		m[a].positions.push_back(no);
	}
	else if(fin=='D')
	{
		a=1;
		m[a].positions.push_back(no);
	}
	else if(fin=='M')
	{
		a=2;
		m[a].positions.push_back(no);
	}
	else
	{
		a=3;
		m[a].positions.push_back(no);
		
	}
	
}
void Player2::reassign(unsigned int no, char fin, char init){
/*
This function reassigns a player to a new position. A player could be occupying this position and in that case multiple players 
will now occupy this position. This function takes the player no as an argument and its destination position and its old postion.
G=Goalkeeper
D=Defender
M=Midfielder
F=Forward
*/


	if(no==player_no)
	{
	positions.push_back(fin);
	int i=0;
	for(i=0;i<positions.size();i++)
	{
		if(positions[i] == init)
		break;
	}
	if(i!=positions.size())
	positions.erase(positions.begin()+i);
}
	
	
	unsigned int a;
	if(init=='G')
	{a=0;
	int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='D')
	{
		a=1;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='M')
	{
		a=2;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else
	{a=3;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}

	
	
	if(fin=='G')
	{
		a=0;
		m[a].positions.push_back(no);
	}
	else if(fin=='D')
	{
		a=1;
		m[a].positions.push_back(no);
	}
	else if(fin=='M')
	{
		a=2;
		m[a].positions.push_back(no);
	}
	else
	{
		a=3;
		m[a].positions.push_back(no);
		
	}
	
}

void Player3::reassign(unsigned int no, char fin, char init){
/*
This function reassigns a player to a new position. A player could be occupying this position and in that case multiple players 
will now occupy this position. This function takes the player no as an argument and its destination position and its old postion.
G=Goalkeeper
D=Defender
M=Midfielder
F=Forward
*/

	if(no==player_no)
	{
	positions.push_back(fin);
	int i=0;
	for(i=0;i<positions.size();i++)
	{
		if(positions[i] == init)
		break;
	}
	if(i!=positions.size())
	positions.erase(positions.begin()+i);
}
	
	
	unsigned int a;
	if(init=='G')
	{a=0;
	int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='D')
	{
		a=1;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else if(init=='M')
	{
		a=2;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}
	else
	{a=3;
		int i=0;
	for(i=0;i<m[a].positions.size();i++)
	{
	if(m[a].positions[i]==no)
	{
		break;
	}
	}
	if(i!=m[a].positions.size())
	m[a].positions.erase(m[a].positions.begin()+i);
	}

	
	
	if(fin=='G')
	{
		a=0;
		m[a].positions.push_back(no);
	}
	else if(fin=='D')
	{
		a=1;
		m[a].positions.push_back(no);
	}
	else if(fin=='M')
	{
		a=2;
		m[a].positions.push_back(no);
	}
	else
	{
		a=3;
		m[a].positions.push_back(no);
		
	}
	
}

void Player0::sleep(void)
{	/*
	Sensor API that puts sensor to sleep after player plays.
	*/
	std::cout<<"Player # "<<player_no<<"'s sensor in sleep mode!"<<std::endl;
}

void Player1::sleep(void)
{	/*
	Sensor API that puts sensor to sleep after player plays.
	*/
	std::cout<<"Player # "<<player_no<<"'s sensor in sleep mode!"<<std::endl;
}

void Player2::sleep(void)
{	/*
	Sensor API that puts sensor to sleep after player plays.
	*/
	std::cout<<"Player # "<<player_no<<"'s sensor in sleep mode!"<<std::endl;
}

void Player3::sleep(void)
{	/*
	Sensor API that puts sensor to sleep after player plays.
	*/
	std::cout<<"Player # "<<player_no<<"'s sensor in sleep mode!"<<std::endl;
}



void Player0::sensor(unsigned int posn)
{		/*
		This function receives the ball's position from the field and this function only activates the sensor if the 
		ball is found within its postion area.
		*/	

if(m[posn].positions.size()>=1)
	{
	if(m[posn].positions[0]==player_no)
	{char ch;
	if(posn==0)
	ch='G';
	else if(posn==1)
	ch='D';
	else if(posn==2)
	ch='M';
	else
	ch='F';
	resume(ch);				//Activate sensor
	}
	
	rotate(m[posn].positions);			//Cycle through the positions!
}
}

void Player1::sensor(unsigned int posn)
{		/*
		This function receives the ball's position from the field and this function only activates the sensor if the 
		ball is found within its postion area.
		*/		

if(m[posn].positions.size()>=1)
	{
	if(m[posn].positions[0]==player_no)
	{char ch;
	if(posn==0)
	ch='G';
	else if(posn==1)
	ch='D';
	else if(posn==2)
	ch='M';
	else
	ch='F';
	resume(ch);					//Activate sensor
	}
	
	rotate(m[posn].positions);				//Cycle through the positions!
}
}

void Player2::sensor(unsigned int posn)
{	/*
		This function receives the ball's position from the field and this function only activates the sensor if the 
		ball is found within its postion area.
		*/		
	
if(m[posn].positions.size()>=1)
	{
	if(m[posn].positions[0]==player_no)
	{char ch;
	if(posn==0)
	ch='G';
	else if(posn==1)
	ch='D';
	else if(posn==2)
	ch='M';
	else
	ch='F';
	resume(ch);					//Activate sensor
	}
	
	rotate(m[posn].positions);			//Cycle through the positions!
}
}

void Player3::sensor(unsigned int posn)
{		/*
		This function receives the ball's position from the field and this function only activates the sensor if the 
		ball is found within its postion area.
		*/			

if(m[posn].positions.size()>=1)
	{
	if(m[posn].positions[0]==player_no)
	{char ch;
	if(posn==0)
	ch='G';
	else if(posn==1)
	ch='D';
	else if(posn==2)
	ch='M';
	else
	ch='F';
	resume(ch);				//Activate sensor
	}
	
	rotate(m[posn].positions);				//Cycle through the positions!
}
}


void Player0::resume(char ch){
	std::cout<<"Player # "<<player_no<<"'s sensor has detected ball!"<<std::endl;
	play(ch);			//play
}

void Player1::resume(char ch){
	std::cout<<"Player # "<<player_no<<"'s sensor has detected ball!"<<std::endl;
	play(ch);			//play
}

void Player2::resume(char ch){
	std::cout<<"Player # "<<player_no<<"'s sensor has detected ball!"<<std::endl;
	play(ch);			//play
}

void Player3::resume(char ch){
	std::cout<<"Player # "<<player_no<<"'s sensor has detected ball!"<<std::endl;
	play(ch);			//play
}




void Player0::play(char ch)
{
	if(ch=='G')
	std::cout<<"Player # "<<player_no<<" Goalkeeper played!"<<std::endl;
	else if(ch=='D')
	std::cout<<"Player # "<<player_no<<" Defender played!"<<std::endl;
	else if(ch=='M')
	std::cout<<"Player # "<<player_no<<" Midfielder played!"<<std::endl;
	else
	std::cout<<"Player # "<<player_no<<" Forward played!"<<std::endl;
	
	sleep();	//Put sensor to sleep
}

void Player1::play(char ch)
{
	if(ch=='G')
	std::cout<<"Player # "<<player_no<<" Goalkeeper played!"<<std::endl;
	else if(ch=='D')
	std::cout<<"Player # "<<player_no<<" Defender played!"<<std::endl;
	else if(ch=='M')
	std::cout<<"Player # "<<player_no<<" Midfielder played!"<<std::endl;
	else
	std::cout<<"Player # "<<player_no<<" Forward played!"<<std::endl;
	
	sleep();	//Put sensor to sleep
}

void Player2::play(char ch)
{
	if(ch=='G')
	std::cout<<"Player # "<<player_no<<" Goalkeeper played!"<<std::endl;
	else if(ch=='D')
	std::cout<<"Player # "<<player_no<<" Defender played!"<<std::endl;
	else if(ch=='M')
	std::cout<<"Player # "<<player_no<<" Midfielder played!"<<std::endl;
	else
	std::cout<<"Player # "<<player_no<<" Forward played!"<<std::endl;
	
	sleep();	//Put sensor to sleep
}

void Player3::play(char ch)
{
	if(ch=='G')
	std::cout<<"Player # "<<player_no<<" Goalkeeper played!"<<std::endl;
	else if(ch=='D')
	std::cout<<"Player # "<<player_no<<" Defender played!"<<std::endl;
	else if(ch=='M')
	std::cout<<"Player # "<<player_no<<" Midfielder played!"<<std::endl;
	else
	std::cout<<"Player # "<<player_no<<" Forward played!"<<std::endl;
	
	sleep();	//Put sensor to sleep
}

void Robot::rotate(std::vector<unsigned int> &v)
{		/*
		This function cycles through all the positions for a particular area. This function 
		updates the data structure in a distributed manner suuch that everyone knows what is going on the field 
		and whose turn is it to play next!
		*/	
if(v.size()>1)
	{
	
	int temp = v[0];
	for(int i=1;i<v.size();i++)
	{
		v[i-1] = v[i];	
	}
	v[v.size()-1] = temp;
	
}
	
}








int main()
{	Robot *p0 = new Player0('G');		//Initialize 1st player
	Robot *p1 = new Player1('D');		//Initialize 2nd player
	Robot *p2 = new Player2('M');		//Initialize 3rd player
	Robot *p3 = new Player3('F');		//Initialize 4th player
	Field f(p0,p1,p2,p3);				//Construct field
	f.simul();							//Start simulation
	return 0;
}

