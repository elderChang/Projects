#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#define Width 40
#define Height 25

using namespace std;

int super_fast = 0;
int super_big = 0;
int growUp = 0;
char movement;

void gotoXY(int x,int y){
	HANDLE consoleoutput;
	COORD cursor_pos = {x,y};
	consoleoutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(consoleoutput,cursor_pos);
}
void replace(int x,int y,char c){
	gotoXY(x,y+1);
	cout<<c;
	gotoXY(x,y-1);
	cout<<c;
	gotoXY(x-1,y);
	cout<<c;
	gotoXY(x-1,y+1);
	cout<<c;
	gotoXY(x-1,y-1);
	cout<<c;
	gotoXY(x+1,y);
	cout<<c;
	gotoXY(x+1,y+1);
	cout<<c;
	gotoXY(x+1,y-1);
	cout<<c;
}

class linkedList;
class UI;

class SnakeBody{
	private:

	public:
		int x;
		int y;
		SnakeBody *next;

		SnakeBody(){
			next = NULL;
			x = Width/2;
			y = Height/2;
		}
		SnakeBody(int X,int Y){
			next = NULL;
			x = X;
			y = Y;
		}

		void Show(){
			gotoXY(x,y);
			if(growUp) cout<<'S';
			else cout<<'s';
			//after eat the big Super food
			if(super_big!=0){
				replace(x,y,'$');
			}
		}
};

class Playground{
	private:
		int width = Width;
		int height = Height;
	public:
		Playground(){
			Build();
		}
		void Build(){
			for(int i=0;i<=width;i++){
				gotoXY(i,0);
				cout<<'-';
				gotoXY(i,height);
				cout<<'-';
			}
			for(int i=0;i<=height;i++){
				gotoXY(0,i);
				cout<<'|';
				gotoXY(width,i);
				cout<<'|';
			}
		}
		void Control(){
			gotoXY((Width-14)/3,3);
			cout<<"Move:  W/A/S/D";
			gotoXY((Width-14)/3,5);
			cout<<"Snake: s";
			gotoXY((Width-14)/3,7);
			cout<<"Food(100 point):  *";
			gotoXY((Width-14)/3,9);
			cout<<"Super Food(500 point):  #/$";
			gotoXY((Width-17)/2,Height-3);
			cout<<"Press Any key Start";
		}
};

class Food{
	private:
		int eaten_food;
		int timer;
		clock_t start;
		clock_t end;
		int superFood;
	public:
		int score;
		int f_x = NULL;
		int f_y = NULL;

		Food(){
			eaten_food = 0;
			score = eaten_food*100;
			gotoXY(Width+2,2);
			cout<<"score: "<<score;
		}
		void produce(){
			if(Width>Height) timer = (Width/5)+1;
			else timer = (Height/5)+1;
			start = clock();

			int temp = (rand()%100)+1;
			if(temp>10&&temp<=20&&score>=1000){
				superFood = 2;
				f_x = (rand()%((int)Width-6))+4;
				f_y = (rand()%((int)Height-6))+4;
				gotoXY(f_x,f_y);
				cout<<'$';
			}
			else{
				f_x = (rand()%((int)Width-1))+1;
				f_y = (rand()%((int)Height-1))+1;
				gotoXY(f_x,f_y);

				if(temp<=10&&score>=1000){
					superFood = 1;
					cout<<'#';
				}
				else{
					superFood = 0;
					cout<<'*';
				}
			}
		}
		void Score(){
			if(superFood==0) eaten_food++;
			else {
				eaten_food+=5;
				if(superFood==1) {
					super_fast = 1;
					gotoXY(Width+2,3+superFood);
					cout<<"Super Fast!";
				}
				if(superFood==2) {
					super_big = 1;
					gotoXY(Width+2,3+superFood);
					cout<<"Super Big!";
				}
			}
			score = eaten_food*100;
			gotoXY(Width+2,2);
			cout<<"score: "<<score;
			//grow up
			if(score>=1000){
				growUp = 1;
				gotoXY(Width+2,3);
				cout<<"Grow up into a big snake";
			}
		}
		//food change place
		void countdown(){
			double duration;
			end = clock();
			duration = (double)(end-start)/CLOCKS_PER_SEC;
			if(duration>=1){
				start = clock();
				timer--;
				if(timer==0){
					gotoXY(f_x,f_y);
					cout<<' ';
					produce();
				}
			}
		}
		int ShowScore(){
			return score;
		}
		void EatFood(linkedList *);
};

class linkedList{
	private:
		SnakeBody *tail;
	public:
		linkedList(){
			tail = NULL;
		}

		void Insert(SnakeBody *newbody){
			if(tail==NULL){
				tail = newbody;
				tail->next = tail;
			}
			else{
				newbody->next = tail->next;
				tail->next = newbody;
			}
			ShowList();
		}

		void ShowList(){
			SnakeBody *q;
			q = tail;
			do{
				q->Show();
				q = q->next;
			}while(q!=tail);
		}

		void Moveto(int x,int y){
			SnakeBody *newhead = new SnakeBody(x,y);
			if(tail!=NULL){
				Insert(newhead);
			}
		}
		void ChangeTail(){
			if(super_big!=0){
				replace(tail->x,tail->y,' ');
			}
			gotoXY(tail->x,tail->y);
			cout<<' ';
			//change tail
			SnakeBody *newtail,*temp;
			newtail = tail;
			do{
				if(newtail->next->next==tail){
					temp = newtail->next;
					tail->x = temp->x;
					tail->y = temp->y;
					newtail->next = tail;
					delete temp;
					break;
				}
				newtail = newtail->next;
			}while(newtail!=tail);
		}
		int FoodPlacement(int X,int Y){
			SnakeBody *q;
			q = tail;
			do{
				if((q->x==X)&&(q->y==Y)) return 1;
				q = q->next;
			}while(q!=tail);
			return 0;
		}
		int Eatself(int X,int Y){
			SnakeBody *q;
			if(tail->next!=tail){
				// q = neck
				q = tail->next->next;
				do{
					if(super_big){
						int bigHead_x = X;
						int bigHead_y = Y;
						switch(movement){
							case 'a':
							case 'A':
								bigHead_x--;
								break;
							case 'd':
							case 'D':
								bigHead_x++;
								break;
							case 'w':
							case 'W':
								bigHead_y--;
								break;
							case 's':
							case 'S':
								bigHead_y++;
								break;
							default:
								break;
						}
						if(((q->x-1)<=bigHead_x&&bigHead_x<=(q->x+1))&&((q->y-1)<=bigHead_y&&bigHead_y<=(q->y+1))) return 0;
					}
					else if((X==q->x)&&(Y==q->y)) return 0;
					q = q->next;
				}while(q!=tail->next);
			}
			return 1;
		}
};

class UI{
	private:
		/*char movement = NULL;*/
		char opposed = NULL;
		int x;
		int y;
		int speed;
		linkedList *list = new linkedList;
	public:
		UI(SnakeBody *head){
			list->Insert(head);
			x = head->x;
			y = head->y;
			speed = 200;
		}
		char whether_pressed_key(){
			if(kbhit()){
				//whether move opposed
				if(opposed==NULL){
					movement = getch();
					opposed = movement;
				}
				else{
					movement = getch();
					switch(movement){
						case 'a':
						case 'A':
							if(opposed=='d'||opposed=='D'){
								movement = opposed;
							}
							break;
						case 'd':
						case 'D':
							if(opposed=='a'||opposed=='A'){
								movement = opposed;
							}
							break;
						case 'w':
						case 'W':
							if(opposed=='s'||opposed=='S'){
								movement = opposed;
							}
							break;
						case 's':
						case 'S':
							if(opposed=='w'||opposed=='W'){
								movement = opposed;
							}
							break;
						default:
							break;
					}
					//big snake turn
					if(super_big){
						switch(opposed){
							case 'a':
							case 'A':
								x--;
								list->Moveto(x,y);
								gotoXY(x-1,y+1);
								cout<<' ';
								gotoXY(x-1,y-1);
								cout<<' ';
								break;
							case 'd':
							case 'D':
								x++;
								list->Moveto(x,y);
								gotoXY(x+1,y-1);
								cout<<' ';
								gotoXY(x+1,y+1);
								cout<<' ';
								break;
							case 'w':
							case 'W':
								y--;
								list->Moveto(x,y);
								gotoXY(x-1,y-1);
								cout<<' ';
								gotoXY(x+1,y-1);
								cout<<' ';
								break;
							case 's':
							case 'S':
								y++;
								list->Moveto(x,y);
								gotoXY(x-1,y+1);
								cout<<' ';
								gotoXY(x+1,y+1);
								cout<<' ';
								break;
							default:
								break;
						}
					}
					opposed = movement;
				}
			}
			return movement;
		}
		int Move(Food *F){
			switch(whether_pressed_key()){
				case 'a':
				case 'A':
					x--;
					list->Moveto(x,y);
					//大蛇三角頭
					if(super_big){
						gotoXY(x-1,y+1);
						cout<<' ';
						gotoXY(x-1,y-1);
						cout<<' ';
					}
					break;
				case 'd':
				case 'D':
					x++;
					list->Moveto(x,y);
					if(super_big){
						gotoXY(x+1,y-1);
						cout<<' ';
						gotoXY(x+1,y+1);
						cout<<' ';
					}
					break;
				case 'w':
				case 'W':
					y--;
					list->Moveto(x,y);
					if(super_big){
						gotoXY(x-1,y-1);
						cout<<' ';
						gotoXY(x+1,y-1);
						cout<<' ';
					}
					break;
				case 's':
				case 'S':
					y++;
					list->Moveto(x,y);
					if(super_big){
						gotoXY(x-1,y+1);
						cout<<' ';
						gotoXY(x+1,y+1);
						cout<<' ';
					}
					break;
				default:
					break;
			}
			// whether eat food
			if(F->f_x==NULL||F->f_y==NULL) F->produce();
			switch(super_big){
				case 0:
					if((x==F->f_x)&&(y==F->f_y)){
						F->EatFood(list);
					}
					else list->ChangeTail();
					break;
				default:
					if((x<=F->f_x+1&&x>=F->f_x-1)&&(y<=F->f_y+1&&y>=F->f_y-1)){
						F->EatFood(list);
					}
					else list->ChangeTail();
					break;
			}
			F->countdown();
			//speeding
			if(super_fast) speed = 25;
			else if(F->score>=400) speed=100;
			else if(F->score>=800) speed=50;
			else if(F->score>=1000) speed=30;
			Sleep(speed);
			// touch wall
			if((x==Width||x==0)||(y==Height||y==0)){
				return 0;
			}
			else if(super_big){
				if((x>=Width-1||x<=1)||(y>=Height-1||y<=1)){
					return 0;
				}
			}
			// touch self
			return list->Eatself(x,y);
		}
};

void Food::EatFood(linkedList *list){
		Score();
		produce();
		// make sure that food won't grow up on snake's body
		while(list->FoodPlacement(f_x,f_y)){
			produce();
		}
}

int main(){
	system("cls");
	srand(time(NULL));
	Playground *P = new Playground();
	// rand initial direction
	if(rand()%4==0) movement = 'a';
	else if(rand()%4==1) movement = 'd';
	else if(rand()%4==2) movement = 'w';
	else movement = 's';
	//start game
	P->Control();
	(void)getch();
	system("cls");
	P->Build();
	//play
	SnakeBody *s = new SnakeBody();
	Food *food = new Food();
	UI *ui = new  UI(s);
	while(ui->Move(food)){
		Sleep(1);
	}
	//end game
	Sleep(3000);
	system("cls");
	P->Build();
	gotoXY((Width-12)/2,Height/3);
	cout<<"Score: "<<food->ShowScore();
	gotoXY((Width-16)/2,Height/2);
	cout<<"U will never win";
	gotoXY((Width-7)/2,Height/2+1);
	cout<<"Looser!";
	(void)getch();
}
