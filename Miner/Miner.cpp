#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;

char Temp_U[] = "user_temp.txt";
char Users[] = "users.txt";
const int KP_8 = 56, KP_4 = 52, KP_2 = 50, KP_6 = 54, K_ONE=49;
const int Enter = 13, F = 102, H = 104;
const int Mine = 9;

 struct User{
    string Name;
    string Password;
    int Score;
    int Difficulty;
    int Sizemap;
    int Sum;
};

 int lines() {
     FILE* fp;
     size_t lines_count = 0;

     if ((fp = fopen(Users, "r+")) == NULL)
     {
         return 0;
     }

     while (!feof(fp))
     {
         if (fgetc(fp) == '\n')
             lines_count++;
     }

     fclose(fp);
     return lines_count;
 }

 int FileOpen(int Comparison, string Name, string Password) {
    int i = 0;
    int countOfLines = lines(), countOfLines_S = lines();
    int TempScore = 0, TempSizeMap = 0, TempDifficuty = 0, TempSum = 0;

    bool exit = true;
    FILE* fp;
    string TempName, TempPassword;
    struct User* ptr;
    system("cls");

    if ((fp = fopen(Users, "r+")) == NULL)
    {
        if (Comparison == 0) {
            cout<<"\n\tЗаписів нема! Ви - перший!"<<endl;
            system("pause");
        }
        return 0;
    }

    ptr = (struct User*)malloc(countOfLines * sizeof(struct User));

    while (countOfLines !=0) {

        fscanf(fp, "%s%s%d%d%d", (ptr + i)->Name, (ptr + i)->Password, &((ptr + i)->Score), &((ptr + i)->Difficulty), &((ptr + i)->Sizemap));

        switch (Comparison) {

            case 1: {
            if (Name == (ptr + i)->Name) {
                return 1;
            }
        };
            case 2: {
                if (Name == (ptr + i)->Name) {
                    if (Password == (ptr + i)->Password) {
                        return -1;
                    }
                }
            }
        }

        (ptr + i)->Sum = (ptr + i)->Difficulty + (ptr + i)->Sizemap - (ptr + i)->Score;

        i++;
        countOfLines--;
    }
    fclose(fp);

    if (Comparison >= 1) return 0;

    for (i = 0; i < countOfLines_S; i++) {

        do {

            exit = false;
            for (i = 0; i < countOfLines_S; i++) {

                if ((ptr + 1 + i)->Sizemap > 0) {

                    if ((ptr + i)->Sum < (ptr + 1 + i)->Sum) {
                        TempSum = (ptr + i)->Sum;
                        TempScore = (ptr + i)->Score;
                        TempSizeMap = (ptr + i)->Sizemap;
                        TempDifficuty = (ptr + i)->Difficulty;
                        TempName = (ptr + i)->Name;
                        TempPassword = (ptr + i)->Password;

                        (ptr + i)->Sum = (ptr + 1 + i)->Sum;
                        (ptr + i)->Score = (ptr + 1 + i)->Score;
                        (ptr + i)->Sizemap = (ptr + 1 + i)->Sizemap;
                        (ptr + i)->Difficulty = (ptr + 1 + i)->Difficulty;
                        (ptr + i)->Name = (ptr + 1 + i)->Name;
                        (ptr + i)->Password = (ptr + 1 + i)->Password;

                        (ptr + 1 + i)->Sum = TempSum;
                        (ptr + 1 + i)->Score=TempScore;
                        (ptr + 1 + i)->Sizemap=TempSizeMap;
                        (ptr + 1 + i)->Difficulty= TempDifficuty;
                        (ptr + 1 + i)->Name = TempName;
                        (ptr + 1 + i)->Password = TempPassword;
                        exit = true;
                    }
                }
            }
        } while (exit);

    }
    for (i = 0; i < countOfLines_S; i++) {
        cout <<""<< i+1 <<" Місце; - Нік: "<< (ptr + i)->Name <<" Мін залишилось: "<< (ptr + i)->Score <<" Відсоток заповненості поля: "<< (ptr + i)->Difficulty <<"%%; Розмір поля: "<< (ptr + i)->Sizemap << endl;
    }
    system("pause");
    free(ptr);

    return 0;

}

void HelpMenu() {
    system("cls");
    cout << "\t\tEnter - Взаємодія з полем\n\t\tF - Поставити флаг\n\t\tУПРАВЛІННЯ:\n\t\t 8  \n\t\t4 6 \t \n\t\t 2" << endl;
    system("pause");
}

void GameStart(int minesCount, int** fieldMines, int** fieldView, int height, int width,int difficulty) {
    const int fieldFlag = 11, fieldOpen = 10, fieldCursor = -1, fieldClosed = 0;
    int end = 1, i = 0, j = 0, iO = 0, jO = 0;

    FILE* fp_temp;
    FILE* fp;

    string name;
    string passWord;

    fieldView[0][0] = fieldCursor;

    int MinesStat = minesCount;
    int Flags = minesCount;

    system("cls");

    do {

        system("cls");
        cout << "\tКількість флажків: %d" << Flags << "\t Кількість мін: %d" << MinesStat << "; H - Допомогти\n" << endl;

        for (i = 0; i < height; i++) {

            cout << "\t\t\t";
            for (j = 0; j < width; j++) {
                switch (fieldView[i][j]) {
                    case fieldCursor:   cout << " "; break;
                    case fieldOpen:     cout << "/"; break;
                    case fieldFlag:     cout << "P"; break;
                    case fieldClosed:   cout << "0"; break;
                    default:            cout << "%d", fieldView[i][j]; break;
                }
            }

            printf("\n");
        }

        switch (_getch()) {

        case KP_8:{
            if (iO > 0) {
                iO--;
                if (fieldView[iO + 1][jO] == fieldCursor) {
                    fieldView[iO + 1][jO] = fieldClosed;
                }
            }
            else {
                iO = fieldClosed;
            }

            if (fieldView[iO][jO] == fieldClosed) {
                fieldView[iO][jO] = fieldCursor;
            }
        break;
        };

        case KP_2: {
            if (iO < height - 1) {
                iO++;
                if (fieldView[iO - 1][jO] == fieldCursor) {
                    fieldView[iO - 1][jO] = fieldClosed;
                }
            }
            else {
                iO = height - 1;
            }

            if (fieldView[iO][jO] == fieldClosed) {
                fieldView[iO][jO] = fieldCursor;
            }
        break;
        };

        case KP_4: {
            if (jO > 0) {
                jO--;
                if (fieldView[iO][jO + 1] == fieldCursor) {
                    fieldView[iO][jO + 1] = fieldClosed;
                }
            }
            else {
                jO = fieldClosed;
            }

            if (fieldView[iO][jO] == fieldClosed) {
                fieldView[iO][jO] = fieldCursor;
            }
        break;
        };

        case KP_6: {
            if (jO < width - 1) {
                jO++;
                if (fieldView[iO][jO - 1] == fieldCursor) {
                    fieldView[iO][jO - 1] = fieldClosed;
                }
            }
            else {
                jO = width - 1;
            }

            if (fieldView[iO][jO] == fieldClosed) {
                fieldView[iO][jO] = fieldCursor;
            }
        break;
        };

        case Enter: {
            if (fieldMines[iO][jO] != Mine) {
                if (fieldView[iO][jO] != fieldFlag) {
                    fieldMines[iO][jO] == fieldClosed ? fieldView[iO][jO] = fieldOpen : fieldView[iO][jO] = fieldMines[iO][jO];
                }
            }
            else {
                system("cls");
                for (i = 0; i < height; i++) {

                    cout << "\t\t\t";

                    for (j = 0; j < width; j++) {

                        if (fieldMines[i][j] == Mine) {
                            cout << "*";
                        }
                        else {
                            cout << "0";
                        }
                    }

                    cout << "\n";

                }
                cout << "\t\tКАБУМ!!!!!!\n\t\tВаш рекорд: %d" << minesCount << endl;
                end = 0;
                system("pause");

            }
        break;
        };

        case F: {
            if (fieldView[iO][jO] == fieldCursor) {
                if (fieldMines[iO][jO] == Mine) {
                    minesCount--; Flags--; fieldView[iO][jO] = fieldFlag;
                }
                else {
                    Flags--;
                    fieldView[iO][jO] = fieldFlag;
                }
            }
            else if (fieldView[iO][jO] == fieldFlag) {
                fieldView[iO][jO] = fieldCursor;
                Flags++;
                if (fieldMines[iO][jO] == Mine) {
                    minesCount++;
                }
            }
         break;
        };

        case H: {HelpMenu(); break; };

        }
        if (minesCount == 0) {
            end = 0;
            system("cls");
            printf("\t\tПЕРЕМОГА!!! ВИ ЗМОГЛИ!!!\n");
            system("pause");
        }

    } while (end);

    fp_temp = fopen(Temp_U, "r");
    fscanf(fp_temp, "%s%s", name, passWord);
    fclose(fp_temp);

    fp = fopen(Users, "a");
    fprintf(fp,"%s %s %d %d %d \n",name, passWord, minesCount, difficulty, height*width);
    fclose(fp);
}

void FieldFilling(int difficulty, int height, int width) {
    int i = 0, j = 0;
    int minesLeft = 0, flags = 0;

    flags = minesLeft = height * width * (difficulty / 100.0);
    int** playGround = (int**)malloc(height * sizeof(int*));
    int** playGroundOn = (int**)malloc(height * sizeof(int*));

    system("cls");

    for (i = 0; i < height; i++)
    {
        playGround[i] = (int*)malloc(width * sizeof(int));
        playGroundOn[i] = (int*)malloc(width * sizeof(int));

        for (j = 0; j < width; j++)
        {
            playGround[i][j] = 0;
            playGroundOn[i][j] = 0;
        }
    }

    do {

        i = rand() % height;
        j = rand() % width;

        if ((playGround[i][j] >= 0  && playGround[i][j] <= Mine - 1) && playGround[i][j] != Mine) {

            playGround[i][j] = Mine;

                if (((i + 1) < height)  && playGround[i + 1][j] != Mine) { playGround[i + 1][j] += 1; }
                if (((j + 1) < width)   && playGround[i][j + 1] != Mine) { playGround[i][j + 1] += 1; }
                if (((i - 1) >= 0)      && playGround[i - 1][j] != Mine) { playGround[i - 1][j] += 1; }
                if (((j - 1) >= 0)      && playGround[i][j - 1] != Mine) { playGround[i][j - 1] += 1; }
                if (((i - 1) >= 0)      && ((j - 1) >= 0)       && playGround[i - 1][j - 1] != Mine) { playGround[i - 1][j - 1] += 1; }
                if (((i + 1) < height)  && ((j - 1) >= 0)       && playGround[i + 1][j - 1] != Mine) { playGround[i + 1][j - 1] += 1; }
                if (((i + 1) < height)  && ((j + 1) < width)    && playGround[i + 1][j + 1] != Mine) { playGround[i + 1][j + 1] += 1; }
                if (((i - 1) >= 0)      && ((j + 1) < width)    && playGround[i - 1][j + 1] != Mine) { playGround[i - 1][j + 1] += 1; }
            
            minesLeft--;

        }

    } while (minesLeft != 0);

    GameStart(flags, playGround, playGroundOn, height, width, difficulty);

    for (i = 0; i < height; i++) {

        free(playGroundOn[i]);
        free(playGround[i]);

    }

    free(playGroundOn);
    free(playGround);
}

void FieldSize(int difficulty) {
    int height = 0, width = 0;

    do {
        system("cls");
        cout << "\t\tРозмірність поля:\n" << endl;

        cout << "\tВведіть висоту поля: " << endl; 
        cin >> height;
        cout << "\tВведіть ширину поля: " << endl; 
        cin >> width;

    } while (height < 2 || width < 2);

    FieldFilling(difficulty, height, width);
}

int DifficultyMenu() {
    int diffuculty = 0;
    int menuOption = 0;
    int exit = 1;

    system("cls");
    do {

        cout << "\t\tВиберіть рівень складності:\n" << endl;
        switch (1) {
            case 1:menuOption == 0 ? cout << "\t> Легко" << endl :       cout << "\tЛегко" << endl;
            case 2:menuOption == 1 ? cout << "\t> Середнє" << endl :     cout << "\tСереднє" << endl;
            case 3:menuOption == 2 ? cout << "\t> Важко" << endl :       cout << "\tВажко" << endl;
            case 4:menuOption == 3 ? cout << "\t> Хардкор" << endl :     cout << "\tХардкор" << endl;
            case 5:menuOption == 4 ? cout << "\t> Налаштувати" << endl : cout << "\tНалаштувати" << endl;
            case 6:menuOption == 5 ? cout << "\t> Назад" << endl :       cout << "\tНазад" << endl;
        }

        switch (_getch()) {
            case KP_8: menuOption > 0 ? menuOption-- : menuOption = 5; break;
            case KP_2: menuOption < 5 ? menuOption++ : menuOption = 0; break;
            case Enter: {
                switch (menuOption) {
                    case 0: diffuculty = 15; break;
                    case 1: diffuculty = 25; break;
                    case 2: diffuculty = 50; break;
                    case 3: diffuculty = 75; break;
                    case 4: {
                        do {
                            system("cls");
                            cout << "\t\tВведіть відсоток заповненості поля мінами: ";
                            cin >> diffuculty;
                        } while (diffuculty > 99 || diffuculty <= 0);
                        break;
                    };
                    case 5: return 0;
                };
            exit = 0;
            break;
            };
        };

    system("cls");

    } while (exit);

    FieldSize(diffuculty);
}

string InputPassword() {
    string passWord;
    do {
        system("cls");
        cout << "Введіть пароль(до 30 символів)!: ";
        cin >> passWord;

    } while (passWord.size() > 30);

    return passWord;
}

void InputUsername() {
    system("cls");
    int comparison=0;
    string passWord;
    string userName;
    FILE* fp;
    do {

        do {
            NicknameEnter:
            system("cls");
            cout<<"\n\t\tВведіть нік(15 символів): ";
            cin >> userName;

        }while (userName.size() >15);

        comparison = FileOpen(1, userName,0);

        if (comparison == 1) {
            system("cls");
            cout << "Нік зайнято! Введіть:\n1 - новий нік\n2- пароль"<<endl;
            switch (_getch()) {
            case K_ONE: goto NicknameEnter;
            case KP_2: {
                passWord = InputPassword();
                comparison = FileOpen(2, userName, passWord);
                break;
              }
            }
        }

    } while (comparison == 1);

    if (comparison != -1) {
        passWord, InputPassword();
    }

    fp = fopen(Temp_U, "w");
    fprintf(fp, "%s %s\n", userName, passWord);
    fclose(fp);
    DifficultyMenu();
}

void MenuHello() {
    int menuOption = 0;
    int exit = 1;

    do {
        cout << "\t\tСАПЕР V 2.2.8. BETA \n\n" << endl;
        switch (1) {
            case 1:  menuOption == 0 ? cout <<"\t> Нова гра" << endl :        cout <<"\tНова гра" << endl;
            case 2:  menuOption == 1 ? cout <<"\t> Допомога" << endl :        cout <<"\tДопомога" << endl;
            case 3:  menuOption == 2 ? cout <<"\t> Таблиця лідерів" << endl : cout <<"\tТаблиця лідерів" << endl;
            case 4:  menuOption == 3 ? cout <<"\t> Вихід" << endl :           cout <<"\tВихід" << endl;
        }

        cout << _getch();
        /*becouse of bug*/

        switch (_getch()) {
            case KP_8: menuOption > 0 ? menuOption-- : menuOption = 3; break;
            case KP_2: menuOption < 3 ? menuOption++ : menuOption = 0; break;
            case Enter: {
                switch (menuOption) {
                    case 0: InputUsername(); break;
                    case 1: HelpMenu(); break;
                    case 2: FileOpen(0, 0, 0); break;
                    case 3: exit = 0; break;
                }
            }break;
        }

        system("cls");

    } while (exit);

    cout <<"\tДо зустрічі!" << endl;
}

int main() {
    SetConsoleOutputCP(1251);
    MenuHello();
}
/*алгоритм открытия ячеек

  файл +

  вин апи
- Меню по центру
- Цветной текст

  Осталось доработать:
  -Изменить вывод текста побуквенно
  - Добавить профиль игрока +
        - Ввод ника +
        - Проверка файла +
  - Добавить таблицу рекордов +
        - распознование +
  - Добавить АККАУНТЫ для игроков
        - пароль
  
  - Алгоритм открытия
  - Немного интерактива
  - Пасхалки
  */