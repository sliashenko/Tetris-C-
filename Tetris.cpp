#include <windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>

using namespace std;


#define KEY_ARROW_UP 72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN 80
#define KEY_ARROW_LEFT 75
#define KEY_SPACE 32
#define KEY_ENTER 13

int array[20][10];
int menu_var = -1;
int score = 0;
int next_figure_numb = -1;
int current_figure_numb = -1;
int var_resume = 0;
char game_name[15];

int SCOREint1 = 0, SCOREint2 = 0, SCOREint3 = 0;

int current_fig = 0;
HRGN current_square1, current_square2, current_square3, current_square4;
int current_coord_ar_x, current_coord_ar_y, current_y_left, current_x_left;
int current_space_pos;

void menu(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void menu_choice(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);

void print_records(HDC hdc);

void drawSquare(HDC hdc, HRGN rgnsquare, HBRUSH bkBrsh, HBRUSH fBrsh, int rght, int dwn) {
	FillRgn(hdc, rgnsquare, bkBrsh);
	OffsetRgn(rgnsquare, rght, dwn);
	FillRgn(hdc, rgnsquare, fBrsh);
}

void clear_array();
void clear_game_area(HDC hdc);

void chek_for_game_over(HDC hdc);
void game_over(HDC hdc);

void waiting(HDC hdc);
void score_print(HDC hdc);

void next_figure(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush, int fig_number);

void clear_score_area(HDC hdc);

void back_for_next_figure(HDC hdc);

void print_help(HDC hdc);

void delete_line(int i, HDC hdc);
void chek_for_delete_line(HDC hdc);
void moving_over_line(int i, HDC hdc);
void draw_line(int i, HDC hdc);
void draw_lineSquare(HDC hdc, HBRUSH bkBrsh, HBRUSH fBrsh, int i, int j);
void blanking_line(int i, HDC hdc);

void figure_generation(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);

void moving_I(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y);

void moving_J(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y);

void moving_L(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y);

void moving_O(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int coord_ar_x, int coord_ar_y);

void moving_S(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y);

void moving_T(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y);

void moving_Z(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y);

void Figure_I(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void Figure_J(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void Figure_L(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void Figure_O(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void Figure_S(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void Figure_T(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void Figure_Z(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);

void next_I(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void next_O(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void next_T(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void next_S(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void next_Z(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void next_L(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);
void next_J(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush);

void delete_virtuals(HDC hdc);
void virtual_I(HDC hdc, int coord_ar_x, int coord_ar_y, int T_space);
void virtual_O(HDC hdc, int coord_ar_x, int coord_ar_y);
void virtual_T(HDC hdc, int coord_ar_x, int coord_ar_y, int T_space);

void Cursor() {
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = false;
	CCI.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
}

int main() {
	static const TCHAR* title = TEXT("TETRIS");
	SetConsoleTitle(title);

	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	Cursor();

	RECT r;
	GetWindowRect(hwnd, &r);
	MoveWindow(hwnd, r.left, r.top, 700, 710, TRUE);
	GetClientRect(hwnd, &r);

	Sleep(1);

	Cursor();

	HBRUSH menuBrush = CreateSolidBrush(RGB(15, 5, 25));
	HRGN menuRgn = CreateRectRgn(0, 0, 900, 850);
	FillRgn(hdc, menuRgn, menuBrush);

	HBRUSH bkBrush = CreateSolidBrush(RGB(45, 0, 55));
	HBRUSH squareBrush1 = CreateSolidBrush(RGB(255, 200, 100));

	HBRUSH squareBrush_for_line = CreateSolidBrush(RGB(45, 0, 55));
	HRGN vert_line = CreateRectRgn(422, 0, 425, 850);
	FillRgn(hdc, vert_line, squareBrush_for_line);

	clear_game_area(hdc);

	string score1, score2, score3;
	char score1_ch[15], score2_ch[15], score3_ch[15];
	fstream in("records.txt");
	if (in.is_open()) {
		if (getline(in, score1)) {
			strcpy_s(score1_ch, 14, score1.c_str());
			cout << endl;
			::SCOREint1 = stoi(score1);

		}
		if (getline(in, score2)) {
			strcpy_s(score2_ch, 14, score2.c_str());
			cout << endl;
			::SCOREint2 = stoi(score2);
		}
		if (getline(in, score3)) {
			strcpy_s(score3_ch, 14, score3.c_str());
			cout << endl;
			::SCOREint3 = stoi(score3);
		}
	}

	COLORREF bk = SetBkColor(hdc, RGB(15, 5, 25));

	SetTextColor(hdc, RGB(255, 100, 250));
	char tetris_str[18] = "T E T R I S";

	HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
	HRGN TETRIS_area;

	char made_by1[] = "MADE BY";
	char made_by2[] = "STUDENT OF IASA";
	char made_by3[] = "LIASEHNKO VIACHESLAV";

	char resume[] = "RESUME";
	char start[] = "NEW GAME";
	char help[] = "HELP";
	char records[] = "RECORDS";
	char ex[] = "EXIT";

	for (int i = 900; i > -140; i -= 5) {
		SetTextColor(hdc, RGB(255, 100, 250));
		TextOutA(hdc, 609, i, tetris_str, strlen(tetris_str) + 1);
		TextOutA(hdc, 608, i + 50, made_by1, strlen(made_by1) + 1);
		TextOutA(hdc, 574, i + 80, made_by2, strlen(made_by2) + 1);
		TextOutA(hdc, 544, i + 110, made_by3, strlen(made_by3) + 1);

		TextOutA(hdc, 598, i + 390, start, strlen(start) + 1);
		TextOutA(hdc, 622, i + 420, help, strlen(help) + 1);
		TextOutA(hdc, 603, i + 450, records, strlen(records) + 1);
		TextOutA(hdc, 625, i + 480, ex, strlen(ex) + 1);

		SetTextColor(hdc, RGB(100, 100, 100));
		TextOutA(hdc, 610, i + 360, resume, strlen(resume) + 1);
		Sleep(6);

		TETRIS_area = CreateRectRgn(540, i - 10, 800, i + 500);
		FillRgn(hdc, TETRIS_area, brush);

	}

	menu(hdc, squareBrush1, bkBrush);
}

void menu(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {


	if (::var_resume == 1) {
		SetTextColor(hdc, RGB(255, 200, 100));
		char resume[] = "RESUME";
		TextOutA(hdc, 610, 220, resume, strlen(resume) + 1);

		SetTextColor(hdc, RGB(255, 100, 250));
		char start[] = "NEW GAME";
		TextOutA(hdc, 598, 250, start, strlen(start) + 1);

		::menu_var = 0;
	}
	else {
		SetTextColor(hdc, RGB(100, 100, 100));
		char resume[] = "RESUME";
		TextOutA(hdc, 610, 220, resume, strlen(resume) + 1);

		SetTextColor(hdc, RGB(255, 200, 100));
		char start[] = "NEW GAME";
		TextOutA(hdc, 598, 250, start, strlen(start) + 1);

		::menu_var = 1;
	}


	SetTextColor(hdc, RGB(255, 100, 250));
	char help[] = "HELP";
	TextOutA(hdc, 622, 280, help, strlen(help) + 1);

	char records[] = "RECORDS";
	TextOutA(hdc, 603, 310, records, strlen(records) + 1);

	char ex[] = "EXIT";
	TextOutA(hdc, 625, 340, ex, strlen(ex) + 1);

	menu_choice(hdc, squareBrush, bkBrush);

}

void menu_choice(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	int iKey = 67;
	while (true) {
		iKey = _getch();
		Sleep(10);
		switch (iKey) {
		case KEY_ENTER:
			if (::menu_var == 0) {
				SetTextColor(hdc, RGB(255, 100, 250));
				char resume[] = "RESUME";
				TextOutA(hdc, 610, 220, resume, strlen(resume));
				switch (::current_fig) {
				case 1:
					moving_I(::current_square1, ::current_square2, ::current_square3, ::current_square4, hdc,
						squareBrush, bkBrush, ::current_x_left, ::current_y_left, ::current_space_pos, ::current_coord_ar_x, ::current_coord_ar_y);
					break;
				case 2:
					moving_O(::current_square1, ::current_square2, ::current_square3, ::current_square4, hdc,
						squareBrush, bkBrush, ::current_x_left, ::current_y_left, ::current_coord_ar_x, ::current_coord_ar_y);
					break;
				case 3:
					moving_T(::current_square1, ::current_square2, ::current_square3, ::current_square4, hdc,
						squareBrush, bkBrush, ::current_x_left, ::current_y_left, ::current_space_pos, ::current_coord_ar_x, ::current_coord_ar_y);
					break;
				case 4:
					moving_J(::current_square1, ::current_square2, ::current_square3, ::current_square4, hdc,
						squareBrush, bkBrush, ::current_x_left, ::current_y_left, ::current_space_pos, ::current_coord_ar_x, ::current_coord_ar_y);
					break;
				case 5:
					moving_L(::current_square1, ::current_square2, ::current_square3, ::current_square4, hdc,
						squareBrush, bkBrush, ::current_x_left, ::current_y_left, ::current_space_pos, ::current_coord_ar_x, ::current_coord_ar_y);
					break;
				case 6:
					moving_S(::current_square1, ::current_square2, ::current_square3, ::current_square4, hdc,
						squareBrush, bkBrush, ::current_x_left, ::current_y_left, ::current_space_pos, ::current_coord_ar_x, ::current_coord_ar_y);
					break;
				case 7:
					moving_Z(::current_square1, ::current_square2, ::current_square3, ::current_square4, hdc,
						squareBrush, bkBrush, ::current_x_left, ::current_y_left, ::current_space_pos, ::current_coord_ar_x, ::current_coord_ar_y);
					break;
				}
			}
			else if (::menu_var == 1) {

				SetTextColor(hdc, RGB(255, 100, 250));
				char start[] = "NEW GAME";
				TextOutA(hdc, 598, 250, start, strlen(start - 1));

				char resume[] = "RESUME";
				TextOutA(hdc, 610, 220, resume, strlen(resume));

				::var_resume = 1;

				clear_score_area(hdc);

				clear_game_area(hdc);
				clear_array();

				back_for_next_figure(hdc);

				waiting(hdc);


				::menu_var = 0;
				::score = -1;

				srand(time(0));
				::current_figure_numb = 1;

				figure_generation(hdc, squareBrush, bkBrush);
			}
			else if (::menu_var == 2) {
				print_help(hdc);
			}
			else if (::menu_var == 3) {
				print_records(hdc);
			}
			else if (::menu_var == 4) {
				exit(0);
			}
			break;
		case KEY_ARROW_DOWN:
			if (::menu_var == 0 && var_resume == 1) {

				SetTextColor(hdc, RGB(255, 200, 100));
				char start[] = "NEW GAME";
				TextOutA(hdc, 598, 250, start, strlen(start) + 1);

				SetTextColor(hdc, RGB(255, 100, 250));
				char resume[] = "RESUME";
				TextOutA(hdc, 610, 220, resume, strlen(resume) + 1);

				::menu_var = 1;
			}
			else if (::menu_var == 1) {

				SetTextColor(hdc, RGB(255, 100, 250));
				char start[] = "NEW GAME";
				TextOutA(hdc, 598, 250, start, strlen(start) + 1);

				SetTextColor(hdc, RGB(255, 200, 100));
				char help[] = "HELP";
				TextOutA(hdc, 622, 280, help, strlen(help) + 1);

				::menu_var = 2;

			}
			else if (::menu_var == 2) {

				HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
				HRGN help_area = CreateRectRgn(450, 395, 900, 500);
				FillRgn(hdc, help_area, brush);

				SetTextColor(hdc, RGB(255, 100, 250));
				char help[] = "HELP";
				TextOutA(hdc, 622, 280, help, strlen(help));

				SetTextColor(hdc, RGB(255, 200, 100));
				char records[] = "RECORDS";
				TextOutA(hdc, 603, 310, records, strlen(records) + 1);

				::menu_var = 3;

			}
			else if (::menu_var == 3) {

				HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
				HRGN records_area = CreateRectRgn(450, 30, 900, 200);
				FillRgn(hdc, records_area, brush);

				SetTextColor(hdc, RGB(255, 100, 250));
				char records[] = "RECORDS";
				TextOutA(hdc, 603, 310, records, strlen(records) + 1);

				SetTextColor(hdc, RGB(255, 200, 100));
				char ex[] = "EXIT";
				TextOutA(hdc, 625, 340, ex, strlen(ex) + 1);


				::menu_var = 4;

			}
			break;
		case KEY_ARROW_UP:
			if (::menu_var == 1 && var_resume == 1) {
				SetTextColor(hdc, RGB(255, 100, 250));
				char start[] = "NEW GAME";
				TextOutA(hdc, 598, 250, start, strlen(start) + 1);

				SetTextColor(hdc, RGB(255, 200, 100));
				char resume[] = "RESUME";
				TextOutA(hdc, 610, 220, resume, strlen(resume) + 1);

				::menu_var = 0;
			}
			else if (::menu_var == 2) {

				HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
				HRGN help_area = CreateRectRgn(450, 395, 900, 500);
				FillRgn(hdc, help_area, brush);

				SetTextColor(hdc, RGB(255, 200, 100));
				char start[] = "NEW GAME";
				TextOutA(hdc, 598, 250, start, strlen(start - 1));

				SetTextColor(hdc, RGB(255, 100, 250));
				char help[] = "HELP";
				TextOutA(hdc, 622, 280, help, strlen(help - 1));

				::menu_var = 1;

			}
			else if (::menu_var == 3) {

				HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
				HRGN records_area = CreateRectRgn(450, 30, 900, 200);
				FillRgn(hdc, records_area, brush);

				SetTextColor(hdc, RGB(255, 200, 100));
				char help[] = "HELP";
				TextOutA(hdc, 622, 280, help, strlen(help));

				SetTextColor(hdc, RGB(255, 100, 250));
				char records[] = "RECORDS";
				TextOutA(hdc, 603, 310, records, strlen(records - 1));

				::menu_var = 2;
			}
			else if (::menu_var == 4) {

				SetTextColor(hdc, RGB(255, 200, 100));
				char records[] = "RECORDS";
				TextOutA(hdc, 603, 310, records, strlen(records - 1));

				SetTextColor(hdc, RGB(255, 100, 250));
				char ex[] = "EXIT";
				TextOutA(hdc, 625, 340, ex, strlen(ex) + 1);

				::menu_var = 3;
			}
			break;
		}
	}
}

void print_records(HDC hdc) {
	SetTextColor(hdc, RGB(255, 100, 250));
	string score1, score2, score3;
	char score1_ch[15], score2_ch[15], score3_ch[15];
	char empty[] = "EMPTY";
	char records_ch[] = "RECORDS";
	ifstream in("records.txt");
	if (in.is_open()) {
		TextOutA(hdc, 603, 60, records_ch, strlen(records_ch) + 1);
		if (getline(in, score1)) {
			strcpy_s(score1_ch, 14, score1.c_str());
			cout << endl;
			SetTextColor(hdc, RGB(255, 215, 0));
			TextOutA(hdc, 622, 100, score1_ch, strlen(score1_ch) + 1);
			::SCOREint1 = stoi(score1);

		}
		if (getline(in, score2)) {
			strcpy_s(score2_ch, 14, score2.c_str());
			cout << endl;
			SetTextColor(hdc, RGB(196, 202, 206));
			TextOutA(hdc, 555, 125, score2_ch, strlen(score2_ch) + 1);
			::SCOREint2 = stoi(score2);
		}
		if (getline(in, score3)) {
			strcpy_s(score3_ch, 14, score3.c_str());
			cout << endl;
			SetTextColor(hdc, RGB(205, 127, 50));
			TextOutA(hdc, 695, 150, score3_ch, strlen(score3_ch) + 1);
			::SCOREint3 = stoi(score3);
		}
	}
	else {
		HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
		HRGN records_area = CreateRectRgn(600, 100, 700, 140);

		TextOutA(hdc, 617, 120, empty, strlen(empty) + 1);
		Sleep(750);

		FillRgn(hdc, records_area, brush);
		Sleep(250);

		TextOutA(hdc, 617, 120, empty, strlen(empty) + 1);
		Sleep(750);

		FillRgn(hdc, records_area, brush);
	}
	in.close();

}


void clear_array() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			::array[i][j] = 0;
		}
	}
}

void clear_game_area(HDC hdc) {
	for (int i = 0; i < 20; i++) {
		delete_line(i, hdc);
	}
}

void waiting(HDC hdc) {

	SetTextColor(hdc, RGB(255, 100, 250));

	char waiting3[] = "3";
	TextOutA(hdc, 638, 700, waiting3, strlen(waiting3) + 1);
	Sleep(1000);

	char waiting2[] = "2";
	TextOutA(hdc, 638, 700, waiting2, strlen(waiting2) + 1);
	Sleep(1000);

	char waiting1[] = "1";
	TextOutA(hdc, 638, 700, waiting1, strlen(waiting1) + 1);
	Sleep(800);

	char score[] = "SCORE:";
	TextOutA(hdc, 568, 700, score, strlen(score) + 1);

}

void score_print(HDC hdc) {
	string s = to_string(::score);
	char score_ch[15];
	strcpy_s(score_ch, 14, s.c_str());
	SetTextColor(hdc, RGB(255, 100, 250));
	TextOutA(hdc, 638, 700, score_ch, strlen(score_ch) + 1);

}

void clear_score_area(HDC hdc) {
	HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
	HRGN score_area = CreateRectRgn(560, 690, 632, 720);
	FillRgn(hdc, score_area, brush);
}

void print_help(HDC hdc) {
	SetTextColor(hdc, RGB(255, 100, 250));

	char help_info1[] = "Use RIGHT Arrow and LEFT Arrow";
	TextOutA(hdc, 512, 400, help_info1, strlen(help_info1) + 1);

	char help_info2[] = "to contol figures.";
	TextOutA(hdc, 513, 420, help_info2, strlen(help_info2) + 1);

	char help_info3[] = "Use SPACE to rotate you figures.";
	TextOutA(hdc, 512, 442, help_info3, strlen(help_info3) + 1);
}

void moving_I(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc,
	HBRUSH squareBrush1, HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y) {
	//virtual_I(hdc, coord_ar_x, coord_ar_y, T_space);
	int iKey = 67;
	while (iKey != 27) {
		if (_kbhit()) {
			iKey = _getch();
			Sleep(20);
			switch (iKey) {
			case KEY_ARROW_RIGHT:
				if (T_space == 0) {
					if (x_left + 210 <= 422 && ::array[coord_ar_y][coord_ar_x + 4] != 1) {
						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y][coord_ar_x + 2] = 0;
						::array[coord_ar_y][coord_ar_x + 3] = 0;

						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);

						x_left += 42;
						coord_ar_x += 1;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y][coord_ar_x + 2] = 1;
						::array[coord_ar_y][coord_ar_x + 3] = 1;
					}
				}
				else {
					if (x_left + 84 <= 422 && ::array[coord_ar_y][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 1][coord_ar_x + 1] != 1
						&& ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 3][coord_ar_x + 1] != 1) {

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 2][coord_ar_x] = 0;
						::array[coord_ar_y + 3][coord_ar_x] = 0;

						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);

						x_left += 42;
						coord_ar_x += 1;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 2][coord_ar_x] = 1;
						::array[coord_ar_y + 3][coord_ar_x] = 1;
					}
				}

				break;
			case KEY_ARROW_LEFT:
				if (T_space == 0) {
					if (x_left - 42 >= 2 && ::array[coord_ar_y][coord_ar_x - 1] != 1) {
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
						x_left -= 42;

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y][coord_ar_x + 2] = 0;
						::array[coord_ar_y][coord_ar_x + 3] = 0;

						coord_ar_x -= 1;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y][coord_ar_x + 2] = 1;
						::array[coord_ar_y][coord_ar_x + 3] = 1;
					}
				}
				else {
					if (x_left - 42 >= 2 && ::array[coord_ar_y][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 1][coord_ar_x - 1] != 1
						&& ::array[coord_ar_y + 2][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 3][coord_ar_x - 1] != 1) {
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
						x_left -= 42;

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 2][coord_ar_x] = 0;
						::array[coord_ar_y + 3][coord_ar_x] = 0;

						coord_ar_x -= 1;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 2][coord_ar_x] = 1;
						::array[coord_ar_y + 3][coord_ar_x] = 1;
					}
				}

				break;
			case KEY_SPACE:
				if (T_space == 0) {
					if (y_left >= 126 && ::array[coord_ar_y - 1][coord_ar_x + 2] != 1
						&& ::array[coord_ar_y - 2][coord_ar_x + 2] != 1 && ::array[coord_ar_y - 3][coord_ar_x + 2] != 1) {

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y][coord_ar_x + 2] = 0;
						::array[coord_ar_y][coord_ar_x + 3] = 0;

						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 84, -126);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, -42);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, -84);

						x_left += 84;
						coord_ar_x += 2;
						coord_ar_y -= 3;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 2][coord_ar_x] = 1;
						::array[coord_ar_y + 3][coord_ar_x] = 1;

						T_space = 1;
					}
				}
				else {
					if (y_left >= 126 && x_left >= 84 && x_left + 84 <= 422 && ::array[coord_ar_y + 3][coord_ar_x - 2] != 1
						&& ::array[coord_ar_y + 3][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 3][coord_ar_x + 1] != 1) {

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 2][coord_ar_x] = 0;
						::array[coord_ar_y + 3][coord_ar_x] = 0;

						x_left -= 84;
						coord_ar_x -= 2;
						coord_ar_y += 3;

						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -84, 126);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 42);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 84);

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y][coord_ar_x + 2] = 1;
						::array[coord_ar_y][coord_ar_x + 3] = 1;

						T_space = 0;
					}
				}
				break;
			}
			//delete_virtuals(hdc);
			//virtual_I(hdc, coord_ar_x, coord_ar_y, T_space);
		}
		else {
			Sleep(220);
			if (T_space == 0) {
				if ((y_left + 42 <= 840) && (::array[coord_ar_y + 1][coord_ar_x] != 1 && ::array[coord_ar_y + 1][coord_ar_x + 1] != 1 &&
					::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && ::array[coord_ar_y + 1][coord_ar_x + 3] != 1)) {
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					y_left += 42;

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 3] = 0;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 3] = 1;

				}
				if (y_left >= 798 or (::array[coord_ar_y + 1][coord_ar_x] == 1 or ::array[coord_ar_y + 1][coord_ar_x + 1] == 1 or
					::array[coord_ar_y + 1][coord_ar_x + 2] == 1 or ::array[coord_ar_y + 1][coord_ar_x + 3] == 1)) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 3] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else {
				if ((y_left + 42 <= 840) && (::array[coord_ar_y + 4][coord_ar_x] != 1)) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y + 3][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);


					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 3][coord_ar_x] = 1;

				}
				if (y_left >= 798 or (::array[coord_ar_y + 4][coord_ar_x] == 1)) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 3][coord_ar_x] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}

		}
	}
	::current_square1 = rgnsquare1;
	::current_square2 = rgnsquare2;
	::current_square3 = rgnsquare3;
	::current_square4 = rgnsquare4;

	::current_coord_ar_x = coord_ar_x;
	::current_coord_ar_y = coord_ar_y;
	::current_y_left = y_left;
	::current_x_left = x_left;
	::current_space_pos = T_space;
	menu(hdc, squareBrush1, bkBrush);
}

void moving_J(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y) {
	int iKey = 67;
	while (iKey != 27) {
		if (_kbhit()) {
			iKey = _getch();
			Sleep(30);
			switch (iKey) {
			case KEY_ARROW_RIGHT:
				if (T_space == 0 && x_left + 126 <= 420 && ::array[coord_ar_y][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 3] != 1) {
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;
				}
				else if (T_space == 1 && x_left + 84 <= 420 && ::array[coord_ar_y][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
				}
				else if (T_space == 2 && x_left + 126 <= 420 && ::array[coord_ar_y][coord_ar_x + 3] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 3] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
				}
				if (T_space == 3 && x_left + 84 <= 420 && ::array[coord_ar_y][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}
				break;
			case KEY_ARROW_LEFT:
				if (T_space == 0 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;
				}

				else if (T_space == 1 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x - 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
				}

				if (T_space == 2 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;

				}
				if (T_space == 3 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x - 1] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
				}
				break;
			case KEY_SPACE:
				if (T_space == 0 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y][coord_ar_x + 1] != 1 &&
					::array[coord_ar_y][coord_ar_x + 2] != 1 && coord_ar_y + 2 < 20) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 84, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, -42);

					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;

					x_left += 42;
					coord_ar_x += 1;

					T_space = 1;
				}

				else if (T_space == 1 && ::array[coord_ar_y + 1][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && coord_ar_x - 1 >= 0) {

					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, -42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 84);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 42);

					::array[coord_ar_y + 1][coord_ar_x - 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

					x_left -= 42;
					coord_ar_x -= 1;
					y_left += 42;
					coord_ar_y += 1;

					T_space = 2;
				}

				else if (T_space == 2 && ::array[coord_ar_y + 1][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, -42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -84, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 42);

					::array[coord_ar_y - 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;

					y_left -= 42;
					coord_ar_y -= 1;

					T_space = 3;
				}

				else if (T_space == 3 && ::array[coord_ar_y][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && coord_ar_x + 2 < 10) {

					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, -84);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, -42);

					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;

					T_space = 0;
				}

				break;
			}
		}
		else {
			Sleep(220);
			if (T_space == 0) {
				if (y_left + 84 <= 840 && ::array[coord_ar_y + 2][coord_ar_x] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;

				}
				else if (y_left + 84 > 840 or ::array[coord_ar_y + 2][coord_ar_x] == 1
					or ::array[coord_ar_y + 2][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 2][coord_ar_x + 2] == 1)
				{
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 1) {
				if (y_left + 126 <= 840 && ::array[coord_ar_y + 3][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;

				}
				else if (y_left + 126 > 840 or ::array[coord_ar_y + 3][coord_ar_x] == 1
					or ::array[coord_ar_y + 1][coord_ar_x + 1] == 1) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 2) {
				if (y_left + 84 <= 840 && ::array[coord_ar_y + 1][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;

				}
				else if (y_left + 84 > 840 or ::array[coord_ar_y + 1][coord_ar_x] == 1
					or ::array[coord_ar_y + 1][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 2][coord_ar_x + 2] == 1) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 3) {
				if (y_left + 126 <= 840 && ::array[coord_ar_y + 3][coord_ar_x] != 1 && ::array[coord_ar_y + 3][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
				}
				else if (y_left + 126 > 840 or ::array[coord_ar_y + 3][coord_ar_x] == 1 or ::array[coord_ar_y + 3][coord_ar_x + 1] == 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
		}
	}
	::current_square1 = rgnsquare1;
	::current_square2 = rgnsquare2;
	::current_square3 = rgnsquare3;
	::current_square4 = rgnsquare4;

	::current_coord_ar_x = coord_ar_x;
	::current_coord_ar_y = coord_ar_y;
	::current_y_left = y_left;
	::current_x_left = x_left;
	::current_space_pos = T_space;

	menu(hdc, squareBrush1, bkBrush);
}

void moving_L(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc, HBRUSH squareBrush1,
	HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y) {
	int iKey = 67;
	while (iKey != 27) {
		if (_kbhit()) {
			iKey = _getch();
			Sleep(30);
			switch (iKey) {
			case KEY_ARROW_RIGHT:
				if (T_space == 0 && x_left + 126 <= 420 && ::array[coord_ar_y][coord_ar_x + 3] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 3] != 1) {
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
				}
				else if (T_space == 1 && x_left + 84 <= 420 && ::array[coord_ar_y][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
				}
				else if (T_space == 2 && x_left + 126 <= 420 && ::array[coord_ar_y][coord_ar_x + 3] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
				}
				if (T_space == 3 && x_left + 84 <= 420 && ::array[coord_ar_y][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}

				break;

			case KEY_ARROW_LEFT:
				if (T_space == 0 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
				}

				else if (T_space == 1 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x - 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
				}

				if (T_space == 2 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;

				}
				if (T_space == 3 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}
				break;
			case KEY_SPACE:
				if (T_space == 0 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x + 2] != 1 && coord_ar_y + 2 < 20) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 84);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, -42);

					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;

					x_left += 42;
					coord_ar_x += 1;


					T_space = 1;
				}

				else if (T_space == 1 && ::array[coord_ar_y + 1][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x - 1] != 1 && coord_ar_x - 1 >= 0) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, -42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -84, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 42);

					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x - 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x - 1] = 1;

					x_left -= 42;
					coord_ar_x -= 1;
					y_left += 42;
					coord_ar_y += 1;

					T_space = 2;
				}

				else if (T_space == 2 && ::array[coord_ar_y + 1][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, -42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, -84);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 42);

					::array[coord_ar_y - 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y - 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;

					y_left -= 42;
					coord_ar_y -= 1;

					T_space = 3;
				}

				else if (T_space == 3 && ::array[coord_ar_y][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x] != 1 && coord_ar_x + 2 < 10) {

					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 84, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, -42);

					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;

					T_space = 0;
				}
				break;
			}
		}
		else {
			Sleep(220);
			if (T_space == 0) {
				if (y_left + 84 <= 840 && ::array[coord_ar_y + 2][coord_ar_x] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;

				}
				else if (y_left + 84 > 840 or ::array[coord_ar_y + 2][coord_ar_x] == 1
					or ::array[coord_ar_y + 2][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 2][coord_ar_x + 2] == 1) {

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 1) {
				if (y_left + 126 <= 840 && ::array[coord_ar_y + 3][coord_ar_x] != 1
					&& ::array[coord_ar_y + 3][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;

				}
				else if (y_left + 126 > 840 or ::array[coord_ar_y + 3][coord_ar_x] == 1
					or ::array[coord_ar_y + 3][coord_ar_x + 1] == 1) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 2) {
				if (y_left + 84 <= 840 && ::array[coord_ar_y + 2][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 1][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;

				}
				else if (y_left + 84 > 840 or ::array[coord_ar_y + 2][coord_ar_x] == 1
					or ::array[coord_ar_y + 1][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 1][coord_ar_x + 2] == 1) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 3) {
				if (y_left + 126 <= 840 && ::array[coord_ar_y + 1][coord_ar_x] != 1
					&& ::array[coord_ar_y + 3][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

				}
				else if (y_left + 126 > 840 or ::array[coord_ar_y + 1][coord_ar_x] == 1 or ::array[coord_ar_y + 3][coord_ar_x + 1] == 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
		}
	}
	::current_square1 = rgnsquare1;
	::current_square2 = rgnsquare2;
	::current_square3 = rgnsquare3;
	::current_square4 = rgnsquare4;

	::current_coord_ar_x = coord_ar_x;
	::current_coord_ar_y = coord_ar_y;
	::current_y_left = y_left;
	::current_x_left = x_left;
	::current_space_pos = T_space;

	menu(hdc, squareBrush1, bkBrush);
}

void moving_O(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc,
	HBRUSH squareBrush1, HBRUSH bkBrush, int x_left, int y_left, int coord_ar_x, int coord_ar_y) {
	//virtual_O(hdc, coord_ar_x, coord_ar_y);
	int iKey = 67;
	while (iKey != 27) {
		if (_kbhit()) {
			iKey = _getch();
			Sleep(15);
			switch (iKey) {
			case KEY_ARROW_RIGHT:
				if (x_left + 126 <= 422 && ::array[coord_ar_y][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1) {
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					coord_ar_x += 1;
					x_left += 42;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}

				break;
			case KEY_ARROW_LEFT:
				if (x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1) {
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					coord_ar_x -= 1;
					x_left -= 42;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}


				break;
			}
			//delete_virtuals(hdc);
			//virtual_O(hdc, coord_ar_x, coord_ar_y);
		}
		else {
			Sleep(220);
			if ((y_left + 126 <= 842) && (::array[coord_ar_y + 2][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1)) {
				drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
				drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);
				drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
				drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);


				::array[coord_ar_y][coord_ar_x] = 0;
				::array[coord_ar_y][coord_ar_x + 1] = 0;
				::array[coord_ar_y + 1][coord_ar_x] = 0;
				::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

				coord_ar_y += 1;
				y_left += 42;

				::array[coord_ar_y][coord_ar_x] = 1;
				::array[coord_ar_y][coord_ar_x + 1] = 1;
				::array[coord_ar_y + 1][coord_ar_x] = 1;
				::array[coord_ar_y + 1][coord_ar_x + 1] = 1;

			}
			else if (y_left + 126 >= 842 or (::array[coord_ar_y + 2][coord_ar_x] == 1 or ::array[coord_ar_y + 2][coord_ar_x + 1] == 1)) {

				::array[coord_ar_y][coord_ar_x] = 1;
				::array[coord_ar_y][coord_ar_x + 1] = 1;
				::array[coord_ar_y + 1][coord_ar_x] = 1;
				::array[coord_ar_y + 1][coord_ar_x + 1] = 1;

				::current_figure_numb = ::next_figure_numb;
				figure_generation(hdc, squareBrush1, bkBrush);
			}
		}
	}
	::current_square1 = rgnsquare1;
	::current_square2 = rgnsquare2;
	::current_square3 = rgnsquare3;
	::current_square4 = rgnsquare4;

	::current_coord_ar_x = coord_ar_x;
	::current_coord_ar_y = coord_ar_y;
	::current_y_left = y_left;
	::current_x_left = x_left;

	menu(hdc, squareBrush1, bkBrush);
}

void moving_S(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc,
	HBRUSH squareBrush1, HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y) {
	int iKey = 67;
	while (iKey != 27) {
		if (_kbhit()) {
			iKey = _getch();
			Sleep(30);
			switch (iKey) {
			case KEY_ARROW_RIGHT:
				if (T_space == 0) {
					if (x_left + 168 <= 422 && ::array[coord_ar_y][coord_ar_x + 3] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1) {
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);

						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y][coord_ar_x + 2] = 0;

						coord_ar_x += 1;
						x_left += 42;

						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y][coord_ar_x + 2] = 1;
					}
				}
				else {
					if (x_left + 126 <= 422 && ::array[coord_ar_y][coord_ar_x + 1] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

						coord_ar_x += 1;
						x_left += 42;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					}
				}
				break;
			case KEY_ARROW_LEFT:
				if (T_space == 0) {
					if (x_left >= 44 && ::array[coord_ar_y][coord_ar_x] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1) {
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y][coord_ar_x + 2] = 0;

						coord_ar_x -= 1;
						x_left -= 42;

						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y][coord_ar_x + 2] = 1;
					}
				}
				else {
					if (x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x] != 1) {
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

						coord_ar_x -= 1;
						x_left -= 42;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					}
				}
				break;
			case KEY_SPACE:
				if (T_space == 0 && y_left > 42 && ::array[coord_ar_y][coord_ar_x] != 1
					&& ::array[coord_ar_y - 1][coord_ar_x] != 1) {

					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, -84);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, -42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 42);



					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y - 1][coord_ar_x] = 1;


					coord_ar_y -= 1;
					y_left -= 42;

					T_space = 1;
				}
				else if (T_space == 1 && ::array[coord_ar_y + 2][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && coord_ar_x + 2 < 10) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;


					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, -42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 84);


					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;

					coord_ar_y += 1;
					y_left += 42;

					T_space = 0;
				}
			}
		}
		else {
			Sleep(220);
			if (T_space == 0) {
				if (y_left + 126 <= 842 && (::array[coord_ar_y + 2][coord_ar_x] != 1 &&
					::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 1][coord_ar_x + 2] != 1)) {

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;

					coord_ar_y += 1;
					y_left += 42;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
				}
				if (y_left + 126 > 842 or (::array[coord_ar_y + 2][coord_ar_x] == 1 or
					::array[coord_ar_y + 2][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 1][coord_ar_x + 2] == 1)) {

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else {
				if (y_left + 126 <= 842 && (::array[coord_ar_y + 2][coord_ar_x] != 1 && ::array[coord_ar_y + 3][coord_ar_x + 1] != 1)) {

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

					coord_ar_y += 1;
					y_left += 42;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
				}
				if (y_left + 126 > 840 or (::array[coord_ar_y + 2][coord_ar_x] == 1 or ::array[coord_ar_y + 3][coord_ar_x + 1] == 1)) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
		}
	}
	::current_square1 = rgnsquare1;
	::current_square2 = rgnsquare2;
	::current_square3 = rgnsquare3;
	::current_square4 = rgnsquare4;

	::current_coord_ar_x = coord_ar_x;
	::current_coord_ar_y = coord_ar_y;
	::current_y_left = y_left;
	::current_x_left = x_left;
	::current_space_pos = T_space;

	menu(hdc, squareBrush1, bkBrush);
}

void moving_T(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc,
	HBRUSH squareBrush1, HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y) {
	int iKey = 67;
	while (iKey != 27) {
		if (_kbhit()) {
			iKey = _getch();
			Sleep(30);
			switch (iKey) {
			case KEY_ARROW_RIGHT:
				if (T_space == 0 && x_left + 126 <= 420 && ::array[coord_ar_y + 1][coord_ar_x + 3] != 1
					&& ::array[coord_ar_y][coord_ar_x + 2] != 1) {
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
				}
				else if (T_space == 1 && x_left + 84 <= 420 && ::array[coord_ar_y][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}
				else if (T_space == 2 && x_left + 126 <= 420 && ::array[coord_ar_y][coord_ar_x + 3] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}
				if (T_space == 3 && x_left + 84 <= 420 && ::array[coord_ar_y][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);

					x_left += 42;
					coord_ar_x += 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}

				break;

			case KEY_ARROW_LEFT:
				if (T_space == 0 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
				}

				else if (T_space == 1 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x - 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}

				if (T_space == 2 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;

				}
				if (T_space == 3 && x_left >= 44 && ::array[coord_ar_y][coord_ar_x] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);

					x_left -= 42;
					coord_ar_x -= 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
				}
				break;
			case KEY_SPACE:
				if (T_space == 0 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && coord_ar_y + 2 < 20) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, -42);

					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

					x_left += 42;
					coord_ar_x += 1;


					T_space = 1;
				}

				else if (T_space == 1 && ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && coord_ar_x - 1 >= 0) {

					::array[coord_ar_y][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, -42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 42);

					::array[coord_ar_y + 1][coord_ar_x - 1] = 1;

					x_left -= 42;
					coord_ar_x -= 1;
					y_left += 42;
					coord_ar_y += 1;

					T_space = 2;
				}

				else if (T_space == 2) {

					::array[coord_ar_y][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, -42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, -42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 42);

					::array[coord_ar_y - 1][coord_ar_x + 1] = 1;

					y_left -= 42;
					coord_ar_y -= 1;

					T_space = 3;
				}

				else if (T_space == 3 && ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && coord_ar_x + 2 < 10) {

					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, -42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, -42);

					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;


					T_space = 0;
				}

				break;
			}
		}
		else {
			Sleep(220);
			if (T_space == 0) {
				if (y_left + 84 <= 840 && ::array[coord_ar_y + 2][coord_ar_x] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1) {

					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;

				}
				else if (y_left + 84 > 840 or ::array[coord_ar_y + 2][coord_ar_x] == 1
					or ::array[coord_ar_y + 2][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 2][coord_ar_x + 2] == 1)
				{
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 1) {
				if (y_left + 126 <= 840 && ::array[coord_ar_y + 3][coord_ar_x] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;

				}
				else if (y_left + 126 > 840 or ::array[coord_ar_y + 3][coord_ar_x] == 1
					or ::array[coord_ar_y + 2][coord_ar_x + 1] == 1) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 2) {
				if (y_left + 84 <= 840 && ::array[coord_ar_y + 1][coord_ar_x] != 1
					&& ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 1][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y][coord_ar_x + 2] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;

				}
				else if (y_left + 84 > 840 or ::array[coord_ar_y + 1][coord_ar_x] == 1
					or ::array[coord_ar_y + 2][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 1][coord_ar_x + 2] == 1) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else if (T_space == 3) {
				if (y_left + 126 <= 840 && ::array[coord_ar_y + 2][coord_ar_x] != 1
					&& ::array[coord_ar_y + 3][coord_ar_x + 1] != 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					y_left += 42;
					coord_ar_y += 1;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

				}
				else if (y_left + 126 > 840 or ::array[coord_ar_y + 1][coord_ar_x] == 1 or ::array[coord_ar_y + 3][coord_ar_x + 1] == 1) {

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
		}
	}
	::current_square1 = rgnsquare1;
	::current_square2 = rgnsquare2;
	::current_square3 = rgnsquare3;
	::current_square4 = rgnsquare4;

	::current_coord_ar_x = coord_ar_x;
	::current_coord_ar_y = coord_ar_y;
	::current_y_left = y_left;
	::current_x_left = x_left;
	::current_space_pos = T_space;

	menu(hdc, squareBrush1, bkBrush);
}

void moving_Z(HRGN rgnsquare1, HRGN rgnsquare2, HRGN rgnsquare3, HRGN rgnsquare4, HDC hdc,
	HBRUSH squareBrush1, HBRUSH bkBrush, int x_left, int y_left, int T_space, int coord_ar_x, int coord_ar_y) {
	int iKey = 67;
	while (iKey != 27) {
		if (_kbhit()) {
			iKey = _getch();
			Sleep(30);
			switch (iKey) {
			case KEY_ARROW_RIGHT:
				if (T_space == 0) {
					if (x_left + 168 <= 422 && ::array[coord_ar_y][coord_ar_x + 2] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x + 3] != 1) {
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

						coord_ar_x += 1;
						x_left += 42;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					}
				}
				else {
					if (x_left + 126 <= 422 && ::array[coord_ar_y][coord_ar_x + 2] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x + 2] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1) {
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 42, 0);
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 0);

						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 2][coord_ar_x] = 0;

						coord_ar_x += 1;
						x_left += 42;

						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 2][coord_ar_x] = 1;
					}

				}

				break;
			case KEY_ARROW_LEFT:
				if (T_space == 0) {
					if (x_left >= 44 && ::array[coord_ar_y][coord_ar_x - 1] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x] != 1) {
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);

						::array[coord_ar_y][coord_ar_x] = 0;
						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

						coord_ar_x -= 1;
						x_left -= 42;

						::array[coord_ar_y][coord_ar_x] = 1;
						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
					}
				}
				else {
					if (x_left >= 44 && ::array[coord_ar_y][coord_ar_x] != 1
						&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x - 1] != 1) {
						drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, -42, 0);
						drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 0);

						::array[coord_ar_y][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 1][coord_ar_x] = 0;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
						::array[coord_ar_y + 2][coord_ar_x] = 0;

						coord_ar_x -= 1;
						x_left -= 42;

						::array[coord_ar_y][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 1][coord_ar_x] = 1;
						::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
						::array[coord_ar_y + 2][coord_ar_x] = 1;
					}
				}
				break;
			case KEY_SPACE:
				if (T_space == 0 && y_left > 42 && ::array[coord_ar_y][coord_ar_x + 2] != 1
					&& ::array[coord_ar_y - 1][coord_ar_x + 2] != 1) {

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, -84);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 42, -42);
					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 42, 42);

					::array[coord_ar_y - 1][coord_ar_x + 2] = 1;
					::array[coord_ar_y][coord_ar_x + 2] = 1;


					coord_ar_y -= 1;
					coord_ar_x += 1;
					y_left -= 42;
					x_left += 42;

					T_space = 1;
				}
				else if (T_space == 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1
					&& ::array[coord_ar_y + 1][coord_ar_x - 1] != 1 && coord_ar_x - 1 >= 0) {

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, -42, -42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, -42, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 84);

					::array[coord_ar_y + 2][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x - 1] = 1;

					coord_ar_y += 1;
					coord_ar_x -= 1;
					y_left += 42;
					x_left -= 42;

					T_space = 0;
				}
			}
		}
		else {
			Sleep(220);
			if (T_space == 0) {
				if (y_left + 126 <= 842 && (::array[coord_ar_y + 1][coord_ar_x] != 1 &&
					::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 2] != 1)) {

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					::array[coord_ar_y][coord_ar_x] = 0;
					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 0;

					coord_ar_y += 1;
					y_left += 42;

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
				}
				if (y_left + 126 > 842 or (::array[coord_ar_y + 1][coord_ar_x] == 1 or
					::array[coord_ar_y + 2][coord_ar_x + 1] == 1 or ::array[coord_ar_y + 2][coord_ar_x + 2] == 1)) {

					::array[coord_ar_y][coord_ar_x] = 1;
					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 2] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
			else {
				if (y_left + 126 <= 842 && (::array[coord_ar_y + 3][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1)) {

					drawSquare(hdc, rgnsquare1, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare2, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare3, bkBrush, squareBrush1, 0, 42);
					drawSquare(hdc, rgnsquare4, bkBrush, squareBrush1, 0, 42);

					::array[coord_ar_y][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 1][coord_ar_x] = 0;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 0;
					::array[coord_ar_y + 2][coord_ar_x] = 0;

					coord_ar_y += 1;
					y_left += 42;

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;
				}
				if (y_left + 126 > 840 or (::array[coord_ar_y + 3][coord_ar_x] == 1 or ::array[coord_ar_y + 2][coord_ar_x + 1] == 1)) {

					::array[coord_ar_y][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 1][coord_ar_x] = 1;
					::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
					::array[coord_ar_y + 2][coord_ar_x] = 1;

					::current_figure_numb = ::next_figure_numb;
					figure_generation(hdc, squareBrush1, bkBrush);
				}
			}
		}
	}
	::current_square1 = rgnsquare1;
	::current_square2 = rgnsquare2;
	::current_square3 = rgnsquare3;
	::current_square4 = rgnsquare4;

	::current_coord_ar_x = coord_ar_x;
	::current_coord_ar_y = coord_ar_y;
	::current_y_left = y_left;
	::current_x_left = x_left;
	::current_space_pos = T_space;

	menu(hdc, squareBrush1, bkBrush);
}


void Figure_I(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	int T_space = 0;

	chek_for_delete_line(hdc);

	srand(time(0));
	int start_x = 1 + rand() % 5;
	int x_left = 2 + start_x * 42;
	int y_left = 2;

	HRGN rgnsquare1 = CreateRectRgn(2 + start_x * 42, 2, 42 + start_x * 42, 42);
	HRGN rgnsquare2 = CreateRectRgn(44 + start_x * 42, 2, 84 + start_x * 42, 42);
	HRGN rgnsquare3 = CreateRectRgn(86 + start_x * 42, 2, 126 + start_x * 42, 42);
	HRGN rgnsquare4 = CreateRectRgn(128 + start_x * 42, 2, 168 + start_x * 42, 42);

	int coord_ar_x = start_x;
	int coord_ar_y = 0;

	::array[coord_ar_y][coord_ar_x] = 1;
	::array[coord_ar_y][coord_ar_x + 1] = 1;
	::array[coord_ar_y][coord_ar_x + 2] = 1;
	::array[coord_ar_y][coord_ar_x + 3] = 1;

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
	moving_I(rgnsquare1, rgnsquare2, rgnsquare3, rgnsquare4, hdc, squareBrush, bkBrush, x_left, y_left, T_space, coord_ar_x, coord_ar_y);
}

void Figure_J(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	chek_for_delete_line(hdc);
	int T_space = 0;

	int start_x = 1 + rand() % 6;
	int x_left = 2 + start_x * 42;
	int y_left = 2;

	HRGN rgnsquare1 = CreateRectRgn(2 + start_x * 42, 44, 42 + start_x * 42, 84);
	HRGN rgnsquare2 = CreateRectRgn(44 + start_x * 42, 44, 84 + start_x * 42, 84);
	HRGN rgnsquare3 = CreateRectRgn(86 + start_x * 42, 44, 126 + start_x * 42, 84);
	HRGN rgnsquare4 = CreateRectRgn(2 + start_x * 42, 2, 42 + start_x * 42, 42);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);

	int coord_ar_x = start_x;
	int coord_ar_y = 0;

	::array[coord_ar_y + 1][coord_ar_x] = 1;
	::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
	::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
	::array[coord_ar_y][coord_ar_x] = 1;

	moving_J(rgnsquare1, rgnsquare2, rgnsquare3, rgnsquare4, hdc, squareBrush, bkBrush, x_left, y_left, T_space, coord_ar_x, coord_ar_y);
}

void Figure_L(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	chek_for_delete_line(hdc);

	int T_space = 0;

	int start_x = 1 + rand() % 6;
	int x_left = 2 + start_x * 42;
	int y_left = 2;

	HRGN rgnsquare1 = CreateRectRgn(2 + start_x * 42, 44, 42 + start_x * 42, 84);
	HRGN rgnsquare2 = CreateRectRgn(44 + start_x * 42, 44, 84 + start_x * 42, 84);
	HRGN rgnsquare3 = CreateRectRgn(86 + start_x * 42, 44, 126 + start_x * 42, 84);
	HRGN rgnsquare4 = CreateRectRgn(86 + start_x * 42, 2, 126 + start_x * 42, 42);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);

	int coord_ar_x = start_x;
	int coord_ar_y = 0;

	::array[coord_ar_y + 1][coord_ar_x] = 1;
	::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
	::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
	::array[coord_ar_y][coord_ar_x + 2] = 1;

	moving_L(rgnsquare1, rgnsquare2, rgnsquare3, rgnsquare4, hdc, squareBrush, bkBrush, x_left, y_left, T_space, coord_ar_x, coord_ar_y);
}

void Figure_O(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	chek_for_delete_line(hdc);

	int start_x = 1 + rand() % 7;
	int x_left = 2 + start_x * 42;
	int y_left = 2;

	HRGN rgnsquare3 = CreateRectRgn(2 + start_x * 42, 44, 42 + start_x * 42, 84);
	HRGN rgnsquare4 = CreateRectRgn(44 + start_x * 42, 44, 84 + start_x * 42, 84);
	HRGN rgnsquare1 = CreateRectRgn(2 + start_x * 42, 2, 42 + start_x * 42, 42);
	HRGN rgnsquare2 = CreateRectRgn(44 + start_x * 42, 2, 84 + start_x * 42, 42);

	int coord_ar_x = start_x;
	int coord_ar_y = 0;

	::array[coord_ar_y][coord_ar_x] = 1;
	::array[coord_ar_y + 1][coord_ar_x] = 1;
	::array[coord_ar_y][coord_ar_x + 1] = 1;
	::array[coord_ar_y + 1][coord_ar_x + 1] = 1;


	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);

	moving_O(rgnsquare1, rgnsquare2, rgnsquare3, rgnsquare4, hdc, squareBrush, bkBrush, x_left, y_left, coord_ar_x, coord_ar_y);
}

void Figure_S(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	int T_space = 0;

	chek_for_delete_line(hdc);

	int start_x = 1 + rand() % 6;
	int x_left = 2 + start_x * 42;
	int y_left = 2;


	HRGN rgnsquare1 = CreateRectRgn(2 + start_x * 42, 44, 42 + start_x * 42, 84);
	HRGN rgnsquare3 = CreateRectRgn(44 + start_x * 42, 2, 84 + start_x * 42, 42);
	HRGN rgnsquare2 = CreateRectRgn(44 + start_x * 42, 44, 84 + start_x * 42, 84);
	HRGN rgnsquare4 = CreateRectRgn(86 + start_x * 42, 2, 126 + start_x * 42, 42);

	int coord_ar_x = start_x;
	int coord_ar_y = 0;


	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);

	moving_S(rgnsquare1, rgnsquare2, rgnsquare3, rgnsquare4, hdc, squareBrush, bkBrush, x_left, y_left, T_space, coord_ar_x, coord_ar_y);
}

void Figure_T(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	chek_for_delete_line(hdc);

	int T_space = 0;

	int start_x = 1 + rand() % 6;
	int x_left = 2 + start_x * 42;
	int y_left = 2;

	HRGN rgnsquare1 = CreateRectRgn(2 + start_x * 42, 44, 42 + start_x * 42, 84);
	HRGN rgnsquare2 = CreateRectRgn(44 + start_x * 42, 44, 84 + start_x * 42, 84);
	HRGN rgnsquare3 = CreateRectRgn(86 + start_x * 42, 44, 126 + start_x * 42, 84);
	HRGN rgnsquare4 = CreateRectRgn(44 + start_x * 42, 2, 84 + start_x * 42, 42);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);

	int coord_ar_x = start_x;
	int coord_ar_y = 0;

	::array[coord_ar_y + 1][coord_ar_x] = 1;
	::array[coord_ar_y + 1][coord_ar_x + 1] = 1;
	::array[coord_ar_y + 1][coord_ar_x + 2] = 1;
	::array[coord_ar_y][coord_ar_x + 1] = 1;

	moving_T(rgnsquare1, rgnsquare2, rgnsquare3, rgnsquare4, hdc, squareBrush, bkBrush, x_left, y_left, T_space, coord_ar_x, coord_ar_y);
}

void Figure_Z(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	int T_space = 0;

	chek_for_delete_line(hdc);

	int start_x = 1 + rand() % 6;
	int x_left = 2 + start_x * 42;
	int y_left = 2;

	HRGN rgnsquare1 = CreateRectRgn(2 + start_x * 42, 2, 42 + start_x * 42, 42);
	HRGN rgnsquare2 = CreateRectRgn(44 + start_x * 42, 2, 84 + start_x * 42, 42);
	HRGN rgnsquare3 = CreateRectRgn(44 + start_x * 42, 44, 84 + start_x * 42, 84);
	HRGN rgnsquare4 = CreateRectRgn(86 + start_x * 42, 44, 126 + start_x * 42, 84);

	int coord_ar_x = start_x;
	int coord_ar_y = 0;

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);

	moving_Z(rgnsquare1, rgnsquare2, rgnsquare3, rgnsquare4, hdc, squareBrush, bkBrush, x_left, y_left, T_space, coord_ar_x, coord_ar_y);
}



void chek_for_delete_line(HDC hdc) {
	int var;
	for (int i = 0; i < 20; i++) {
		var = 1;
		for (int j = 0; j < 10; j++) {
			if (::array[19 - i][j] != 1) {
				var = 0;
			}
		}
		if (var == 1) {
			Sleep(100);
			blanking_line(i, hdc);
			delete_line(i, hdc);
			Sleep(100);
			for (int j = 0; j <= 9; j++) {
				::array[19 - i][j] = 0;
			}
			moving_over_line(i, hdc);
			::score += 10;
			score_print(hdc);
			i--;
		}
	}
}

void chek_for_game_over(HDC hdc) {
	int var = 0;
	for (int j = 0; j < 10; j++) {
		if (::array[0][j] == 1) {
			var = 1;
			break;
		}
	}
	if (var == 1) {
		game_over(hdc);
	}
}

void game_over(HDC hdc) {
	clear_game_area(hdc);
	clear_array();

	SetTextColor(hdc, RGB(255, 100, 250));

	HBRUSH brush = CreateSolidBrush(RGB(15, 5, 25));
	HRGN game_over_area = CreateRectRgn(550, 660, 750, 700);

	char game_over_str[] = "GAME OVER!";
	char record_str[] = "NEW RECORD!";

	TextOutA(hdc, 585, 660, game_over_str, strlen(game_over_str) + 1);
	Sleep(500);

	FillRgn(hdc, game_over_area, brush);
	Sleep(220);

	TextOutA(hdc, 585, 660, game_over_str, strlen(game_over_str) + 1);
	Sleep(500);

	FillRgn(hdc, game_over_area, brush);
	Sleep(220);

	TextOutA(hdc, 585, 660, game_over_str, strlen(game_over_str) + 1);
	Sleep(500);

	FillRgn(hdc, game_over_area, brush);
	Sleep(220);

	HBRUSH bkBrush = CreateSolidBrush(RGB(45, 0, 55));
	HBRUSH squareBrush1 = CreateSolidBrush(RGB(255, 200, 100));

	::var_resume = 0;

	if (::score > ::SCOREint1 or ::score > ::SCOREint2 or ::score > ::SCOREint3) {

		TextOutA(hdc, 580, 660, record_str, strlen(record_str) + 1);
		Sleep(500);

		FillRgn(hdc, game_over_area, brush);
		Sleep(220);

		TextOutA(hdc, 580, 660, record_str, strlen(record_str) + 1);
		Sleep(500);

		FillRgn(hdc, game_over_area, brush);
		Sleep(220);

		TextOutA(hdc, 580, 660, record_str, strlen(record_str) + 1);
		Sleep(500);

		FillRgn(hdc, game_over_area, brush);

		remove("records.txt");

		ofstream oFile("records.txt");

		if (oFile.is_open()) {
			if (::score > ::SCOREint1 && ::score > ::SCOREint2 && ::score > ::SCOREint3) {
				oFile << ::score << endl;
				if (::SCOREint1 != 0) {
					oFile << ::SCOREint1 << endl;

				}
				if (::SCOREint2 != 0) {
					oFile << ::SCOREint2 << endl;

				}
				::SCOREint3 = ::SCOREint3;
				::SCOREint2 = ::SCOREint1;
				::SCOREint1 = ::score;
			}
			else if (::score > ::SCOREint2 && ::score > ::SCOREint3) {
				oFile << ::SCOREint1 << endl;
				oFile << ::score << endl;
				if (::SCOREint2 != 0) {
					oFile << ::SCOREint2 << endl;
				}
				::SCOREint3 = ::SCOREint2;
				::SCOREint2 = ::score;
			}
			else if (::score > ::SCOREint3) {
				oFile << ::SCOREint1 << endl;
				oFile << ::SCOREint2 << endl;
				oFile << ::score;
				::SCOREint3 = ::score;
			}
		}
		oFile.close();
	}

	game_over_area = CreateRectRgn(550, 500, 750, 820);
	FillRgn(hdc, game_over_area, brush);
	menu(hdc, squareBrush1, bkBrush);
}

void back_for_next_figure(HDC hdc) {
	HBRUSH bkBrush = CreateSolidBrush(RGB(45, 0, 55));
	HBRUSH del_squareBrush = CreateSolidBrush(RGB(45, 0, 55));

	HRGN line = CreateRectRgn(554, 546, 556, 632);
	FillRgn(hdc, line, bkBrush);

	line = CreateRectRgn(554, 632, 726, 634);
	FillRgn(hdc, line, bkBrush);

	line = CreateRectRgn(726, 546, 728, 634);
	FillRgn(hdc, line, bkBrush);

	line = CreateRectRgn(554, 544, 728, 546);
	FillRgn(hdc, line, bkBrush);

	for (int i = 13; i < 15; i++) {
		HRGN delete_square = CreateRectRgn(558, 2 + i * 42, 598, 42 + i * 42);
		for (int j = 0; j < 3; j++) {
			drawSquare(hdc, delete_square, bkBrush, del_squareBrush, 42, 0);
		}
	}
}


void next_figure(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush, int fig_number) {
	back_for_next_figure(hdc);
	srand(time(0));
	switch (fig_number) {
	case 1:
		next_I(hdc, squareBrush, bkBrush);
		break;
	case 2:
		next_O(hdc, squareBrush, bkBrush);
		break;
	case 3:
		next_T(hdc, squareBrush, bkBrush);
		break;
	case 4:
		next_J(hdc, squareBrush, bkBrush);
		break;
	case 5:
		next_L(hdc, squareBrush, bkBrush);
		break;
	case 6:
		next_S(hdc, squareBrush, bkBrush);
		break;
	case 7:
		next_Z(hdc, squareBrush, bkBrush);
		break;
	}
}

void next_I(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	HRGN rgnsquare1 = CreateRectRgn(558, 590, 598, 630);
	HRGN rgnsquare2 = CreateRectRgn(600, 590, 640, 630);
	HRGN rgnsquare3 = CreateRectRgn(642, 590, 682, 630);
	HRGN rgnsquare4 = CreateRectRgn(684, 590, 724, 630);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
}

void next_O(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	HRGN rgnsquare1 = CreateRectRgn(600, 590, 640, 630);
	HRGN rgnsquare2 = CreateRectRgn(642, 590, 682, 630);
	HRGN rgnsquare3 = CreateRectRgn(600, 548, 640, 588);
	HRGN rgnsquare4 = CreateRectRgn(642, 548, 682, 588);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
}

void next_T(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	int i = rand() % 2;
	int rand_pos = 42 * i;

	HRGN rgnsquare1 = CreateRectRgn(558 + rand_pos, 590, 598 + rand_pos, 630);
	HRGN rgnsquare2 = CreateRectRgn(600 + rand_pos, 590, 640 + rand_pos, 630);
	HRGN rgnsquare3 = CreateRectRgn(642 + rand_pos, 590, 682 + rand_pos, 630);
	HRGN rgnsquare4 = CreateRectRgn(600 + rand_pos, 548, 640 + rand_pos, 588);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
}

void next_J(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	int i = rand() % 2;
	int rand_pos = 42 * i;

	HRGN rgnsquare1 = CreateRectRgn(558 + rand_pos, 590, 598 + rand_pos, 630);
	HRGN rgnsquare2 = CreateRectRgn(600 + rand_pos, 590, 640 + rand_pos, 630);
	HRGN rgnsquare3 = CreateRectRgn(642 + rand_pos, 590, 682 + rand_pos, 630);
	HRGN rgnsquare4 = CreateRectRgn(558 + rand_pos, 548, 598 + rand_pos, 588);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
}

void next_L(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	int i = rand() % 2;
	int rand_pos = 42 * i;

	HRGN rgnsquare1 = CreateRectRgn(558 + rand_pos, 590, 598 + rand_pos, 630);
	HRGN rgnsquare2 = CreateRectRgn(600 + rand_pos, 590, 640 + rand_pos, 630);
	HRGN rgnsquare3 = CreateRectRgn(642 + rand_pos, 590, 682 + rand_pos, 630);
	HRGN rgnsquare4 = CreateRectRgn(642 + rand_pos, 548, 682 + rand_pos, 588);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
}

void next_S(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {
	int i = rand() % 2;
	int rand_pos = 42 * i;

	HRGN rgnsquare1 = CreateRectRgn(558 + rand_pos, 590, 598 + rand_pos, 630);
	HRGN rgnsquare2 = CreateRectRgn(600 + rand_pos, 590, 640 + rand_pos, 630);
	HRGN rgnsquare3 = CreateRectRgn(642 + rand_pos, 548, 682 + rand_pos, 588);
	HRGN rgnsquare4 = CreateRectRgn(600 + rand_pos, 548, 640 + rand_pos, 588);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
}

void next_Z(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	int i = rand() % 2;
	int rand_pos = 42 * i;

	HRGN rgnsquare1 = CreateRectRgn(558 + rand_pos, 548, 598 + rand_pos, 588);
	HRGN rgnsquare2 = CreateRectRgn(600 + rand_pos, 548, 640 + rand_pos, 588);
	HRGN rgnsquare3 = CreateRectRgn(642 + rand_pos, 590, 682 + rand_pos, 630);
	HRGN rgnsquare4 = CreateRectRgn(600 + rand_pos, 590, 640 + rand_pos, 630);

	FillRgn(hdc, rgnsquare1, squareBrush);
	FillRgn(hdc, rgnsquare2, squareBrush);
	FillRgn(hdc, rgnsquare3, squareBrush);
	FillRgn(hdc, rgnsquare4, squareBrush);
}


void virtual_I(HDC hdc, int coord_ar_x, int coord_ar_y, int T_space) {
	HRGN virtual_square1, virtual_square2, virtual_square3, virtual_square4;
	HBRUSH bkBrush = CreateSolidBrush(RGB(55, 0, 75));
	int y = 19;
	if (T_space == 0) {
		while (::array[y][coord_ar_x] == 1 or ::array[y][coord_ar_x + 1] == 1 or
			::array[y][coord_ar_x + 2] == 1 or ::array[y][coord_ar_x + 3] == 1) {
			y -= 1;
		}

		::array[y][coord_ar_x] = 2;
		::array[y][coord_ar_x + 1] = 2;
		::array[y][coord_ar_x + 2] = 2;
		::array[y][coord_ar_x + 3] = 2;

		if (::array[y][coord_ar_x] != 1) {
			virtual_square1 = CreateRectRgn(2 + coord_ar_x * 42, 2 + y * 42, 42 + coord_ar_x * 42, 42 + y * 42);
			FillRgn(hdc, virtual_square1, bkBrush);
		}
		if (::array[y][coord_ar_x + 1] != 1) {
			virtual_square2 = CreateRectRgn(44 + coord_ar_x * 42, 2 + y * 42, 84 + coord_ar_x * 42, 42 + y * 42);
			FillRgn(hdc, virtual_square2, bkBrush);
		}
		if (::array[y][coord_ar_x + 2] != 1) {
			virtual_square3 = CreateRectRgn(86 + coord_ar_x * 42, 2 + y * 42, 126 + coord_ar_x * 42, 42 + y * 42);
			FillRgn(hdc, virtual_square3, bkBrush);
		}
		if (::array[y][coord_ar_x + 3] != 1) {
			virtual_square4 = CreateRectRgn(128 + coord_ar_x * 42, 2 + y * 42, 168 + coord_ar_x * 42, 42 + y * 42);
			FillRgn(hdc, virtual_square4, bkBrush);
		}
	}
	else {
		while (::array[y][coord_ar_x] == 1 or ::array[y - 1][coord_ar_x] == 1 or
			::array[y - 2][coord_ar_x] == 1 or ::array[y - 3][coord_ar_x] == 1) {
			y -= 1;
		}

		::array[y][coord_ar_x] = 2;
		::array[y - 1][coord_ar_x] = 2;
		::array[y - 2][coord_ar_x] = 2;
		::array[y - 3][coord_ar_x] = 2;

		if (::array[y][coord_ar_x] != 1) {
			virtual_square1 = CreateRectRgn(2 + coord_ar_x * 42, 2 + y * 42, 42 + coord_ar_x * 42, 42 + y * 42);
			FillRgn(hdc, virtual_square1, bkBrush);
		}
		if (::array[y - 1][coord_ar_x] != 1) {
			virtual_square2 = CreateRectRgn(2 + coord_ar_x * 42, 2 + (y - 1) * 42, 42 + coord_ar_x * 42, 42 + (y - 1) * 42);
			FillRgn(hdc, virtual_square2, bkBrush);
		}
		if (::array[y - 2][coord_ar_x] != 1) {
			virtual_square3 = CreateRectRgn(2 + coord_ar_x * 42, 2 + (y - 2) * 42, 42 + coord_ar_x * 42, 42 + (y - 2) * 42);
			FillRgn(hdc, virtual_square3, bkBrush);
		}
		if (::array[y - 3][coord_ar_x] != 1) {
			virtual_square4 = CreateRectRgn(2 + coord_ar_x * 42, 2 + (y - 3) * 42, 42 + coord_ar_x * 42, 42 + (y - 3) * 42);
			FillRgn(hdc, virtual_square4, bkBrush);
		}
	}
}

void virtual_O(HDC hdc, int coord_ar_x, int coord_ar_y) {
	HRGN virtual_square1, virtual_square2, virtual_square3, virtual_square4;
	HBRUSH bkBrush = CreateSolidBrush(RGB(55, 0, 75));
	while (::array[coord_ar_y + 2][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 && coord_ar_y + 2 < 20) {
		coord_ar_y += 1;
	}
	if (::array[coord_ar_y][coord_ar_x] == 0) {
		virtual_square1 = CreateRectRgn(2 + coord_ar_x * 42, 2 + coord_ar_y * 42, 42 + coord_ar_x * 42, 42 + coord_ar_y * 42);
		FillRgn(hdc, virtual_square1, bkBrush);
	}
	if (::array[coord_ar_y][coord_ar_x + 1] == 0) {
		virtual_square2 = CreateRectRgn(44 + coord_ar_x * 42, 2 + coord_ar_y * 42, 84 + coord_ar_x * 42, 42 + coord_ar_y * 42);
		FillRgn(hdc, virtual_square2, bkBrush);
	}
	if (::array[coord_ar_y + 1][coord_ar_x] == 0) {
		virtual_square3 = CreateRectRgn(2 + coord_ar_x * 42, 44 + coord_ar_y * 42, 42 + coord_ar_x * 42, 84 + coord_ar_y * 42);
		FillRgn(hdc, virtual_square3, bkBrush);
	}
	if (::array[coord_ar_y + 1][coord_ar_x + 1] == 0) {
		virtual_square4 = CreateRectRgn(44 + coord_ar_x * 42, 44 + coord_ar_y * 42, 84 + coord_ar_x * 42, 84 + coord_ar_y * 42);
		FillRgn(hdc, virtual_square4, bkBrush);
	}
}

void virtual_T(HDC hdc, int coord_ar_x, int coord_ar_y, int T_space) {
	HRGN virtual_square1, virtual_square2, virtual_square3, virtual_square4;
	HBRUSH bkBrush = CreateSolidBrush(RGB(55, 0, 75));
	if (T_space == 0) {
		while (::array[coord_ar_y + 2][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 &&
			::array[coord_ar_y + 2][coord_ar_x + 2] != 1 && coord_ar_y + 2 < 20) {
			coord_ar_y += 1;
		}

		if (::array[coord_ar_y][coord_ar_x + 1] == 0) {
			virtual_square1 = CreateRectRgn(44 + coord_ar_x * 42, 2 + coord_ar_y * 42, 84 + coord_ar_x * 42, 42 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square1, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x] == 0) {
			virtual_square2 = CreateRectRgn(2 + coord_ar_x * 42, 44 + coord_ar_y * 42, 42 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square2, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x + 1] == 0) {
			virtual_square3 = CreateRectRgn(44 + coord_ar_x * 42, 44 + coord_ar_y * 42, 84 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square3, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x + 2] == 0) {
			virtual_square4 = CreateRectRgn(86 + coord_ar_x * 42, 44 + coord_ar_y * 42, 126 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square4, bkBrush);
		}
	}
	else if (T_space == 1) {
		while (::array[coord_ar_y + 3][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1
			&& coord_ar_y + 3 < 20) {
			coord_ar_y += 1;
		}
		if (::array[coord_ar_y][coord_ar_x] == 0) {
			virtual_square1 = CreateRectRgn(2 + coord_ar_x * 42, 2 + coord_ar_y * 42, 42 + coord_ar_x * 42, 42 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square1, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x] == 0) {
			virtual_square2 = CreateRectRgn(2 + coord_ar_x * 42, 44 + coord_ar_y * 42, 42 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square2, bkBrush);
		}
		if (::array[coord_ar_y + 2][coord_ar_x] == 0) {
			virtual_square3 = CreateRectRgn(2 + coord_ar_x * 42, 86 + coord_ar_y * 42, 42 + coord_ar_x * 42, 126 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square3, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x + 1] == 0) {
			virtual_square4 = CreateRectRgn(44 + coord_ar_x * 42, 44 + coord_ar_y * 42, 84 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square4, bkBrush);
		}
	}
	else if (T_space == 2) {
		while (::array[coord_ar_y + 1][coord_ar_x] != 1 && ::array[coord_ar_y + 2][coord_ar_x + 1] != 1 &&
			::array[coord_ar_y + 2][coord_ar_x + 2] != 1 && coord_ar_y + 2 < 20) {
			coord_ar_y += 1;
		}
		if (::array[coord_ar_y][coord_ar_x] == 0) {
			virtual_square1 = CreateRectRgn(2 + coord_ar_x * 42, 2 + coord_ar_y * 42, 42 + coord_ar_x * 42, 42 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square1, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x] == 0) {
			virtual_square2 = CreateRectRgn(44 + coord_ar_x * 42, 2 + coord_ar_y * 42, 84 + coord_ar_x * 42, 42 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square2, bkBrush);
		}
		if (::array[coord_ar_y + 2][coord_ar_x] == 0) {
			virtual_square3 = CreateRectRgn(86 + coord_ar_x * 42, 2 + coord_ar_y * 42, 126 + coord_ar_x * 42, 42 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square3, bkBrush);
		}
		if (::array[coord_ar_y + 3][coord_ar_x] == 0) {
			virtual_square4 = CreateRectRgn(44 + coord_ar_x * 42, 44 + coord_ar_y * 42, 84 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square4, bkBrush);
		}
	}
	else {
		while (::array[coord_ar_y + 2][coord_ar_x] != 1 && ::array[coord_ar_y + 3][coord_ar_x + 1] != 1 && coord_ar_y + 3 < 20) {
			coord_ar_y += 1;
		}
		if (::array[coord_ar_y][coord_ar_x + 1] == 0) {
			virtual_square1 = CreateRectRgn(44 + coord_ar_x * 42, 2 + coord_ar_y * 42, 84 + coord_ar_x * 42, 42 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square1, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x + 1] == 0) {
			virtual_square2 = CreateRectRgn(44 + coord_ar_x * 42, 44 + coord_ar_y * 42, 84 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square2, bkBrush);
		}
		if (::array[coord_ar_y + 2][coord_ar_x + 1] == 0) {
			virtual_square3 = CreateRectRgn(44 + coord_ar_x * 42, 86 + coord_ar_y * 42, 84 + coord_ar_x * 42, 126 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square3, bkBrush);
		}
		if (::array[coord_ar_y + 1][coord_ar_x] == 0) {
			virtual_square4 = CreateRectRgn(2 + coord_ar_x * 42, 44 + coord_ar_y * 42, 42 + coord_ar_x * 42, 84 + coord_ar_y * 42);
			FillRgn(hdc, virtual_square4, bkBrush);
		}
	}
}

void delete_virtuals(HDC hdc) {
	HRGN delete_square_virtual;
	HBRUSH Brush = CreateSolidBrush(RGB(45, 0, 55));
	int numb = 0;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 10; j++) {
			if (::array[19 - i][j] == 2) {
				numb += 1;
				delete_square_virtual = CreateRectRgn(2 + j * 42, 2 + (19 - i) * 42, 42 + j * 42, 42 + (19 - i) * 42);
				FillRgn(hdc, delete_square_virtual, Brush);
			}
			//if (numb == 3) {
			//	break;
			//}
		}
	}

}


void moving_over_line(int i, HDC hdc) {
	i++;
	int var = 1;
	while (i <= 18 && var != 0) {
		delete_line(i, hdc);
		for (int j = 0; j <= 9; j++) {
			::array[20 - i][j] = ::array[19 - i][j];
		}
		draw_line(i, hdc);
		i++;
	}
	delete_line(i, hdc);
}

void delete_line(int i, HDC hdc) {
	HRGN delete_square = CreateRectRgn(2, 2 + (19 - i) * 42, 42, 42 + (19 - i) * 42);
	HBRUSH bkBrush = CreateSolidBrush(RGB(45, 0, 55));
	HBRUSH del_squareBrush = CreateSolidBrush(RGB(45, 0, 55));
	for (int j = 0; j < 9; j++) {
		drawSquare(hdc, delete_square, bkBrush, del_squareBrush, 42, 0);
	}
}

void draw_line(int i, HDC hdc) {
	HRGN draw_square = CreateRectRgn(2, 2 + (20 - i) * 42, 42, 42 + (20 - i) * 42);
	HBRUSH bkBrush = CreateSolidBrush(RGB(255, 200, 100));
	HBRUSH del_squareBrush = CreateSolidBrush(RGB(255, 200, 100));
	for (int j = 0; j < 10; j++) {
		if (::array[20 - i][j] == 1) {
			draw_lineSquare(hdc, bkBrush, del_squareBrush, i, j);
		}
	}
}

void draw_lineSquare(HDC hdc, HBRUSH bkBrsh, HBRUSH fBrsh, int i, int j) {
	HRGN draw_square = CreateRectRgn(2 + j * 42, 2 + (20 - i) * 42, 42 + j * 42, 42 + (20 - i) * 42);
	FillRgn(hdc, draw_square, bkBrsh);
	FillRgn(hdc, draw_square, fBrsh);
}

void blanking_line(int i, HDC hdc) {
	HBRUSH bkBrush = CreateSolidBrush(RGB(45, 0, 55));
	HBRUSH del_squareBrush = CreateSolidBrush(RGB(45, 0, 55));
	for (int j = 0; j < 10; j++) {
		draw_lineSquare(hdc, bkBrush, del_squareBrush, i + 1, j);
	}
	Sleep(220);
	bkBrush = CreateSolidBrush(RGB(255, 200, 100));
	del_squareBrush = CreateSolidBrush(RGB(255, 200, 100));
	for (int j = 0; j < 10; j++) {
		draw_lineSquare(hdc, bkBrush, del_squareBrush, i + 1, j);
	}
	Sleep(100);
}

void figure_generation(HDC hdc, HBRUSH squareBrush, HBRUSH bkBrush) {

	chek_for_game_over(hdc);
	::score += 1;
	score_print(hdc);
	Sleep(10);

	srand(time(0));

	::next_figure_numb = 1 + rand() % 7;

	next_figure(hdc, squareBrush, bkBrush, ::next_figure_numb);


	switch (::current_figure_numb) {
	case 1:
		::current_fig = 1;
		Figure_I(hdc, squareBrush, bkBrush);
	case 2:
		::current_fig = 2;
		Figure_O(hdc, squareBrush, bkBrush);
	case 3:
		::current_fig = 3;
		Figure_T(hdc, squareBrush, bkBrush);
	case 4:
		::current_fig = 4;
		Figure_J(hdc, squareBrush, bkBrush);
	case 5:
		::current_fig = 5;
		Figure_L(hdc, squareBrush, bkBrush);
	case 6:
		::current_fig = 6;
		Figure_S(hdc, squareBrush, bkBrush);
	case 7:
		::current_fig = 7;
		Figure_Z(hdc, squareBrush, bkBrush);
	}
}


