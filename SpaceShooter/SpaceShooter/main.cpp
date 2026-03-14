#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define screen_width 200
#define screen_height 45
#define window_width 208

void gotoxy(int x, int y);
void drawBoss();
void eraseBoss();
void bossShoot();
bool updateBossBullets();
void gameOverScreen();

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// this is the cords for destroyer
int destroyerY[3];
int destroyerX[3];

int destroyerFlag[3]; // this is a trigger when the enemy will spawn

//this is the model of the ship which is me
char tieAdvanced[6][4] = {
	{' ', '*', '*', ' '},
	{'*', '*', '*', '*'},
	{'*', '*', '*', '*'},
	{' ', '*', '*', ' '},
	{'*', ' ', ' ', '*'},
	{'*', ' ', ' ', '*'}
};

int bulletX[20];
int bulletY[20];
int bulletFlag[20];
int shipPos = window_width / 2;
int score = 0;

//special thing
int bossX;
int bossY;
bool bossFlag = false;
int bossHealth = 100;
int bossDirection = 1;


int bossBulletX[10];
int bossBulletY[10];
int bossBulletFlag[10];
int bossFireDelay = 0;


void drawBoss() {
	if (bossFlag) {
		gotoxy(bossX, bossY);     cout << "  [IIIIIIIIII]  ";
		gotoxy(bossX, bossY + 1); cout << " [HHHHHHHHHHHH] ";
		gotoxy(bossX, bossY + 2); cout << "  [IIIIIIIIII]  ";
		gotoxy(bossX, bossY - 1); cout << "HP: " << bossHealth << "   ";
	}
}

void eraseBoss() {
	for (int i = -1; i < 3; i++) {
		gotoxy(bossX, bossY + i); cout << "                ";
	}
}


void bossShoot() {
	for (int i = 0; i < 10; i++) {
		if (bossBulletFlag[i] == 0) {
			bossBulletFlag[i] = 1;
			bossBulletX[i] = bossX + 8;
			bossBulletY[i] = bossY + 3;
			break;
		}
	}
}

bool updateBossBullets() {
	for (int i = 0; i < 10; i++) {
		if (bossBulletFlag[i]) {

			gotoxy(bossBulletX[i], bossBulletY[i]); cout << " ";

			bossBulletY[i]++;


			if (bossBulletY[i] > screen_height - 2) {
				bossBulletFlag[i] = 0;
			}
			else {

				gotoxy(bossBulletX[i], bossBulletY[i]); cout << "V";


				if (bossBulletX[i] >= shipPos && bossBulletX[i] < shipPos + 4 && bossBulletY[i] >= 38) {

					return true;


				}
			}
		}
	}
	return false;
}


//------------------------------------------------------------------------------------------------


void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {

	for (int i = 0; i < screen_height; i++) {
		for (int j = 0; j < 12; j++) {
			gotoxy(0 + j, i);
			cout << "±";
			gotoxy(window_width - j, i);
			cout << "±";
		}
	}

}

void genDestroyer(int ind) {
	destroyerX[ind] = 12 + rand() % (180);
}

void drawDestroyer(int ind) {
	if (destroyerFlag[ind] == true) {
		gotoxy(destroyerX[ind], destroyerY[ind]);
		cout << " ** ";
		gotoxy(destroyerX[ind], destroyerY[ind] + 1);
		cout << "****";
		gotoxy(destroyerX[ind], destroyerY[ind] + 2);
		cout << "****";
		gotoxy(destroyerX[ind], destroyerY[ind] + 3);
		cout << "****";
		gotoxy(destroyerX[ind], destroyerY[ind] + 4);
		cout << "*  *";
		gotoxy(destroyerX[ind], destroyerY[ind] + 5);
		cout << "*  *";
		gotoxy(destroyerX[ind], destroyerY[ind] + 6);
		cout << "*  *";
	}
}

void eraseDestroyer(int ind) {
	if (destroyerFlag[ind] == true) {
		gotoxy(destroyerX[ind], destroyerY[ind]);
		cout << "    ";
		gotoxy(destroyerX[ind], destroyerY[ind] + 1);
		cout << "    ";
		gotoxy(destroyerX[ind], destroyerY[ind] + 2);
		cout << "    ";
		gotoxy(destroyerX[ind], destroyerY[ind] + 3);
		cout << "    ";
		gotoxy(destroyerX[ind], destroyerY[ind] + 4);
		cout << "    ";
		gotoxy(destroyerX[ind], destroyerY[ind] + 5);
		cout << "    ";
		gotoxy(destroyerX[ind], destroyerY[ind] + 6);
		cout << "    ";
	}
}

void resetDestroyer(int ind) {
	eraseDestroyer(ind);
	destroyerY[ind] = 1;
	genDestroyer(ind);
}

void drawTieAdvanced() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			gotoxy(j + shipPos, i + 38);
			cout << tieAdvanced[i][j];
		}
	}
}

void eraseTieAdvanced() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			gotoxy(j + shipPos, i + 38);
			cout << " ";
		}
	}
}

// everything about bullets
void drawBullet(int ind) {
	if (bulletFlag[ind] == true) {
		gotoxy(bulletX[ind], bulletY[ind]);
		cout << "^";
	}
}

void eraseBullet(int ind) {
	if (bulletFlag[ind] == true) {
		gotoxy(bulletX[ind], bulletY[ind]);
		cout << " ";
	}
}

void shoot() {
	for (int i = 0; i < 20; i++) {
		if (bulletFlag[i] == 0) {
			bulletFlag[i] = 1;
			bulletX[i] = shipPos + 2;
			bulletY[i] = 37;
			break;
		}

	}
}

void collisionWithBullet() {
	for (int i = 0; i < 20; i++) {
		if (bulletFlag[i]) {

			if (bossFlag && bulletX[i] >= bossX && bulletX[i] <= bossX + 16 && bulletY[i] >= bossY && bulletY[i] <= bossY + 2) {
				eraseBullet(i);
				bulletFlag[i] = 0;
				bossHealth -= 5;
				if (bossHealth <= 0) {
					bossFlag = false;
					eraseBoss();
					score += 20;
				}
			}

			else if (!bossFlag) {
				for (int j = 0; j < 3; j++) {
					if (bulletX[i] >= destroyerX[j] && bulletX[i] < destroyerX[j] + 4 && bulletY[i] >= destroyerY[j] && bulletY[i] < destroyerY[j] + 7) {
						eraseBullet(i);
						bulletFlag[i] = 0;
						resetDestroyer(j);
						score += 5;
					}
				}
			}
		}
	}
}

int collisionWithDestroyer() {
	for (int i = 0; i < 3; i++) {
		if (destroyerY[i] + 6 >= 38 && destroyerX[i] + 4 > shipPos && destroyerX[i] < shipPos + 4) {
			return 1;
		}
	}
	return 0;
}

void menu() {
	system("cls");
	gotoxy(window_width / 2 - 10, 10); cout << "--------------------------";
	gotoxy(window_width / 2 - 10, 11); cout << "    TIE ADVANCED ATTACK   ";
	gotoxy(window_width / 2 - 10, 12); cout << "--------------------------";
	gotoxy(window_width / 2 - 10, 15); cout << "1. Start Game";
	gotoxy(window_width / 2 - 10, 16); cout << "2. Instructions";
	gotoxy(window_width / 2 - 10, 17); cout << "3. Quit";
	gotoxy(window_width / 2 - 10, 19); cout << "Select option: ";
}

void gameOverScreen() {
	system("cls");

	gotoxy(window_width / 2 - 15, 13); cout << "                   Game Over                    ";
	gotoxy(window_width / 2 - 15, 14); cout << "               Your Score : " << score;
	gotoxy(window_width / 2 - 15, 15); cout << "         Press space to go to main menu         ";

	char key = 0;
	while (key != 32) {
		key = _getch();
	}

}

void theGame() {

	int fireDelay = 0;
	bossFlag = false;
	score = 0;
	shipPos = window_width / 2;
	for (int i = 0; i < 20; i++) {
		bulletFlag[i] = 0;
	}

	system("cls");

	for (int i = 0; i < 3; i++) {
		destroyerFlag[i] = true;
		destroyerY[i] = 1 + (i * 10);
		genDestroyer(i);
	}



	drawBorder();

	while (true) {
		gotoxy(15, 0); cout << "SCORE: " << score << "      ";

		if (score > 0 && score % 60 == 0 && !bossFlag) {
			for (int i = 0; i < 3; i++) {
				eraseDestroyer(i);
			}

			bossFlag = true;
			bossHealth = 100;
			bossX = window_width / 2 - 8;
			bossY = 5;
		}

		if (!bossFlag) {

			for (int i = 0; i < 3; i++) {
				eraseDestroyer(i);
				destroyerY[i]++;
				if (destroyerY[i] > screen_height - 7) {
					resetDestroyer(i);
				}
				drawDestroyer(i);
			}
		}
		else {
			eraseBoss();
			bossX += bossDirection * 2;
			if (bossX > 170 || bossX < 20) bossDirection *= -1;
			drawBoss();
		}

		fireDelay++;
		if (fireDelay >= 4) {
			shoot();
			fireDelay = 0;
		}



		drawTieAdvanced();

		for (int i = 0; i < 20; i++) {
			if (bulletFlag[i] == true) {
				eraseBullet(i);
				bulletY[i]--;
				if (bulletY[i] <= 1) {
					bulletFlag[i] = false;
				}
				else {
					drawBullet(i);
				}
			}
		}

		if (bossFlag) {
			bossFireDelay++;
			if (bossFireDelay >= 10) {
				bossShoot();
				bossFireDelay = 0;
			}
			updateBossBullets();

			for (int i = 0; i < 10; i++) {
				if (bossBulletFlag[i] && bossBulletX[i] >= shipPos && bossBulletX[i] < shipPos + 4 && bossBulletY[i] >= 38) {
					gameOverScreen();
					return;
				}
			}
		}

		collisionWithBullet();

		if (collisionWithDestroyer() == 1) {
			gameOverScreen();
			break;
		}


		int gameSpeed = 35 - (score / 5);
		if (gameSpeed < 10) gameSpeed = 10;
		Sleep(gameSpeed);

		if (_kbhit()) {
			char ch = _getch();
			if (ch == 27) break;
			if (ch == 97 || ch == 65 || ch == 75) {
				if (shipPos > 14) {
					eraseTieAdvanced();
					shipPos -= 4;
				}
			}
			if (ch == 100 || ch == 68 || ch == 77) {
				if (shipPos < 180) {
					eraseTieAdvanced();
					shipPos += 4;
				}
			}

		}
	}
}

void instruction() {
	system("cls");

	gotoxy(window_width / 2 - 15, 13); cout << "Avoid Destroyers at any costs.......";
	gotoxy(window_width / 2 - 15, 14); cout << "USE 'A' or 'left arrow key' to move to the left  ";
	gotoxy(window_width / 2 - 15, 15); cout << "USE 'D' or 'right arrow key' to move to the right";
	gotoxy(window_width / 2 - 15, 16); cout << "           THE SHIP FIRES AUTOMATICALLY          ";
	gotoxy(window_width / 2 - 15, 17); cout << "Press any key to go back to the main menu";
	gotoxy(window_width / 2 - 15, 19); cout << "------------------------------------------------";
	gotoxy(window_width / 2 - 15, 20); cout << "              Happy Gaming               ";
	gotoxy(window_width / 2 - 15, 21); cout << "------------------------------------------------";

	_getch();
}



int main() {

	setcursor(0, 0);
	srand((unsigned)time(NULL));

	do {
		system("cls");
		menu();
		char op = _getch();

		if (op == '1') {
			theGame();
		}
		else if (op == '2') {
			instruction();
		}
		else if (op == '3') {
			exit(0);
		}

	} while (true);

	return 0;
}