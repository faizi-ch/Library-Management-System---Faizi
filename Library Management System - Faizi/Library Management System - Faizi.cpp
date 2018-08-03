#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <dos.h>
#include <time.h>
void TimeandDate();
void SetColor();
void ClearConsoleToColors();
void SetColorAndBackground();
void Password();
void mainmenu();
void addbooks();
void deletebooks();
void searchbooks();
void issuebooks();
void issueabook();
void viewissued();
void searchissued();
void removeissued();
void viewbooks();
void editbooks();

int s;
FILE *fb, *ft, *fi;
char categories[][15] = { "Computer","Electronics","Electrical","Civil","Mechanical","Architecture" };
char password[10] = "faizi";
char findbook;
struct books
{
	int id;
	char name[30];
	char Author[30];
	int quantity;
	float Price;
	int rackno;
	char *cat;
	char stname[30];
};
struct books a;

void main() 
{
	//mainmenu();
	Password();
	
	getchar();
}



void SetColor(int ForgC)
{
	WORD wColor;
	///We will need this handle to get the current background attribute
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	///We use csbi for the wAttributes word.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		///Mask out all but the background attribute, and add in the forgournd color
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	///Get the handle to the current output buffer...
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	///This is used to reset the carat/cursor to the top left.
	COORD coord = { 0, 0 };
	///A return value... indicating how many chars were written
	///   not used but we need to capture this since it will be
	///   written anyway (passing NULL causes an access violation).
	DWORD count;
	///This is a structure containing all of the console info
	/// it is used here to find the size of the console.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	///Here we will set the current color
	SetConsoleTextAttribute(hStdOut, wColor);
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		///This fills the buffer with a given character (in this case 32=space).
		FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
		///This will set our cursor position for the next print statement.
		SetConsoleCursorPosition(hStdOut, coord);
	}
	return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	return;
}

COORD coord = { 0, 0 }; // sets coordinates to 0,0
						//COORD max_buffer_size = GetLargestConsoleWindowSize(hOut);
COORD max_res, cursor_size;
void gotoxy(int x, int y)
{
	coord.X = x; coord.Y = y; // X and Y coordinates
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TimeandDate()
{
	time_t t;
	time(&t);
	printf(ctime(&t));
}
void Password()
{
	system("cls");
	char p[120] = "Password Protected";
	int i, j;
	int l=0;
	char pass[10], ch=0;
	//ClearConsoleToColors(0, 255);
	//SetColorAndBackground(10, 9);
	gotoxy(30, 3);
	for (j = 0; j < 19; j++)
	{
		Sleep(50);
		printf("*");
	}
	int jj;
	for (i = 0; p[i] != '\0'; i++)
	{
		for (jj = 0; jj < 50; jj++);
		{
			Sleep(50);
			SetColorAndBackground(15, 12);
			printf("%c", p[i]);


		}
	}
	for (j = 0; j <= 19; j++);
	{
		Sleep(50);
		printf("*");
	}
	gotoxy(35, 7);
	SetColorAndBackground(1, 0);
	printf("Enter Password: ");
	while (ch != 13)
	{
		ch = _getch();

		if (ch != 13 && ch != 8) {
			printf("*");
			pass[l] = ch;
			l++;
		}
	}
	pass[l] = '\0';
		if (strcmp(pass, password) == 0)
		{
			gotoxy(35, 9);
			printf("Password Matched\n");
			gotoxy(35, 11);
			printf("Press any key to continue.....");
			_getch();
			mainmenu();
		}
		else
		{
			gotoxy(30, 16);
			printf("\aWarning!!! Incorrect Password");
			_getch();
			Password();
		}
	
}

//mainmenu
void mainmenu(void)
		{
			system("cls");
			ClearConsoleToColors(3, 0);
			gotoxy(37, 3);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(37, 5);
			printf("\xDB\xDB\xDB\xDB\xB2 1. Add Books");
			gotoxy(37, 7);
			printf("\xDB\xDB\xDB\xDB\xB2 2. Delete Books");
			gotoxy(37, 9);
			printf("\xDB\xDB\xDB\xDB\xB2 3. Search Books");
			gotoxy(37, 11);
			printf("\xDB\xDB\xDB\xDB\xB2 4. Issue Books");
			gotoxy(37, 13);
			printf("\xDB\xDB\xDB\xDB\xB2 5. View Book List");
			gotoxy(37, 15);
			printf("\xDB\xDB\xDB\xDB\xB2 6. Edit Books Record");
			gotoxy(37, 17);
			printf("\xDB\xDB\xDB\xDB\xB2 7. Change Password");
			gotoxy(37, 19);
			printf("\xDB\xDB\xDB\xDB\xB2 8. Close Application");
			gotoxy(37, 21);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(44, 22);
			TimeandDate();
			gotoxy(37, 24);
			printf("Enter your choice: ");
			switch (_getch())
			{
			case '1':
			{
				addbooks();
				break;
			}
			case '2':
			{
				deletebooks();
				break;
			}
			case '3':
			{
				searchbooks();
				break;
			}
			case '4':
			{
				issuebooks();
				break;
			}
			case '5':
			{
				viewbooks();
				break;
			}
			case '6':
			{
				editbooks();
				break;
			}
			case '7':
			{
				system("cls");
				int i;
				gotoxy(68, 13);
				char st[20] = "Under Construction";
				for (i = 0; st[i] != '\0'; i++)
				{
					Sleep(50);
					SetColorAndBackground(15, 9);
					printf("%c", st[i]);
				}
				gotoxy(59, 15);
				SetColorAndBackground(1, 15);
				printf("Press any key to return to Main Menu");
				fflush(stdin);
				if (_getch())
					mainmenu();
				break;
			}
			case '8':
			{
				system("cls");
				ClearConsoleToColors(9, 0);
				gotoxy(30, 12);
				SetColorAndBackground(0, 15);
				printf("Programmers:");
				int i;
				char f[20] = "Faizan Ishfaq";
				char k[20] = "Kamal Shah";
				gotoxy(35, 14);
				for (i = 0; f[i] != '\0'; i++)
				{
					Sleep(100);
					SetColorAndBackground(15, 9);
					printf("%c", f[i]);
				}
				SetColorAndBackground(9, 0);
				gotoxy(35, 15);
				printf("CIIT/FA14-BCS-081/WAH");
				gotoxy(35, 16);
				printf("Cell: 0311-0222221		Email: faizi.ch@live.com");
				gotoxy(35, 18);
				for (i = 0; k[i] != '\0'; i++)
				{
					Sleep(100);
					SetColorAndBackground(15, 9);
					printf("%c", k[i]);
				}
				SetColorAndBackground(9, 0);
				gotoxy(35, 19);
				printf("CIIT/FA14-BCS-058/WAH");
				gotoxy(35, 20);
				printf("Cell: 0303-5693938		Email: kamalshah205@gmail.com");
				Sleep(500);
				gotoxy(50, 22);
				SetColor(10);
				printf("Exiting");
				Sleep(500);
				printf(".");
				Sleep(700);
				printf(".");
				Sleep(700);
				printf(".");
				Sleep(700);
				printf(".");
				Sleep(700);
				printf(".");
				Sleep(700);
				exit(0);
				break;
			}
			default:
			{
				gotoxy(37, 25);
				printf("\aWrong Entry!!Press any key to re-enter...");
				if (_getch())
					mainmenu();
			}
			}	
		}


//function to add books:
void addbooks()				//ERROR: saving categories in a.cat
{
	system("cls");
	gotoxy(37, 3);
	SetColor(37);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SELECT CATEGORIES \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 5);
	printf("\xDB\xDB\xDB\xDB\xB2 1. Computer");
	gotoxy(37, 7);
	printf("\xDB\xDB\xDB\xDB\xB2 2. Electronics");
	gotoxy(37, 9);
	printf("\xDB\xDB\xDB\xDB\xB2 3. Electrical");
	gotoxy(37, 11);
	printf("\xDB\xDB\xDB\xDB\xB2 4. Civil");
	gotoxy(37, 13);
	printf("\xDB\xDB\xDB\xDB\xB2 5. Mechanical");
	gotoxy(37, 15);
	printf("\xDB\xDB\xDB\xDB\xB2 6. Architecture");
	gotoxy(37, 17);
	printf("\xDB\xDB\xDB\xDB\xB2 7. Back to Main Menu");
	gotoxy(37, 19);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 21);
	printf("Enter your choice:");
	scanf_s("%d", &s);
	if (s == 7)
		mainmenu();
	system("cls");
	fopen_s(&fb, "Books.dat", "ab+");
	gotoxy(20, 3); printf("Enter the Information Below");
	gotoxy(20, 4); printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(20, 5);
	printf("\xB2"); gotoxy(46, 5); printf("\xB2");
	gotoxy(20, 6);
	printf("\xB2"); gotoxy(46, 6); printf("\xB2");
	gotoxy(20, 7);
	printf("\xB2"); gotoxy(46, 7); printf("\xB2");
	gotoxy(20, 8);
	printf("\xB2"); gotoxy(46, 8); printf("\xB2");
	gotoxy(20, 9);
	printf("\xB2"); gotoxy(46, 9); printf("\xB2");
	gotoxy(20, 10);
	printf("\xB2"); gotoxy(46, 10); printf("\xB2");
	gotoxy(20, 11);
	printf("\xB2"); gotoxy(46, 11); printf("\xB2");
	gotoxy(20, 12);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(21, 5);
	printf("Category:");
	gotoxy(31, 5);
	printf("%s", categories[s - 1]);

	gotoxy(21, 6);
	int bookid;
	printf("Book ID:\t");
	gotoxy(30, 6);
	scanf_s("%d", &bookid);
	rewind(fb);
	while (fread(&a, sizeof(a), 1, fb) == 1)
		if (bookid == a.id)
		{
			gotoxy(21, 13);
			getchar();
			printf("\aThe book id already exists\a");
			getchar();
			fclose(fb);
			mainmenu();
		}
	a.id = bookid;
	gotoxy(21, 7);
	fflush(stdin);
	printf("Book Name:"); gotoxy(33, 7);
	gets_s(a.name);
	gotoxy(21, 8);
	printf("Author:"); gotoxy(30, 8);
	gets_s(a.Author);
	gotoxy(21, 9);
	printf("Quantity:"); gotoxy(31, 9);
	scanf_s("%d", &a.quantity);
	gotoxy(21, 10);
	printf("Price:Rs."); gotoxy(31, 10);
	scanf_s("%f", &a.Price);
	gotoxy(21, 11);
	printf("Rack No:"); gotoxy(30, 11);
	scanf_s("%d", &a.rackno);
	a.cat = categories[s - 1];
	fseek(fb, 0, SEEK_END);
	fwrite(&a, sizeof(a), 1, fb);
	fclose(fb);
	gotoxy(21, 14);
	printf("The record is successfully saved");
	gotoxy(21, 15);
	printf("Save any more?(Y / N):");
	fflush(stdin);
	if (_getch() == 'n')
		mainmenu();
	else
	addbooks();
}
void deletebooks()
{
	system("cls");
	int bookid;
	gotoxy(37, 3);
	system("COLOR 2");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 DELETE BOOKS RECORD \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 5);
	printf("\xDB\xDB\xDB\xDB\xB2 Enter the Book ID to delete: ");
	scanf_s("%d", &bookid);
	int flag = 0;
	fopen_s(&fb, "Books.dat", "rb+");
	rewind(fb);
	while (fread(&a, sizeof(a), 1, fb) == 1)
	{
		if (a.id == bookid)
		{
			gotoxy(10, 7);
			getchar();
			gotoxy(40, 7);
			printf("The Book is available");
			gotoxy(40, 8);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(40, 9);
			printf("\xB2 ID:%d", a.id); gotoxy(67, 9); printf("\xB2");
			gotoxy(40, 10);
			printf("\xB2 Name:%s", a.name); gotoxy(67, 10); printf("\xB2");
			gotoxy(40, 11);
			printf("\xB2 Author:%s ", a.Author); gotoxy(67, 11); printf("\xB2");
			gotoxy(40, 12);
			printf("\xB2 Quantity:%d ", a.quantity); gotoxy(67, 12); printf("\xB2"); gotoxy(67, 11); printf("\xB2");
			gotoxy(40, 13);
			printf("\xB2 Price:Rs.%.2f", a.Price); gotoxy(67, 13); printf("\xB2");
			gotoxy(40, 14);
			printf("\xB2 Rack No:%d ", a.rackno); gotoxy(67, 14); printf("\xB2");
			gotoxy(40, 15);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(40, 16);
			printf("Do you want to delete it? (Y/N)");
			fflush(stdin);
			if (_getch() == 'y')
			{
				fopen_s(&ft, "temp.dat", "wb+");//temporary file for delete
				rewind(fb);
				while (fread(&a, sizeof(a), 1, fb) == 1)
				{
					if (a.id != bookid)
					{
						fseek(ft, 0, SEEK_CUR);
						fwrite(&a, sizeof(a), 1, ft); //write all in temporary file except that
					}                              //we want to delete
				}
				fclose(ft);
				fclose(fb);
				remove("Books.dat");
				rename("temp.dat", "Books.dat"); //copy all item from temporary file to fb except that
				fopen_s(&fb, "Books.dat", "rb+"); //we want to delete
				fclose(fb);
				gotoxy(40, 18);
				printf("The record is successfully deleted");
				flag++;
			}
			else
			{
				fclose(fb);
				mainmenu();
			}
		}
	}
	if (flag == 0)
	{
		system("cls");
		gotoxy(20, 8);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 9); printf("\xB2");  gotoxy(38, 9); printf("\xB2");
		gotoxy(20, 10);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(22, 9); printf("\aNo Record Found");
	}
	gotoxy(37, 20);
	printf("Delete another Record? (Y/N)");
	fflush(stdin);
	if (_getch() == 'y')
	{
		fclose(fb);
		deletebooks();
	}
	else
	{
		fclose(fb);
		mainmenu();
	}
}		
void searchbooks()
{
	system("cls");
	int id;
	gotoxy(37, 3);
	SetColor(39);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCH BOOKS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 6);
	printf("\xDB\xDB\xDB\xDB\xB2 1. Search by ID");
	gotoxy(37, 10);
	printf("\xDB\xDB\xDB\xDB\xB2 2. Search by Name");
	gotoxy(37, 14);
	printf("\xDB\xDB\xDB\xDB\xB2 3. Back to Main Menu");
	gotoxy(37, 17);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 19);
	printf("Enter your choice:");
	switch (_getch())
	{
	case '1':
	{
		system("cls");
		gotoxy(37, 3);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCH BOOKS BY ID \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(37, 8);
		printf("\xDB\xDB\xDB\xDB\xB2 Enter the Book ID: ");
		gotoxy(37, 13);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(62, 8);
		scanf_s("%d", &id);
		int flag = 0;
		fopen_s(&fb, "Books.dat", "rb");
		rewind(fb);
		while (fread(&a, sizeof(a), 1, fb) == 1)
		{
			if (a.id == id)
			{
				system("cls");
				gotoxy(20, 7);
				printf("The Book is available");
				gotoxy(20, 8);
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				gotoxy(20, 9);
				printf("\xB2 ID:%d", a.id); gotoxy(47, 9); printf("\xB2");
				gotoxy(20, 10);
				printf("\xB2 Name:%s", a.name); gotoxy(47, 10); printf("\xB2");
				gotoxy(20, 11);
				printf("\xB2 Author:%s ", a.Author); gotoxy(47, 11); printf("\xB2");
				gotoxy(20, 12);
				printf("\xB2 Quantity:%d ", a.quantity); gotoxy(47, 12); printf("\xB2"); gotoxy(47, 11); printf("\xB2");
				gotoxy(20, 13);
				printf("\xB2 Price:Rs.%.2f", a.Price); gotoxy(47, 13); printf("\xB2");
				gotoxy(20, 14);
				printf("\xB2 Rack No:%d ", a.rackno); gotoxy(47, 14); printf("\xB2");
				gotoxy(20, 15);
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				flag++;
			}
		}
		if (flag == 0)
		{
			system("cls");
			gotoxy(20, 8);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(20, 9); printf("\xB2");  gotoxy(38, 9); printf("\xB2");
			gotoxy(20, 10);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(22, 9); printf("\aNo Record Found");
		}
		gotoxy(20, 17);
		printf("Try another search? (Y/N)");
		fflush(stdin);
		if (_getch() == 'y')
		{
			fclose(fb);
			searchbooks();
		}
		else
		{
			fclose(fb);
			mainmenu();
		}
		break;
	}
	case '2':
	{
		system("cls");
		char n[25]="\0";
		gotoxy(37, 3);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCH BOOKS BY NAME \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(37, 8);
		printf("\xDB\xDB\xDB\xDB\xB2 Enter Book Name: ");
		gotoxy(37, 13);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(60, 8);
		gets_s(n);
		int flag2 = 0;
		fopen_s(&fb, "Books.dat", "rb");
		rewind(fb);
		while (fread(&a, sizeof(a), 1, fb) == 1)
		{
			if (strcmp(a.name, (n)) == 0)
			{
				system("cls");
				gotoxy(20, 7);
				printf("The Book is available");
				gotoxy(20, 8);
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				gotoxy(20, 9);
				printf("\xB2 ID:%d", a.id); gotoxy(47, 9); printf("\xB2");
				gotoxy(20, 10);
				printf("\xB2 Name:%s", a.name); gotoxy(47, 10); printf("\xB2");
				gotoxy(20, 11);
				printf("\xB2 Author:%s", a.Author); gotoxy(47, 11); printf("\xB2");
				gotoxy(20, 12);
				printf("\xB2 Quantity:%d", a.quantity); gotoxy(47, 12); printf("\xB2");
				gotoxy(20, 13);
				printf("\xB2 Price:Rs.%.2f", a.Price); gotoxy(47, 13); printf("\xB2");
				gotoxy(20, 14);
				printf("\xB2 Rack No:%d ", a.rackno); gotoxy(47, 14); printf("\xB2");
				gotoxy(20, 15);
				printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
				flag2++;
			}
		}
		if (flag2 == 0)
		{
			system("cls");
			gotoxy(20, 8);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(20, 9); printf("\xB2");  gotoxy(38, 9); printf("\xB2");
			gotoxy(20, 10);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(22, 9); printf("\aNo Record Found");
		}
		gotoxy(20, 17);
		printf("Try another search? (Y/N)");
		fflush(stdin);
		if (_getch() == 'y')
		{
			fclose(fb);
			searchbooks();
		}
		else
		{
			fclose(fb);
			mainmenu();
		}
		break;
	}
	case '3':
	{
		mainmenu();
		break;
	}
	default:
	{
		gotoxy(37, 21);
		printf("\aWrong Entry!!Press any key to re-enter...");
		if (_getch())
			searchbooks();
	}
}
}
void issueabook()
{
	system("cls");
	int id;
	gotoxy(15, 4);
	printf("***Issue Book section***");
	gotoxy(10, 6);
	printf("Enter the Book Id:");
	scanf_s("%d", &id);
	int flag = 0;
	fopen_s(&fb, "Books.dat", "rb");
	fopen_s(&fi, "Issue.dat", "ab+");
	rewind(fb);
	while (fread(&a, sizeof(a), 1, fb) == 1)
	{
		if (a.id == id)
		{
			gotoxy(10, 8);
			printf("The book record is available");
			gotoxy(10, 9);
			printf("There are %d unissued books in library ", a.quantity);
			gotoxy(10, 10);
			printf("The name of book is %s", a.name);
			gotoxy(10, 11);
			fflush(stdin);
			printf("Enter student name:");
			gets_s(a.stname);
			// struct dosdate_t d; //for current date
			// _dos_getdate(&d);
			// a.issued.dd=d.day;
			// a.issued.mm=d.month;
			//a.issued.yy=d.year;
			gotoxy(10, 12);
			//printf("Issued date=%d-%d-%d", a.issued.dd, a.issued.mm, a.issued.yy);
			gotoxy(10, 13);
			printf("The BOOK of ID %d is issued", a.id);
			/*a.duedate.dd = a.issued.dd + RETURNTIME;   //for return date
			a.duedate.mm = a.issued.mm;
			a.duedate.yy = a.issued.yy;
			if (a.duedate.dd > 30)
			{
			a.duedate.mm += a.duedate.dd / 30;
			a.duedate.dd -= 30;

			}
			if (a.duedate.mm > 12)
			{
			a.duedate.yy += a.duedate.mm / 12;
			a.duedate.mm -= 12;

			}
			gotoxy(10, 14);
			printf("To be return:%d-%d-%d", a.duedate.dd, a.duedate.mm, a.duedate.yy);*/
			fseek(fi, sizeof(a), SEEK_END);
			fwrite(&a, sizeof(a), 1, fi);
			fclose(fi);
			flag++;
		}
	}
	if (flag == 0)
	{
		system("cls");
		gotoxy(20, 8);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 9); printf("\xB2");  gotoxy(38, 9); printf("\xB2");
		gotoxy(20, 10);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(22, 9); printf("\aNo Record Found");
	}
	gotoxy(20, 17);
	printf("Issue any more? (Y/N)");
	if (_getch() == 'y')
	{
		fclose(fi);
		fclose(fb);
		issueabook();
	}
	else
	{
		fclose(fi);
		fclose(fb);
		issuebooks();
	}
}
void viewissued()
{
	int total = 0, j = 6;
	system("cls");
	gotoxy(15, 3);
	SetColor(38);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BOOK LIST \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(14, 4);
	printf("    STUDENT NAME     |  CATEGORY   |   ID   |      BOOK NAME      |    ISSUE DATE    |    RETURN DATE    ");
	gotoxy(15, 5);
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	fopen_s(&fi, "Issue.dat", "rb");
	rewind(fi);
	while (fread(&a, sizeof(a), 1, fi) == 1)
	{
		fflush(stdin);
		gotoxy(14, j);
		printf("| %s", a.stname);
		//printf("%s", a.cat);
		gotoxy(36, j);
		printf("| %s", a.name);
		gotoxy(27, j);
		printf("| %d", a.id);
		j++;
	}
	fclose(fi);
	gotoxy(70, j + 1);
	printf("Press ENTER to return to Main Menu");
	if (_getch())
		mainmenu();
}
void searchissued()
{
	system("cls");
	int id;
	gotoxy(37, 3);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 SEARCH ISSUED BOOKS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 8);
	printf("\xDB\xDB\xDB\xDB\xB2 Enter the Book ID: ");
	gotoxy(37, 13);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(62, 8);
	scanf_s("%d", &id);
	int flag = 0;
	fopen_s(&fi, "Issue.dat", "rb");
	rewind(fi);
	while (fread(&a, sizeof(a), 1, fi) == 1)
	{
		if (a.id == id)
		{
			system("cls");
			gotoxy(20, 7);
			printf("The Book is available");
			gotoxy(20, 8);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(20, 9);
			printf("\xB2 Issued to:%s", a.stname); gotoxy(47, 9); printf("\xB2");
			gotoxy(20, 10);
			printf("\xB2 Name:%s", a.name); gotoxy(47, 10); printf("\xB2");
			gotoxy(20, 11);
			printf("\xB2 Issue Date:%s ", a.Author); gotoxy(47, 11); printf("\xB2");
			gotoxy(20, 12);
			printf("\xB2 Return Date:%d ", a.quantity); gotoxy(47, 12); printf("\xB2"); gotoxy(47, 11); printf("\xB2");
			gotoxy(20, 13);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			flag++;
		}
	}
	if (flag == 0)
	{
		system("cls");
		gotoxy(20, 8);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 9); printf("\xB2");  gotoxy(38, 9); printf("\xB2");
		gotoxy(20, 10);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(22, 9); printf("\aNo Record Found");
	}
	gotoxy(20, 15);
	printf("Try another search? (Y/N)");
	fflush(stdin);
	if (_getch() == 'y')
	{
		fclose(fi);
		searchissued();
	}
	else
	{
		fclose(fi);
		issuebooks();
	}
}
void removeissued()
{
	system("cls");
	int bookid;
	FILE *fti;
	gotoxy(37, 3);
	system("COLOR 2");
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 REMOVE ISSUED BOOKS \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 5);
	printf("\xDB\xDB\xDB\xDB\xB2 Enter the Book ID to remove: ");
	scanf_s("%d", &bookid);
	int flag = 0;
	fopen_s(&fi, "Issue.dat", "rb+");
	rewind(fi);
	while (fread(&a, sizeof(a), 1, fi) == 1)
	{
		if (a.id == bookid)
		{
			gotoxy(10, 7);
			getchar();
			gotoxy(40, 7);
			printf("The Book is available");
			gotoxy(40, 8);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(40, 9);
			printf("\xB2 Issued to:%s", a.stname); gotoxy(67, 9); printf("\xB2");
			gotoxy(40, 10);
			printf("\xB2 Name:%s", a.name); gotoxy(67, 10); printf("\xB2");
			gotoxy(40, 11);
			printf("\xB2 Issue Date:%s ", a.Author); gotoxy(67, 11); printf("\xB2");
			gotoxy(40, 12);
			printf("\xB2 Return Date:%d ", a.quantity); gotoxy(67, 12); printf("\xB2"); gotoxy(67, 11); printf("\xB2");
			gotoxy(40, 13);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(40, 14);
			printf("Do you want to delete it? (Y/N)");
			fflush(stdin);
			if (_getch() == 'y')
			{
				fopen_s(&fti, "tempissue.dat", "wb+");//temporary file for delete
				rewind(fi);
				while (fread(&a, sizeof(a), 1, fi) == 1)
				{
					if (a.id != bookid)
					{
						fseek(fti, 0, SEEK_CUR);
						fwrite(&a, sizeof(a), 1, fti); //write all in temporary file except that
					}                              //we want to delete
				}
				fclose(fti);
				fclose(fi);
				remove("Issue.dat");
				rename("tempissue.dat", "Issue.dat"); //copy all item from temporary file to fb except that
				fopen_s(&fi, "Issue.dat", "rb+"); //we want to delete
				fclose(fi);
				gotoxy(40, 16);
				printf("The record is successfully deleted");
				flag++;
			}
			else
			{
				fclose(fi);
				issuebooks();
			}
		}
	}
	if (flag == 0)
	{
		system("cls");
		gotoxy(20, 8);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 9); printf("\xB2");  gotoxy(38, 9); printf("\xB2");
		gotoxy(20, 10);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(22, 9); printf("\aNo Record Found");
	}
	gotoxy(37, 20);
	printf("Delete another Record? (Y/N)");
	fflush(stdin);
	if (_getch() == 'y')
	{
		fclose(fi);
		removeissued();
	}
	else
	{
		fclose(fi);
		issuebooks();
	}
}
void issuebooks()
{
	system("cls");
	gotoxy(37, 3);
	SetColor(40);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ISSUE SECTION \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 5);
	printf("\xDB\xDB\xDB\xDB\xB2 1. Issue a Book");
	gotoxy(37, 7);
	printf("\xDB\xDB\xDB\xDB\xB2 2. View Issued Books");
	gotoxy(37, 9);
	printf("\xDB\xDB\xDB\xDB\xB2 3. Search Issued Book");
	gotoxy(37, 11);
	printf("\xDB\xDB\xDB\xDB\xB2 4. Remove Issued Book");
	gotoxy(37, 13);
	printf("\xDB\xDB\xDB\xDB\xB2 5. Back to Main Menu");
	gotoxy(37, 15);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 17);
	printf("Enter your choice:");
	switch (_getch())
	{
	case '1':
	{
		issueabook();
		break;
	}
	case '2':
	{
		viewissued();
		break;
	}
	case '3':
	{
		searchissued();
		break;
	}
	case '4':
	{
		removeissued();
		break;
	}
	case '5':
	{
		mainmenu();
	}
	default:
	{
		gotoxy(57, 20);
		printf("\aWrong Entry!!Press any key to re-enter...");
		if (_getch())
			issuebooks();
	}
	}
}
void viewbooks()
{
	int total=0, j = 6;
	system("cls");
	gotoxy(15, 3);
	SetColor(38);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 BOOK LIST \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(14, 4);
	printf("  CATEGORY   |   ID   |      BOOK NAME      |      AUTHOR      |  QTY  |   PRICE  |  RackNo ");
	gotoxy(15, 5);
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	fopen_s(&fb, "Books.dat", "rb");
	//rewind(fb);
	while (fread(&a, sizeof(a), 1, fb) == 1)
	{
		gotoxy(15, j);
		fflush(stdin);
		//printf("%s", a.cat);
		gotoxy(36, j);
		printf("| %s", a.name);
		gotoxy(58, j);
		printf("| %s", a.Author);
		gotoxy(27, j);
		printf("| %d", a.id);
		gotoxy(77, j);
		printf("| %d", a.quantity);
		gotoxy(85, j);
		printf("| %.2f", a.Price);
		gotoxy(96, j);
		printf("| %d", a.rackno);
		j++;
		total += a.quantity;
	}
	gotoxy(15, j + 1);
	printf("Total Books: %d",total);
	fclose(fb);
	gotoxy(70, j + 1);
	printf("Press ENTER to return to Main Menu");
	if (_getch())
		mainmenu();
}
void editbooks()
{
	system("cls");
	int id;
	gotoxy(37, 3);
	SetColor(20);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 EDIT BOOKS RECORD \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(37, 8);
	printf("\xDB\xDB\xDB\xDB\xB2 Enter the Book ID to be edited: ");
	gotoxy(37, 13);
	printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	gotoxy(75, 8);
	scanf_s("%d", &id);
	int flag = 0;
	fopen_s(&fb, "Books.dat", "rb+");
	rewind(fb);
	while (fread(&a, sizeof(a), 1, fb) == 1)
	{
		if (a.id == id)
		{
			system("cls");
			gotoxy(20, 7);
			printf("The Book is available");
			gotoxy(20, 8);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(20, 9);
			printf("\xB2 ID:%d", a.id); gotoxy(47, 9); printf("\xB2");
			gotoxy(20, 10);
			printf("\xB2 Name:%s", a.name); gotoxy(47, 10); printf("\xB2");
			gotoxy(20, 11);
			printf("\xB2 Author:%s ", a.Author); gotoxy(47, 11); printf("\xB2");
			gotoxy(20, 12);
			printf("\xB2 Quantity:%d ", a.quantity); gotoxy(47, 12); printf("\xB2"); gotoxy(47, 11); printf("\xB2");
			gotoxy(20, 13);
			printf("\xB2 Price:Rs.%.2f", a.Price); gotoxy(47, 13); printf("\xB2");
			gotoxy(20, 14);
			printf("\xB2 Rack No:%d ", a.rackno); gotoxy(47, 14); printf("\xB2");
			gotoxy(20, 15);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(60, 7);
			printf("Enter new record:");
			gotoxy(60, 8);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			gotoxy(60, 9);
			printf("\xB2 ID:%d", a.id); gotoxy(87, 9); printf("\xB2");
			gotoxy(60, 10);
			printf("\xB2 Name:"); gotoxy(87, 10); printf("\xB2");
			gotoxy(60, 11);
			printf("\xB2 Author:"); gotoxy(87, 11); printf("\xB2");
			gotoxy(60, 12);
			printf("\xB2 Quantity:"); gotoxy(87, 12); printf("\xB2"); gotoxy(87, 11); printf("\xB2");
			gotoxy(60, 13);
			printf("\xB2 Price:Rs."); gotoxy(87, 13); printf("\xB2");
			gotoxy(60, 14);
			printf("\xB2 Rack No:"); gotoxy(87, 14); printf("\xB2");
			gotoxy(60, 15);
			printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
			fflush(stdin);
			gotoxy(67, 10);
			gets_s(a.name);
			gotoxy(69, 11);
			gets_s(a.Author);
			gotoxy(71, 12);
			scanf_s("%d", &a.quantity);
			gotoxy(71, 13);
			scanf_s("%f", &a.Price);
			gotoxy(70, 14);
			scanf_s("%d", &a.rackno);
			gotoxy(60, 16);
			printf("The record is modified");
			fseek(fb, ftell(fb) - sizeof(a), 0);
			fwrite(&a, sizeof(a), 1, fb);
			fclose(fb);
			flag++;
		}
	}
	if (flag == 0)
	{
		system("cls");
		gotoxy(20, 8);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(20, 9); printf("\xB2");  gotoxy(38, 9); printf("\xB2");
		gotoxy(20, 10);
		printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		gotoxy(22, 9); printf("\aNo Record Found");
	}
	gotoxy(20, 17);
	printf("Modify another Record? (Y/N)");
	fflush(stdin);
	if (_getch() == 'y')
	{
		fclose(fb);
		editbooks();
	}
	else
	{
		fclose(fb);
		mainmenu();
	}
}
