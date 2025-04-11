#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
using namespace std;
void gotoxy(int tx, int ty){
    COORD pos = {tx,ty};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}
void HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
class DieReset{
	protected:
		static int mobdoor[5];
	public:
		DieReset(){
			
		}
};
int DieReset::mobdoor[5]={0};
class Timer{//for Buff
    protected:
    double timer;
    double Duration;
    clock_t Start;
    clock_t end;
    public:
    Timer(double n){// duration time
        timer = n;
    }
    void StartCount(){
        Start = clock();
    }
    int Countdown(){
        end = clock();
        Duration = (double)(end - Start)/CLOCKS_PER_SEC;
        if(Duration>=timer) return 1;
        else return 0;
    }
    void End(){
        delete this;
    }
};
class Object{
    private:
        Object  *next;
    protected:
        clock_t start,finish;
        static int player_x,player_y;
        static int m[62][42];
        int DoorX,DoorY;
        static int Buff_F,Buff_S,Buff_B,Buff_T;
        static int score_all;
        static int gameend;
    public:
      double during(){
                finish=clock();
                double duration=(double)(finish-start)/CLOCKS_PER_SEC;
                return duration;
    }
    virtual void Move(){
        cout<<" ";
    }
    void Nextset(Object *n){
        next=n;
    }
    Object* Returnnext(){
        return next;
    }
    virtual ~Object(){}
    virtual void Die(){}//For Buff_B
    static void ResetBuff_B(){
        Buff_B = 0;
    }
    static int return_Buff_B(){
        return Buff_B;
    }
  void GameOver(){
            if(gameend==1){
                    gameend=0;
	        int s=0;    //用sc-s可以讓螢幕從下往上
	        int sc=30; //讓畫面從下開始
	        for(int i;i<100;i++){
	            if(sc-s!=0) system("cls");
	            if(sc-s==0) break;
	            if(sc-s<30){
	                gotoxy(20,sc-s);
	                cout<<" ****      *     *******  ***** "<<endl;
	            }
	            if(sc+1-s<30){
	                gotoxy(20,sc+1-s);
	                cout<<"*         * *    *  *  *  *     "<<endl;
	            }
	            if(sc+2-s<30){
	                gotoxy(20,sc+2-s);
	                cout<<"*  ***   *****   *  *  *  ***** "<<endl;
	            }
	            if(sc+3-s<30){
	                gotoxy(20,sc+3-s);
	                 cout<<"*   **  *     *  *  *  *  *     "<<endl;
	            }
	            if(sc+4-s<30){
	                gotoxy(20,sc+4-s);
	                cout<<" *** * *       * *  *  *  ***** "<<endl;
	            }
	            if(sc+5-s<30){
	                gotoxy(20,sc+5-s);
	                cout<<"                                "<<endl;
	            }
	            if(sc+6-s<30){
	                gotoxy(20,sc+6-s);
	                cout<<"                          "<<endl;
	            }
	            if(sc+7-s<30){
	                gotoxy(20,sc+7-s);
	                cout<<"   ****** *       * ***** *  **   "<<endl;
	            }
	            if(sc+8-s<30){
	                gotoxy(20,sc+8-s);
	                cout<<"   *    *  *     *  *   * * *     "<<endl;
	            }
	            if(sc+9-s<30){
	                gotoxy(20,sc+9-s);
	                cout<<"   *    *   *   *   ***** **      "<<endl;
	            }
	            if(sc+10-s<30){
	                gotoxy(20,sc+10-s);
	                cout<<"   *    *    * *    *     *       "<<endl;
	            }
	            if(sc+11-s<30){
	                gotoxy(20,sc+11-s);
	                 cout<<"   ******     *     ***** *       "<<endl;
	            }
	            if(sc+12-s<30){
	                gotoxy(20,sc+12-s);
	                cout<<"                                  "<<endl;
	            }
	             if(sc+13-s<30){
	                gotoxy(20,sc+13-s);
	                cout<<"最終得分:"<<score_all<<endl;
	            }
	             if(sc+14-s<30){
	                gotoxy(20,sc+14-s);
	                cout<<"製作人名單:"<<endl;
	            }
	             if(sc+15-s<30){
	                gotoxy(20,sc+15-s);
	                cout<<"蘇柏修:人類，Monster1，傳送門 ，結尾動畫"<<endl;
	            }
	             if(sc+16-s<30){
	                gotoxy(20,sc+16-s);
	                cout<<"胡詠堯:Monster2，Linkedlist，後面整合，炸彈"<<endl;
	            }
	             if(sc+17-s<30){
	                gotoxy(20,sc+17-s);
	                cout<<"張庭碩:人類，Monster3，linklist，buff"<<endl;
	            }
	             if(sc+18-s<30){
	                gotoxy(20,sc+18-s);
	                cout<<"廖祐麟:人類，Monster4，開場動畫，得分系統"<<endl;
	            }
	             if(sc+19-s<30){
	                gotoxy(20,sc+19-s);
	                cout<<"李承勳:人類，Monster5，生成障礙物，buff，UI，遊戲介面"<<endl;
	            }
	            sc--;
	            _sleep(100);
	        }
	        if(sc-s==0) {
                    _sleep(5000);
                    return;}    //讓程式停止,不然會變成跑馬燈
            }
	    }
};
int Object::gameend=1;
int Object::m[][42]={0};
int Object::player_x=0;
int Object::player_y=0;
int Object::Buff_F = 0;
int Object::Buff_S = 0;
int Object::Buff_B = 0;
int Object::Buff_T = 0;
int Object::score_all=-5;
//Object map code setting default=0; Player=1; Monster=2; Buff=3; Obstacle=4; Wall=5;
class Showscore:public Object{
	public:
		void Gamestart(){
		HideCursor();
		int x=22;
	    gotoxy(x,1);
	    cout<<"  *  *                     *             *    *          *    *    *   * "<<endl;
	    gotoxy(x,2);
	    cout<<"******** ******            *            *    *            *   *    *  *  "<<endl;
	    gotoxy(x,3);
	    cout<<"  *  *   *    *    *****************   *    ***********  ****************"<<endl;
	    gotoxy(x,4);
	    cout<<"  ****   ******            *          **   *     *          *       *    "<<endl;
	    gotoxy(x,5);
	    cout<<"  *  *   *    *            *         * *  *      *        ************** "<<endl;
	    gotoxy(x,6);
	    cout<<"  *  *   *    *       ***********   *  *         *              *        "<<endl;
	    gotoxy(x,7);
	    cout<<"  ****   *    *            *           *         ******     **********   "<<endl;
	    gotoxy(x,8);
	    cout<<"  *  *   ******           ***          *         *              *        "<<endl;
	    gotoxy(x,9);
	    cout<<"******** *    *          * * *         *         ******   ************** "<<endl;
	    gotoxy(x,10);
	    cout<<"  *  *   *    *         *  *  *        *         *           *  *  *     "<<endl;
	    gotoxy(x,11);
	    cout<<" *    *  *    *        *   *   *       *         *          *   *   *    "<<endl;
		for(int i=0;i<3;i++){
			gotoxy(x,15);
		    cout<<"                           press any key                           "<<endl;
		     _sleep(200);
		    gotoxy(x,15);
		    cout<<"                                                                   "<<endl;
		    _sleep(200);
		}
		gotoxy(x,15);
		cout<<"                           press any key                           "<<endl;
	    getch();
		system("cls");
	    score_all=0;
	    }
		void scoreCounting(){
			if(during()>1){
				gotoxy(65,2);
				cout << "Score=" << score_all << endl;
				score_all++;
				start = clock();
			}
		}
		int End(){
            return gameend;
		}
};
class Obstacle:public Object{
public:
    Obstacle(){
    }
    void normalObstacle(){
        for(int cc=0;cc<3;cc++){
            int i=rand()%12+2,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int j_temp=j,j_max=rand()%5+5+j;//j_temp for迴圈中計數用；j_max X軸終點位置
            int i_max=rand()%5+i+2;//Y軸終點位置
            for(;i<i_max;i++)
            {
                for(j_temp=j;j_temp<j_max;j_temp++)
                {
                        if(m[j_temp][i]!=4){
                            gotoxy(j_temp,i);
                            cout<<'H';
                            m[j_temp][i]=4;}
                    }
            }
        }
        for(int cc=0;cc<3;cc++){
            int i=rand()%12+5,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int j_temp=j,j_max=rand()%2+2+j;//j_temp for迴圈中計數用；j_max X軸終點位置
            int i_max=rand()%3+i+2;//Y軸終點位置
            for(;i<i_max;i++)
            {
                for(j_temp=j;j_temp<j_max;j_temp++)
                {
                    if(m[j_temp][i]!=4){
                        gotoxy(j_temp,i);
                        cout<<'H';
                        m[j_temp][i]=4;
                    }
                }
            }
        }
        for(int cc=0;cc<5;cc++){
            int i=rand()%12+5,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int i_max=rand()%5+i+2;//Y軸終點位置
            for(;i<i_max;i++)
            {
                gotoxy(j,i);
                cout<<'H';
                m[j][i]=4;
            }
        }
        for(int cc=0;cc<5;cc++){
            int i=rand()%12+5,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int j_max=rand()%5+j+2;//X軸終點位置
            for(;j<j_max;j++)
            {
                gotoxy(j,i);
                cout<<'H';
                m[j][i]=4;
            }
        }
    }
    void preMapCl(){
        int i,j;
        for(i=25;i<88;i++)
        {
            for(j=0;j<22;j++){
                gotoxy(i,j);
            cout<<" ";
            m[i-25][j]=0;
            }
        }
    }
    void preMapset(){
        for(int i=0;i<62;i++){
            gotoxy(i+25,0);
            cout<<'_';
            m[i][0]=5;
            gotoxy(i+25,21);
            cout<<'T';
            m[i][21]=5;
        }
        for(int i=0;i<22;i++){
            gotoxy(25,i);
            cout<<'|';
            m[0][i]=5;
            gotoxy(87,i);
            cout<<'|';
            m[62][i]=5;
        }
            for(int cc=0;cc<3;cc++){
            int i=rand()%12+2,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int j_temp=j,j_max=rand()%5+5+j;//j_temp for迴圈中計數用；j_max X軸終點位置
            int i_max=rand()%5+i+2;//Y軸終點位置
            for(;i<i_max;i++)
            {
                for(j_temp=j;j_temp<j_max;j_temp++)
                {
                        if(m[j_temp][i]!=4){
                            gotoxy(j_temp+25,i);
                            cout<<'H';
                            m[j_temp][i]=4;}
                    }
            }
        }
        for(int cc=0;cc<3;cc++){
            int i=rand()%12+5,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int j_temp=j,j_max=rand()%2+2+j;//j_temp for迴圈中計數用；j_max X軸終點位置
            int i_max=rand()%3+i+2;//Y軸終點位置
            for(;i<i_max;i++)
            {
                for(j_temp=j;j_temp<j_max;j_temp++)
                {
                    if(m[j_temp][i]!=4){
                        gotoxy(j_temp+25,i);
                        cout<<'H';
                        m[j_temp][i]=4;
                    }
                }
            }
        }
        for(int cc=0;cc<5;cc++){
            int i=rand()%12+5,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int i_max=rand()%5+i+2;//Y軸終點位置
            for(;i<i_max;i++)
            {
                gotoxy(j+25,i);
                cout<<'H';
                m[j][i]=4;
            }
        }
        for(int cc=0;cc<5;cc++){
            int i=rand()%12+5,j=rand()%50+3;//i 起始Y軸位置；j 起始X軸位置
            while(m[j][i]==4)
                i=rand()%12+5,j=rand()%50+3;
            int j_max=rand()%5+j+2;//X軸終點位置
            for(;j<j_max;j++)
            {
                gotoxy(j+25,i);
                cout<<'H';
                m[j][i]=4;
            }
        }
    }
   void testmap(){
        m[5][5]=4,m[5][6]=4,m[5][7]=4,m[5][8]=4,m[5][9]=4,m[5][10]=4;
        m[6][5]=4,m[7][5]=4,m[8][5]=4,m[9][5]=4,m[10][5]=4,m[10][6]=4,m[10][7]=4;
        m[6][10]=4,m[7][10]=4,m[8][10]=4,m[9][10]=4,m[10][10]=4;
        m[9][11]=4;m[10][11]=4;
        m[20][5]=4,m[21][5]=4,m[22][5]=4,m[23][5]=4,m[24][5]=4,m[25][5]=4,m[26][5]=4,m[27][5]=4;
        m[20][6]=4,m[21][6]=4,m[22][6]=4,m[23][6]=4,m[24][6]=4,m[25][6]=4,m[26][6]=4,m[27][6]=4;
        m[20][8]=4,m[20][9]=4,m[20][10]=4,m[20][11]=4,m[20][12]=4,m[20][13]=4,m[20][14]=4;
        m[21][8]=4,m[21][9]=4,m[21][10]=4,m[21][11]=4,m[21][12]=4,m[21][13]=4,m[21][14]=4;
        m[10][11]=4;m[10][12]=4,m[9][12]=4,m[8][12]=4,m[8][13]=4,m[8][14]=4,m[7][14]=4,m[6][14]=4,m[6][15]=4,m[6][16]=4,m[7][16]=4;
        for(int i=0;i<42;i++){
            for(int j=0;j<55;j++){
                if(m[j][i]==4){
                    gotoxy(j,i);
                    cout<<"H";}
            }
        }
    }
};
class UI:public Object{
	private:
	    int gameEndcc=1;
	    Obstacle *obstacle=new Obstacle();
 	public :
	    UI(){
	        srand(time(NULL));
	
	    }
	    void resetFleemode(){
	        Buff_T=0;//fleemode2=0;
	    }
	    void ShowMap(){
	        for(int i=0;i<22;i++){
	            for(int j=0;j<62;j++){
	                if(m[j][i]==4){
	                    gotoxy(j,i);
	                    cout<<"H";}
	            }
	        }
	    }
	    void resetgame(){
	        system("cls");
	        gameEndcc=0;
	    }
	    void Previewcl(){
	        int i,j;
	        for(i=25;i<88;i++)
	        {
	            for(j=0;j<22;j++){
	            gotoxy(i,j);
	            cout<<" ";
	            }
	        }
	    }
	    void ReviewMap(){
	        for(int i=25;i<88;i++)
	        {
	            for(int j=0;j<22;j++){
	                if(m[i-25][j]==4){
	                    gotoxy(i,j);
	                    cout<<"H";
	                }
	            }
	        }
	        for(int i=0;i<62;i++){
	            gotoxy(i+25,0);
	            cout<<'_';
	            m[i][0]=5;
	            gotoxy(i+25,21);
	            cout<<'T';
	            m[i][21]=5;
	        }
	        for(int i=0;i<22;i++){
	            gotoxy(25,i);
	            cout<<'|';
	            m[0][i]=5;
	            gotoxy(87,i);
	            cout<<'|';
	            m[62][i]=5;
	        }
	    }
	    void GameFramesetting(){
	        gameend=1;
	        gameEndcc=0;
	        gotoxy(player_x,player_y);
	        cout<<" ";
	        HideCursor();
	        //mapsetting
	        for(int i=0;i<62;i++){
	            gotoxy(i,0);
	            cout<<'_';
	            m[i][0]=5;
	            gotoxy(i,21);
	            cout<<'T';
	            m[i][21]=5;
	        }
	        for(int i=0;i<22;i++){
	            gotoxy(0,i);
	            cout<<'|';
	            m[0][i]=5;
	            gotoxy(62,i);
	            cout<<'|';
	            m[62][i]=5;
	        }
	    }
	    int endgame(){
	        return gameEndcc;
	    }
	    int gameendreset(){
	        gameEndcc=1;
	    }
	    void gamestartUIsetting(){
	        obstacle->preMapCl();
	        HideCursor();
	        int Option=1,breakpoint=1,tempOption,OptionOpen=1,mapsetin=1,mapreview=0;
	        gotoxy(2,1);
	        cout<<"DICE Map ";
	        gotoxy(5,2);
	        cout<<"review Map";
	        gotoxy(2,3);
	        cout<<"Game start";
	        gotoxy(2,5);
	        cout<<"Game Instructions\n";
	        gotoxy(2,7);
	        cout<<"Monsters information";
	        gotoxy(2,9);
	        cout<<"score information";
	        gotoxy(2,11);
	        cout<<"End Game";
	        gotoxy(0,1);
	        cout<<"->";
	        while(breakpoint){
	            while(_kbhit()){
	                tempOption=Option;
	                int in2=getch();
	                int temp_x=player_x,temp_y=player_y;
	                gotoxy(player_x,player_y);
	                switch(in2){
	                    case 72:
	                        if((Option-1)==2&&mapsetin==0&&mapreview)
	                            Option=2;
	                        else if(Option==2)
	                            Option--;
	                        else    { Option-=2;
	                            mapreview=1;
	                        }
	                        break;
	                    case 80:
	                        if((Option+1)==2&&mapsetin==0&&mapreview)
	                                Option=2;
	                        else if(Option==2)
	                            Option++;
	                        else     {Option+=2;
	                            mapreview=1;
	                        }
	                        break;
	                    case 13:
	                        OptionOpen=0;
	                        break;
	                    }
	                if(OptionOpen){
	                    if(Option<=0){
	                        Option=9;
	                    }
	                    else if(Option>=12){
	                        Option=1;
	                    }
	                    if(Option!=2){
	                        if(tempOption!=2){
	                            gotoxy(0,tempOption);
	                            cout<<"  ";
	                            gotoxy(0,Option);
	                            cout<<"->";
	                        }
	                        else {
	                            gotoxy(3,2);
	                            cout<<"  ";
	                            gotoxy(0,Option);
	                            cout<<"->";
	                        }
	
	                    }
	                    else {
	                        gotoxy(0,tempOption);
	                        cout<<"  ";
	                        gotoxy(3,2);
	                        cout<<"->";
	                    }
	                }
	                else {
	                    Previewcl();
	                    switch(Option){
	                        case 1:
	                            obstacle->preMapCl();
	                            obstacle->preMapset();
	                            mapsetin=0;
	                            break;
	                        case 2:
	                            ReviewMap();
	                            break;
	                        case 3:
	                            gameEndcc=1;
	                            system("cls");
	                            if(mapsetin){
	                                GameFramesetting();
	                                obstacle->normalObstacle();
	                                breakpoint=0;
	                            }
	                            else {
	                                ShowMap();
	                                breakpoint=0;
	                                GameFramesetting();
	                            }
	                            return;
	                        case 5:
	                            gotoxy(25,1);
	                            cout<<"MOVE: up , down , left , right";
	                            gotoxy(25,2);
	                            cout<<"       or w , a , s , d";
	                            gotoxy(25,4);
	                            cout<<"BUFF:";
	                            gotoxy(24,5);
	                            cout<<"       F: Player acceleration";
	                            gotoxy(24,7);
	                            cout<<"       S: Monster decelerate";
	                            gotoxy(24,9);
	                            cout<<"       B:All Monster go die ";
	                            gotoxy(24,11);
	                            cout<<"       T:Reverse";
	                            break;
	                        case 7:
	                            gotoxy(30,1);
	                            cout<<"K: Normal monster but  stupid...?";
	                            gotoxy(30,3);
	                            cout<<"D: Random Move,Random future";
	                            gotoxy(30,5);
	                            cout<<"N: BOOM BOOM King! (Crazy Arcade)";
	                            gotoxy(30,7);
	                            cout<<"L: MinoTaurus,easy to hit a wall,\n\t\t\t\t    but a acceleration after";
	                            gotoxy(30,10);
	                            cout<<"M: Teleporter but only pass through Y axis";
	                            break;
	                        case 9:
	                            gotoxy(25,1);
	                            cout<<"Score mechanism:";
	                            gotoxy(25,3);
	                            cout<<" +1 = Pass 1 sec";
	                            gotoxy(25,4);
	                            cout<<" +5 = get BUFF:T and Kill A Monster";
	                            break;
	                        case 11:
	                            gameEndcc=1;
	                            return ;
	                    }
	                    OptionOpen=1;
	                }
	
	            }
	        }
	    }
};
class Food:public Object{
    //F:30 S:31 B:32 T:33
    protected:
	    int F_x = 0;
	    int F_y = 0;
	    int type;
	    Timer *F = new Timer(5);
	    Timer *S = new Timer(5);
	    Timer *B = new Timer(5);
	    Timer *T = new Timer(5);
    public:
	    Food(){
	        Object::start = clock();
	        Buff_F = 0;
	        Buff_S = 0;
	        Buff_B = 0;
	        Buff_T = 0;
	    }
	    void produce(){
	        if(Object::during()>=10){// per sec
	            if(F_x!=0&&F_y!=0) Replace();//delete first one
	            type = /*33;//*/rand()%4+30;
	            do{
	                F_x = (rand()%61)+1;
	                F_y = (rand()%20)+1;
	            }while(m[F_x][F_y]==4||m[F_x][F_y]==5);
	            gotoxy(F_x,F_y);
	            switch(type){
	                case 30:
	                    cout<<'F';
	                    break;
	                case 31:
	                    cout<<'S';
	                    break;
	                case 32:
	                    cout<<'B';
	                    break;
	                case 33:
	                    cout<<'T';
	                    break;
	            }
		        m[F_x][F_y] = type;
			    Object::start = clock();
	        }
	    }
	    void Replace(){
	        gotoxy(F_x,F_y);
	        cout<<' ';
	        m[F_x][F_y] = 0;
	    }
	    void start(int type){
	        switch(type){
	            case 30:
	                F->StartCount();
	                break;
	            case 31:
	                S->StartCount();
	                break;
	            case 32:
	                B->StartCount();
	                break;
	            case 33:
	                T->StartCount();
	                break;
	        }
	    }
	    void countDown(){
	        if(F->Countdown()) Buff_F = 0;
	        if(S->Countdown()) Buff_S = 0;
	        if(B->Countdown()) Buff_B = 0;
	        if(T->Countdown()) Buff_T = 0;
	    }
};
class Player:public Object{
    protected:
	    int score=1;
	    int state=1;
	    Food *Buff;
	    double P_Speed;
    public:
        Player(Food *buff){
            start=clock();
            Buff = buff;
        }
        void setp(){
            int xp=rand()%40+10,yp=rand()%18+3;
            while(m[xp][yp]==4){
                xp=rand()%40+10,yp=rand()%18+3;
            }
            player_x=xp;
            player_y=yp;
            gotoxy(player_x,player_y);
            cout<<"P";
        }
        void testsetp(){
            player_x=3;
            player_y=7;
            gotoxy(player_x,player_y);
            cout<<"P";
        }
        void CheckDoor(int a){
            if(a==1){
                while(m[DoorX][DoorY]!=6){
                    DoorY--;
                }
                m[DoorX][DoorY]=0;
                gotoxy(DoorX,DoorY);
                cout<<" ";
                if(m[DoorX][DoorY-1]==4) CheckDoor(1);
            }
            else if(a==2){
                 while(m[DoorX][DoorY]!=6){
                    DoorY++;
                }
                m[DoorX][DoorY]=0;
                gotoxy(DoorX,DoorY);
                cout<<" ";
                if(m[DoorX][DoorY+1]==4) CheckDoor(2);
            }
        }
        void BreakDoor(int in2,int temp_x,int temp_y){
            DoorX = temp_x;
            DoorY = temp_y;
            int up=1;
            int down=1;
            int u=0;
            int d=0;
            int BreakAction = 1;
            m[player_x][player_y]=0;
            player_x=temp_x;
            player_y=temp_y;
            m[player_x][player_y]=1;
            gotoxy(player_x,player_y);
            cout<<"P";
            Show_input(in2);
            if(m[player_x][player_y+1]==4&&m[player_x][player_y-1]==4) BreakAction = 2;
            if(BreakAction==1){
                while(u==0&&d==0){
                    if(m[DoorX][DoorY-up]==4){
                            up++;
                    }
                    else if(m[DoorX][DoorY-up]==6){
                            u = 1;
                            break;
                    }
                    if(m[DoorX][DoorY+down]==4){
                            down++;
                    }
                    else if(m[DoorX][DoorY+down]==6){
                            d = 1;
                            break;
                    }
                }
                if(u==1){
                    DoorY=DoorY-up;
                    m[DoorX][DoorY]=0;
                    gotoxy(DoorX,DoorY);
                    cout<<" ";
                    if(m[DoorX][DoorY-1]==4) CheckDoor(1);
                }
                else if(d==1){
                    DoorY = DoorY+down;
                    m[DoorX][DoorY]=0;
                    gotoxy(DoorX,DoorY);
                    cout<<" ";
                    if(m[DoorX][DoorY+1]==4) CheckDoor(2);
                }
            }
            else if(BreakAction==2){
                while(u==0||d==0){
                    if(m[DoorX][DoorY-up]==6||m[DoorX][DoorY-up]==0) u=1;
                    else if(u==0){
                        if(m[DoorX][DoorY-up]==4) up++;
                    }
                    if(m[DoorX][DoorY+down]==6||m[DoorX][DoorY+down]==0) d=1;
                    else if(d==0){
                        if(m[DoorX][DoorY+down]==4) down++;
                    }
                }
                m[DoorX][DoorY-up]=0;
                gotoxy(DoorX,DoorY-up);
                cout<<" ";
                m[DoorX][DoorY+down]=0;
                gotoxy(DoorX,DoorY+down);
                cout<<" ";
            }
        }
        void Move(){
            if(m[player_x][player_y]==2) GameOver();
            P_Speed = 0.05;//Player Speed(sec per movement)
            if(Buff_F==1) P_Speed = P_Speed/(double)2;//buff F
            if(during()>=P_Speed){
                int in2;
                if(_kbhit()){
                    while(_kbhit())
                        in2=getch();
                    int temp_x=player_x,temp_y=player_y;
                    gotoxy(player_x,player_y);
                    cout<<' ';
                    switch(in2){
                        case 'u':
                            state=4;
                            break;
                        case 'i':
                            state=1;
                            break;
                        case 119:
                        case 72:
                            temp_y-=1;
                            break;
                        case 80:
                        case 115:
                            temp_y+=1;
                            break;
                        case 97:
                        case 75:
                            temp_x-=1;
                            break;
                        case 100:
                        case 77:
                            temp_x+=1;
                            break;
                	}
                    if((m[temp_x][temp_y]==0)||((m[temp_x][temp_y]/10)==3)){
                        switch(m[temp_x][temp_y]){
                            case 30:
                                Buff_F=1;
                                Buff->start(30);//timer 5sec
                                break;
                            case 31:
                                Buff_S=1;
                                Buff->start(31);//timer 5sec
                                break;
                            case 32:
                                Buff_B=1;
                                Buff->start(32);//timer 5sec
                                break;
                            case 33:
                                Buff_T=1;
                                Buff->start(33);//timer 5sec
                                break;
                        }
                        m[player_x][player_y]=0;
                        player_x=temp_x;
                        player_y=temp_y;
                        m[player_x][player_y]=/*4;//*/state;
                        gotoxy(player_x,player_y);
                        cout<<"P";

                    }
	                else if(m[temp_x][temp_y]==6){
	                        BreakDoor(in2,temp_x,temp_y);
	                }
	                else{
	                        gotoxy(player_x,player_y);
	                        cout<<"P";
	                }
	            }
	        start=clock();
	        Buff->countDown();
            }
        }
        void Show_input(int i){
            gotoxy(65,3);
            cout<<"\t\t\t\t\t\t";
            gotoxy(65,3);
            switch(i){
                case 72:
                    cout<<"Up";
                    break;
                case 80:
                    cout<<"Down";
                    break;
                case 75:
                    cout<<"Left";
                    break;
                case 77:
                    cout<<"Right";
                    break;
            }
        }
};
class Monster:public Object,public DieReset{
    private:
	    int ring=5;
	    int ta[17][17],rn=1,rw=0,rs=0,re=0,tax=7,tay=7,pretax,pretay;
	    int testcc=5;
	    int tpcheck=1;
    protected:
	    int fleemode=0;
	    double origin_speed;
	    double speed=0.3;
	    int tx,ty;
	    int x,y;
    public:
	    Monster():x(2),y(2){
	        start=clock();

	        for(int i=0;i<16;i++){
	            for(int j=0;j<16;j++){
	                ta[i][j]=9;
	            }
	        }
		}
		~Monster(){
			Die();
		}
	    void Move(){}
	    void DeBuff(){//Buff S
	        if(Buff_S==1) speed = origin_speed*2;
	        else speed = origin_speed;
	    }
	    void Die(){//Buff B
	        gotoxy(x,y);
	        cout<<' ';
	        m[x][y] = 0;
	    }
	    void taClean(){
	        for(int i=0;i<16;i++){
	            for(int j=0;j<16;j++){
	                ta[i][j]=9;
	            }
	        }
	    }
	    void fleeWayCheck(){
	        int breakpoint=1;
	        for(testcc=7;testcc>5&&breakpoint;testcc--){
	            for(int i=0;i<16&&breakpoint;i++){
	                for(int j=0;j<16&&breakpoint;j++){
	                    if(ta[i][j]==testcc){
	                        breakpoint=0;
	                        break;
	                    }
	                }
	            }
	        }
	        if(breakpoint){
	            taClean();
	            int newfleedirection=rn+rs+rw+re;
	            int tempdirection;
	            if(newfleedirection==3){
	                if(rn&&rs){
	                    tempdirection=rw;
	                    rw=re;
	                    re=tempdirection;
	                }
	                else {
	                    tempdirection=rn;
	                    rn=rs;
	                    rs=tempdirection;
	                }
	            }
	            else {
	                tempdirection=rn;
	                rn=rs;
	            	rs=tempdirection;
	                tempdirection=rw;
	                rw=re;
	                re=tempdirection;
	            }
	            tap(0,0,0);
	        }
	    }
	    void fleeDirection(){
	        pretax=tax,pretay=tay;
	        rn=0,rw=0,rs=0,re=0;
	        if(x==player_x){
	            if(y>player_y){
	                rs=1,rw=1,re=1;
	                tax=7,tay=7;
	            }
	            else{
	                rn=1;rw=1,re=1;
	                tax=7,tay=0;
	            }
	        }
	        else if(y==player_y){
	            if(x>player_x){
	                rn=1,rs=1,re=1;
	                tax=0,tay=7;
	            }
	            else {
	                rn=1,rs=1,rw=1;
	                tax=7,tay=7;
	            }
	        }
	        else {
	            if(x>player_x)
	                re=1;
	            else rw=1;
	            if(y>player_y)
	                rs=1;
	            else rn=1;
	            if(re)
	                tax=0;
	            else tay=7;
	            if(rn)
	                tay=7;
	            else tay=0;
	        }
	    }
	    void tap(int xc,int yc,int cc){
	        ta[tax][tay]=0;
	        int tempc=cc;
	        int tx=xc,ty=yc;
	        if(cc>6)return;
	        if(rn){
	            tempc=cc;
	            ty--;
	            if(m[x+xc][y+ty]!=4&&m[x+xc][y+ty]!=5){
	                if(ta[tax+xc][tay+ty]==(tempc+1)){}
	                else {
	                    if(ta[tax+xc][tay+ty]>tempc){
	                        tempc++;
	                        //gotoxy(x+xc,y+ty);
	                        //cout<<tempc;
	                        ta[tax+xc][tay+ty]=tempc;
	                        //_sleep(100);
	                        if(ta[tax+xc][tay+ty-1]>tempc){
	                            if(ta[tax+xc][tay+ty]==0)
	                                return;
	                            tap(xc,ty,tempc);
	                        }
						}
	                }
	            }
	        }
	        if(rw){
	            tempc=cc;
	            tx--;
	            if(m[x+tx][y+yc]!=4&&m[x+tx][y+yc]!=5){
	                if(ta[tax+tx][tay+yc]==(tempc+1)){}
	                else {
	                    if(ta[tax+tx][tay+yc]>tempc){
	                        tempc++;
	                        //gotoxy(x+tx,y+yc);
	                        //cout<<tempc;
	                        ta[tax+tx][tay+yc]=tempc;
	                        if(ta[tax+tx][tay+yc-1]>tempc){
	                            if(ta[tax+tx][tay+xc]==0)
	                                return;
	                            // _sleep(100);
	                            tap(tx,yc,tempc);
	                        }
						}
	                }
	            }
	        }
	        if(rs){
	            ty=yc+1;
	            tempc=cc;
	            if(m[x+xc][y+ty]!=4&&m[x+xc][y+ty]!=5){
	                if(ta[tax+xc][tay+ty]!=(tempc+1)){
	                    if(ta[tax+xc][tay+ty]>tempc){
	                        tempc++;
	                        //gotoxy(x+xc,y+ty);
	                        //cout<<tempc;
	                        ta[tax+xc][tay+ty]=tempc;

	                        if(ta[tax+xc][tay+ty+1]>tempc)
	                        {
	                            if(ta[tax+xc][tay+ty]==0)
	                                return;
	                            // _sleep(100);
	                            tap(xc,ty,tempc);
	                        }
						}
	                }
	            }
	        }
	        if(re){
	            tempc=cc;
	            tx=xc+1;
	            if(m[x+tx][y+yc]!=4&&m[x+tx][y+yc]!=5){
	                if(ta[tax+tx][tay+yc]==(tempc+1)){}
	                else {
	                    if(ta[tax+tx][tay+yc]>tempc){
	                        tempc++;
	                        //gotoxy(x+tx,y+yc);
	                        //cout<<tempc;
	                        ta[tax+tx][tay+yc]=tempc;
	                        if(ta[tax+tx][tay+yc+1]>tempc){
	                            if(ta[tax+tx][tay+xc]==0)
	                                return;
	                          //  _sleep(100);
	                            tap(tx,yc,tempc);
	                        }
						}
	                }
	            }
	        }
	    return;
	    }
	    void tapmove(){
	        if(rn&&m[x][y-1]!=5&&m[x][y-1]!=4){
	            ta[tax][tay-1]==1;
	            y--;
	        }
	        else if(rs&&m[x][y+1]!=5&&m[x][y+1]!=4){
	            ta[tax][tay+1]==1;
	            y++;
	        }
	        if(rw&&m[x-1][y]!=5&&m[x-1][y]!=4){
	            ta[tax-1][tay]==1;
	            x--;
	        }
	        else if(re&&m[x+1][y]!=5&&m[x+1][y]!=4){
	            ta[tax+1][tay]==1;
	            x++;
	        }
	        taClean();
	    }
	    void fleeCheck(int* in_X,int* in_Y){
	        x=*in_X,y=*in_Y;
	        if(abs(x-player_x)<9&&abs(y-player_y)<9)
	        {
	            if(m[x][y]!=6){
	            m[x][y]=0;
	            gotoxy(x,y);
	            cout<<" ";}
	            else{gotoxy(x,y);
	            cout<<"@";}
	            fleeDirection();
	            tap(0,0,0);
	            tapmove();
	            if(m[x][y]==6){
	                tpcheck=0;
	                InterDoor();
	            }
	            else m[x][y]=2;
	            if(tpcheck){gotoxy(x,y);
	            cout<<"B";
	            }
	            *in_X=x;
	            * in_Y=y;
	            tpcheck=1;
	        }
	    }
	    void CheckDoor(int a){
	        m[x][y]=0;
	        gotoxy(x,y);
	        cout<<" ";
	        if(a==1){
	            while(m[x][y]!=6){
	                y--;
	            }
	            tx=x;
	            ty=y;
	            m[x][y]=2;
	            gotoxy(x,y);
	            cout<<"M";
	            if(m[x][y-1]==4) CheckDoor(1);
	        }
	        else if(a==2){
	             while(m[x][y]!=6){
	                y++;
	            }
	            tx=x;
	            ty=y;
	            m[x][y]=2;
	            gotoxy(x,y);
	            cout<<"M";
	            if(m[x][y+1]==4) CheckDoor(2);
	        }
	    }
	    void InterDoor(){
	        int InterAction=1;
	        int u=0;
	        int d=0;
	        int up=1;
	        int down=1;
	        int a=0;
	        int check=0;
	        tx = x;
	        ty = y;
	        m[x][y]=0;
	        gotoxy(x,y);
	        cout<<" ";
	        if(m[x][y+1]==4&&m[x][y-1]==4) InterAction=2;
	        if(InterAction==1){
	            if(m[x][y+1]==4) a=2;
	            else if(m[x][y-1]==4) a=1;
	            if(a==2){
	               while(m[x][y]!=6){
	                    y++;
	                }
	                ty=y;
	                while(1){
	                    ty++;
	                    if(m[x][ty]==6){
	                        check=1;
	                        break;
	                    }
	                    else if(m[x][ty]==0) break;
	                }
	            }
	            else  if(a==1){
	               while(m[x][y]!=6){
	                    y--;
	                }
	                ty=y;
	                while(1){
	                    ty--;
	                    if(m[x][ty]==6){
	                        check=1;
	                        break;
	                    }
	                    else if(m[x][ty]==0) break;
	                }
	            }
	            tx=x;
	            ty=y;
	            m[x][y]=2;
	            gotoxy(x,y);
	            cout<<"M";
	            if(a==1&&check==1){
	                if(m[x][y-1]==4) CheckDoor(1);
	            }
	            else if(a==2&&check==1){
	                if(m[x][y+1]==4) CheckDoor(2);
	            }
	        }
	        else if(InterAction==2){
	             while(u==0||d==0){
	                if(m[x][y-up]==6) u=1;
	                else if(m[x][y-up]==0) u=2;
	                else if(u==0){
	                    if(m[x][y-up]==4) up++;
	                }
	                if(m[x][y+down]==6) d=1;
	                else if(m[x][y+down]==0) d=2;
	                else if(d==0){
	                    if(m[x][y+down]==4) down++;
	                }
	            }
	            if(u==1&&d==2){
	                y=y-up;
	                tx=x;
	                ty=y;
	                m[x][y]=2;
	                gotoxy(x,y);
	                cout<<"M";
	            }
	            else if(u==2&&d==1){
	                y=y+down;
	                tx=x;
	                ty=y;
	                m[x][y]=2;
	                gotoxy(x,y);
	                cout<<"M";
	            }
	            else{
	                int dice=rand()%3;
	                if(dice==1){
	                    m[x][y+down]=0;
	                    gotoxy(x,y+down);
	                    cout<<" ";
	                    y=y-up;
	                    tx=x;
	                    ty=y;
	                    m[x][y]=2;
	                    gotoxy(x,y);
	                    cout<<"M";
	                }else{
	                    m[x][y-up]=0;
	                    gotoxy(x,y-up);
	                    cout<<" ";
	                    y=y+down;
	                    tx=x;
	                    ty=y;
	                    m[x][y]=2;
	                    gotoxy(x,y);
	                    cout<<"M";
	                    }
	                }
	            }
	            //_sleep(1000);
	    }

};
class Wyrd:public Monster{
    private:
	    int x,y;
	    int temp_x,temp_y,pre_x,pre_y;
	    int mode=0,movedirection_x=0,movedirection_y=0,detectdirection_x=0,detectdirection_y=0,modeswitch=1,playerdirection_x=0,playerdirection_y=0;
	    int skipportal=0;
    public:
	    Wyrd(){
	        origin_speed = 0.2;
	        speed = origin_speed;
	        start=clock();
	        gotoxy(x,y);
	        cout<<'K';
	    }
	    ~Wyrd(){
	    	mobdoor[0]=0;
	        score_all+=5;
	        gotoxy(x,y);
            cout<<" ";
			m[x][y] = 0;
	    }
	    void Move(){
	        DeBuff();
	        if(x==player_x&& y==player_y) GameOver();
	        if(during()>speed){
	            if(Buff_T==1){
	                fleeCheck(&x,&y);
	                start=clock();
	                mode=0,movedirection_x=0,movedirection_y=0,detectdirection_x=0,detectdirection_y=0,modeswitch=1,playerdirection_x=0,playerdirection_y=0;
	                skipportal=0;
	            }
	            else{
	                if(mode==0){
		                pre_x=x,pre_y=y;
		                gotoxy(x,y);
		                if(skipportal){
		                    cout<<"@";
		                    skipportal=0;
		                }
		                else{
		                    cout<<' ';
		                    m[pre_x][pre_y]=0;
		                }
		                temp_x=x,temp_y=y;
		                if(x>player_x){
		                    temp_x--;
		                }
		                else if(x<player_x)
		                {
		                    temp_x++;
		                }
		                if(y>player_y){
		                    temp_y--;
		                }
		                else if(y<player_y){
		                    temp_y++;
		                }
		                if(m[temp_x][temp_y]==4){
		                    if(m[x][temp_y]!=4)
		                    {
		                        y=temp_y;
		                    }
		                    else if(m[temp_x][y]!=4)
		                    {
		                        x=temp_x;
		                    }
		                }
		                else{
		                    x=temp_x,y=temp_y;
		                }
		                    gotoxy(x,y);
		                    cout<<'K';
		                    start=clock();
		                    if(pre_x==x&&pre_y==y)
		                        mode=1;
	                }
	                else if(mode==2){
		                pre_x=x,pre_y=y;
		                temp_x=x;
		                temp_y=y;
		                gotoxy(x,y);
		                if(skipportal){
		                    cout<<"@";
		                    skipportal=0;
		                    }
		                else {
		                        cout<<' ';
		                        m[pre_x][pre_y]=0;
		                }
		                if(modeswitch==1){
		                    temp_x+=movedirection_x;
		                    temp_y+=movedirection_y;
		                    if(m[temp_x][temp_y]==0){
		                        if(movedirection_x&&(m[temp_x][y+detectdirection_y]==0)){
		                            detectdirection_y=0;
		                            modeswitch=2;
		                        }
		                        else if(movedirection_y&&(m[x+detectdirection_x][temp_y]==0)){
		                            detectdirection_x=0;
		                            modeswitch=2;
		                        }
		                        x=temp_x;
		                        y=temp_y;
		                        gotoxy(70,5);
		                        cout<<"\t\t\t\t";
		                        gotoxy(70,5);
		                        cout<<movedirection_x<<","<<movedirection_y;
		                    }
	                        else{
		                        if(movedirection_x)
		                        {
		                            if(m[temp_x][temp_y]==4){
		                                movedirection_y=0-detectdirection_y;
		                                detectdirection_x=movedirection_x;
		                                detectdirection_y=0;
		                                movedirection_x=0;
		                                modeswitch=3;
		                            }
		                            else if(m[temp_x][temp_y]==5){
		                                movedirection_x=0-movedirection_x;
		                            }
		                        }
		                        else if(movedirection_y)
		                        {
		                            if(m[temp_x][temp_y]==4){
		                                movedirection_x=0-detectdirection_x;
		                                detectdirection_y=movedirection_y;
		                                detectdirection_x=0;
		                                movedirection_y=0;
		                                modeswitch=3;
		                            }
		                            else if(m[temp_x][temp_y]==5){
		                                movedirection_y=0-movedirection_y;
		                            }
		                        }
		                    }
		                }
	                    else if(modeswitch==3){
	                        temp_x+=movedirection_x;
	                        temp_y+=movedirection_y;
	                        if(movedirection_x){
	                            if(m[temp_x][y]==4){
	                                temp_x=x;
	                                movedirection_y=0-detectdirection_y;
	                                detectdirection_x=movedirection_x;
	                                detectdirection_y=0;
	                                movedirection_x=0;
	                            }
	                            else if(m[temp_x][y+detectdirection_y]==0){
	                                movedirection_y=detectdirection_y;
	                                detectdirection_x=0-movedirection_x;
	                                detectdirection_y=0;
	                                movedirection_x=0;
	                            }
	                        }
	                        else if(movedirection_y){
	                            if(m[x][temp_y]==4){
	                                temp_y=y;
	                                movedirection_x=0-detectdirection_x;
	                                detectdirection_y=movedirection_y;
	                                detectdirection_x=0;
	                                movedirection_y=0;
	                            }
	                            else if (m[x+detectdirection_x][temp_y]==0){
	                                movedirection_x=detectdirection_x;
	                                detectdirection_y=0-movedirection_y;
	                                detectdirection_x=0;
	                                movedirection_y=0;
	                            }
	                        }
	                        if(playerdirection_x){
	                            if((movedirection_x==playerdirection_x)&&m[temp_x+movedirection_x][temp_y+detectdirection_y]==0&&m[temp_x+movedirection_x][temp_y]==0){
	                                //temp_x=temp_x-detectdirection_x;
	                                modeswitch=2;
	                                movedirection_y=1;
	                                movedirection_x=0;
	                                playerdirection_x=0;
	                            }
	                        }
	                        else if(playerdirection_y){
	                            if((movedirection_y==playerdirection_y)&&m[temp_x+detectdirection_x][temp_y-movedirection_y]==0&&m[temp_x][temp_y+movedirection_y]==0){
	                                //temp_y=temp_y-detectdirection_y;
	                                modeswitch=2;
	                                movedirection_x=1;
	                                movedirection_y=0;
	                                playerdirection_y=0;
	                            }
	                        }
	                        x=temp_x;
	                        y=temp_y;
	                    }
	                    else if(modeswitch==2){
	                        if(movedirection_x){
	                            if(y>player_y){
	                                y--;
	                            }
	                            else if(y<player_y){
	                                y++;
	                            }
	                        }
	                        else if(movedirection_y){
	                            if(x>player_x){
	                                x--;
	                            }
	                            else if(x<player_x){
	                                x++;
	                            }
	                        }
	                        mode=0;
	                        modeswitch=1;
	                    }
	                    gotoxy(x,y);
	                    cout<<'K';
	                    start=clock();
	                }
	                else if(mode==1){
	                    movedirection_x=0;
	                    movedirection_y=0;
	                    if(m[x][temp_y]==4){
	                        movedirection_x=rand()%2;
	                        if(movedirection_x==0)
	                            movedirection_x=-1;
	                        else
	                            movedirection_x=1;
	                        if(m[x+movedirection_x][y]==4)
	                            movedirection_x=0-movedirection_x;
	                            detectdirection_x=0;
	                        if(player_y>y){
	                            detectdirection_y=1;
	                            playerdirection_y=1;
	                        }
	                        else{
	                            detectdirection_y=-1;
	                            playerdirection_y=-1;
	                        }

	                    }
	                    else if(m[temp_x][y]==4){
	                        movedirection_y=rand()%2;
	                        if(movedirection_y==0)
	                            movedirection_y=-1;
	                        else
	                            movedirection_y=1;
	                        if(m[x][y+movedirection_y]==4)
	                            movedirection_y=0-movedirection_y;
	                            detectdirection_y=0;
	                        if(player_x>x){
	                            detectdirection_x =1;
	                            playerdirection_x =1;
	                        }
	                        else{
	                            detectdirection_x=-1;
	                            playerdirection_x=-1;
	                        }
	                    }
	                    mode=2;
	                }
	                if(m[x][y]==6){
		                skipportal=1;
		                m[x][y]=6;
	            	}
	            	else m[x][y]=2;
                if(x==player_x&& y==player_y) GameOver();
	            }
	        }

	    }
};
class Dino:public Monster{
    protected:
    	int count = 1000;
    public:
	    Dino(){
	        origin_speed = 1;
	        speed = origin_speed;
	        start = clock();
	        //speed = 1;
	    }
	    ~Dino(){
	    	mobdoor[1]=0;
	    	score_all+=5;
	        Die();
	    }
	    void Move(){
	        if(x==player_x&&y==player_y) GameOver();
	        //int reTurn = 1;
	        int tempx;
	        int tempy;
	        int direction;
	        DeBuff();
	        if(during()>speed){//time to move
	            if(Buff_T==1){
	                fleeCheck(&x,&y);
	                start=clock();
	            }
	            else{
	                count++;
	                tempx = x;
	                tempy = y;
	                if(x<player_x) tempx++;
	                else if(x>player_x) tempx--;
	                if(y<player_y) tempy++;
	                else if(y>player_y) tempy--;
	                if(origin_speed<=0.2){// wether speeding
	                    origin_speed = 0.2;
	                }
	                if(m[tempx][tempy]!=4&&m[tempx][tempy]!=5&&count>=7){
	                    if(m[tempx][tempy]==6){
	                        gotoxy(x,y);
	                        cout<<" ";
	                        m[x][y]==0;
	                        x=tempx;
	                        y=tempy;
	                        InterDoor();
	                        tempx=tx;
	                        tempy=ty;
	                    }
	                }//have not Kissed Wall
	                else{//have Kissed Wall
	                    if(m[tempx][tempy]==4||m[tempx][tempy]==5){
	                        count = 0;//when hit wall count = 0;
	                        origin_speed-=0.1;
	                    }
	                    do{
	                        direction = rand()%8;
	                        tempx = x;
	                        tempy = y;
	                        if(direction==0){//right up
	                            tempx++;
	                            tempy--;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                        else if(direction==1){//right down
	                            tempx++;
	                            tempy++;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                        else if(direction==2){//left down
	                            tempx--;
	                            tempy++;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                        else if(direction==3){//left up
	                            tempx--;
	                            tempy--;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                        else if(direction==4){//up
	                            tempy--;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                        else if(direction==5){//down
	                            tempy++;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                        else if(direction==6){//left
	                            tempx--;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                        else if(direction==7){//right
	                            tempx++;
	                            if(m[tempx][tempy]==6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y]==0;
	                                x=tempx;
	                                y=tempy;
	                                InterDoor();
	                                tempx=tx;
	                                tempy=ty;
	                            }
	                        }
	                    }while(m[tempx][tempy]==4||m[tempx][tempy]==5);
	                }
	                //reTurn = wetherKissWall(tempx,tempy);
	                wetherKissWall(tempx,tempy);
	                start = clock();
	            }
	        }
	        if(x==player_x&&y==player_y) GameOver();
	        //return reTurn;
	    }
	    int wetherKissWall(int tempx,int tempy){
	        gotoxy(x,y);
	        cout<<' ';
	        m[x][y] = 0;
	        x = tempx;
	        y = tempy;
	        gotoxy(x,y);
	        cout<<'D';
	        if(m[x][y]==1) return 0;//eat Player
	        m[x][y] = 2;
	        return 1;
	    }
};
class Mon:public Monster{
	protected:
		int temp_x=x,temp_y=y;
		double temp;
	public:
        Mon(){
            origin_speed = 1;
            speed = origin_speed;
        }
        ~Mon(){
        	mobdoor[3]=0;
        	score_all+=5;
        	Die();
		}
		void Move(){
	        if(x==player_x&&y==player_y) GameOver();
            DeBuff();
            if(during()>=speed){
	        if(x==player_x&&y==player_y) GameOver();
                if(Buff_T==1){
                    speed=origin_speed;
                    fleeCheck(&x,&y);
                    start=clock();
                }
                else{
                    temp_x=x,temp_y=y;
                    gotoxy(x,y);
                    cout<<" ";
                    if(x<player_x) temp_x++;
                    else
                        if(x>player_x)
                            temp_x--;
                    if(y<player_y) temp_y++;
                    else
                        if(y>player_y)
                            temp_y--;
                    if(m[temp_x][temp_y]!=4){
                        if(m[temp_x][temp_y]==6){
                            x=temp_x;
                            y=temp_y;
                            InterDoor();
                            temp_x=tx;
                            temp_y=ty;
                        }
                        else{
                            m[x][y]=0;
                            x=temp_x;
                            y=temp_y;
                            m[x][y]=2;
                            gotoxy(x,y);
                            cout<<"L";
                        }
                        if(speed==5.0) go();
                    }
                    else{
                        gotoxy(x,y);
                        cout<<"L";
                        speed_up();
                        stop();
                    }
                    start=clock();
                }
            }
		}
		void speed_up(){
			if(origin_speed>=0.2)
			origin_speed-=0.1;
			if(temp>=0.2&&temp<=5.0)
			temp-=0.1;
		}
		void stop(){
			if(origin_speed<=1.0)
			temp=origin_speed;
			origin_speed=5.0;
		}
		void go(){
			origin_speed=temp;
		}
};
class Su:public Monster{
    private:
        int x,y;
        int t_x,t_y; //next step
        int up = 1;
        int down = 1;
        int i = 1;//count step
        int w1=0,w2=0;
        int a = 0;//go up or down when kiss Wall
    public:
        Su():x(2),y(2){
            origin_speed = 0.3;
            speed = origin_speed;
            gotoxy(x,y);
            cout<<"M";
            t_x = x;
            t_y = y;
            start=clock();
            }
        ~Su(){
        	mobdoor[2]=0;
        	score_all+=5;
            gotoxy(x,y);
            cout<<" ";
			m[x][y] = 0;
        }
	    void ActionAdd(){
	        for(int k=1;k<=i;k++){
	            if(m[t_x][t_y+k]==4||m[t_x][t_y+k]==5){
	              a = 1;
	              i = 1;
	              break;
	            }
	        }
	        if(a==2){
	            i = 1;
	        }
	    }
	    void ActionRed(){
	        for(int k=1;k<=i;k++){
	            if(m[t_x][t_y-k]==4||m[t_x][t_y-k]==5){
	              a = 2;
	              i = 1;
	              break;
	            }
	        }
	         if(a==1){
	            i = 1;
	        }
	    }
	    void Empty(){
	        i = 1;
	        up = 1;
	        down = 1;
	        a = 0;
	        w1 = 0;
	        w2 = 0;
	    }
	    void CreateDoor(int a){
	        gotoxy(x,y);
	        cout<<"@";
	        m[x][y] = 6; //傳送門6
	        if(a==1){
	            while(m[x][y]!=0&&m[x][y]!=1){
	               y++;
	            }
	            if(x==player_x&&y==player_y) GameOver();
	            m[x][y]=2;
	            gotoxy(x,y);
	            cout<<"M";
	            //_sleep(1000);
	            m[x][y] = 6;
	            gotoxy(x,y);
	            cout<<"@";
	            t_y=y;
	        }
	        else if(a==2){
	            while(m[x][y]!=0&&m[x][y]!=1){
	               y--;
	            }
	            if(x==player_x&&y==player_y) GameOver();
	            m[x][y]=2;
	            gotoxy(x,y);
	            cout<<"M";
	            //_sleep(1000);
	            m[x][y] = 6;
	            gotoxy(x,y);
	            cout<<"@";
	            t_y=y;
	        }

	    }
	    void CheckDoor(int a){
	            m[x][y]=0;
	            gotoxy(x,y);
	            cout<<" ";
	            if(a==1){
	                while(m[x][y]!=6){
	                    y--;
	                }
	                t_x=x;
	                t_y=t_y;
	                m[x][y]=2;
	                gotoxy(x,y);
	                cout<<"M";
	                if(m[x][y-1]==4) CheckDoor(1);
	            }
	            else if(a==2){
	                 while(m[x][y]!=6){
	                    y++;
	                }
	                t_x=x;
	                t_y=y;
	                m[x][y]=2;
	                gotoxy(x,y);
	                cout<<"M";
	                if(m[x][y+1]==4) CheckDoor(2);
	            }
	    }
	    void InterDoor(){
	        int InterAction=1;
	        int u=0;
	        int d=0;
	        int up=1;
	        int down=1;
	        int a=0;
	        int check=0;
	        m[x][y]=0;
	        gotoxy(x,y);
	        cout<<" ";
	        if(m[x][y+1]==4&&m[x][y-1]==4) InterAction=2;
	        if(InterAction==1){
	            if(m[x][y+1]==4) a=2;
	            else if(m[x][y-1]==4) a=1;
	            if(a==2){
	               while(m[x][y]!=6){
	                    y++;
	                }
	                t_y=y;
	                while(1){
	                    t_y++;
	                    if(m[x][t_y]==6){
	                        check=1;
	                        break;
	                    }
	                    else if(m[x][t_y]==0) break;
	                }
	            }
	            else  if(a==1){
	               while(m[x][y]!=6){
	                    y--;
	                }
	                t_y=y;
	                while(1){
	                    t_y--;
	                    if(m[x][t_y]==6){
	                        check=1;
	                        break;
	                    }
	                    else if(m[x][t_y]==0) break;
	                }
	            }
	            t_x=x;
	            t_y=y;
	            m[x][y]=2;
	            gotoxy(x,y);
	            cout<<"M";
	            if(a==1&&check==1){
	                if(m[x][y-1]==4) CheckDoor(1);
	            }
	            else if(a==2&&check==1){
	                if(m[x][y+1]==4) CheckDoor(2);
	            }
	        }
	        else if(InterAction==2){
	             while(u==0||d==0){
	                if(m[x][y-up]==6) u=1;
	                else if(m[x][y-up]==0) u=2;
	                else if(u==0){
	                    if(m[x][y-up]==4) up++;
	                }
	                if(m[x][y+down]==6) d=1;
	                else if(m[x][y+down]==0) d=2;
	                else if(d==0){
	                    if(m[x][y+down]==4) down++;
	                }
	            }
	            if(u==1&&d==2){
	                y=y-up;
	                t_x=x;
	                t_y=y;
	                m[x][y]=2;
	                gotoxy(x,y);
	                cout<<"M";
	            }
	            else if(u==2&&d==1){
	                y=y+down;
	                t_x=x;
	                t_y=y;
	                m[x][y]=2;
	                gotoxy(x,y);
	                cout<<"M";
	            }
	            else{
	                int dice=rand()%3;
	                if(dice==1){
	                    m[x][y+down]=0;
	                    gotoxy(x,y+down);
	                    cout<<" ";
	                    y=y-up;
	                    t_x=x;
	                    t_y=y;
	                    m[x][y]=2;
	                    gotoxy(x,y);
	                    cout<<"M";
	                }else{
	                    m[x][y-up]=0;
	                    gotoxy(x,y-up);
	                    cout<<" ";
	                    y=y+down;
	                    t_x=x;
	                    t_y=y;
	                    m[x][y]=2;
	                    gotoxy(x,y);
	                    cout<<"M";
	                    }
	                }
	            }
	            //_sleep(1000);
	    }
	    void Move(){
	        DeBuff();
            if(x==player_x&&y==player_y) GameOver();
	        if(during()>=speed){
	            if(Buff_T==1){
	                fleeCheck(&x,&y);
	                start=clock();
	            }
	            else if(x!=player_x||y!=player_y){
	                if(a==1){
	                   if(m[t_x][t_y-i]==0||m[t_x][t_y-i]==1){
	                        gotoxy(x,y);
	                        cout<<" ";
	                        m[x][y] = 0;
	                        y--;
	                        m[x][y] = 2;
	                        t_y = y;
	                        i++;
	                   }
	                   if(m[t_x][t_y-i]==4) Empty();
	                   if(up<i){
	                        Empty();
	                    }
	                }
	                else if(a==2){
	                    if(m[t_x][t_y+i]==0||m[t_x][t_y+i]==1){
	                        gotoxy(x,y);
	                        cout<<" ";
	                        m[x][y] = 0;
	                        y++;
	                        m[x][y] = 2;
	                        t_y = y;
	                        i++;
	                    }
	                    if(m[t_x][t_y+i]==4) Empty();
	                    if(down<i){
	                        Empty();
	                    }
	                }
	                else{
	                    if(x<player_x){
	                        if(m[t_x+1][t_y]==0||m[t_x+1][t_y]==1||m[t_x+1][t_y]==6){
	                           if(m[x][y]!=6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y] = 0;
	                            };
	                            x++;
	                            if(m[x][y]!=6){
	                            m[x][y] = 2;
	                            t_x = x;
	                            }
	                            else if(m[x][y]==6){
	                                InterDoor();
	                            }
	                        }
	                        else if(m[t_x+1][t_y]==4){
	                            while(1){
	                                if(w2==1&&w1==1){
	                                    break;
	                                }
	                                if(m[t_x+1][t_y-i]==4&&w1==0){
	                                    up++;
	                                }
	                                else if(m[t_x+1][t_y-i]==0){
	                                    w1 = 1;
	                                }
	                                if(m[t_x+1][t_y+i]==4&&w2==0){
	                                    down++;
	                                }
	                                else if(m[t_x+1][t_y+i]==0){
	                                    w2 = 1;
	                                }
	                                i++;
	                            }
	                            if(up<down||up==down){
	                                a = 1;
	                                i = up;
	                                ActionRed();
	                            }else if(down<up){
	                                a = 2;
	                                i = down;
	                                ActionAdd();
	                            }
	                        }
	                    }
	                    else if(x>player_x){
	                        if(m[t_x-1][t_y]==0||m[t_x-1][t_y]==1||m[t_x-1][t_y]==6){
	                            if(m[x][y]!=6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y] = 0;
	                            };
	                            x--;
	                            if(m[x][y]!=6){
	                                m[x][y] = 2;
	                                t_x = x;
	                            }
	                            else if(m[x][y]==6){
	                                InterDoor();
	                            }
	                        }
	                        else if(m[t_x-1][t_y]==4){
	                            while(1){
	                                if(w2==1&&w1==1){
	                                    break;
	                                }
	                                if(m[t_x-1][t_y-i]==4&&w1==0){
	                                    up++;
	                                }
	                                else if(m[t_x-1][t_y-i]==0){
	                                    w1 = 1;
	                                }
	                                if(m[t_x-1][t_y+i]==4&&w2==0){
	                                    down++;
	                                }
	                                else if(m[t_x-1][t_y+i]==0){
	                                    w2 = 1;
	                                }
	                                i++;
	                            }
	                            if(up<down||up==down){
	                                a = 1;
	                                i = up;
	                                ActionRed();
	                            }else if(down<up){
	                                a = 2;
	                                i = down;
	                                ActionAdd();
	                            }
	                        }
	                    }
	                    else if(y<player_y){
	                        if(m[t_x][t_y+1]==0||m[t_x][t_y+1]==1||m[t_x][t_y+1]==6){
	                            if(m[x][y]!=6){
	                            gotoxy(x,y);
	                            cout<<" ";
	                            m[x][y] = 0;
	                            };
	                            y++;
	                            if(m[x][y]!=6){
	                                m[x][y] = 2;
	                                t_y = y;
	                            }
	                            else if(m[x][y]==6){
	                                InterDoor();
	                            }
	                        }
	                        else if(m[t_x][t_y+1]==4){
	                            CreateDoor(1);
	                            a=4;
	                        }
	                    }
	                    else if(y>player_y){
	                        if(m[t_x][t_y-1]==0||m[t_x][t_y-1]==1||m[t_x][t_y-1]==6){
	                            if(m[x][y]!=6){
	                                gotoxy(x,y);
	                                cout<<" ";
	                                m[x][y] = 0;
	                            };
	                            y--;
	                            if(m[x][y]!=6){
	                                m[x][y] = 2;
	                                t_y = y;
	                            }
	                            else if(m[x][y]==6){
	                                InterDoor();
	                            }
	                        }
	                        else if(m[t_x][t_y-1]==4){
	                             CreateDoor(2);
	                                a=4;
	                        }
	                    }
	                }
	                if(a!=4){
	                    gotoxy(x,y);
	                    cout<<"M";
	                }
	                if(a==4) Empty();
	               start=clock();
	            }
	        }
	    }
};
class BoomBoomKing:public Monster{
    private:
    	int x,y,tempx,tempy,tempx_2,tempy_2,dotx,doty,backx,backy;
    	int countx,county,boomx,boomy;
    	int timer;
    	int movedoor=1;
    	int setdoor=0;
    	int over=0;
    	double ti;
    	clock_t First;
    	clock_t End;
    	//double speed=0.3;
    public:
	    BoomBoomKing():x(2),y(2){
	        origin_speed = 0.3;
	        speed = origin_speed;
	        start=clock();
	        gotoxy(x,y);
	        cout<<"N";
	        timer=8;
	        countx=county=0;
		}
	    ~BoomBoomKing(){
	    	mobdoor[4]=0;
	    	score_all+=5;
	        //Die();
	        gotoxy(boomx,boomy);
	        cout<<' ';
	        gotoxy(x,y);
	        cout<<' ';
	        m[x][y] = 0;
	    }
		void CheckDoor(int a){
	            if(a==1){
	                while(m[DoorX][DoorY]!=6){
	                    DoorY--;
	                }
	                m[DoorX][DoorY]=0;
	                gotoxy(DoorX,DoorY);
	                cout<<" ";
	                if(m[DoorX][DoorY-1]==4) CheckDoor(1);
	            }
	            else if(a==2){
	                 while(m[DoorX][DoorY]!=6){
	                    DoorY++;
	                }
	                m[DoorX][DoorY]=0;
	                gotoxy(DoorX,DoorY);
	                cout<<" ";
	                if(m[DoorX][DoorY+1]==4) CheckDoor(2);
	            }
	        }
	    void BreakDoor(int temp_x,int temp_y){
	            DoorX = temp_x;
	            DoorY = temp_y;
	            int up=1;
	            int down=1;
	            int u=0;
	            int d=0;
	            int BreakAction = 1;//紀錄傳送門有一個門還兩個門(重疊門情況下)
	            gotoxy(DoorX,DoorY);
	            cout<<" ";
	            m[DoorX][DoorY]=0;
	            if(m[DoorX][DoorY+1]==4&&m[DoorX][DoorY-1]==4) BreakAction = 2; //破壞一個門還兩個門
	            if(BreakAction==1){
	                while(u==0&&d==0){
	                    if(m[DoorX][DoorY-up]==4){
	                            up++;
	                    }
	                    else if(m[DoorX][DoorY-up]==6){
	                            u = 1;
	                            break;
	                    }
	                    if(m[DoorX][DoorY+down]==4){
	                            down++;
	                    }
	                    else if(m[DoorX][DoorY+down]==6){
	                            d = 1;
	                            break;
	                    }
	                }
	                if(u==1){
	                    DoorY=DoorY-up;
	                    m[DoorX][DoorY]=0;
	                    gotoxy(DoorX,DoorY);
	                    cout<<" ";
	                    if(m[DoorX][DoorY-1]==4) CheckDoor(1);
	                }
	                else if(d==1){
	                    DoorY = DoorY+down;
	                    m[DoorX][DoorY]=0;
	                    gotoxy(DoorX,DoorY);
	                    cout<<" ";
	                    if(m[DoorX][DoorY+1]==4) CheckDoor(2);
	                }
	            }
	            else if(BreakAction==2){
	                while(u==0||d==0){
	                    if(m[DoorX][DoorY-up]==6||m[DoorX][DoorY-up]==0) u=1;
	                    else if(u==0){
	                        if(m[DoorX][DoorY-up]==4) up++;
	                    }
	                    if(m[DoorX][DoorY+down]==6||m[DoorX][DoorY+down]==0) d=1;
	                    else if(d==0){
	                        if(m[DoorX][DoorY+down]==4) down++;
	                    }
	                }
	                m[DoorX][DoorY-up]=0;
	                gotoxy(DoorX,DoorY-up);
	                cout<<" ";
	                m[DoorX][DoorY+down]=0;
	                gotoxy(DoorX,DoorY+down);
	                cout<<" ";
	            }
	    }
		void BoomItem(){
			for (int i=1;i<=2;i++){//右
				if (m[boomx+i][boomy]==4){
					m[boomx+i][boomy]=0;
					gotoxy(boomx+i,boomy);
					cout<<" ";
				}
				else if(m[boomx+i][boomy]==6){
	                BreakDoor(boomx+i,boomy);
				}
			}
			for (int i=1;i<=2;i++){//左
				if (m[boomx-i][boomy]==4){
					m[boomx-i][boomy]=0;
					gotoxy(boomx-i,boomy);
					cout<<" ";
				}
				else if(m[boomx-i][boomy]==6){
	                BreakDoor(boomx-i,boomy);
				}
			}
			for (int i=1;i<=2;i++){//上
				if (m[boomx][boomy-i]==4){
					m[boomx][boomy-i]=0;
					gotoxy(boomx,boomy-i);
					cout<<" ";
				}
				else if(m[boomx][boomy-i]==6){
	                BreakDoor(boomx,boomy-i);
				}
			}
			for (int i=1;i<=2;i++){//下
				if (m[boomx][boomy+i]==4){
					m[boomx][boomy+i]=0;
					gotoxy(boomx,boomy+i);
					cout<<" ";
				}
				else if(m[boomx][boomy+i]==6){
	                BreakDoor(boomx,boomy+i);
				}
			}
			if (m[boomx][boomy]==6){
				gotoxy(boomx,boomy);
				cout<<"@";
			}

		}
		double BoomTimer(){
			End=clock();
			ti=(double)(End-First)/CLOCKS_PER_SEC;
			return ti;
		}
		void Place(int xx,int yy){
			boomx=xx;
			boomy=yy;
			gotoxy(xx,yy);
			cout<<timer-3;
			First=clock();
			movedoor=0;
		}
		void Select(){
			tempx=x;
			tempy=y;
			if (x<player_x)
				tempx++;
		 	else if(x>player_x)
				tempx--;
			if (y<player_y)
				tempy++;
			else if(y>player_y)
				tempy--;
			tempx_2=tempx;
			tempy_2=tempy;
			if (tempx<player_x)
				tempx_2++;
		 	else if(tempx>player_x)
				tempx_2--;
			if (tempy<player_y)
				tempy_2++;
			else if(tempy>player_y)
				tempy_2--;
		/*	gotoxy(77,12);
				cout<<"                                                 " ;
				gotoxy(77,12);
				cout<<"tempX,Y="<<tempx<<","<<tempy;
			gotoxy(77,13);
				cout<<"                                                 " ;
				gotoxy(77,13);
				cout<<"temp_2X,Y="<<tempx_2<<","<<tempy_2;*/
			if (m[tempx_2][tempy_2]==4){//兩步後為障礙物

				if (m[tempx][tempy]==0 && movedoor==1){
					if (m[tempx][tempy-1]==4){//上
						Place(tempx,tempy);
					}
					else if (m[tempx][tempy+1]==4){//下
						Place(tempx,tempy);
					}
					else if (m[tempx-1][tempy]==4){//左
						Place(tempx,tempy);
					}
					else if (m[tempx+1][tempy]==4){//右
						Place(tempx,tempy);
					}
				}
				else if (m[tempx][tempy]==4 && m[tempx][y]==0 &&m[x][tempy]==0 &&movedoor==1){
					dotx=tempx;
					doty=tempy;
					for (;m[dotx][tempy]==4;countx++){
						dotx++;
					}
					for (;m[tempx][doty]==4;county++){
						doty++;
					}
					if (countx<county){
						Place(x,tempy);
					}
					else {
						Place(tempx,y);
					}
				}
				else if (m[tempx][tempy]==4 && movedoor==1){
					if (tempx==tempx_2)
						Place(x,tempy);
					else if (tempy==tempy_2)
						Place(tempx,y);

					else if (m[x][y-1]==4){//上
						Place(x+1,y);
					}
					else if (m[x][y+1]==4){//下
						Place(x+1,y);
					}
					else if (m[x-1][y]==4){//左
						Place(x,y-1);
					}
					else if (m[x+1][y]==4){//右
						Place(x,y-1);
					}

				}
			}
			else { //兩部後為可走
				if (m[tempx][tempy]==0){
					movedoor==1;
				}
				else if (m[tempx][tempy]==4 && m[tempx][y]==0 &&m[x][tempy]==0 &&movedoor==1){ //下一步為障礙物且靠近怪物的X,Y為空 (斜角走
					dotx=tempx;
					doty=tempy;
					for (;m[dotx][tempy]==4;countx++){
						dotx++;
					}
					for (;m[tempx][doty]==4;county++){
						doty++;
					}
					if (countx<county){
						Place(x,tempy);
					}
					else {
						Place(tempx,y);
					}
				}
				else if (m[tempx][tempy]==4 && movedoor==1 && (m[tempx][tempy-1]==4 || m[tempx][tempy+1]==4 || m[tempx-1][tempy]==4 || m[tempx+1][tempy]==4)){
					m[tempx][tempy]=0;
					gotoxy(tempx,tempy);
					cout<<" ";
					if (tempx-x>x)
						x--;
					else
						x++;
					if (tempy-y>y)
						y--;
					else
						y++;
					gotoxy(x,y);
					cout<<"N";
					Place(tempx,tempy);
					movedoor=0;
				}
			}
		}
	    void Move(){
	        DeBuff();
	        if(x==player_x&&y==player_y) GameOver();
	    	if (during()>=speed){
	            if(Buff_T==1){
	                fleeCheck(&x,&y);
	                start=clock();
	                if (timer==0){
	                        timer=8;
	                        movedoor=1;
	                    }
	                else if (BoomTimer()>=1 && over==0){
	                    if (timer>=3){
	                        gotoxy(boomx,boomy);
	                        cout<<timer-3;
	               	        if (timer==3){
	                            gotoxy(boomx,boomy);
	                            BoomItem();
	                        }
	                        timer--;
	                        movedoor=0;
	                    }
	                    else if (timer<3 && timer>0){
	                        gotoxy(boomx,boomy);
	                        cout<<" ";
	                        timer--;
	                    }
	                    if (timer==0) over=1;
	                    First=clock();
	                }
	            }
	            else {
	                Select();
	                if (movedoor==0){
	                    if (timer==0){
	                        timer=8;
	                        movedoor=1;
	                    }
	                    if (BoomTimer()>=1){
	                        if (timer>=3){
	                            gotoxy(boomx,boomy);
	                            cout<<timer-3;
	                            if (timer==3){
	                                gotoxy(boomx,boomy);
	                                BoomItem();
	                            }
	                            timer--;
	                            movedoor=0;
	                        }
	                        else if (timer<3 && timer>0){
	                            gotoxy(boomx,boomy);
	                            cout<<" ";
	                            timer--;
	                        }
	                        First=clock();
	                    }
	                    gotoxy(x,y);
	                    cout<<"N";
	                }
	                else if (movedoor==1){
	                    if (setdoor==1){
	                        m[x][y]=6;
	                        gotoxy(x,y);
	                        cout<<"@";
	                        setdoor=0;
	                        if (x<player_x)
	                            x++;
	                        else if(x>player_x)
	                            x--;
	                        if (y<player_y)
	                            y++;
	                        else if(y>player_y)
	                            y--;
	                        m[x][y]=2;
	                        gotoxy(x,y);
	                        cout<<"N";
	                    }
	                    else{
	                        m[x][y]=0;
	                        gotoxy(x,y);
	                        cout<<" ";
	                        if (x<player_x)
	                            x++;
	                        else if(x>player_x)
	                            x--;
	                        if (y<player_y)
	                            y++;
	                        else if(y>player_y)
	                            y--;
	                        if (m[x][y]==6)
	                            setdoor=1;
	                        m[x][y]=2;
	                        gotoxy(x,y);
	                        cout<<"N";
	                    }
	                }
	                start=clock();
	            }
			}
	        if(x==player_x&&y==player_y) GameOver();
	    }
};
class Linklist;
class Linklist:public DieReset{
    private:
    	Wyrd *m1;
	    Dino *m2;
	    Su   *m3;
	    Mon  *m4;
	    BoomBoomKing *m5;
	    int gt=0;
    	int mob; // 1:Wyrd  2:Dino  3:Su  4:Mon  5:BoomBoomKing
    	int allmob=0,one;
    	double Ltimer;
    	clock_t L_start;
    	clock_t L_end;
	    Object *first=NULL;
	    Object *current=NULL;
	    Object *temp=NULL;
	    Object *q;//first's
	    Food *food = new Food();
	    Player *P=new Player(food);
	public:
	    Linklist(){
	    	L_start=clock();
	    	//P=NULL;
	    	P->setp();
	    	one=1;
	    	Setfirst(P);
	    }
	    void Setfirst(Object *NewFirstnode){//first=player
	        first=NewFirstnode;
	        current=first;//when first is Player
	        current->Nextset(first);
	    }
	    double ListTimer(){
	    	L_end=clock();
	    	Ltimer = (double)(L_end - L_start)/CLOCKS_PER_SEC;
	    	return Ltimer;
		}
	    void Setnext(Object *newnode){//設定新的怪物接在環狀linklist裡
	        newnode->Nextset(current->Returnnext());
	        current->Nextset(newnode);
	        }
	    void Gotonext(){//移動current到下一車廂
	        current=current->Returnnext();
	        }
	    void Switch(int a){
	    	switch (a){
    			case 1 ://Wyrd
    				m1=new Wyrd;
    				Setnext(m1);
    				m1->Move();
    				mobdoor[0]=1;
    				break;
    			case 2 ://Dino
    				m2=new Dino;
    				Setnext(m2);
    				m2->Move();
    				mobdoor[1]=2;
    				break;
    			case 3 ://Su
    				m3=new Su;
    				Setnext(m3);
    				m3->Move();
    				mobdoor[2]=3;
    				break;
    			case 4 ://Mon
    				m4=new Mon;
    				Setnext(m4);
    				m4->Move();
    				mobdoor[3]=4;
    				break;
    			case 5 ://BoomBoomKing
    				m5=new BoomBoomKing;
    				Setnext(m5);
    				m5->Move();
    				mobdoor[4]=5;
    				break;
			}
		}
	    void Action(){

	    	gotoxy(65,18);
	    	cout<<"怪物生成大於20時生成:"<<(int)Ltimer;
	    	if (Ltimer>=20){
	    		gotoxy(86,18);
	    		cout<<"           ";
			}
	    	if (ListTimer()>=20&&one==0){//Caculate Monsters creatative timer
	    		do{
	    			mob=rand()%5+1;
	    			if (mobdoor[0]==1 && mobdoor[1]==2 && mobdoor[2]==3 && mobdoor[3]==4 && mobdoor[4]==5){
	    				allmob=1;
	    				break;
	    			}
	    			else allmob=0;
				}while(mob==mobdoor[0] || mob==mobdoor[1] || mob==mobdoor[2] || mob==mobdoor[3] || mob==mobdoor[4]);
				if (allmob==0){
					Switch(mob);
				}
				L_start=clock();
			}
			if (one==1){
				mob=rand()%5+1;
				Switch(mob);
				one=0;
			}
			while(current->Returnnext()!=first){
				if(Object::return_Buff_B()==1) Buff_B();
				current->Move();
				Gotonext();
			}
			current->Move();
			Gotonext();
			food->produce();
		}
	    void Buff_B(){//all monster Go Die
	        Object::ResetBuff_B();
	        int cc=0;
	        while(first->Returnnext()!=first){
	            Object *Temp;
	            Temp = first->Returnnext();
	            first->Nextset(Temp->Returnnext());
	            Temp->Die();
	            delete Temp;
	            cc++;
	            //_sleep(3000);
	        }
	        current=first;
	        first->Nextset(first);
	    }
};

void Gamestart(){
	HideCursor();
	int x=22;
    gotoxy(x,1);
    cout<<"  *  *                     *             *    *          *    *    *   * "<<endl;
    gotoxy(x,2);
    cout<<"******** ******            *            *    *            *   *    *  *  "<<endl;
    gotoxy(x,3);
    cout<<"  *  *   *    *    *****************   *    ***********  ****************"<<endl;
    gotoxy(x,4);
    cout<<"  ****   ******            *          **   *     *          *       *    "<<endl;
    gotoxy(x,5);
    cout<<"  *  *   *    *            *         * *  *      *        ************** "<<endl;
    gotoxy(x,6);
    cout<<"  *  *   *    *       ***********   *  *         *              *        "<<endl;
    gotoxy(x,7);
    cout<<"  ****   *    *            *           *         ******     **********   "<<endl;
    gotoxy(x,8);
    cout<<"  *  *   ******           ***          *         *              *        "<<endl;
    gotoxy(x,9);
    cout<<"******** *    *          * * *         *         ******   ************** "<<endl;
    gotoxy(x,10);
    cout<<"  *  *   *    *         *  *  *        *         *           *  *  *     "<<endl;
    gotoxy(x,11);
    cout<<" *    *  *    *        *   *   *       *         *          *   *   *    "<<endl;
	for(int i=0;i<3;i++){
		gotoxy(x,15);
	    cout<<"                           press any key                           "<<endl;
	     _sleep(200);
	    gotoxy(x,15);
	    cout<<"                                                                   "<<endl;
	    _sleep(200);
	}
	gotoxy(x,15);
	cout<<"                           press any key                           "<<endl;
	    getch();
	system("cls");
}
void GameRestart(){
	system("cls");
    int x=10;
    for(int i=0;i<3;i++){
        gotoxy(x,15);
        cout<<"               press any key to restart                           "<<endl;
        _sleep(200);
        gotoxy(x,15);
        cout<<"                                                                   "<<endl;
        _sleep(200);
	}
	gotoxy(x,15);
	cout<<"               press any key to restart                           "<<endl;
    getch();
	system("cls");
}

int main()
{
    system("cls");
	Showscore *S=new Showscore();
    S->Gamestart();
    UI *ui=new UI();
    while(ui->endgame()){
        ui->gamestartUIsetting();
        if(ui->endgame())
            return 0;
        ui->gameendreset();
        Linklist *L=new Linklist();
        do{
            S->scoreCounting();
            L->Action();
        }while(S->End());
        GameRestart();
    }
}
