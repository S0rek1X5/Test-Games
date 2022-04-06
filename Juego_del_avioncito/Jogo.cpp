#include <iostream>
#include <windows.h>
#include <conio.h>
#include<stdlib.h>
#include <list>
using namespace std;
void gotoxy(int x, int y){
	HANDLE hCon; COORD dwPos;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hCon, dwPos);
}
void OcultarCursor(){
	HANDLE hCon; COORD dwPos;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize= 2;
	cci.bVisible= FALSE;
	SetConsoleCursorInfo(hCon,&cci);
}

void pintar_limites(){
	for(int i=2;i<78;i++){
		gotoxy(i,3);printf("%c",205);
		gotoxy(i,33);printf("%c",205);
	}
	for(int i=4;i<33;i++){
		gotoxy(2,i);printf("%c",186);
		gotoxy(77,i);printf("%c",186);
	}
	gotoxy(2,3);printf("%c",201);
	gotoxy(2,33);printf("%c",200);
	gotoxy(77,3);printf("%c",187);
	gotoxy(77,33);printf("%c",188);
}

class NAVE{
	int x,y;
	int corazones;
	int vidas;
public:
	int X(){ return x;}
	int Y(){ return y;}
	int VID(){ return vidas;}
	void COR() { corazones--;}
	NAVE(int _x, int _y, int _corazones,int _vidas): x(_x),y(_y),corazones(_corazones),vidas(_vidas){}
	void pintar();
	void borrar();
	void mover();
	void pintar_corazones();
	void morir();
};

void NAVE::pintar(){
	gotoxy(x,y);printf("  %c",206);
	gotoxy(x,y+1);printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2);printf("%c%c %c%c",30,190,30);
}
void NAVE::borrar(){
	gotoxy(x,y);printf("        ");
	gotoxy(x,y+1);printf("        ");
	gotoxy(x,y+2);printf("         ");
}
void NAVE::mover(){
	if(kbhit()){
			char tecla = getch();
			borrar();
			if(tecla=='a' && x>3) x--;
			if(tecla=='d' && x+6 <77) x++;
			if(tecla=='w' && y >4) y--;
			if(tecla=='s' && y+3 <33) y++;
			pintar();
			pintar_corazones();
		}
}
void NAVE::pintar_corazones(){
	gotoxy(50,2); printf("VIDAS %d",vidas);
	gotoxy(64,2);printf("Salud");
	gotoxy(73,2);printf("      ");
	for(int i=0;i<corazones;i++){
		gotoxy(70+i,2); printf("%c",3);
	}
}
void NAVE::morir(){
	if(corazones ==0){
		borrar();
		gotoxy(x,y);  printf("   **   ");
		gotoxy(x,y+1);printf("  ****  ");
		gotoxy(x,y+2);printf("   **   ");
		Sleep(200);
		borrar();
		gotoxy(x,y);  printf(" * ** *");
		gotoxy(x,y+1);printf("  ****  ");
		gotoxy(x,y+2);printf("*  ** *");
		Sleep(200);
		borrar();
		vidas--;
		corazones =3;
		pintar_corazones();
		pintar();
	}
}
class AST{
	int x,y;
public:
	AST(int _x, int _y): x(_x),y(_y){}
	void pintar();
	void mover();
	void choque(class NAVE &N);
};
void AST::choque(class NAVE &N){
	if( x >= N.X() && x < N.X()+5 && y>= N.Y() && y<=N.Y()+2){
		N.COR();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x = rand()%71+4;
		y=4;
	}
}
void AST::pintar(){
	gotoxy(x,y); printf("%c",185);
}
void AST::mover(){
	gotoxy(x,y); printf(" ");
	y++;
	if(y> 32){
		x = rand()%71+4;
		y=4;
	}
	pintar();
}

class BALA{
	int x,y;
	
public:
	BALA(int _x, int _y): x(_x), y(_y){}
	int X(){ return x;}
	int Y(){ return y;}
	void mover();
	bool fuera();
};
bool BALA::fuera(){
	if(y==4)return true;
	return false;
}
void BALA::mover(){
	gotoxy(x,y); printf(" ");
	y--;
	gotoxy(x,y); printf("o");
}
int main(){
	OcultarCursor();
	pintar_limites();
	NAVE N(7,7,3,3);
	N.pintar();
	N.pintar_corazones();
	AST ast1(10,4),ast2(4,8),ast3(18,15);
	
	list<BALA*> B;
	list<BALA*>::iterator it;
	
	bool game_over = false;
	while(!game_over){
		
		if(kbhit()){
			char tecla=getch();
			if(tecla=='v')
			B.push_back(new BALA(N.X()+2,N.Y()-1));
		}
		for(it=B.begin(); it!=B.end();it++){
			(*it)->mover();
			if((*it)->fuera()){
				gotoxy((*it)->X(),(*it)->Y());printf(" ");
				delete(*it);
				it = B.erase(it);
				
			}
			
		}
		ast1.mover(); ast1.choque(N);
		ast2.mover(); ast2.choque(N);
		ast3.mover(); ast3.choque(N);
		if(N.VID()==0) game_over=true;
		N.morir();
		N.mover();
		Sleep(30);
	}
	cout<<"Juego terminado, pronto espero que sepas hacer esto sin ayuda y mucho mejor";
	return 0;
}
