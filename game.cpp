#include<iostream>
#include<bits/stdc++.h>


#define MAXVAL 2048
#define SIZE 4
using namespace std;


int board[SIZE][SIZE];
int undoboard[SIZE][SIZE];
int temp2[SIZE][SIZE];
int futurearray[4][SIZE][SIZE];
int zerostore[16];

void reset(){

	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			board[i][j]=0;
		}
	}
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			undoboard[i][j]=0;
		}
	}	
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			temp2[i][j]=0;
		}
	}

}
void printboard(int board[SIZE][SIZE]){
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			cout<<board[i][j]<<"\t";
		}
		cout<<endl;
	}
}

void printUI(){
	cout<<"Commands:\n N - New Game\n W - Up\n A - Left\n S - Down\n D - Right\n P - Predict next 4 moves\n U - Undo(only till one move)\n Q - Quit\n";

	printboard(board);

	cout<<"\nEnter command: ";
}
void downshift(int board[SIZE][SIZE]){

	for(int i=0; i<SIZE; i++){
		if(board[0][i]==0 && board[1][i]==0 && board[2][i]==0 && board[3][i]==0){
			//do nothing
		}
		else{
		
		int j=SIZE-1;
		while(j>0){
			if(board[j][i]==0){
				board[j][i]=board[j-1][i];
				board[j-1][i]=0;
			}
			j--;
		}
		
		}
	}

}
void downmerge(int board[SIZE][SIZE]){
	for(int i=0;i<SIZE;i++){
		for(int j=SIZE-1;j>0; j--){
			if(board[j][i]==board[j-1][i]){
				board[j][i]*=2;
				board[j-1][i]=0;
			}
			
		}
	}
}
void rightshift(int board[SIZE][SIZE]){

	for(int i=0; i<SIZE; i++){
		if(board[i][0]==0 && board[i][1]==0 && board[i][2]==0 && board[i][3]==0){
			//do nothing
		}
		else{
		
		int j=SIZE-1;
		while(j>0){
			if(board[i][j]==0){
				board[i][j]=board[i][j-1];
				board[i][j-1]=0;
			}
			j--;
		}
		
		}
	}

}
void rightmerge(int board[SIZE][SIZE]){
	for(int i=0;i<SIZE;i++){
		for(int j=SIZE-1;j>0; j--){
			if(board[i][j]==board[i][j-1]){
				board[i][j]*=2;
				board[i][j-1]=0;
			}
			
		}
	}
}
void leftshift(int board[SIZE][SIZE]){

	for(int i=0; i<SIZE; i++){
		if(board[i][0]==0 && board[i][1]==0 && board[i][2]==0 && board[i][3]==0){
			//do nothing
		}
		else{
		
		int j=0;
		while(j<SIZE-1){
			if(board[i][j]==0){
				board[i][j]=board[i][j+1];
				board[i][j+1]=0;
			}
			j++;
		}
		
		}
	}

}
void leftmerge(int board[SIZE][SIZE]){
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE-1; j++){
			if(board[i][j]==board[i][j+1]){
				board[i][j]*=2;
				board[i][j+1]=0;
			}
			
		}
	}
}
void upshift(int board[SIZE][SIZE]){

	for(int i=0; i<SIZE; i++){
		if(board[0][i]==0 && board[1][i]==0 && board[2][i]==0 && board[3][i]==0){
			//do nothing
		}
		else{
		
		int j=0;
		while(j<SIZE-1){
			if(board[j][i]==0){
				board[j][i]=board[j+1][i];
				board[j+1][i]=0;
			}
			j++;
		}
		
		}
	}
}

void upmerge(int board[SIZE][SIZE]){
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE-1; j++){
			if(board[j][i]==board[j+1][i]){
				board[j][i]*=2;
				board[j+1][i]=0;
			}
			
		}
	}
}

void move(char command, int board[SIZE][SIZE]){

	switch(command){
		case 'a'://left command
		{
			leftshift(board);
			leftshift(board);
			leftmerge(board);
			leftshift(board);
			leftshift(board);
			break;
		}
		case 'd'://right command
		{
			rightshift(board);
			rightshift(board);
			rightmerge(board);
			rightshift(board);
			rightshift(board);
			break;
		}
		case 's'://down command
		{
			downshift(board);
			downshift(board);
			downmerge(board);
			downshift(board);
			downshift(board);
			break;
		}
		case 'w'://up command
		{
			upshift(board);
			upshift(board);
			upmerge(board);
			upshift(board);
			upshift(board);
			break;
		}
	}

}
void undomove(){
	for(int i=0; i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			board[i][j]=undoboard[i][j];
		}
	}
}
void elementchecker(){
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			if(board[i][j]==0){
				zerostore[4*i+j]=1;
			}
			else
				zerostore[4*i+j]=0;
		}
	}
}
void insrandom(){

	int x;
	vector<int> temp;
	for(int i=0; i<16; i++){
		if(zerostore[i]==1){
			temp.push_back(i);
		}
	}
	x=rand()%temp.size();

	int y=rand()%2+1;
	y*=2;//either 2 or 4 gets inserted

	board[temp[x]/4][temp[x]%4]=y;
	zerostore[temp[x]]=0;

}
bool similaritycheck(int temp2[SIZE][SIZE]){
	for(int i=0;i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			if(temp2[i][j]!=board[i][j]){
				return true;
			}
		}
	}
	return false;
}

void storecopyboard(int x[SIZE][SIZE], int y[SIZE][SIZE]){
	for(int i=0; i<SIZE;i++){
		for(int j=0;j<SIZE;j++){
			x[i][j]=y[i][j];
		}
	}
}

bool gameover(){
	int copiedtemp[SIZE][SIZE];


	storecopyboard(copiedtemp,board);
	move('a',copiedtemp);//left move on copy
	storecopyboard(futurearray[1],copiedtemp);

	storecopyboard(copiedtemp,board);
	move('w',copiedtemp);//up move on copy
	storecopyboard(futurearray[2],copiedtemp);	

	storecopyboard(copiedtemp,board);
	move('s',copiedtemp);//down move on copy
	storecopyboard(futurearray[3],copiedtemp);

	storecopyboard(copiedtemp,board);
	move('d',copiedtemp);//right move on copy
	storecopyboard(futurearray[0],copiedtemp);

	if(!similaritycheck(futurearray[0]) && !similaritycheck(futurearray[2]) && !similaritycheck(futurearray[1]) && !similaritycheck(futurearray[3])){
		return true;
	}
	else
		return false;

}
bool maxelementchecker(int board[SIZE][SIZE]){
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(board[i][j]==MAXVAL){
				return true;
			}
		}
	}
	return false;
}

int main(){

	reset();
	elementchecker();
	insrandom();
	storecopyboard(undoboard,board);
	while(true){
		printUI();
		char command;

		cin>>command;
		if(gameover()){
			printboard(board);
			cout<<"Matrix is full, no more moves possible\n";
			break;
		}

		if(command=='n'){
			reset();
			elementchecker();
			insrandom();
			storecopyboard(undoboard,board);
		}
		else if(command=='u'){
			undomove();
		}
		else if(command=='q'){
			cout<<"\nNow exiting\n";
			break;
		}	
		else if(command=='w' || command=='s' || command=='a' || command=='d'){
			storecopyboard(temp2,board);
			storecopyboard(undoboard,board);			

			switch(command){
				case 'w':{
					storecopyboard(board,futurearray[2]);
					break;
				}
				case 'a':{
					storecopyboard(board,futurearray[1]);
					break;
				}
				case 's':{
					storecopyboard(board,futurearray[3]);
					break;
				}
				case 'd':{
					storecopyboard(board,futurearray[0]);
					break;
				}
			}
			if(similaritycheck(temp2)){

				elementchecker();
				insrandom();
			}
	
						
		}
		else if(command=='p'){	
			cout << "Right Move or 'd':\n";
			printboard(futurearray[0]);
			cout << "Left Move or 'a':\n";
			printboard(futurearray[1]);
			cout << "Up Move or 'w':\n";
			printboard(futurearray[2]);
			cout << "Down Move or 's':\n";
			printboard(futurearray[3]);
			cout<<endl;
		}
		else{
			cout<<"\nEnter Valid Input!\n";
		}
		if(maxelementchecker(board)){
			cout<<"\n YOU HAVE WON, THE GAME WILL NOW END !!!\n";
		}

	}
	cout<<"Game Over\n";

	return 0;
}
