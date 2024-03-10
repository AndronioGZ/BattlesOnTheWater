#include <fstream>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

//************************************************************************************************************************************
//********************************************* CLASS CBattlefield *******************************************************************
//************************************************************************************************************************************

struct PT {
	int x;
	int y;
};

#define IND (m_nDeck==4 ? 1 : m_nDeck==3 ? (j-4)/3+1 : m_nDeck==2 ? (j-10)/2+1 : (j-15))
#define bool int
#define true 1
#define false 0

class CBattleField {
private:
	bool m_Hit;
	int  m_Unkilled;
	PT   m_LastPt;
	bool m_Shot;
	int  m_Win;
	char m_HumFd[10][10];
	char m_ComFd[10][10];
	int  m_HumScr;
	int  m_ComScr;
	bool m_ShotDir;
	bool CheckHPl(int x, int y, int nDeck, int Dir);
	bool CheckCPl(int x, int y, int nDeck, int Dir);
	int  CheckHumPt(int x,int y);
	int  CheckComPt(int x,int y);
public:
	bool GetShot();
	int  Win();
	void HumShot();
	void ComShot();
	void FillHF();
	void FillCF();
	void ShowFields(bool ShowScore);
	void Help();
	friend ostream &operator <<(ostream &s, CBattleField a);
	friend istream &operator >>(istream &s, CBattleField &a);
	CBattleField();
	~CBattleField();
};

//************************************************************************************************************************************
//********************************************* CLASS CBattlefield *******************************************************************
//************************************************************************************************************************************

//************************************************************************************************************************************
//********************************** Class CBattlefield (Members) ********************************************************************
//************************************************************************************************************************************


CBattleField::CBattleField(){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			m_HumFd[i][j]='~';
			m_ComFd[i][j]='~';
		}
	}
	m_HumScr = 20;
	m_ComScr = 20;
	m_Win = 0;
	m_Shot = false;
	m_Unkilled = 0;
}

CBattleField::~CBattleField(){
}

bool CBattleField::GetShot(){
	return m_Shot;
}

int CBattleField::Win(){
	if(m_Win==0){
		return 0;
	}
	if(m_Win==1){
		cout<<"Human = Winner\n";
		return 1;
	}
	else{
		cout<<"Computer = Winner\n";
		return 2;
	}
}

bool CBattleField::CheckCPl(int x, int y, int nDeck, int Dir){
	int xx, yy;
	if(Dir==0){
		for(yy=y==0?0:y-1;yy<=y+1&&yy<10;yy++){
			for(xx=x==0?0:x-1;xx<=x+nDeck&&xx<10;xx++){
				if(m_ComFd[yy][xx]==2){
					return true;
				}
			}
		}
	}
	else{
		for(yy=y==0?0:y-1;yy<=y+nDeck&&yy<10;yy++){
			for(xx=x==0?0:x-1;xx<=x+1&&xx<10;xx++){
				if(m_ComFd[yy][xx]==2){
					return true;
				}
			}
		}		
	}
	return false;
}

bool CBattleField::CheckHPl(int x, int y, int nDeck, int Dir){
	int xx, yy;
	if(Dir==0){
		for(yy=y==0?0:y-1;yy<=y+1&&yy<10;yy++){
			for(xx=x==0?0:x-1;xx<=x+nDeck&&xx<10;xx++){
				if(m_HumFd[yy][xx]==2){
					return true;
				}
			}
		}
	}
	else{
		for(yy=y==0?0:y-1;yy<=y+nDeck&&yy<10;yy++){
			for(xx=x==0?0:x-1;xx<=x+1&&xx<10;xx++){
				if(m_HumFd[yy][xx]==2){
					return true;
				}
			}
		}		
	}
	return false;
}

void CBattleField::FillCF(){
	int x, y;
	int m_nDeck;
	int m_Dir;
	srand(time(NULL));
	for(int j=0;j<20;j++){
		if(j==0||j==4||j==7||j==10||j==12||j==14||(j>15&&j<20)){
			m_nDeck = j>15 ? 1 : j>9 ? 2 : j>3 ? 3 : 4;
			m_Dir=rand();
			m_Dir = m_Dir<16000 ? 0 : 1;
			if(m_Dir==0){				
				do{
					x = rand()%(11-m_nDeck);
					y = rand()%10;
				}while(CheckCPl(x, y, m_nDeck, m_Dir));
				for(int i=0;i<m_nDeck;i++){
					m_ComFd[y][x+i] = 2;						
				}
			}
			else{
				do{
					x = rand()%10;
					y = rand()%(11-m_nDeck);
				}while(CheckCPl(x, y, m_nDeck, m_Dir));
				for(int i=0;i<m_nDeck;i++){
					m_ComFd[y+i][x] = 2;
				}
			}
		}
	}
}

void CBattleField::FillHF(){
	int x, y;
	int m_nDeck;
	int m_Dir;
	for(int j=0;j<20;j++){
		if(j==0||j==4||j==7||j==10||j==12||j==14||(j>15&&j<20)){
			m_nDeck = j>15 ? 1 : j>9 ? 2 : j>3 ? 3 : 4;
			if(m_nDeck==1){
				m_Dir = 0;
			}
			if(m_nDeck!=1){
				do{
					cout<<"Enter the direction of the "<<IND<<" "<<m_nDeck<<"-deck ship\n";
					cin>>m_Dir;
				}while(m_Dir!=0&&m_Dir!=1);
			}
			if(m_Dir==0){				
				do{
					do{
						cout<<"Enter the X of startpoint of the "<<IND<<" "<<m_nDeck<<"-deck ship\n";
						cin>>x;
					}while(x<0||x>(10-m_nDeck));
					do{
						cout<<"Enter the Y of startpoint of the "<<IND<<" "<<m_nDeck<<"-deck ship\n";
						cin>>y;
					}while(y<0||y>9);
				}while(CheckHPl(x, y, m_nDeck, m_Dir));
				for(int i=0;i<m_nDeck;i++){
					m_HumFd[y][x+i] = 2;						
				}
				ShowFields(false);
			}
			else{
				do{
					do{
						cout<<"Enter the X of startpoint of the "<<IND<<" "<<m_nDeck<<"-deck ship\n";
						cin>>x;
					}while(x<0||x>9);
					do{
						cout<<"Enter the Y of startpoint of the "<<IND<<" "<<m_nDeck<<"-deck ship\n";
						cin>>y;
					}while(y<0||y>(10-m_nDeck));
				}while(CheckHPl(x, y, m_nDeck, m_Dir));
				for(int i=0;i<m_nDeck;i++){
					m_HumFd[y+i][x] = 2;
				}
				ShowFields(false);
			}
		}
	}
}

int CBattleField::CheckComPt(int x, int y){
	bool fl=false;
	int i=1;
	while(m_ComFd[y][x-i]!=3&&m_ComFd[y][x-i]!='~'&&(x-i>=0&&x-i<=9)){
		if(m_ComFd[y][x-i]==2){
			fl=true;
		}
		i++;
	}
	i=1;
	while(m_ComFd[y][x+i]!=3&&m_ComFd[y][x+i]!='~'&&(x+i>=0&&x+i<=9)){
		if(m_ComFd[y][x+i]==2){
			fl=true;
		}
		i++;
	}
	i=1;
	while(m_ComFd[y-i][x]!=3&&m_ComFd[y-i][x]!='~'&&(y-i>=0&&y-i<=9)){
		if(m_ComFd[y-i][x]==2){
			fl=true;
		}
		i++;
	}
	i=1;
	while(m_ComFd[y+i][x]!=3&&m_ComFd[y+i][x]!='~'&&(y+i>=0&&y+i<=9)){
		if(m_ComFd[y+i][x]==2){
			fl=true;
		}
		i++;
	}
	if(m_ComFd[y][x]==2){
		if(fl){
			m_ComFd[y][x] = 1;
			return 2;
		}
		else{
			m_ComFd[y][x] = 1;
			if(x!=9&&m_ComFd[y][x+1]!=1){
				m_ComFd[y][x+1] = 3;
				if(y!=0) m_ComFd[y-1][x+1] = 3;
				if(y!=9) m_ComFd[y+1][x+1] = 3;
			}
			if(x!=0&&m_ComFd[y][x-1]!=1){
				m_ComFd[y][x-1] = 3;
				if(y!=0) m_ComFd[y-1][x-1] = 3;
				if(y!=9) m_ComFd[y+1][x-1] = 3;
			}
			if(y!=9&&m_ComFd[y+1][x]!=1){
				m_ComFd[y+1][x] = 3;
				if(x!=0) m_ComFd[y+1][x-1] = 3;
				if(x!=9) m_ComFd[y+1][x+1] = 3;
			}
			if(y!=0&&m_ComFd[y-1][x]!=1){
				m_ComFd[y-1][x] = 3;
				if(x!=0) m_ComFd[y-1][x-1] = 3;
				if(x!=9) m_ComFd[y-1][x+1] = 3;
			}
			i=1;
			while(m_ComFd[y][x-i]!=3&&m_ComFd[y][x-i]!='~'&&(x-i>=0&&x-i<=9)){
				if(m_ComFd[y][x-i]==1){
					if(y!=0) m_ComFd[y-1][x-i] = 3;
					if(y!=9) m_ComFd[y+1][x-i] = 3;
				}
				if(x-i!=0){
					if(m_ComFd[y][x-i-1]==3||m_ComFd[y][x-i-1]=='~'){
						m_ComFd[y][x-i-1] = 3;
						if(y!=0) m_ComFd[y-1][x-i-1] = 3;
						if(y!=9) m_ComFd[y+1][x-i-1] = 3;
					}
				}
				i++;
			}
			i=1;
			while(m_ComFd[y][x+i]!=3&&m_ComFd[y][x+i]!='~'&&(x+i>=0&&x+i<=9)){
				if(m_ComFd[y][x+i]==1){
					if(y!=0) m_ComFd[y-1][x+i] = 3;
					if(y!=9) m_ComFd[y+1][x+i] = 3;
				}
				if(x+i!=9){
					if(m_ComFd[y][x+i+1]==3||m_ComFd[y][x+i+1]=='~'){
						m_ComFd[y][x+i+1] = 3;
						if(y!=0) m_ComFd[y-1][x+i+1] = 3;
						if(y!=9) m_ComFd[y+1][x+i+1] = 3;
					}
				}
				i++;
			}
			i=1;
			while(m_ComFd[y-i][x]!=3&&m_ComFd[y-i][x]!='~'&&(y-i>=0&&y-i<=9)){
				if(m_ComFd[y-i][x]==1){
					if(x!=0) m_ComFd[y-i][x-1] = 3;
					if(x!=9) m_ComFd[y-i][x+1] = 3;
				}
				if(y-i!=0){
					if(m_ComFd[y-i-1][x]==3||m_ComFd[y-i-1][x]=='~'){
						m_ComFd[y-i-1][x] = 3;
						if(x!=0) m_ComFd[y-i-1][x-1] = 3;
						if(x!=9) m_ComFd[y-i-1][x+1] = 3;
					}
				}
				i++;
			}
			i=1;
			while(m_ComFd[y+i][x]!=3&&m_ComFd[y+i][x]!='~'&&(y+i>=0&&y+i<=9)){
				if(m_ComFd[y+i][x]==1){
					if(x!=0) m_ComFd[y+i][x-1] = 3;
					if(x!=9) m_ComFd[y+i][x+1] = 3;
				}
				if(y+i!=9){
					if(m_ComFd[y+i+1][x]==3||m_ComFd[y+i+1][x]=='~'){
						m_ComFd[y+i+1][x] = 3;
						if(x!=0) m_ComFd[y+i+1][x-1] = 3;
						if(x!=9) m_ComFd[y+i+1][x+1] = 3;
					}
				}
				i++;
			}
			return 1;
		}
	}
	else{
		m_ComFd[y][x] = 3;
		return 0;
	}
}

int CBattleField::CheckHumPt(int x, int y){
	bool fl=false;
	int i=1;
	while(m_HumFd[y][x-i]!=3&&m_HumFd[y][x-i]!='~'&&(x-i>=0&&x-i<=9)){
		if(m_HumFd[y][x-i]==2){
			fl=true;
		}
		i++;
	}
	i=1;
	while(m_HumFd[y][x+i]!=3&&m_HumFd[y][x+i]!='~'&&(x+i>=0&&x+i<=9)){
		if(m_HumFd[y][x+i]==2){
			fl=true;
		}
		i++;
	}
	i=1;
	while(m_HumFd[y-i][x]!=3&&m_HumFd[y-i][x]!='~'&&(y-i>=0&&y-i<=9)){
		if(m_HumFd[y-i][x]==2){
			fl=true;
		}
		i++;
	}
	i=1;
	while(m_HumFd[y+i][x]!=3&&m_HumFd[y+i][x]!='~'&&(y+i>=0&&y+i<=9)){
		if(m_HumFd[y+i][x]==2){
			fl=true;
		}
		i++;
	}
	if(m_HumFd[y][x]==2){
		if(fl){
			m_HumFd[y][x] = 1;
			if(m_Unkilled==0){
				m_Unkilled = 1;
			}
			else{
				m_Unkilled = 2;
			}
			m_LastPt.x = x;
			m_LastPt.y = y;
			if(m_Unkilled==2){
				if(x!=0&&m_HumFd[y][x-1]==1){
					if(y!=0) m_HumFd[y-1][x-1]=3;
					if(y!=9) m_HumFd[y+1][x-1]=3;
					if(y!=0&&m_HumFd[y-1][x]=='~') m_HumFd[y-1][x]=3;
					if(y!=9&&m_HumFd[y+1][x]=='~') m_HumFd[y+1][x]=3;
					m_ShotDir = true;
				}
				if(x!=9&&m_HumFd[y][x+1]==1){
					if(y!=0) m_HumFd[y-1][x+1]=3;
					if(y!=9) m_HumFd[y+1][x+1]=3;
					if(y!=0&&m_HumFd[y-1][x]=='~') m_HumFd[y-1][x]=3;
					if(y!=9&&m_HumFd[y+1][x]=='~') m_HumFd[y+1][x]=3;
					m_ShotDir = true;
				}
				if(y!=0&&m_HumFd[y-1][x]==1){
					if(x!=0) m_HumFd[y-1][x-1]=3;
					if(x!=9) m_HumFd[y-1][x+1]=3;
					if(x!=0&&m_HumFd[y][x-1]=='~') m_HumFd[y][x-1]=3;
					if(x!=9&&m_HumFd[y][x+1]=='~') m_HumFd[y][x+1]=3;
					m_ShotDir = false;
				}
				if(y!=9&&m_HumFd[y+1][x]==1){
					if(x!=0) m_HumFd[y+1][x-1]=3;
					if(x!=9) m_HumFd[y+1][x+1]=3;
					if(x!=0&&m_HumFd[y][x-1]=='~') m_HumFd[y][x-1]=3;
					if(x!=9&&m_HumFd[y][x+1]=='~') m_HumFd[y][x+1]=3;
					m_ShotDir = false;
				}
			}
			return 2;
		}
		else{
			m_HumFd[y][x] = 1;
			m_Unkilled = 0;
			if(x!=9&&m_HumFd[y][x+1]!=1){
				m_HumFd[y][x+1] = 3;
				if(y!=0) m_HumFd[y-1][x+1] = 3;
				if(y!=9) m_HumFd[y+1][x+1] = 3;
			}
			if(x!=0&&m_HumFd[y][x-1]!=1){
				m_HumFd[y][x-1] = 3;
				if(y!=0) m_HumFd[y-1][x-1] = 3;
				if(y!=9) m_HumFd[y+1][x-1] = 3;
			}
			if(y!=9&&m_HumFd[y+1][x]!=1){
				m_HumFd[y+1][x] = 3;
				if(x!=0) m_HumFd[y+1][x-1] = 3;
				if(x!=9) m_HumFd[y+1][x+1] = 3;
			}
			if(y!=0&&m_HumFd[y-1][x]!=1){
				m_HumFd[y-1][x] = 3;
				if(x!=0) m_HumFd[y-1][x-1] = 3;
				if(x!=9) m_HumFd[y-1][x+1] = 3;
			}
			i=1;
			while(m_HumFd[y][x-i]!=3&&m_HumFd[y][x-i]!='~'&&(x-i>=0&&x-i<=9)){
				if(m_HumFd[y][x-i]==1){
					if(y!=0) m_HumFd[y-1][x-i] = 3;
					if(y!=9) m_HumFd[y+1][x-i] = 3;
				}
				if(x-i!=0){
					if(m_HumFd[y][x-i-1]==3||m_HumFd[y][x-i-1]=='~'){
						m_HumFd[y][x-i-1] = 3;
						if(y!=0) m_HumFd[y-1][x-i-1] = 3;
						if(y!=9) m_HumFd[y+1][x-i-1] = 3;
					}
				}
				i++;
			}
			i=1;
			while(m_HumFd[y][x+i]!=3&&m_HumFd[y][x+i]!='~'&&(x+i>=0&&x+i<=9)){
				if(m_HumFd[y][x+i]==1){
					if(y!=0) m_HumFd[y-1][x+i] = 3;
					if(y!=9) m_HumFd[y+1][x+i] = 3;
				}
				if(x+i!=9){
					if(m_HumFd[y][x+i+1]==3||m_HumFd[y][x+i+1]=='~'){
						m_HumFd[y][x+i+1] = 3;
						if(y!=0) m_HumFd[y-1][x+i+1] = 3;
						if(y!=9) m_HumFd[y+1][x+i+1] = 3;
					}
				}
				i++;
			}
			i=1;
			while(m_HumFd[y-i][x]!=3&&m_HumFd[y-i][x]!='~'&&(y-i>=0&&y-i<=9)){
				if(m_HumFd[y-i][x]==1){
					if(x!=0) m_HumFd[y-i][x-1] = 3;
					if(x!=9) m_HumFd[y-i][x+1] = 3;
				}
				if(y-i!=0){
					if(m_HumFd[y-i-1][x]==3||m_HumFd[y-i-1][x]=='~'){
						m_HumFd[y-i-1][x] = 3;
						if(x!=0) m_HumFd[y-i-1][x-1] = 3;
						if(x!=9) m_HumFd[y-i-1][x+1] = 3;
					}
				}
				i++;
			}
			i=1;
			while(m_HumFd[y+i][x]!=3&&m_HumFd[y+i][x]!='~'&&(y+i>=0&&y+i<=9)){
				if(m_HumFd[y+i][x]==1){
					if(x!=0) m_HumFd[y+i][x-1] = 3;
					if(x!=9) m_HumFd[y+i][x+1] = 3;
				}
				if(y+i!=9){
					if(m_HumFd[y+i+1][x]==3||m_HumFd[y+i+1][x]=='~'){
						m_HumFd[y+i+1][x] = 3;
						if(x!=0) m_HumFd[y+i+1][x-1] = 3;
						if(x!=9) m_HumFd[y+i+1][x+1] = 3;
					}
				}
				i++;
			}
			return 1;
		}
	}
	else{
		m_HumFd[y][x] = 3;
		return 0;
	}
}

void CBattleField::ComShot(){
	//srand(GetTickCount());
	bool RndCount[4]={false, false, false, false};
	int x, y;
	int i;
	i=rand()%4;
	if(!m_Unkilled){
		do{
			x = rand()%10;
			y = rand()%10;
		}while(m_HumFd[y][x]==3||m_HumFd[y][x]==1);
	}
	else{
		do{
			RndCount[i] = true;
			x=(m_LastPt.x!=0&&i==0)?m_LastPt.x-1:(m_LastPt.x!=9&&i==1)?m_LastPt.x+1:m_LastPt.x;
			y=(m_LastPt.y!=0&&i==2)?m_LastPt.y-1:(m_LastPt.y!=9&&i==3)?m_LastPt.y+1:m_LastPt.y;
			i=rand()%4;
		}while((m_HumFd[y][x]==3||m_HumFd[y][x]==1)&&
			!(RndCount[0]&&RndCount[1]&&RndCount[2]&&RndCount[3]));
		if(RndCount[0]&&RndCount[1]&&RndCount[2]&&RndCount[3]&&(m_HumFd[y][x]==3||m_HumFd[y][x]==1)){
			if(m_ShotDir){
				if(m_LastPt.x!=0&&m_HumFd[m_LastPt.y][m_LastPt.x-1]==1){
					i=2;
					do{
						if(m_LastPt.x-i>=0&&m_HumFd[m_LastPt.y][m_LastPt.x-i]!=1&&
							m_HumFd[m_LastPt.y][m_LastPt.x-i]!=3){
							x = m_LastPt.x-i;
							y = m_LastPt.y;
						}
						i++;
					}while(m_LastPt.x-i+1>=0&&(m_HumFd[m_LastPt.y][m_LastPt.x-i+1]==1||
						m_HumFd[m_LastPt.y][m_LastPt.x-i+1]==3));
				}
				if(m_LastPt.x!=9&&m_HumFd[m_LastPt.y][m_LastPt.x+1]==1){
					i=2;
					do{
						if(m_LastPt.x+i<=9&&m_HumFd[m_LastPt.y][m_LastPt.x+i]!=1&&
							m_HumFd[m_LastPt.y][m_LastPt.x+i]!=3){
							x = m_LastPt.x+i;
							y = m_LastPt.y;
						}
						i++;
					}while(m_LastPt.x+i-1<=9&&(m_HumFd[m_LastPt.y][m_LastPt.x+i-1]==1||
						m_HumFd[m_LastPt.y][m_LastPt.x+i-1]==3));
				}
			}
			else{
				if(m_LastPt.y!=0&&m_HumFd[m_LastPt.y-1][m_LastPt.x]==1){
					i=2;
					do{
						if(m_LastPt.x>=0&&m_HumFd[m_LastPt.y-i][m_LastPt.x]!=1&&
							m_HumFd[m_LastPt.y-i][m_LastPt.x]!=3){
							x = m_LastPt.x;
							y = m_LastPt.y-i;
						}
						i++;
					}while(m_LastPt.y-i+1>=0&&(m_HumFd[m_LastPt.y-i+1][m_LastPt.x]==1||
						m_HumFd[m_LastPt.y-i+1][m_LastPt.x]==3));
				}
				if(m_LastPt.y!=9&&m_HumFd[m_LastPt.y+1][m_LastPt.x]==1){
					i=2;
					do{
						if(m_LastPt.y+i<=9&&m_HumFd[m_LastPt.y+i][m_LastPt.x]!=1&&
							m_HumFd[m_LastPt.y+i][m_LastPt.x]!=3){
							x = m_LastPt.x;
							y = m_LastPt.y+i;
						}
						i++;
					}while(m_LastPt.y+i-1<=9&&(m_HumFd[m_LastPt.y+i-1][m_LastPt.x]==1||
						m_HumFd[m_LastPt.y+i-1][m_LastPt.x]==3));
				}
			}
		}
	}
	cout<<"Computer shoots...\n";
	if(CheckHumPt(x, y)){
		cout<<"Computer did some damage to you!\n";
		m_HumScr--;
		m_Shot = false;
		m_Hit = true;
		if(m_HumScr==0){
			m_Win = 2;
		}
	}
	else{
		m_Hit = false;
		m_Shot = true;
	}
}

void CBattleField::HumShot(){
	int x, y;
	do{
		do{
			cout<<"Enter the X of the point where you're going to shot\n";
			cin>>x;
		}while(x<0||x>9);
		do{
			cout<<"Enter the Y of the point where you're going to shot\n";
			cin>>y;
		}while(y<0||y>9);
	}while(m_ComFd[y][x]==3||m_ComFd[y][x]==1);
	switch(CheckComPt(x, y)){
	case 2:
		cout<<"You damaged enemy ship!\n";
		m_ComScr--;
		m_Shot = true;
		if(m_ComScr==0){
			m_Win = 1;
		}
		break;
	case 1:
		cout<<"You killed enemy ship!\n";
		m_ComScr--;
		m_Shot = true;
		if(m_ComScr==0){
			m_Win = 1;
		}
		break;
	case 0:
		m_Shot = false;
	}
}

void CBattleField::ShowFields(bool ShowScore){
	int i, j;
	char chr; 
	cout<<"    ";
	for(i=0;i<10;i++){
		cout<<i<<" ";
	}
	cout<<"    ";
	for(i=0;i<10;i++){
		cout<<i<<" ";
	}
	cout<<"\n\n";
	for(i=0;i<10;i++){
		cout<<"  "<<i<<" ";
		for(j=0;j<10;j++){
			switch(m_HumFd[i][j]){
				case 2: chr = 'O'; break;
				case 1: chr = 'C'; break;
				case 3: chr = 'v'; break;
				case 126: chr = '~';
			}
			cout<<chr<<" ";
		}
		cout<<"  "<<i<<" ";
		for(j=0;j<10;j++){
			if(m_ComFd[i][j]==2){
				cout<<"~"<<" ";
			}
			else{
				switch(m_ComFd[i][j]){
					case 1: chr = 'C'; break;
					case 3: chr = 'v'; break;
					case 126: chr = '~';
				}
				cout<<chr<<" ";
			}
		}
		cout<<"\n";
	}
	if(ShowScore){
		cout<<"\n	Computer:"<<m_ComScr<<" <> Human:"<<m_HumScr<<"\n";
	}
	cout<<"\n";
}

void CBattleField::Help(){
	cout<<"\n********************************************************************************";
	cout<<"***********************HELP FOR 'BATTLES ON THE WATER'**************************";
	cout<<"********************************************************************************\n";
	cout<<"1.'Startpoint' is the point(deck) of the ship,\nwhich is the nearest to the point (0,0)\n\n";
	cout<<"2.'X' is the horizontal coordinate (from 0 to 9)\n  'Y' is the vertical coordinate (from 0 to 9).\n\n";
	cout<<"3.The 'direction' is the direction of the ship(from the 'startpoint'):\n  right(Enter '0') or down(Enter '1').\n\n";
}

ostream &operator <<(ostream &s, CBattleField a){
	int i, j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			s<<a.m_HumFd[i][j]<<" ";
		}
		for(j=0;j<10;j++){
			s<<a.m_ComFd[i][j]<<" ";
		}
		s<<"\n";
	}
	return s;
}

istream &operator >>(istream &s, CBattleField &a){
	char ch;
	int i, j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			s>>ch;
			a.m_HumFd[i][j] = ch;
		}
		for(j=0;j<10;j++){
			s>>ch;
			a.m_ComFd[i][j] = ch;
		}
	}
	return s;
}

//************************************************************************************************************************************
//********************************** Class CBattlefield (Members) ********************************************************************
//************************************************************************************************************************************

///////////////////////////////////////////////////////
//////////////// MAIN /////////////////////////////////
///////////////////////////////////////////////////////

void save(CBattleField c, char s[]){
	ofstream t;
	t.open(s);
	t<<c;
	if(t){
		cout<<"saved with no errors\n";
	}
	t.close();
}

void load(CBattleField &c, char s[]){
	ifstream t;
	t.open(s);
	t>>c;
	if(t){
		cout<<"loaded file...\n";
	}
	t.close();
}

int MainLoop(){
	CBattleField btf;
	btf.Help();
	btf.FillCF();
	btf.FillHF();
	save(btf, "./save.sav");
	//load(btf, "E:\\save1.txt");
	btf.ShowFields(false);
	while(true){
		if(btf.Win()!=0){
			return 0;
		}
		cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>\n";
		cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>\n";
		if(!btf.GetShot()){
			btf.ComShot();
		}
		btf.ShowFields(true);
		cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>\n";
		if(btf.GetShot()){
			btf.HumShot();
		}
		btf.ShowFields(true);
		save(btf, "./save.sav");
	}
}


int main(){
	cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~WELCOME TO 'BATTLES ON THE WATER'~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	char a;
	do{
		MainLoop();
		cout<<"\aDo you want to play again?"<<(char)2<<" (y/n)\n";
		cin>>a;
	}while(a!='n');
	return 0;
}

///////////////////////////////////////////////////////
//////////////// MAIN /////////////////////////////////
///////////////////////////////////////////////////////
