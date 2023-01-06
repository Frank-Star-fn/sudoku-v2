#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <windows.h>
#define ll long long
#define cer(x) cerr<<(#x)<<" = "<<(x)<<'\n'
using namespace std;
const int N=50; // ��������С 
int a[N][N]; // �����ĸ������� 
int b[N][N]; // ��¼�Ƿ��ǳ�ʼ���� 

int n=9; // �����С��n����[2,9] 
int cnt=0; // ��¼�Ѿ����õĸ��� 

int random(int n){
	return rand()%n;
}

bool ckline(int x,int a[N][N]){ // ����� 
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		if(a[x][i]!=0){
			if(mp[a[x][i]]==1)return 0; // ���Ϸ� 
			mp[a[x][i]]=1;
		}
	}
	return 1; // �Ϸ� 
}
bool ckcol(int y,int a[N][N]){ // ����� 
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		if(a[i][y])
		if(mp[a[i][y]]==1)return 0; // ���Ϸ� 
		mp[a[i][y]]=1;
	}
	return 1; // �Ϸ� 
}

int F1; // �Ƿ����� 
int a2[N][N]; // ������
int ans[N][N]; // ��¼�� 

void dfs2(int num){
	if(F1)return; 
	if(num>n*n){ // �ݹ�߽磬������ 
		F1=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				ans[i][j]=a2[i][j];
			}
		}
		return;
	}
	
	int x=(num+n-1)/n , y=(num-1)%n+1;
	for(int i=1;i<=n;i++){ // ö�� 
		a2[x][y]=i;
		if(ckline(x,a2) && ckcol(y,a2)){ // �Ϸ� 
			dfs2(num+1); // ������һ�׶� 
		}else{ // ���Ϸ���׼������ 
			a2[x][y]=0; // ����ǰ�Ȼ�ԭ�ֳ� 
		}
		if(F1==1)return; // �ҵ��⣬�˳� 
	} 
}

void setnum(){ // ���ó�ʼֵ 
	srand((unsigned)time(0));
	
	// ��õ�һ�� 
	map<int,bool> mp;
	for(int i=1;i<=n;i++){
		int t1=random(n)+1;
		while(mp[t1]==1){ // ѡ���� 
			t1=random(n)+1; // ����ѡ 
		}
		a2[1][i]=t1;
		mp[a2[1][i]]=1;
	}

	F1=0; 
	dfs2(n+1); 
	
	// ѡ��num��������ʾ(�����̶�Ϊnum), num����[1,n*n-1] 
	int num=n;
	for(int i=1;i<=num;i++){
		ll x=random(n)+1,y=random(n)+1; // �����һ��λ�� 
		while(b[x][y]==1){ // �Ѿ�ѡ�� 
			x=random(n)+1,y=random(n)+1; // ����ѡ 
		}	
		a[x][y]=ans[x][y];
		b[x][y]=1;
		cnt++; 		
	}
}

void line(){ // ������ 
	int h=n*3;
	cout<<"  ";
	for(int i=1;i<=h;i++)cout<<"-";
	cout<<endl;
}
void SetColorAndBackground(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void print(){
	system("cls"); // ���� 
	cout<<"   ";
	for(int i=1;i<=n;i++)cout<<i<<"  ";
	cout<<endl;
	line();
	for(int i=1;i<=n;i++){
		cout<<i<<"  "; 
		for(int j=1;j<=n;j++){
			if(a[i][j]==0)cout<<'-'<<"  ";
			else{
				if(b[i][j]==1){ // ��ʼ����
					cout<<a[i][j]<<"  ";
				}else{ // ���ǳ�ʼ����
					SetColorAndBackground(6,0);
					cout<<a[i][j];
					SetColorAndBackground(7,0);
					cout<<"  ";
				} 
			} 
		}
		cout<<endl;
		line();
	}
} 

void interact(){ // ���û����� 
	int x,y,val;
	cout<<"����x y val��"; 
	while(cin>>x>>y>>val){		
		if(x>=1 && x<=n && y>=1 && y<=n){
			if(val>=1 && val<=n){ // ���ò��� 
				if(b[x][y]==0){ // ���ǳ�ʼλ��,���Է��� 
					int num0=0; // ���ڼ�¼ԭ�ȵ����� 
					if(a[x][y]!=0)num0=a[x][y]; // ԭ�������֣���¼ԭ�ȵ����� 
					else cnt++; // ԭ��û�����֣����ۼӷ��õ��������� 
					
					a[x][y]=val;
					
					if(!ckline(x,a) || !ckcol(y,a)){ // �л����г�ͻ 
						cout<<"���ﲻ�ܷ���"<<val<<endl;
						
						// �ָ��ֳ�
						if(num0==0)cnt--; // ԭ��û�����֣������� 
						a[x][y]=num0; // �Ż�ȥ 
					}else{ // ���Է��� 
						print();
					} 
				}else{ // b[x][y]==1,��ʼλ�ò��ܷ���
					cout<<"��ʼλ�ò��ܷ���"<<endl;
				}
				if(cnt==n*n){ // ������ 
					cout<<"��ϲ�㣬���ʤ�ˣ�"<<endl;
					break; 
				} 
				
			}else if(val==0){ // �������� 
				if(b[x][y]==0){ // ���ǳ�ʼλ��
					if(a[x][y]!=0){
						cnt--; 
						a[x][y]=0;
						print();
					}else{
						cout<<"û�����ֵĵط����ܳ���"<<endl;
					}
				}else{ // b[x][y]==1,��ʼλ�ò��ܳ���
					cout<<"��ʼλ�ò��ܳ���"<<endl;
				}
				
			}else{
				cout<<"�������ݲ��Ϸ�,valӦ����[0,n]��Χ��"<<endl;
			}

		}else{
			cout<<"�������ݲ��Ϸ�,�±�Խ��"<<endl;
		}
		cout<<"����x y val��"; 
	}
}

void play(){
	print();
	string welcome="Welcome!";
	int len1=welcome.size();
	int h=(n*3-len1)/2;
	cout<<"  ";
	for(int i=1;i<=h;i++)cout<<' ';
	cout<<welcome<<endl;
	line();
	interact(); 
}

int main(){
//	clock_t start,finish;
//	start=clock();
	
	setnum(); // ���ó�ʼֵ 
	
//	finish=clock();
//	double Times=(double)(finish-start)/CLOCKS_PER_SEC;
//	cout<<Times<<endl;
	
	play(); // ��ʼ��Ϸ 	
    return 0;
}
/*
   1  2  3  4
  ------------
1  4  3  2  1
  ------------
2  1  2  3  4
  ------------
3  2  1  4  3
  ------------
4  3  4  1  2
  ------------
��ϲ�㣬���ʤ�ˣ�

*/
