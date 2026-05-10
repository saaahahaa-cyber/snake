//move�����Ƿ��������Ŀǰ���ɡ� 
//����ҵʹ�õ����Ż����bfs�㷨�� 
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
char map[25][25];
int dir[4][2]={{-1,0},
               {1,0},
			   {0,-1},
			   {0,1}};
typedef struct snake{
	int x,y;
	struct snake* prior;
	struct snake* next; 
}snake;
int get_h(int x1,int x2,int y1,int y2){
	return abs(x1-x2)+abs(y1-y2);
}
bool SnakeDeath(int nx,int ny){
	//SnakeDeath����Ӧ��Ϊ�����֣�һ�����ж��Ƿ�ײ��Χǽ���ϰ��һ���������ж��Ƿ�ײ��������(�ܺ�ʵ��) 
	//1��
	 if(nx<=0||nx>=19||ny<=0||ny>=19){
	 	return true;
	 }
	//2:
	 if(map[nx][ny]=='o'||map[nx][ny]=='B'){
	 	return true;
	 }
	 return false;
}
typedef struct walk{
	int x;
	int y;
	int f;//�������Ǵ�ʱ��ͷ��ʳ���������С���롣 
	int h;//��������Ԥѡ�㵽ʳ��������پ��롣 
	int g;//�����õ㵽��ͷ��Ҫ�߼����� 
	//��px,py����¼ÿ�����ǰ���ڵ���������׷�ٳ��ߵ��ƶ����� 
}walk;
snake body[390];
//
//�����������ͷ����Ϊhead�����²��ô���ʱ���Խ����Ϊbody[0]���Ѿ�������λ�á�4.20�� 
//
//
//move�����Ĺ���Ϊ������һ������ʱ������߼��Ϸ����޸��ߵ�λ��(���������ͷ)�����������������һ�����򷵻�false����������к����жϡ� 
bool move(char c,snake *head){
	bool game_over=false;
	int nx;
	int ny;
//	while(ptrtail!=head){


//		ptrtail->x=ptrtail->prior->x;
//		ptrtail->y=ptrtail->prior->y;
//		ptrtail=ptrtail->prior;
//	}//���whileѭ������д��ͷָ���ƶ���ǰ�档 
	switch(c){
		case 'W':
			nx=head->x+dir[0][0];
			ny=head->y+dir[0][1];
			if(SnakeDeath(nx,ny)){
				game_over=true;
			}
			break;
		case 'S':
			nx=head->x+dir[1][0];
			ny=head->y+dir[1][1];
			if(SnakeDeath(nx,ny)){
				game_over=true;
			}
			break;
		case 'A':
			nx=head->x+dir[2][0];
			ny=head->y+dir[2][1];
			if(SnakeDeath(nx,ny)){
				game_over=true;
			}
			break;
		case 'D':
			nx=head->x+dir[3][0];
			ny=head->y+dir[3][1];
			if(SnakeDeath(nx,ny)){
				game_over=true;
			}
			break;		
	}
	return game_over;
}
//����move����������һ��ptrtailָ�룬���Ǹ�ָ���ʱ��δ���塣(4.25��ptrtailָ��õ��˶���) 
//��move��������ʹ����SnakeDeath��������ʱ��δʵ�֡�(SnakeDeath�������������ͷ����һ����ײ���ϰ�����������򷵻�true)4.21�� 
//����������������һ������move�����ж����Ƿ���Խ����ƶ������ҵ�headλ��ʳ����ʱ��������������ƶ� (Ҳ��Ҫ�õ�ptrtailָ�룬��ʱ��δʵ�֣��� 
void growth(int nx,int ny,snake* head,snake* ptrtail){
	while(ptrtail!=head){
		ptrtail->x=ptrtail->prior->x;
		ptrtail->y=ptrtail->prior->y;
		map[ptrtail->x][ptrtail->y]='B';
		ptrtail=ptrtail->prior;
	}
	head->x=nx;
	head->y=ny;
	map[nx][ny]='H';
}
char jud(int headx,int heady,int curx,int cury){
	if(curx==headx+1&&cury==heady){
		return 'S';
	}
	else if(curx==headx-1&&cury==heady){
		return 'W';
	}
	else if(curx==headx&&cury==heady+1){
		return 'D';
	}
	else{
		return 'A';
	}
}
//judge�����Ĺ���Ϊ��ȷ��һ�����У����������ǿ��ܵ��˶�·���ϵĵ� ��Ȼ�����С��Fֵ��ʼ�ң����ұ����ĸ������ҵ��ܹ��¼���ĵ㣬ֱ������ҵ�ʳ��Ϊֹ��ÿ�ҵ�һ��Ҫ��parentindex���и��¡� 
char judge(int headx,int heady,int foodx,int foody){
	int visited[20][20];
	int parx[20][20];
	int pary[20][20];
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			visited[i][j]=0;
			parx[i][j]=0;
			pary[i][j]=0;
		}
	}
    walk queue[400];
    int rear=0;
    int top=0;   
	queue[top].x=headx;
	queue[top].y=heady;
	queue[top].g=0;
	queue[top].h=get_h(queue[top].x,queue[top].y,foodx,foody);
	queue[top].f=queue[top].g+queue[top].h;
	parx[headx][heady]=-1;
	pary[headx][heady]=-1;
	top++;
	visited[headx][heady]=1;
	char ans;
	while(top>0){
		int ans2=0;
		int min=1e9;
		for(int i=0;i<top;i++){
			if(queue[i].f<=min){
				min=queue[i].f;
				ans2=i;
			}
		}
		walk temp1=queue[ans2];
		//���queue�����Ǳ���Ҫ����ġ�(Ŀǰ�ҵ��뷨������qsort��������) 
		if(map[temp1.x][temp1.y]=='F'){
			int curx=temp1.x;
		    int cury=temp1.y;
		    int prex=parx[curx][cury];
		    int prey=pary[curx][cury];
			while(!(prex==headx&&prey==heady)){
				curx=prex;
				cury=prey;
				prex=parx[curx][cury];
				prey=pary[curx][cury];
			}
			ans=jud(headx,heady,curx,cury);
			return ans;
		}
		//������һ��������������±������Ļ���ÿ���ڶ�queue��������ʱ�±��п��ܻ���ң���͵���par_idx�������⣬��׼������ʹ��ָ�����׷�١� 
		for(int i=0;i<4;i++){
			int tempx=temp1.x+dir[i][0];
			int tempy=temp1.y+dir[i][1];
			if((tempx>=0&&tempx<=19)&&(tempy>=0&&tempy<=19)&&!visited[tempx][tempy]&&(map[tempx][tempy]=='.'||map[tempx][tempy]=='F')){
				queue[top].x=tempx;
				queue[top].y=tempy;
				queue[top].h=get_h(tempx,tempy,foodx,foody);
				queue[top].g=temp1.g+1;
				queue[top].f=queue[top].g+queue[top].h;
				parx[tempx][tempy]=temp1.x;
				pary[tempx][tempy]=temp1.y;
				visited[tempx][tempy]=1;
				top++;
			}	
		}
		walk temp2;
		temp2=queue[top-1];
		queue[top-1]=queue[ans2];
		queue[ans2]=temp2;
		top--;
	}
	return 'W';
}
int main()
{ 
	
	for(int i=0;i<20;i++)
	{
	    scanf("%s",map[i]);
	}
//���ڼ�¼ʳ���λ�á� 
	int foodx;
	int foody;
	snake head;
	snake* ptrtail=NULL;
	int cnt=2;
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			if(map[i][j]=='F'){
				foodx=i;
				foody=j;
			}
			if(map[i][j]=='H'){
				head.next=NULL;
				head.prior=NULL;
				head.x=i;
				head.y=j;
				break;
			}
		}
	}
	for(int i=0;i<4;i++){
		int nx=head.x+dir[i][0];
		int ny=head.y+dir[i][1];
		if(nx>0&&nx<20&&ny>0&&ny<20&&map[nx][ny]=='B'){
			body[1].prior=&head;
			body[1].next=NULL;
			body[1].x=nx;
			body[1].y=ny;
		}
	}
	for(int i=0;i<4;i++){
		int nx=body[1].x+dir[i][0];
		int ny=body[1].y+dir[i][1];
		if(nx>0&&nx<20&&ny>0&&ny<20&&map[nx][ny]=='B'){
			body[2].prior=&body[1];
			body[2].next=NULL;
			body[2].x=nx;
			body[2].y=ny;
		}
	}	
	ptrtail=&(body[2]);
	int n;
	scanf("%d",&n);
	int score=0;
	int cnt2=0;//����ͳ���û����ָ��Ĵ�����ÿN��ָ���Ҫ�Զ�����һ�ء� 
	char c;//cͨ��һ���㷨�����õ�'w','s,'a','d'�е�һ����
	//��Ϊһ��ʼ��ʳ�������̺����˵�ͼ������޷���whileѭ�����ϣ�������Ҫ��whileѭ��������ִ��һ�����ж��Ĳ��� 	
	c=judge(head.x,head.y,foodx,foody);
	printf("%c\n",c);
	printf("%d\n",score);
	cnt2++;
	fflush(stdout);
	//��move�����жϵȵȡ�
/*	int dir2;//���ڱ��ÿ�����ߵķ������ȷ��head����һ��λ�á� 	
	bool gameover=move(c,&head);
	cnt2++;
	if(c=='W'){
		dir2=0;
	}
	else if(c=='S'){
		dir2=1;
	}
	else if(c=='A'){
		dir2=2;
	}
	else{
		dir2=3;
	}
	if(!gameover){
		int nx=head.x+dir[dir2][0];
	    int ny=head.y+dir[dir2][1];
	    snake *temp=ptrtail;
	    if(map[nx][ny]=='F'||cnt2%n==0||(map[nx][ny]=='F'&&cnt2%n==0)){
	    	if(map[nx][ny]=='F'){
	            score+=10;
	        }
	    	snake *old_tail = ptrtail;
            ptrtail = &(body[++cnt]);
            ptrtail->prior = old_tail;
            ptrtail->next = NULL;
            growth(nx, ny, &head, ptrtail);
	    }
	    else{
            map[temp->x][temp->y]='.';
	        while(temp!=&head){
	        	temp->x=temp->prior->x;
		        temp->y=temp->prior->y;
		        map[temp->x][temp->y]='B';
		        temp=temp->prior;
	        }
	        head.x=nx;
	        head.y=ny;
	        map[nx][ny]='H';
		}
	}
	*/
	int sx,sy; 
	while(fscanf(stdin,"%d %d",&sx,&sy)==2){
		if(sx==100||sy==100){
			break;
		}
		else{
			int dir2;//���ڱ��ÿ�����ߵķ������ȷ��head����һ��λ�á� 	
	        bool gameover=move(c,&head);
    	    if(c=='W'){
		        dir2=0;
    	    }
	        else if(c=='S'){
		        dir2=1;
        	}
	        else if(c=='A'){
		        dir2=2;
	        }
	        else{
		        dir2=3;
     	    }
	        if(!gameover){
		        int nx=head.x+dir[dir2][0];
	            int ny=head.y+dir[dir2][1];
	            snake *temp=ptrtail;
	            if(map[nx][ny]=='F'||cnt2%n==0||(map[nx][ny]=='F'&&cnt2%n==0)){
	    	       if(map[nx][ny]=='F'){
	                    score+=10;
	               }
	        	    snake *old_tail = ptrtail;
                    ptrtail = &(body[++cnt]);
                    ptrtail->prior = old_tail;
                    ptrtail->next = NULL;
                    growth(nx, ny, &head, ptrtail);
	            }
	            else{
                    map[temp->x][temp->y]='.';
	                while(temp!=&head){
	        	        temp->x=temp->prior->x;
		                temp->y=temp->prior->y;
		                map[temp->x][temp->y]='B';
		                temp=temp->prior;
	                }
	                head.x=nx;
	                head.y=ny;
	                map[nx][ny]='H';
		        }
    	    }
		}
		if(sx!=20)
		{
			foodx=sx;
			foody=sy;
			map[foodx][foody]='F';
		}
	    c=judge(head.x,head.y,foodx,foody); 
        printf("%c\n",c);
	    printf("%d\n",score);
	    cnt2++;
	    fflush(stdout);
/*	    bool gameover=move(c,&head);
		cnt2++;
		if(c=='W'){
			dir2=0;
		}
		else if(c=='S'){
			dir2=1;
		}
		else if(c=='A'){
			dir2=2;
		}
		else{
			dir2=3;
		}
	    if(!gameover){
		    int nx=head.x+dir[dir2][0];
	        int ny=head.y+dir[dir2][1];
	        snake *temp=ptrtail;
	        if(map[nx][ny]=='F'||cnt2%n==0||(map[nx][ny]=='F'&&cnt2%n==0)){
	        	if(map[nx][ny]=='F'){
	                score+=10;
	            }
	    	    snake *old_tail = ptrtail;
                ptrtail = &(body[++cnt]);
                ptrtail->prior = old_tail;
                ptrtail->next = NULL;
                growth(nx, ny, &head, ptrtail);
	        }
	        else{
                map[temp->x][temp->y]='.';
	            while(temp!=&head){
	                temp->x=temp->prior->x;
		            temp->y=temp->prior->y;
		            map[temp->x][temp->y]='B';
		            temp=temp->prior;
	            }
	            head.x=nx;
	            head.y=ny;
	            map[nx][ny]='H';
		    }
	    }
	    */
	}
	for(int i=0;i<20;i++){
		for(int j=0;j<20;j++){
	        printf("%c",map[i][j]);	
			if(j==19){
				printf("\n");
			}	
		}
	} 
	printf("%d",score);
	return 0;
}
//4.24��������������Ĺ��죬����������while�����������������̵������������������ϡ� 
//4.25�����ƶ��������޸�map�Ĳ����Լ�������ֲ����ߣ����ߵ��ǲ�������������������������� 
