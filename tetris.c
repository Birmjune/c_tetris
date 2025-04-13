//�ʿ��� ������� include 
#include <stdio.h>
#include <Turboc.h>
#include <stdio.h> 
#include <time.h>
#include <windows.h>
#include <Windows.h>

//��� ����  
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ESC 27
#define BX 5
#define BY 1
#define BW 12
#define BH 25
#define EVENT_CONTINUE_TIME 6 //�̺�Ʈ�� ���ӽð��� ��Ÿ���� ��  

void DrawScreen(); //Screen�� �׸��� �Լ� 
void SetColor(int color); //���� ���� 
void DrawBoard(); //���Ӻ��带 �׸��� �Լ�  
BOOL ProcessKey(); //Ű���� �Է¹޴� �Լ�  
void PrintBrick(BOOL Show); //������ �����ִ� �Լ�  
int GetAround(int x, int y, int b, int r); //���� �ֺ��� Ȯ���ϴ� �Լ�  
BOOL MoveDown(); //������ �Ʒ��� ������ �Լ�  
void TestFull(); //�� �� �Ǵ� �������� �� á���� Ȯ���ϴ� �Լ�  
void PrintPreview(BOOL Show); //���� ������ �̸� �����ִ� �Լ�_�����������  
void PreView(); //���� ������ �̸� �����ִ� �Լ�_�۾�����  
void PrintTime(); //����ð��� �����ִ� �Լ�  
int Time(); //����ð��� ���ϴ� �Լ�    
void PrintDesign(); //�������� ������ ���������ִ� �Լ� (������ �� ��, ���� �� ���� ���� ������) 
void textcolor(int color_number); //�۾� ���� �ٲ��ִ� �Լ�  
void Event(); //������ �̺�Ʈ�� ������ �Լ�  
void ErasePrintPreview(); //PrintPreview�� ������ �����ִ� �Լ�  
void MakeInvisible(BOOL Show); //������ ���� Ȥ�� �������ϰ� ������ִ� �Լ�   
void Print_icon(); //���� �޽��� 

typedef struct Point {
	int x, y;
}Point; //Point ����ü ����

Point Shape[][4][16] = {
	{ {0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2}, {0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2} },
	{ {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1} },
	{ {0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1}, {0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1} },
	{ {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1}, {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1} },
	{ {0,0,-1,0,1,0,-1,-1}, {0,0,0,-1,0,1,-1,1}, {0,0,-1,0,1,0,1,1}, {0,0,0,-1,0,1,1,-1} },
	{ {0,0,1,0,-1,0,1,-1}, {0,0,0,1,0,-1,-1,-1}, {0,0,1,0,-1,0,-1,1}, {0,0,0,-1,0,1,1,1} },
	{ {0,0,-1,0,1,0,0,1}, {0,0,0,-1,0,1,1,0}, {0,0,-1,0,1,0,0,-1}, {0,0,-1,0,0,-1,0,1} },
	
	{ {0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,-1,0,-1,1,-1,2,-1,3,-1,4,-1,5,-1,6,-1,7},
	{0,0,0,1,-1,0,-1,1,-2,0,-2,1,-3,0,-3,1,-4,0,-4,1,-5,0,-5,1,-6,0,-6,1,-7,0,-7,1},
	{0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,-1,0,-1,1,-1,2,-1,3,-1,4,-1,5,-1,6,-1,7},
	{0,0,0,1,-1,0,-1,1,-2,0,-2,1,-3,0,-3,1,-4,0,-4,1,-5,0,-5,1,-6,0,-6,1,-7,0,-7,1} }, //0�� ������ �Ŵ�ȭ ����  
	
	{ {0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,0,-2,1,-2,2,-2,3,-2,0,-3,1,-3,2,-3,3,-3}, 
	{0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,0,-2,1,-2,2,-2,3,-2,0,-3,1,-3,2,-3,3,-3}, 
	{0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,0,-2,1,-2,2,-2,3,-2,0,-3,1,-3,2,-3,3,-3}, 
	{0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,0,-2,1,-2,2,-2,3,-2,0,-3,1,-3,2,-3,3,-3} }, //1�� ������ �Ŵ�ȭ ����  
	
	{ {0,0,-1,0,-2,0,-3,0,0,-1,-1,-1,-2,-1,-3,-1,0,-2,-1,-2,0,-3,-1,-3,1,-3,2,-3,1,-2,2,-2},
	{0,0,1,0,2,0,3,0,2,1,3,1,2,2,3,2,0,-1,1,-1,2,-1,3,-1,0,-2,1,-2,0,-3,1,-3},
	{0,0,-1,0,-2,0,-3,0,0,-1,-1,-1,-2,-1,-3,-1,0,-2,-1,-2,0,-3,-1,-3,1,-3,2,-3,1,-2,2,-2},
	{0,0,1,0,2,0,3,0,2,1,3,1,2,2,3,2,0,-1,1,-1,2,-1,3,-1,0,-2,1,-2,0,-3,1,-3} }, //2�� ������ �Ŵ�ȭ ����  
	
	{ {0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,-2,-2,-1,-2,0,-2,1,-2,-2,-3,-1,-3,0,-3,1,-3},
	{0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,2,-2,3,-2,2,-3,3,-3,0,1,1,1,0,2,1,2},
	{0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,-2,-2,-1,-2,0,-2,1,-2,-2,-3,-1,-3,0,-3,1,-3},
	{0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,2,-2,3,-2,2,-3,3,-3,0,1,1,1,0,2,1,2} }, //3�� ������ �Ŵ�ȭ ����  
	
	{ {0,0,1,0,2,0,3,0,4,0,5,0,0,-1,1,-1,2,-1,3,-1,4,-1,5,-1,0,-2,1,-2,0,-3,1,-3},
	{0,0,-1,0,-2,0,-3,0,0,-1,-1,-1,-2,-1,-3,-1,0,-2,-1,-2,0,-3,-1,-3,0,-4,-1,-4,0,-5,-1,-5},
	{0,0,-1,0,0,-1,-1,-1,0,-2,-1,-2,-2,-2,-3,-2,-4,-2,-5,-2,0,-3,-1,-3,-2,-3,-3,-3,-4,-3,-5,-3},
	{0,0,0,-1,0,-2,0,-3,0,-4,0,-5,-1,0,-1,-1,-1,-2,-1,-3,-1,-4,-1,-5,1,-4,1,-5,2,-4,2,-5} }, //4�� ������ �Ŵ�ȭ ����
	
	{ {0,0,1,0,2,0,3,0,4,0,5,0,0,-1,1,-1,2,-1,3,-1,4,-1,5,-1,4,-2,4,-3,5,-2,5,-3},
	{0,0,1,0,0,-1,1,-1,0,-2,1,-2,0,-3,1,-3,0,-4,1,-4,0,-5,1,-5,-1,-4,-1,-5,-2,-4,-2,-5},
	{0,0,0,-1,0,-2,0,-3,1,0,1,-1,1,-2,1,-3,2,-2,2,-3,3,-2,3,-3,4,-2,4,-3,5,-2,5,-3},
	{0,0,1,0,2,0,3,0,0,-1,1,-1,2,-1,3,-1,0,-2,1,-2,0,-3,1,-3,0,-4,1,-4,0,-5,1,-5} }, //5�� ������ �Ŵ�ȭ ����  
	
	{ {0,0,1,0,0,-1,1,-1,-2,-2,-1,-2,0,-2,1,-2,2,-2,3,-2,-2,-3,-1,-3,0,-3,1,-3,2,-3,3,-3},
	{0,0,1,0,0,-1,1,-1,0,-2,1,-2,0,-3,1,-3,0,-4,1,-4,0,-5,1,-5,2,-2,3,-2,2,-3,3,-3},
	{0,0,1,0,2,0,3,0,4,0,5,0,0,-1,1,-1,2,-1,3,-1,4,-1,5,-1,2,-2,3,-2,2,-3,3,-3},
	{0,0,1,0,0,-1,1,-1,-2,-2,-1,-2,0,-2,1,-2,-2,-3,-1,-3,0,-3,1,-3,0,-4,1,-4,0,-5,1,-5} } //6�� ������ �Ŵ�ȭ ����  (index = 13) 
};


enum { EMPTY, BRICK, WALL, PRE_BRICK, CLEAN, INVISIBLE_BRICK }; //�̸����� ����, ����, �������� �߰�  
char* arTile[] = { ". ","��","��", "��", "  ", "  "};
int board[BW + 2][BH + 2];
int nx, ny;
int brick, rot;
int p_brick, p_rot;
int score = 0;
int best_score=0;
int event = 0;
time_t start;
time_t event_time = 0;
int block_cnt = 0;
int event_cnt = 0;
int clear_lines = 0;

void main()
{
	int nFrame, nStay;
	int x = 40;
	int y= 8;
	
	setCursorType(NOCURSOR);
	clearScreen();
	
	int level = 0; //���� ���� (1-6) ������ ���̴� ������ �������� �ӵ�  
	
	gotoXY(x,y+0);printf("����������������");Sleep(100);
	gotoXY(x,y+1);printf("�����  ����    ������");Sleep(100);
	gotoXY(x,y+2);printf("�����              ���  ��");Sleep(100);
	gotoXY(x,y+3);printf("������  ��  ��  ������");Sleep(100);
	gotoXY(x,y+4);printf("���  �������������");Sleep(100);
	gotoXY(x,y+5);printf("                     kim & cha");Sleep(100);
	gotoXY(x+5,y+2);printf("   T E T R I S");Sleep(100);
	
	gotoXY(x, y+8); puts("Select Level From 1 to 6");
	gotoXY(x,y+9); puts("Press the number");
	
	gotoXY(x,y+11); printf("  ��   : TURN");     
	gotoXY(x,y+12); printf("��  �� : Left / Right");     
	gotoXY(x,y+13); printf("  ��   : DOWN");
	
	char ch1 = getch();
	while ((ch1 != '1') && (ch1 != '2') && (ch1 != '3') && (ch1 != '4') && (ch1 != '5') && (ch1 != '6'))
	ch1 = getch();
	
	setCursorType(NOCURSOR);
	gotoXY(x, y+15); printf("������ �����ϰڽ��ϴ�! ");
	Sleep(2000);
	clearScreen();

	for (x = 0; x < BW + 2; x++) {
		for (y = 0; y < BH + 2; y++) {
			board[x][y] = (y == 0 || y == BH + 1 || x == 0 || x == BW + 1) ? WALL : EMPTY;
		}
	}
	DrawScreen();
	
	//���ӽ��� �ð� ���  
	start = time(NULL);
	
	//������ ���� ������ �������� �ӵ��� ����, 1.5�� ������ ����������  
	if (ch1 == '1')
		nFrame = 20;
	else if (ch1 == '2')
		nFrame = (int)((double)20/1.5);
	else if (ch1 == '3')
		nFrame = (int)((double)20/1.5/1.5);
	else if (ch1 == '4')
		nFrame = (int)((double)20/1.5/1.5/1.5);
	else if (ch1 == '5')
		nFrame = (int)((double)20/1.5/1.5/1.5/1.5);
	else
		nFrame = (int)((double)20/1.5/1.5/1.5/1.5/1.5);


	for (; 1;) {
	
	if(score > best_score){
		Print_icon();
	}
	
	//������ Ư�� ���� ������ ������ �̺�Ʈ �߻�  
	if (score >= 3 * event_cnt + 1) { 
		Event();      
	}
	
	//�ð��� ������ �ð��� ������ ������ �̺�Ʈ�� ����  
	else if (Time() - event_time < EVENT_CONTINUE_TIME){
		;
	}
	
	//�ð��� ���� �Ŀ��� �̺�Ʈ�� 0������ �ʱ�ȭ  
	else {
		event = 0;
		if (Time() - event_time < EVENT_CONTINUE_TIME + 6) {
			MakeInvisible(FALSE);
			clearScreen();
			DrawScreen();
		}
	}

	brick = random(7); //���� ����  

	//������ġ ����  
	if (event != 2){
		nx = BW / 2;
		ny = 3;
	}
	else {
		nx = BW / 3;
		ny = 4;
	}
	
	rot = 0;
	p_rot = 0; //�ʱ�ȸ�� ����  

	if (event != 2)
		brick = p_brick; //�̸����⿡ ���� ������ ���� �������� ������  
	else
		brick = p_brick+7; //�Ŵ������ ��� brick�� �Ŵ��ϰ� ó��  
	
	p_brick = random(7); //�̸����� ���� ����  

	//�����ǿ� ���� ���� ���  
	PrintBrick(TRUE);
	
	PreView();
	ErasePrintPreview();
	PrintPreview(TRUE);
	
	PrintDesign();  
	
	if (GetAround(nx, ny, brick, rot) != EMPTY) break;
		nStay = nFrame;
		for (; 2;) {
			PrintTime(TRUE); //����ð� ���  
			if (--nStay == 0) {
				nStay = nFrame;
				if (MoveDown()) break;
			}
			if (ProcessKey()) break;
			delay(1000 / 50);
		} 
	
	}
	
	clearScreen();
	textcolor(13);
	gotoXY(30, 12); puts("G A M E  O V E R");
	textcolor(7);
	gotoXY(40, 14); printf("   ���� : %d\n\n\n\n\n", score); //�������� ���  
	
	if(score>best_score){ //�ְ���� ���Ž� 
		FILE* file=fopen("score.txt", "wt"); //score.dat�� ���� ����                
	
		gotoXY(41,16); printf("BEST SCORE!");

		if(file==0){ //���� �����޼���  
		    gotoXY(0,0); 
		    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"SCORE.DAT\"");
		}
		else{
		    fprintf(file,"%d", score);
		    fclose(file);
		}
	}
	setCursorType(NORMALCURSOR);
	Sleep(1000);
	FILE *file=fopen("score.txt", "rt"); // score.txt������ ���� 
	
	if(file==0){best_score=0;} //������ ������ �ְ������� 0 
	else {
		fscanf(file,"%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
		fclose(file); //���� ���� 
	}
}

void DrawScreen()
{

	FILE *file=fopen("score.txt", "rt"); // score.txt������ ���� 
	if(file==0){best_score=0;} //������ ������ �ְ������� 0 
	else {
		fscanf(file,"%d", &best_score); // ������ ������ �ְ������� �ҷ��� 
		fclose(file); //���� ���� 
	}

	int x, y;
	
	for (x = 0; x < BW + 2; x++) {
		for (y = 0; y < BH + 2; y++) {
			gotoXY(BX + x * 2, BY + y);
			if (arTile[board[x][y]] != arTile[INVISIBLE_BRICK])
				puts(arTile[board[x][y]]); //���������� �ƴ� ���� �״�� ���  
			else
				puts(". "); //���������� ���� .���� ���  
		}
	}
	
	//���� �⺻���� ��� 
	gotoXY(50, 3); puts("Tetris By kim & cha");
	gotoXY(50, 5); puts("�¿�:�̵�, ��:ȸ��, �Ʒ�:����");
	gotoXY(50, 7); puts("����:���� ����");  
}

void DrawBoard()
{
int x, y;

	for (x = 1; x < BW + 1; x++) {
		for (y = 1; y < BH + 1; y++) {
			gotoXY(BX + x * 2, BY + y);
		puts(arTile[board[x][y]]);
		}
	}
}

BOOL ProcessKey()
{
	int ch, trot;
	
	if (kbhit()) {
		ch = getch();
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
			switch (ch) {
			case LEFT:
				if (GetAround(nx - 1, ny, brick, rot) == EMPTY) {
					PrintBrick(FALSE);
					nx--;
					if (event != 1)
				    	PrintBrick(TRUE); //�������� ������ �������� ���� ��츸 ������ ������  
				}
				break;
			case RIGHT:
				if (GetAround(nx + 1, ny, brick, rot) == EMPTY) {
					PrintBrick(FALSE);
					nx++;
				  	if (event != 1)
				     	PrintBrick(TRUE); //�������� ������ �������� ���� ��츸 ������ ������ 
				}
				break;
			case UP:
				trot = (rot == 3 ? 0 : rot + 1);
				if (GetAround(nx, ny, brick, trot) == EMPTY) {
					PrintBrick(FALSE);
					rot = trot;
					if (event != 1)   
					  	PrintBrick(TRUE); //�������� ������ �������� ���� ��츸 ������ ������ 
				}   
				break;
			case DOWN:
				if (MoveDown()) {
				    return TRUE;
				}
				break;
			}	
		}
		else {
			switch (ch) {
				case ' ':
					while (MoveDown() == FALSE) { ; }
				return TRUE;
			}
		}
	}
	return FALSE;
}

void PrintBrick(BOOL Show)
{
	int i;
	
	if (event != 2){
	for (i = 0; i < 4; i++) {
		gotoXY(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + ny);
		puts(arTile[Show ? BRICK : EMPTY]);
	}

}
	else { //�Ŵ���� ���  
		for (i = 0; i < 16; i++) {
			gotoXY(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + ny);
			puts(arTile[Show ? BRICK : EMPTY]);
		}
	}

	//������ ������ ��ġ�� �̸� �����ִ� �ڵ� (��, ���� ������ ����ȭ�� ��� �� �ڵ尡 �۵��Ǹ� �̺�Ʈ�� �ǹ̰� �����Ƿ� Ư�� �̺�Ʈ�� �� ����ó��) 
	if (event != 3) {
		if (GetAround(nx, ny, brick, rot) == EMPTY){
			int pre_ny = ny;
			while (GetAround(nx, pre_ny, brick, rot) == EMPTY) {
				pre_ny++;
			}
			pre_ny--;
			if (pre_ny != ny) {
				if (event != 2){
					for (i = 0; i < 4; i++) {
					    gotoXY(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + pre_ny);
					    puts(arTile[Show ? PRE_BRICK : EMPTY]);
					}
				}
				else {
					for (i = 0; i < 16; i++) {
					    gotoXY(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + pre_ny);
					    puts(arTile[Show ? PRE_BRICK : EMPTY]);
					}
				}   
			}   
		}
	} 
}

// ������ ���� ������ �̸� �����ִ� �ڵ�  
void PrintPreview(BOOL Show)
{
	int i;
	if (event != 2){
		for (i = 0; i < 4; i++){
			gotoXY(27 + (Shape[p_brick][p_rot][i].x + nx) * 2, 3 + Shape[p_brick][p_rot][i].y + ny);
			puts(arTile[Show ? BRICK : CLEAN]);
		}
	}
	else {
		for (i = 0; i < 4; i++){
			gotoXY(31 + (Shape[p_brick][p_rot][i].x + nx) * 2, 1 + Shape[p_brick][p_rot][i].y + ny);
			puts(arTile[Show ? BRICK : CLEAN]);
		}
	}
}

//PrintPreview�� �����ִ� �Լ�. ���� �׸� �� ��ġ�� �ʵ��� �Ѵ�  
void ErasePrintPreview(){
	int i, j;
	for (i=32; i<36; i++){
		for (j=3; j<9; j++){
			gotoXY(i,j);
			printf(" ");
		}
	}
}

int GetAround(int x, int y, int b, int r)
{
	int i, k = EMPTY;
	
	if (event != 2){
		for (i = 0; i < 4; i++) 
		k = max(k, board[x + Shape[b][r][i].x][y + Shape[b][r][i].y]);   
	}
	else { //�Ŵ������ ��� ����ó��  
		for (i = 0; i < 16; i++) 
		k = max(k, board[x + Shape[b][r][i].x][y + Shape[b][r][i].y]);
	}
	return k;
}

BOOL MoveDown()
{
		if (event == 1){ //�������� ������ ����ȭ�� ���, ������ �� �ؿ����� ������ ��쿡�� ������ �����ش� 
			if (GetAround(nx, ny + 1, brick, rot) != EMPTY)
			PrintBrick(TRUE);
		}
	
		if (GetAround(nx, ny + 1, brick, rot) != EMPTY) {
			TestFull();
			block_cnt++; //����� ������ 1 ����  
			return TRUE;
		}
	PrintBrick(FALSE);
	ny++;
	if (event != 1)
		PrintBrick(TRUE);   
	return FALSE;
}

void TestFull()
{
	int i, x, y, ty;
	
	if (event != 2 && event != 3){
		for (i = 0; i < 4; i++) 
			board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = BRICK;
	}
	else if (event == 3){
		for (i=0; i<4; i++)
		board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = INVISIBLE_BRICK; //��������  
	}
	else {
		for (i = 0; i < 16; i++) 
		board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = BRICK; //�Ŵ����  
	} 

	for (y = 1; y < BH + 1; y++) {
		for (x = 1; x < BW + 1; x++) 
			if (board[x][y] != BRICK) break;
		if (x == BW + 1) {
			for (ty = y; ty > 1; ty--) {
				for (x = 1; x < BW + 1; x++) 
				    board[x][ty] = board[x][ty - 1];
				}
			DrawBoard();
			score += 1; //���� 1 ����  
			clear_lines++; //������ ���� �� 1 ����  
			delay(100);
		}
	}
}

//���� �����̶�� ���� ȭ�鿡 ǥ���� �ִ� �ڵ�  
void PreView()
{
	gotoXY(36, 3); puts(" ��������\n");
	gotoXY(35, 4); puts("              \n");
	gotoXY(35, 5); puts("              \n");
	gotoXY(35, 6); puts("              \n");
	gotoXY(35, 7); puts("              \n"); 
	gotoXY(35, 8); puts("              \n");
	gotoXY(35, 9); puts("              \n");
	gotoXY(35, 10); puts("              \n");
	gotoXY(35, 11); puts("              \n");
}

//���� �ð��� �����ִ� �ڵ�  
int Time(){
	int d = (int)(time(NULL)-start);
	return d;
}

//����ð� ����ϴ� �ڵ�  
void PrintTime(){
	int d = Time();
	gotoXY(35, 12); printf("����ð�: %d�� ", d);
}

//textcolor�� �ٲٴ� �Լ� 
void textcolor(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}


//ȭ�� ���� ������ �Լ�   
void PrintDesign(){

	//�̺�Ʈ�� ���� ��� ���  
	if (event == 0){
		gotoXY(35,16); printf("���� �̺�Ʈ ����                                                "); 
	}
	else if (event == 1){
		textcolor(12);
		gotoXY(35,16); printf("���� �������� ������ ���������ϴ�!                             ");
		textcolor(7);
	} 
	else if (event == 2) {
		textcolor(10);
		gotoXY(35,16); printf("���� �Ŵ��� ������ �����ɴϴ�!                                    "); 
		textcolor(7); 
	}
	else {
		textcolor(9);
		gotoXY(35,16); printf("�Ǹ��� �峭���� �׾Ƴ��� ������ �� �� �����ϴ�!         "); 
		textcolor(7);
	}

	gotoXY(35,18); printf("������ �� ��: %d��", clear_lines); 
	gotoXY(50, 8); printf("�ְ� ���� : %d", best_score);
	gotoXY(50, 9); printf("���� : %d", score);
	gotoXY(35, 14); printf("���� ���� ��: %d��", block_cnt); //���� ���� ǥ��  
}

void Event(){
	event = rand()%3 + 1; //1~3 �� ������ �̺�Ʈ ��ȣ ����  
	event_time = Time();
	event_cnt++; //����� �̺�Ʈ �� 1 ����  
	if (event == 3){
		//���� ���� ����ȭ 
		MakeInvisible(TRUE); 
		clearScreen();
		DrawScreen();
	}
}

//�ְ����� �޼� ���� �޼��� ���  
void Print_icon(){
	int x,y;
	x=90;
	y = 3;
	gotoXY(x,y+0);printf("��������������"); Sleep(100);
	gotoXY(x,y+1);printf("�����  ����    ����"); Sleep(100);
	gotoXY(x,y+2);printf("�����              ���"); Sleep(100);
	gotoXY(x,y+3);printf("������  ��  ��  ����"); Sleep(100);
	gotoXY(x,y+4);printf("���  �����������"); Sleep(100); 
	gotoXY(x, y+8); puts("�ְ� ������ �޼��ϼ̽��ϴ�!"); Sleep(100);
}

//�׾Ƴ��� �������� ���� Ȥ�� �������ϰ� ����� �Լ�. Show�� ��/������ ���� �ɼ��� �޶���. 
void MakeInvisible(BOOL Show){
	int x, y;
	for (x = 1; x < BW + 1; x++) {
		for (y = 1; y < BH + 1; y++) {
			if (Show){
				if (board[x][y] == BRICK)
					board[x][y] = INVISIBLE_BRICK;
			}
			else {
				if (board[x][y] == INVISIBLE_BRICK)
					board[x][y] = BRICK;
			}
		}
	}
}
