#include<iostream>

#include<fstream>

#include<cstring>

#include<cstdlib>

#include<conio.h>

#include<time.h>

using namespace std;
int Score;
//------------------------------------------------------------------Functions For 4x4 Board------------------------------------------------------------------------------
void Invalid_Selection();
void Temp_Save44(int Board44[4][4], int Score); //For Saving Board in File
void Help_Table();
void Cout_Func(int[]);
void Sortsc(int sc[5]);
void Display44(int Board[4][4]);
void Select_Two_Blank(int Board[4][4]);
void Up_Func(int Board[4][4]);
void Down_Func(int Board[4][4]);
void Left_Func(int Board[4][4]);
void Right_Func(int Board[4][4]);
void Undo_Func(int Board[4][4], int Temp[4][4]);
int Check_Func(int Board[4][4], int Temp[4][4]);
void Add2o4_Func(int Board[4][4]);
int CheckGO_Func(int Board[4][4]);
//---------------------------------------------------------------------Manual Functionss--------sth M ==> Manual Functions--------------------------------------------------------
int ** Make_BoardM(int Num_Of_Rows, int Num_Of_Cols);
void Temp_SaveM(int ** Board, int Num_Of_Rows, int Num_Of_Cols, int Score); //For Saving Board in File
void Load_Row_Col(int RowCol[2]);
void Load_Temp_Board(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
int Load_Score();
void Select_Two_BlankM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
void DisplayM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
void Undo_FuncM(int ** Board, int ** Temp, int Num_Of_Rows, int Num_Of_Cols);
int Check_FuncM(int ** Board, int ** Temp, int Num_Of_Rows, int Num_Of_Cols);
void Add2o4_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
void Up_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
void Down_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
void Left_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
void Right_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);
int CheckGO_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols);

int main() {

  Startpage: int First_Menu,
  sc[5];
  FILE * fptr,
  * ptr;
  fptr = fopen("Scores.txt", "r");
  if (fptr == NULL) {
    cout << "\n\n\nError!!! File can not be opened" << endl;
    system("pause");
    exit(1);
  }
  for (int i = 0; i < 5; i++) {
    fscanf(fptr, "%d", & sc[i]);
  }

  fclose(fptr);

  cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n" << "<1> Continue\n" << "<2> New Game\n" << "<3> High Scores\n" << "<4> Exit\n\n" << "Please Enter A Number: ";
  cin >> First_Menu;

  int Board44[4][4] = {
    0
  },
  Temp44[4][4] = {
    0
  },
  **
  Board,
  **
  Temp,
  RowCol[2] = {
    0
  };
  char Key;
  switch (First_Menu) { //First We have Three Cases , That Case 1 (That Is Our Second Menu ) Has 3 Options Again That I Show Them again with Switch-Case
  case 1:
    ptr = fopen("Temp Board.txt", "r");
    if (ptr == NULL) {
      cout << "\n\n\nThere Isn't Any Checkpoint.Please Create A New Game";
      cout << "\n\nPress Any Key to Continue...";
      getch();
      system("cls");
      goto Startpage;
    } else {

      int Num_Of_Rows, Num_Of_Cols, Temp_Score;
      system("cls");
      cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";

      Load_Row_Col(RowCol); //Getting Number Of Rows And Coloumns Of Checkpoint (Temp Board)
      Num_Of_Rows = RowCol[0];
      Num_Of_Cols = RowCol[1];

      Board = Make_BoardM(Num_Of_Rows, Num_Of_Cols);
      Temp = Make_BoardM(Num_Of_Rows, Num_Of_Cols);
      Load_Temp_Board(Board, Num_Of_Rows, Num_Of_Cols); //Here We Copy Temp Board To our Board that we want to use it in our functions
      DisplayM(Board, Num_Of_Rows, Num_Of_Cols);
      Score = Load_Score();

      while (1) {

        Help_Table();
        cout << "\n\nPress a Key : ";

        Key = getch();
        system("cls");

        if (Key == 'Z' || Key == 'z') {
          Undo_FuncM(Board, Temp, Num_Of_Rows, Num_Of_Cols);
          Score = Temp_Score;
        }

        for (int i = 0; i < Num_Of_Rows; i++) {
          for (int j = 0; j < Num_Of_Cols; j++) Temp[i][j] = Board[i][j];
        }

        Temp_Score = Score;

        cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";

        if (Key == 'W' || Key == 'w') Up_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 'S' || Key == 's') Down_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 'D' || Key == 'd') Right_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 'A' || Key == 'a') Left_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 27) break;

        if (Key != 'Z' && Key != 'z' && Check_FuncM(Board, Temp, Num_Of_Rows, Num_Of_Cols)) {
          Add2o4_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        }

        if (!CheckGO_FuncM(Board, Num_Of_Rows, Num_Of_Cols)) { //GO -> Game Over
          cout << "\n\n\t\t\t.:. GAME OVER .:.\n\n\n";
          bool flag = false; //If Game Is Over , We Put The Score in "High Scores" Table

          for (int i = 0; i < 5; i++) {
            if (sc[i] == 0) {
              flag = true;
            }
          }
          if (flag == true) {
            for (int i = 0; i < 5; i++) {
              if (sc[i] == 0) {
                sc[i] = Score;
                break;
              }
            }
            Sortsc(sc);
          } else {
            if (Score > sc[4]) {
              sc[4] = Score;
            }
            Sortsc(sc);
          }
          remove("Temp Board.txt");
          fptr = fopen("Scores.txt", "w");
          fprintf(fptr, "%d\n%d\n%d\n%d\n%d", sc[0], sc[1], sc[2], sc[3], sc[4]);
          fclose(fptr);
          getch();
          break;
        }
        Temp_SaveM(Board, Num_Of_Rows, Num_Of_Cols, Score);
        DisplayM(Board, Num_Of_Rows, Num_Of_Cols);

      }
      system("cls");
      goto Startpage;

    }
    break;
  case 2:
    New_Game:
      int Second_Menu, Temp_Score;
    Score = 0;
    system("cls");
    cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n" << "<1> 4*4\n" << "<2> Manual\n" << "<3> Back\n\n";
    cout << "Please Enter A Number: ";
    cin >> Second_Menu;
    switch (Second_Menu) {
    case 1: //The User Want To Play 2048 In A 4x4 Board
      system("cls");
      cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";
      Select_Two_Blank(Board44);
      Display44(Board44);

      while (1) {

        Help_Table();
        cout << "\n\nPress a Key : ";

        Key = getch();
        system("cls");

        if (Key == 'Z' || Key == 'z') {
          Undo_Func(Board44, Temp44);
          Score = Temp_Score;
        }

        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) Temp44[i][j] = Board44[i][j];
        }

        Temp_Score = Score;

        cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";

        if (Key == 'W' || Key == 'w') Up_Func(Board44);
        if (Key == 'S' || Key == 's') Down_Func(Board44);
        if (Key == 'D' || Key == 'd') Right_Func(Board44);
        if (Key == 'A' || Key == 'a') Left_Func(Board44);
        if (Key == 27) break;

        if (Key != 'Z' && Key != 'z' && Check_Func(Board44, Temp44)) {
          Add2o4_Func(Board44);
        }

        if (!CheckGO_Func(Board44)) { //GO -> Game Over   (Here We Check That The Game is Over Or Not
          cout << Score << "\n";
          cout << sc[0] << " " << sc[1] << " " << sc[2] << " " << sc[3] << sc[4] << " \n";
          cout << "\n\n\t\t\t.:. GAME OVER .:.\n\n\n";
          bool flag = false;
          for (int i = 0; i < 5; i++) { //If Game Is Over , We Put The Score in "High Scores" Table
            if (sc[i] == 0) {
              flag = true;
              break;
            }
          }
          if (flag == true) {
            for (int i = 0; i < 5; i++) {
              if (sc[i] == 0) {
                sc[i] = Score;
                break;
              }
            }
            Sortsc(sc);
          } else {
            if (Score > sc[4]) {
              sc[4] = Score;
            }
            Sortsc(sc);
          }
          remove("Temp Board.txt");
          fptr = fopen("Scores.txt", "w"); //Here We Change The Records In Our 'High Scores' File
          fprintf(fptr, "%d\n%d\n%d\n%d\n%d", sc[0], sc[1], sc[2], sc[3], sc[4]);
          fclose(fptr);

          getch();
          break;
        }

        Temp_Save44(Board44, Score);
        Display44(Board44);

      }
      system("cls");
      goto Startpage;

      break;
    case 2: //The User Want To Play 2048 In A Board With Manual Size
      int Num_Of_Rows, Num_Of_Cols;
      Score = 0;
      system("cls");
      cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";
      cout << "Enter The Number Of Rows(Between 3-20) : ";
      cin >> Num_Of_Rows;
      while (Num_Of_Rows > 20 || Num_Of_Rows < 3) {
        cout << "\nPlease Enter A Number Between 3-20: ";
        cin >> Num_Of_Rows;
      }
      cout << "\nEnter The Number Of Columns(Between 3-20) : ";
      cin >> Num_Of_Cols;
      while (Num_Of_Cols > 20 || Num_Of_Cols < 3) {
        cout << "\nPlease Enter A Number Between 3-20: ";
        cin >> Num_Of_Cols;
      }

      cout << "\n.:.Number Of Rows: " << Num_Of_Rows << " .:.\n" << "\n.:. Number Of Columns: " << Num_Of_Cols << " .:.\n";
      cout << "\n\n\nPress Any Key To Continue";
      getch();
      system("cls");
      cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";

      Board = Make_BoardM(Num_Of_Rows, Num_Of_Cols);
      Temp = Make_BoardM(Num_Of_Rows, Num_Of_Cols);
      Select_Two_BlankM(Board, Num_Of_Rows, Num_Of_Cols);
      DisplayM(Board, Num_Of_Rows, Num_Of_Cols);

      while (1) {

        Help_Table();
        cout << "\n\nPress a Key : ";

        Key = getch();
        system("cls");

        if (Key == 'Z' || Key == 'z') {
          Undo_FuncM(Board, Temp, Num_Of_Rows, Num_Of_Cols);
          Score = Temp_Score;
        }

        for (int i = 0; i < Num_Of_Rows; i++) {
          for (int j = 0; j < Num_Of_Cols; j++) Temp[i][j] = Board[i][j];
        }

        Temp_Score = Score;

        cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";

        if (Key == 'W' || Key == 'w') Up_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 'S' || Key == 's') Down_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 'D' || Key == 'd') Right_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 'A' || Key == 'a') Left_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        if (Key == 27) break;

        if (Key != 'Z' && Key != 'z' && Check_FuncM(Board, Temp, Num_Of_Rows, Num_Of_Cols)) {
          Add2o4_FuncM(Board, Num_Of_Rows, Num_Of_Cols);
        }

        if (!CheckGO_FuncM(Board, Num_Of_Rows, Num_Of_Cols)) { //GO -> Game Over
          cout << "\n\n\t\t\t.:. GAME OVER .:.\n\n\n";
          bool flag = false; //If Game Is Over , We Put The Score in "High Scores" Table

          for (int i = 0; i < 5; i++) {
            if (sc[i] == 0) {
              flag = true;
            }
          }
          if (flag == true) {
            for (int i = 0; i < 5; i++) {
              if (sc[i] == 0) {
                sc[i] = Score;
                break;
              }
            }
            Sortsc(sc);
          } else {
            if (Score > sc[4]) {
              sc[4] = Score;
            }
            Sortsc(sc);
          }
          remove("Temp Board.txt");
          fptr = fopen("Scores.txt", "w");
          fprintf(fptr, "%d\n%d\n%d\n%d\n%d", sc[0], sc[1], sc[2], sc[3], sc[4]);
          fclose(fptr);
          getch();
          break;
        }
        Temp_SaveM(Board, Num_Of_Rows, Num_Of_Cols, Score);
        DisplayM(Board, Num_Of_Rows, Num_Of_Cols);

      }
      system("cls");
      goto Startpage;
      break;
    case 3:
      system("cls");
      goto Startpage;
      break;
    default:
      Invalid_Selection();
      goto New_Game;
      break;
    }
    break;

  case 3:
    system("cls");
    cout << "::[ 2048 ]::\t\t\t\t\t\t\t\t\t\t Developed By Mohammad Dehghani\n\n";
    Cout_Func(sc);
    cout << "\n\nPress Any Key To Go Back To Home Page...";
    getch();
    system("cls");
    goto Startpage;
    break;

  case 4:
    cout << "\n.:. Thanks For Attention .:. \n           Bye";
    return 0;
    break;

  default:
    Invalid_Selection();
    goto Startpage;
    break;

  }
  system("pause");
  return 0;
}

void Invalid_Selection() {
  cout << "\nNumber Isn't Valid.Select A Valid Number\n";
  cout << "\n\nPress Any Key to Continue...";
  getch();
  system("cls");

}

void Help_Table() {
  cout << "\n\n\n\n\t\t\t\t\t\tKey Controls :\n\t\t\t\t\t\t'W' ==> Up\n\t\t\t\t\t\t'S' ==> Down\n\t\t\t\t\t\t'D' ==> Right\n\t\t\t\t\t\t'A' ==> Left\n\t\t\t\t\t\t'Z'==> Undo\n\t\t\t\t\t\t'ESC' ==> Exit\n\n\n";
  cout << "Your Score: " << Score;
}

//------------------------------------------------------------------Functions For 4x4 Board------------------------------------------------------------------------------
void Temp_Save44(int Board44[4][4], int Score) {
  FILE * fptr;
  fptr = fopen("Temp Board.txt", "w");
  fprintf(fptr, "%d\n%d\n%d\n", 4, 4, Score);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      fprintf(fptr, "%d\n", Board44[i][j]);
    }
  }

}
void Display44(int Board[4][4]) {
  int i, j;
  for (i = 0; i < 4; i++) {
    cout << "\t\t\t\t\t\t-----------------\n\t\t\t\t\t\t";
    for (j = 0; j < 4; j++) {
      if (Board[i][j] == 0) cout << "|   ";
      else
        cout << "| " << Board[i][j] << " ";
    }
    cout << "|" << endl;
  }
  cout << "\t\t\t\t\t\t-----------------\n";
}

void Select_Two_Blank(int Board[4][4]) {
  int a1, b1, a2, b2, First_rnd[2] = {
    2,
    4
  }, i;
  srand(time(0));
  a1 = rand() % 4;
  b1 = rand() % 4;
  while (1) {
    a2 = rand() % 4;
    b2 = rand() % 4;
    if (a2 != a1 && b2 != b1) break;
  }
  i = rand() % (2);
  Board[a1][b1] = First_rnd[i];
  i = rand() % (2);
  Board[a2][b2] = First_rnd[i];

}

void Up_Func(int Board[4][4]) {
  int row, col, i;
  for (col = 0; col < 4; col++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (row = 1; row < 4; row++) {
        if (Board[row][col] != 0 && Board[row - 1][col] == 0) {
          Board[row - 1][col] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (row = 0; row < 3; row++) {
      if (Board[row][col] == Board[row + 1][col]) {
        Board[row][col] += Board[row + 1][col];
        Board[row + 1][col] = 0;
        Score += Board[row][col];

        for (i = 0; i < 100; i++) { //Gravity Code(After Combined Two Parameters Of Board)
          for (row = 1; row < 4; row++) {
            if (Board[row][col] != 0 && Board[row - 1][col] == 0) {
              Board[row - 1][col] = Board[row][col];
              Board[row][col] = 0;
            }
          }

        }

      }

    }

  }

}

void Down_Func(int Board[4][4]) {
  int row, col, i;
  for (col = 0; col < 4; col++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (row = 2; row >= 0; row--) {
        if (Board[row][col] != 0 && Board[row + 1][col] == 0) {
          Board[row + 1][col] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (row = 3; row > 0; row--) {
      if (Board[row][col] == Board[row - 1][col]) {
        Board[row][col] += Board[row - 1][col];
        Board[row - 1][col] = 0;
        Score += Board[row][col];

        for (row = 2; row >= 0; row--) { //Gravity Code(After Combined Two Parameters Of Board)
          if (Board[row][col] != 0 && Board[row + 1][col] == 0) {
            Board[row + 1][col] = Board[row][col];
            Board[row][col] = 0;
          }
        }

      }

    }

  }

}

void Left_Func(int Board[4][4]) {
  int row, col, i;
  for (row = 0; row < 4; row++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (col = 1; col < 4; col++) {
        if (Board[row][col] != 0 && Board[row][col - 1] == 0) {
          Board[row][col - 1] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (col = 0; col < 3; col++) {
      if (Board[row][col] == Board[row][col + 1]) {
        Board[row][col] += Board[row][col + 1];
        Board[row][col + 1] = 0;
        Score += Board[row][col];

        for (col = 1; col < 4; col++) { //Gravity Code(After Combined Two Parameters Of Board)
          if (Board[row][col] != 0 && Board[row][col - 1] == 0) {
            Board[row][col - 1] = Board[row][col];
            Board[row][col] = 0;
          }
        }

      }
    }

  }

}

void Right_Func(int Board[4][4]) {
  int row, col, i;
  for (row = 0; row < 4; row++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (col = 2; col >= 0; col--) {
        if (Board[row][col] != 0 && Board[row][col + 1] == 0) {
          Board[row][col + 1] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (col = 3; col > 0; col++) {
      if (Board[row][col] == Board[row][col - 1]) {
        Board[row][col] += Board[row][col - 1];
        Board[row][col - 1] = 0;
        Score += Board[row][col];

        for (i = 0; i < 100; i++) { //Gravity Code(First time)
          for (col = 2; col >= 0; col--) {
            if (Board[row][col] != 0 && Board[row][col + 1] == 0) {
              Board[row][col + 1] = Board[row][col];
              Board[row][col] = 0;
            }
          }

        }
      }

    }
  }
}

void Undo_Func(int Board[4][4], int Temp[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      Board[i][j] = Temp[i][j];
    }
  }
}

int Check_Func(int Board[4][4], int Temp[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (Board[i][j] != Temp[i][j]) return 1;
    }
  }
  return 0;
}

void Add2o4_Func(int Board[4][4]) {
  int x[2] = {
    2,
    4
  }, i, rnd_num, a1, b1;
  srand(time(0));
  i = rand() % 2;
  rnd_num = x[i];

  while (1) {
    a1 = rand() % 4;
    b1 = rand() % 4;
    if (Board[a1][b1] == 0) {
      Board[a1][b1] = rnd_num;
      break;
    }
  }
}

int CheckGO_Func(int Board[4][4]) {
  int i, j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (Board[i][j] == 0) {
        return 1;
      }

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (Board[i][j] == Board[i + 1][j] || Board[i][j] == Board[i][j + 1]) {
        return 1;
      }

    }

  }
  return 0;
}
//---------------------------------------------------------------------Manual Funcs--------sth M ==> Manual Functions--------------------------------------------------------

int ** Make_BoardM(int Num_Of_Rows, int Num_Of_Cols) {
  int ** Board = new int * [Num_Of_Rows];
  for (int i = 0; i < Num_Of_Rows; i++) {
    Board[i] = new int[Num_Of_Cols];
  }

  for (int i = 0; i < Num_Of_Rows; i++) {
    for (int j = 0; j < Num_Of_Cols; j++) {
      Board[i][j] = 0;
    }
  }

  return Board;
}

void Select_Two_BlankM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int a1, b1, a2, b2, First_rnd[2] = {
    2,
    4
  }, i;
  srand(time(0));
  a1 = rand() % Num_Of_Rows;
  b1 = rand() % Num_Of_Cols;
  while (1) {
    a2 = rand() % Num_Of_Rows;
    b2 = rand() % Num_Of_Cols;
    if (a2 != a1 && b2 != b1) break;
  }
  i = rand() % (2);
  Board[a1][b1] = First_rnd[i];
  i = rand() % (2);
  Board[a2][b2] = First_rnd[i];

}

void DisplayM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int i, j;
  for (i = 0; i < Num_Of_Rows; i++) {
    cout << "\t\t\t\t\t\t\n\t\t\t\t\t\t";
    for (j = 0; j < Num_Of_Cols; j++) {
      if (Board[i][j] == 0) cout << "|   ";
      else
        cout << "| " << Board[i][j] << " ";
    }
    cout << "|" << endl;
  }
  cout << "\t\t\t\t\t\t\n";
}

void Undo_FuncM(int ** Board, int ** Temp, int Num_Of_Rows, int Num_Of_Cols) {
  for (int i = 0; i < Num_Of_Rows; i++) {
    for (int j = 0; j < Num_Of_Cols; j++) {
      Board[i][j] = Temp[i][j];
    }
  }

}

int Check_FuncM(int ** Board, int ** Temp, int Num_Of_Rows, int Num_Of_Cols) {
  for (int i = 0; i < Num_Of_Rows; i++) {
    for (int j = 0; j < Num_Of_Cols; j++) {
      if (Board[i][j] != Temp[i][j]) return 1;
    }
  }
  return 0;
}

void Add2o4_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int x[2] = {
    2,
    4
  }, i, rnd_num, a1, b1;
  srand(time(0));
  i = rand() % 2;
  rnd_num = x[i];

  while (1) {
    a1 = rand() % Num_Of_Rows;
    b1 = rand() % Num_Of_Cols;
    if (Board[a1][b1] == 0) {
      Board[a1][b1] = rnd_num;
      break;
    }
  }
}

void Up_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int row, col, i;
  for (col = 0; col < Num_Of_Cols; col++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (row = 1; row < Num_Of_Rows; row++) {
        if (Board[row][col] != 0 && Board[row - 1][col] == 0) {
          Board[row - 1][col] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (row = 0; row < Num_Of_Rows - 1; row++) {
      if (Board[row][col] == Board[row + 1][col]) {
        Board[row][col] += Board[row + 1][col];
        Board[row + 1][col] = 0;
        Score += Board[row][col];

        for (i = 0; i < 100; i++) { //Gravity Code(After Combined Two Parameters Of Board)
          for (row = 1; row < Num_Of_Rows; row++) {
            if (Board[row][col] != 0 && Board[row - 1][col] == 0) {
              Board[row - 1][col] = Board[row][col];
              Board[row][col] = 0;
            }
          }

        }

      }

    }

  }

}

void Down_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int row, col, i;
  for (col = 0; col < Num_Of_Cols; col++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (row = Num_Of_Rows - 2; row >= 0; row--) {
        if (Board[row][col] != 0 && Board[row + 1][col] == 0) {
          Board[row + 1][col] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (row = Num_Of_Rows - 1; row > 0; row--) {
      if (Board[row][col] == Board[row - 1][col]) {
        Board[row][col] += Board[row - 1][col];
        Board[row - 1][col] = 0;
        Score += Board[row][col];

        for (row = Num_Of_Rows - 2; row >= 0; row--) { //Gravity Code(After Combined Two Parameters Of Board)
          if (Board[row][col] != 0 && Board[row + 1][col] == 0) {
            Board[row + 1][col] = Board[row][col];
            Board[row][col] = 0;
          }
        }

      }

    }

  }

}

void Left_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int row, col, i;
  for (row = 0; row < Num_Of_Rows; row++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (col = 1; col < Num_Of_Cols; col++) {
        if (Board[row][col] != 0 && Board[row][col - 1] == 0) {
          Board[row][col - 1] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (col = 0; col < Num_Of_Cols - 1; col++) {
      if (Board[row][col] == Board[row][col + 1]) {
        Board[row][col] += Board[row][col + 1];
        Board[row][col + 1] = 0;
        Score += Board[row][col];

        for (col = 1; col < Num_Of_Cols; col++) { //Gravity Code(After Combined Two Parameters Of Board)
          if (Board[row][col] != 0 && Board[row][col - 1] == 0) {
            Board[row][col - 1] = Board[row][col];
            Board[row][col] = 0;
          }
        }

      }
    }

  }

}

void Right_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int row, col, i;
  for (row = 0; row < Num_Of_Rows; row++) {
    for (i = 0; i < 100; i++) { //Gravity Code(First time)
      for (col = Num_Of_Cols - 2; col >= 0; col--) {
        if (Board[row][col] != 0 && Board[row][col + 1] == 0) {
          Board[row][col + 1] = Board[row][col];
          Board[row][col] = 0;
        }
      }

    }
    for (col = Num_Of_Cols - 1; col > 0; col++) {
      if (Board[row][col] == Board[row][col - 1]) {
        Board[row][col] += Board[row][col - 1];
        Board[row][col - 1] = 0;
        Score += Board[row][col];

        for (i = 0; i < 100; i++) { //Gravity Code(First time)
          for (col = Num_Of_Cols - 2; col >= 0; col--) {
            if (Board[row][col] != 0 && Board[row][col + 1] == 0) {
              Board[row][col + 1] = Board[row][col];
              Board[row][col] = 0;
            }
          }

        }
      }

    }
  }
}

int CheckGO_FuncM(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int i, j;
  for (i = 0; i < Num_Of_Rows; i++)
    for (j = 0; j < Num_Of_Cols; j++)
      if (Board[i][j] == 0) {
        return 1;
      }

  for (i = 0; i < Num_Of_Rows - 1; i++) {
    for (j = 0; j < Num_Of_Cols - 1; j++) {
      if (Board[i][j] == Board[i + 1][j] || Board[i][j] == Board[i][j + 1]) {
        return 1;
      }

    }

  }

  return 0;

}
void Temp_SaveM(int ** Board, int Num_Of_Rows, int Num_Of_Cols, int Score) {
  FILE * fptr;
  fptr = fopen("Temp Board.txt", "w");
  fprintf(fptr, "%d\n%d\n%d\n", Num_Of_Rows, Num_Of_Cols, Score);
  for (int i = 0; i < Num_Of_Rows; i++) {
    for (int j = 0; j < Num_Of_Cols; j++) {
      fprintf(fptr, "%d\n", Board[i][j]);
    }
  }
  fclose(fptr);
}

void Load_Row_Col(int RowCol[2]) {
  FILE * fptr;
  fptr = fopen("Temp Board.txt", "r");
  fscanf(fptr, "%d", & RowCol[0]);
  fscanf(fptr, "%d", & RowCol[1]);
  fclose(fptr);
}
void Load_Temp_Board(int ** Board, int Num_Of_Rows, int Num_Of_Cols) {
  int Row, Col, Score;
  FILE * fptr;
  fptr = fopen("Temp Board.txt", "r");
  fscanf(fptr, "%d", & Row);
  fscanf(fptr, "%d", & Col);
  fscanf(fptr, "%d", & Score);

  for (int i = 0; i < Num_Of_Rows; i++) {
    for (int j = 0; j < Num_Of_Cols; j++) {
      fscanf(fptr, "%d", & Board[i][j]);

    }
  }
  fclose(fptr);
}
int Load_Score() {
  int Row, Col, Score;
  FILE * fptr;
  fptr = fopen("Temp Board.txt", "r");
  fscanf(fptr, "%d", & Row);
  fscanf(fptr, "%d", & Col);
  fscanf(fptr, "%d", & Score);
  fclose(fptr);
  return Score;
}
void Cout_Func(int sc[5]) {
  for (int i = 1; i <= 5; i++) {
    cout << i << ": " << sc[i - 1] << "\n";
  }
}
void Sortsc(int sc[5]) {
  int temp;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {
      if (sc[j] < sc[j + 1]) {
        temp = sc[j];
        sc[j] = sc[j + 1];
        sc[j + 1] = temp;
      }
    }
  }

}
