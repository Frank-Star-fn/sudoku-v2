#pragma GCC optimize(3)
#include <bits/stdc++.h>
#include <windows.h>
#define ll long long
#define cer(x) cerr<<(#x)<<" = "<<(x)<<'\n'
using namespace std;
const int N=50; // 最大网格大小 
int a[N][N]; // 数独的各个数字 
int b[N][N]; // 记录是否是初始数据 

int n=9; // 网格大小，n属于[2,9] 
int cnt=0; // 记录已经放置的个数 

int random(int n){
	return rand()%n;
}

bool ckline(int x,int a[N][N]){ // 检查行 
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		if(a[x][i]!=0){
			if(mp[a[x][i]]==1)return 0; // 不合法 
			mp[a[x][i]]=1;
		}
	}
	return 1; // 合法 
}
bool ckcol(int y,int a[N][N]){ // 检查列 
	map<int,int> mp;
	for(int i=1;i<=n;i++){
		if(a[i][y])
		if(mp[a[i][y]]==1)return 0; // 不合法 
		mp[a[i][y]]=1;
	}
	return 1; // 合法 
}

int F1; // 是否搜完 
int a2[N][N]; // 新数组
int ans[N][N]; // 记录答案 

void dfs2(int num){
	if(F1)return; 
	if(num>n*n){ // 递归边界，搜完了 
		F1=1;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				ans[i][j]=a2[i][j];
			}
		}
		return;
	}
	
	int x=(num+n-1)/n , y=(num-1)%n+1;
	for(int i=1;i<=n;i++){ // 枚举 
		a2[x][y]=i;
		if(ckline(x,a2) && ckcol(y,a2)){ // 合法 
			dfs2(num+1); // 进入下一阶段 
		}else{ // 不合法，准备回溯 
			a2[x][y]=0; // 回溯前先还原现场 
		}
		if(F1==1)return; // 找到解，退出 
	} 
}

void setnum(){ // 设置初始值 
	srand((unsigned)time(0));
	
	// 获得第一行 
	map<int,bool> mp;
	for(int i=1;i<=n;i++){
		int t1=random(n)+1;
		while(mp[t1]==1){ // 选过了 
			t1=random(n)+1; // 重新选 
		}
		a2[1][i]=t1;
		mp[a2[1][i]]=1;
	}

	F1=0; 
	dfs2(n+1); 
	
	// 选择num个数字显示(总数固定为num), num属于[1,n*n-1] 
	int num=n;
	for(int i=1;i<=num;i++){
		ll x=random(n)+1,y=random(n)+1; // 随机抽一个位置 
		while(b[x][y]==1){ // 已经选了 
			x=random(n)+1,y=random(n)+1; // 重新选 
		}	
		a[x][y]=ans[x][y];
		b[x][y]=1;
		cnt++; 		
	}
}

void line(){ // 画横线 
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
	system("cls"); // 清屏 
	cout<<"   ";
	for(int i=1;i<=n;i++)cout<<i<<"  ";
	cout<<endl;
	line();
	for(int i=1;i<=n;i++){
		cout<<i<<"  "; 
		for(int j=1;j<=n;j++){
			if(a[i][j]==0)cout<<'-'<<"  ";
			else{
				if(b[i][j]==1){ // 初始数据
					cout<<a[i][j]<<"  ";
				}else{ // 不是初始数据
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

void interact(){ // 和用户交互 
	int x,y,val;
	cout<<"输入x y val："; 
	while(cin>>x>>y>>val){		
		if(x>=1 && x<=n && y>=1 && y<=n){
			if(val>=1 && val<=n){ // 放置操作 
				if(b[x][y]==0){ // 不是初始位置,可以放置 
					int num0=0; // 用于记录原先的数字 
					if(a[x][y]!=0)num0=a[x][y]; // 原先有数字，记录原先的数字 
					else cnt++; // 原先没有数字，先累加放置的数字数量 
					
					a[x][y]=val;
					
					if(!ckline(x,a) || !ckcol(y,a)){ // 行或者列冲突 
						cout<<"这里不能放置"<<val<<endl;
						
						// 恢复现场
						if(num0==0)cnt--; // 原先没有数字，减回来 
						a[x][y]=num0; // 放回去 
					}else{ // 可以放置 
						print();
					} 
				}else{ // b[x][y]==1,初始位置不能放置
					cout<<"初始位置不能放置"<<endl;
				}
				if(cnt==n*n){ // 放满了 
					cout<<"恭喜你，你获胜了！"<<endl;
					break; 
				} 
				
			}else if(val==0){ // 撤销操作 
				if(b[x][y]==0){ // 不是初始位置
					if(a[x][y]!=0){
						cnt--; 
						a[x][y]=0;
						print();
					}else{
						cout<<"没有数字的地方不能撤销"<<endl;
					}
				}else{ // b[x][y]==1,初始位置不能撤销
					cout<<"初始位置不能撤销"<<endl;
				}
				
			}else{
				cout<<"输入数据不合法,val应该在[0,n]范围内"<<endl;
			}

		}else{
			cout<<"输入数据不合法,下标越界"<<endl;
		}
		cout<<"输入x y val："; 
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
	
	setnum(); // 设置初始值 
	
//	finish=clock();
//	double Times=(double)(finish-start)/CLOCKS_PER_SEC;
//	cout<<Times<<endl;
	
	play(); // 开始游戏 	
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
恭喜你，你获胜了！

*/
