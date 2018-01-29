/*
 @author 	: ONKAR V.KOTASTHANED
 @version	: 1.0
 @reference	: http://sudokusolver.esy.es
*/
#include<time.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>

// MAIN MENU
void mainmenu();
// SUB MENU
void submenu();
// VALUE INPUT
void inpval();
// PRINTING
int print();
void help2();
void help3();
void rss();
int col[9][3][3], ancopcol[81], reportdata[12], totfilll, bspw;
char sno[11], sdate[11];
float per, counter;
time_t start_time, done_time;

void main() {
	// DETECTING GRAPHICS DRIVER
	int gd = DETECT, gm, errorcode;
	// GRAPHICS INITIALIZATION
	initgraph(&gd, &gm, "bgi//");
	errorcode = graphresult();
	if (errorcode != grOk) {
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}
	// GO TO MAIN MENU
	mainmenu();
}
int drawsudoku() {
	setcolor(8);
	setlinestyle(0, 0, 3);
	// VGA: 640 x 480 (639 x 479)
	line(240, 1, 639, 1);
	//EGA: 640 X 350
	line(240, 479, 639, 479);
	line(240, 1, 240, 479);
	line(639, 1, 639, 479);
	//SLEEPING LINE...
	line(240, 159, 639, 159);
	line(240, 318, 639, 318);
	//STANDING LINE...
	line(373, 1, 373, 479);
	line(506, 1, 506, 479);
	//THIN STANDING LINE
	setlinestyle(1, 4, 1);
	line(284, 1, 284, 479);
	line(328, 1, 328, 479);
	line(417, 1, 417, 479);
	line(461, 1, 461, 479);
	line(550, 1, 550, 479);
	line(593, 1, 594, 479);
	//THIN SLEEPING LINE
	line(240, 54, 636, 54);
	line(240, 107, 636, 107);
	line(240, 212, 639, 212);
	line(240, 265, 639, 265);
	line(240, 371, 639, 371);
	line(240, 424, 639, 424);
	setlinestyle(0, 0, 0);
	return (0);
}

// RAPID SUDOKU SOLVER LOGO PRINTING
void rss() {
	settextstyle(10, 0, 2);
	setcolor(11);
	outtextxy(135, 0, "RAPID SUDOKU SOLVER");
}

// AUTHOR NAME
int myname() {
	outtextxy(20, 450, "ONKAR V.KOTASTHANE");
	outtextxy(20, 460, "onkar.kotasthane@gmail.com");
	return (0);
}

void help2() {
	int y = 260;
	outtextxy(280, y, "* HELP *");
	outtextxy(10, y += 20, "* HOW TO ENTER VALUES?");
	outtextxy(10, y += 20, "1. START ENTERING VALUES ROW BY ROW.");
	outtextxy(10, y += 20, "2. USE '0'(ZERO) FOR EMPTY FIELD.");
	outtextxy(10, y += 20, "3. FOLLOW THE INSTRUCTIONS.");
	outtextxy(250, y += 20, "- PRESS ANY KEY...");
	getch();
}

void help3() {
	int y = 260;
	outtextxy(280, y, "* HELP *");
	outtextxy(10, y += 20, "* HOW TO SOLVE SUDOKU MANUALLY?");
	outtextxy(10, y += 20, "1. FILL 1~9 DIGITS IN ROWS AND COLUMNS AND 3 x 3 MATRIX IN SUCH A WAY THAT, IN");
	outtextxy(30, y += 20, "ONE ROW AND 3 x 3 MATRIX ONE DIGIT SHOULD APPEARE ONLY ONCE.");
	outtextxy(30, y += 20, "i.e DIGIT SHOULD BE UNIQUE ");
	outtextxy(10, y += 20, "2. DO NOT MOVE PRINTED DIGITS.");
	outtextxy(10, y += 20, "3. EVERY SUDOKU HAS ONLY ONE ANSWER.");
	outtextxy(10, y += 20, "4. START SOLVING TO ROW WHICH CONTAINS MORE DIGIT.");
	outtextxy(250, y += 20, "- PRESS ANY KEY...");
	getch();
}

// LOADING/ PROCESSING SCREEN
int loading() {
	int i, x = 180, y = 305, lp = 0;
	cleardevice();
	settextstyle(0, 0, 1);
	outtextxy(270, 270, "PROCESSING...");
	// 	VGA/EGA=640 x 480 pixel's  (320 x 240)
	line(175, 300, 450, 300);
	line(175, 330, 450, 330);
	line(175, 300, 175, 330);
	line(450, 300, 450, 330);
	for (i = 1; i <= 18; i++) {
		gotoxy(39, 22);
		printf("%d %", lp);
		setcolor(10);
		setfillstyle(1, 10);
		bar3d(x, y, x + 10, y + 20, 0, 1);
		if (i == 14)
			delay(150);
		else
			delay(50);
		lp += 6;
		if (i == 17)
			lp = 100;
		x += 15;
	}
	return (0);
}

// PRINTING SUDOKU FORMAT
int print(int col[][3][3]) {
	int j, i, x, y, b, r, c, copcol[81], ctr;
	char a[25];
	cleardevice();
	// DRAWING SUDOKU IN FORMAT
	drawsudoku();
	settextstyle(1, 0, 2);
	setcolor(11);
	outtextxy(0, 0, "RAPID SUDOKU SOLVER");
	settextstyle(0, 0, 1);
	setcolor(7);
	outtextxy(70, 50, "-REPORT-");
	outtextxy(0, 80, "BLANK SPACES WERE:");
	setcolor(15);
	itoa(bspw, a, 10);
	outtextxy(185, 80, a);
	setcolor(7);
	outtextxy(0, 100, "PRE FILLED WERE:");
	setcolor(15);
	itoa((81 - bspw), a, 10);
	outtextxy(185, 100, a);
	setcolor(7);
	outtextxy(70, 275, "-PROCESS-");
	settextstyle(1, 0, 4);
	setcolor(GREEN);
	outtextxy(65, 325, "DONE!");
	setcolor(7);
	settextstyle(0, 0, 1);
	setlinestyle(0, 0, 0);
	line(0, 415, 238, 415);
	outtextxy(0, 430, "DEVELOPED BY,");
	myname();

	// CONVERSION OF 3D ARRAY TO LINER ARRAY
	ctr = 0;
	for (r = 0; r < 3; r++)
		for (b = 0; b < 3; b++)
			for (c = 0; c < 3; c++)
				copcol[ctr++] = col[b][r][c];
	for (r = 0; r < 3; r++)
		for (b = 3; b < 6; b++)
			for (c = 0; c < 3; c++)
				copcol[ctr++] = col[b][r][c];
	for (r = 0; r < 3; r++)
		for (b = 6; b < 9; b++)
			for (c = 0; c < 3; c++)
				copcol[ctr++] = col[b][r][c];
	// CONVERSION END

	settextstyle(5, 0, 1);
	setcolor(15);
	ctr = 0;
	y = 15;
	for (j = 0; j < 9; j++) {
		x = 258;
		for (i = 0; i <= 8; i++) {
			setcolor(15);
			itoa(copcol[ctr++], a, 10);
			if (copcol[ctr - 1] == 0)
				outtextxy(x, y, " ");
			else {
				if (copcol[ctr - 1] == ancopcol[ctr - 1])
					setcolor(8);
				outtextxy(x, y, a);
			}
			x += 44;
		}
		y += 53;
	}
	getch();
	getch();
	submenu();
	closegraph();
	return 1;
}

// PRINTING SUDOKU
int printSudo(int prob[][3][3]) {
	int b, b2, i, j, sudo[3] = { 0, 3, 6 };
	printf("\n");
	for (b2 = 0; b2 <= 2; b2++) {
		for (i = 0; i <= 2; i++) {
			for (b = sudo[b2]; b <= sudo[b2] + 2; b++) {
				for (j = 0; j <= 2; j++)
					prob[b][i][j] != 0 ? printf(" %d", prob[b][i][j]) : printf(" -");
				printf(" ");
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}

int canPut(int prob[][3][3], int block, int row, int col, int num) //CHECKING IF NUMBER CAN BE PUT ON SELECTED FIELD
{
	int flag = 1, i, j, k, b, b2, colset[3];
	for (i = 0; i <= 2; i++)
		for (j = 0; j <= 2; prob[block][i][j] == num ? flag = 0 : NULL, j++)
			;
	(block / 3) == 0 ? b = 0 : (block / 3) == 1 ? b = 3 : (b = 6);
	for (b2 = b + 2; b <= b2; b++)
		for (j = 0; j <= 2; prob[b][row][j] == num ? flag = 0 : NULL, j++)
			;
	block == 0 || block == 3 || block == 6 ? colset[0] = 0, colset[1] = 3, colset[2] = 6 : (block == 1 || block == 4 || block == 7 ? colset[0] = 1, colset[1] = 4, colset[2] = 7 : (colset[0] = 2, colset[1] = 5, colset[2] = 8));
	for (b = 0; b <= 2; b++)
		for (j = 0; j <= 2; prob[colset[b]][j][col] == num ? flag = 0 : NULL, j++)
			;
	return flag;
}

// CHECKING IF SUDOKU IS SOLVED
int isSolved(int prob[][3][3]) {
	int flag = 1, b1, sum, b, i, j, sudo[3] = { 0, 3, 6 };
	for (b1 = 0; b1 <= 2; b1++)
		for (i = 0; i <= 2; i++) {
			for (sum = 0, b = sudo[b1]; b <= sudo[b1] + 2; b++)
				for (j = 0; j <= 2; sum += prob[b][i][j], j++)
					;
			// IF SUM IS 45
			sum != 45 ? flag = 0 : NULL;
		}
	return flag;
}

// BACKTRACK ALGO
int solve(int prob[][3][3], int block) {
	int i, j, row = 999, col = 999;
	if (block == 9) {
		isSolved(prob) ? print(prob) : NULL;
		return 0;
	}
	for (i = 0; i <= 2; i++)
		for (j = 0; j <= 2; j++)
			if (prob[block][i][j] == 0) {
				row = i;
				col = j;
				goto xx;
			}
	xx: if (row == 999 && col == 999) {
		solve(prob, block + 1);
		return 0;
	} else {
		for (i = 1; i <= 9; i++)
			if (canPut(prob, block, row, col, i)) {
				prob[block][row][col] = i;
				solve(prob, block);
				prob[block][row][col] = 0;
			}
	}
	return 0;
}

void mainmenu() {
	int i;
	cleardevice();
	rss();
	//PRINTING RAPID SUDOKU SOLVER ON TOP
	//OUTSIDE BORDER...
	setcolor(2);
	line(0, 0, 639, 0);
	line(0, 0, 0, 479);
	line(0, 479, 639, 479);
	line(639, 479, 639, 0);
	//MENU BOX...
	setcolor(2);
	line(100, 50, 539, 50);
	line(100, 250, 539, 250);
	line(100, 50, 100, 250);
	line(539, 50, 539, 250);
	line(100, 210, 539, 210);
	setcolor(15);
	settextstyle(0, 0, 1);
	outtextxy(269, 60, "MAIN MENU");
	outtextxy(150, 100, "1.   SOLVE SUDOKU");
	outtextxy(150, 120, "2.   HELP ABOUT RAPID SUDOKU SOLVER");
	outtextxy(150, 140, "3.   HOW TO SOLVE SUDOKU?");
	outtextxy(150, 160, "4.   EXIT");
	outtextxy(150, 228, "ENTER YOUR CHOICE >> ");
	gotoxy(41, 15);
	fflush(stdin);
	scanf("%d", &i);
	if (isalpha(i))
		mainmenu();
	switch (i) {
	case 1:
		submenu();
		break;
	case 2:
		settextstyle(2, 0, 5);
		setcolor(10);
		help2();
		cleardevice();
		mainmenu();
		break;
	case 3:
		settextstyle(2, 0, 5);
		setcolor(10);
		help3();
		cleardevice();
		mainmenu();
		break;
	case 4:
		closegraph();
		exit(0);
		break;
	default:
		mainmenu();
	}
}

void submenu() {
	int i;
	cleardevice();
	rss();
	// PRINTING RAPID SUDOKU SOLVER ON TOP
	// OUTSIDE BORDER...
	setcolor(2);
	line(0, 0, 639, 0);
	line(0, 0, 0, 479);
	line(0, 479, 639, 479);
	line(639, 479, 639, 0);
	// MENU BOX...
	setcolor(2);
	line(100, 50, 539, 50);
	line(100, 250, 539, 250);
	line(100, 50, 100, 250);
	line(539, 50, 539, 250);
	line(100, 210, 539, 210);
	setcolor(15);
	settextstyle(0, 0, 1);
	outtextxy(269, 60, "MAIN MENU >> SUB MENU");
	outtextxy(150, 100, "1.   3 x 3 x 3 SUDOKU");
	outtextxy(150, 120, "2.   MAIN MENU");
	outtextxy(150, 140, "3.   EXIT");
	outtextxy(150, 228, "ENTER YOUR CHOICE >> ");
	gotoxy(41, 15);
	fflush(stdin);
	scanf("%d", &i);
	if (isalpha(i))
		submenu();
	switch (i) {
	case 1:
		inpval();
		break;
	case 2:
		mainmenu();
		break;
	case 3:
		closegraph();
		exit(0);
		break;
	default:
		submenu();
	}
}

void inpval() {
	int inp, x, y, ip, i, j, k, sens, copcol[81], ctr = 0, b, r, c;
	int evx = 1;
	char ev[17] = "* ENTER VALUE >> ";
	char a[10];
	cleardevice();
	fflush(stdin);
	// DRAWING SUDOKU
	drawsudoku();

	// SCANNING VALUES IN ARRAY(LINER AND GRAPHICS)
	printf("\n\n\n\n");
	outtextxy(80, 350, "- NOTE -");
	outtextxy(0, 370, "* START ENTERING VALUES ROW");
	outtextxy(15, 390, "BY ROW.");
	outtextxy(0, 410, "* '999' TO EXIT.");
	settextstyle(1, 0, 2);
	setcolor(11);
	outtextxy(0, 0, "RAPID SUDOKU SOLVER");
	settextstyle(5, 0, 1);
	// ENTER VALUES ANIMATION
	for (evx = 1; ev[evx] != '\0'; evx++) {
		gotoxy(evx, 5);
		printf("%c", ev[evx - 1]);
		delay(100);
	}
	gotoxy(18, 5);
	y = 15;
	setcolor(7);
	bspw = 0;
	// INITIAL VALUE (IF FIRST VALUE IS ALPHABATE)
	copcol[ctr] = 9999;
	for (j = 0; j < 9; j++) {
		x = 258;
		for (i = 0; i < 9; i++) {
			xx: fflush(stdin);
			scanf("%d", &copcol[ctr++]);
			ancopcol[ctr - 1] = copcol[ctr - 1];
			gotoxy(18, 5);
			if (copcol[ctr - 1] == 999)
				submenu();
			if ((copcol[ctr - 1] > 9) || (copcol[ctr - 1] < 0)) {
				gotoxy(1, 10);
				printf("* WRONG INPUT");
				getch();
				gotoxy(1, 10);
				printf("              ");
				gotoxy(18, 5);
				printf("             ");
				gotoxy(18, 5);
				ctr -= 1;
				goto xx;
			}
			printf("             ");
			itoa(copcol[ctr - 1], a, 10);
			fflush(stdin);
			if (copcol[ctr - 1] == 0) {
				outtextxy(x, y, ".");
				++bspw;
			} else
				outtextxy(x, y, a);
			x += 44;
			gotoxy(18, 5);
		}
		y += 53;
	}
	getch();
	// LINER_ARRAY TO 3D ARRAY CONVERSION
	ctr = 0;
	for (r = 0; r < 3; r++)
		for (b = 0; b < 3; b++)
			for (c = 0; c < 3; c++)
				col[b][r][c] = copcol[ctr++];
	for (r = 0; r < 3; r++)
		for (b = 3; b < 6; b++)
			for (c = 0; c < 3; c++)
				col[b][r][c] = copcol[ctr++];
	for (r = 0; r < 3; r++)
		for (b = 6; b < 9; b++)
			for (c = 0; c < 3; c++)
				col[b][r][c] = copcol[ctr++];
	setcolor(15);
	settextstyle(0, 0, 1);
	outtextxy(0, 230, "* HIT ANY KEY TO PROCESS *");
	getch();
	// LOADING...
	loading();
	fflush(stdin);
	start_time = time(NULL);
	solve(col, 0);
	print(col);
}
