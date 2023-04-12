#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#include <conio.h>
#include <windows.h>
using namespace std;

char Temp_U[] = "user_temp.txt";
char Users[] = "users.txt";
const int KP_8 = 56, KP_4 = 52, KP_2 = 50, KP_6 = 54, K_1=49;
const int Enter = 13, F = 102, H = 104;
const int Mine = 9;
int row[] = { -1,  0, 0, 1, 1, -1, -1,  1};
int col[] = {  0, -1, 1, 0, 1, -1,  1, -1};

struct User{
    string Name;
    string Password;
    int Score;
    int Difficulty;
    int Sizemap;
    int Sum;
};

int lines() {
     string check;
     ifstream file(Users);
     int lines_count = 0;
     if (file.peek() == EOF)
     {
         return 0;
     }
     while (getline(file, check))
     {
         lines_count++;
     }

     file.close();
     return lines_count;
 }
 
int InRange(vector<vector<int>>& field, int i, int j, int target) {
     if (target == 0) {
         return(i >= 0 && i < field.size()) && (j >= 0 && j < field[0].size() && field[i][j] != Mine);
     }
     else {
         return (i >= 0 && i < field.size()) && (j >= 0 && j < field[0].size())
             && field[i][j] == target;
     }
}

int FileOpen(int Comparison, string Name, string Password) {
    int i = 0;
    int countOfLines = lines();
    const int countOfLines_C = lines();
    int tempScore = 0, tempSizeMap = 0, tempDifficuty = 0, tempSum = 0;
    User* ptr = new User[countOfLines_C];
    bool exit = true;
    ifstream file(Users);
    string tempName, tempPassword;
    system("cls");
    if (file.peek() == EOF)
    {
        if (Comparison == 0) {
            cout<<"\n\tЗаписів нема! Ви - перший!"<<endl;
            system("pause");
        }
        return 0;
    }
    for(int j =0;j<countOfLines_C;j++){
        file >> ptr[i].Name;
        file >> ptr[i].Password;
        file >> ptr[i].Difficulty;
        file >> ptr[i].Score;
        file >> ptr[i].Sizemap;
        file >> ptr[i].Sum;
        switch (Comparison) {
            case 1: {
            if (Name == ptr[i].Name) {
                return 1;
            }
        };
            case 2: {
                if (Name == ptr[i].Name) {
                    if (Password == ptr[i].Password) {
                        return -1;
                    }
                }
            }
        }
        cout << "" << i + 1 << " Місце; - Нік: " << (ptr + i)->Name << " Мін залишилось: " << (ptr + i)->Score << " Відсоток заповненості поля: " << (ptr + i)->Difficulty << "%%; Розмір поля: " << (ptr + i)->Sizemap << endl;
        i++;
    }
    file.close();

    if (Comparison >= 1) {
        return 0;
    }

    for (i = 0; i < countOfLines_C; i++) {

        do {

            exit = false;
            for (i = 0; i < countOfLines_C; i++) {

                if ((ptr + 1 + i)->Sizemap > 0) {

                    if ((ptr + i)->Sum < (ptr + 1 + i)->Sum) {
                        tempSum = (ptr + i)->Sum;
                        tempScore = (ptr + i)->Score;
                        tempSizeMap = (ptr + i)->Sizemap;
                        tempDifficuty = (ptr + i)->Difficulty;
                        tempName = (ptr + i)->Name;
                        tempPassword = (ptr + i)->Password;

                        (ptr + i)->Sum = (ptr + 1 + i)->Sum;
                        (ptr + i)->Score = (ptr + 1 + i)->Score;
                        (ptr + i)->Sizemap = (ptr + 1 + i)->Sizemap;
                        (ptr + i)->Difficulty = (ptr + 1 + i)->Difficulty;
                        (ptr + i)->Name = (ptr + 1 + i)->Name;
                        (ptr + i)->Password = (ptr + 1 + i)->Password;

                        (ptr + 1 + i)->Sum = tempSum;
                        (ptr + 1 + i)->Score = tempScore;
                        (ptr + 1 + i)->Sizemap = tempSizeMap;
                        (ptr + 1 + i)->Difficulty = tempDifficuty;
                        (ptr + 1 + i)->Name = tempName;
                        (ptr + 1 + i)->Password = tempPassword;
                        exit = true;
                    }
                }
            }
        } while (exit);

    }
    for (i = 0; i < countOfLines_C; i++) {
        cout <<""<< i+1 <<" Місце; - Нік: "<< (ptr + i)->Name <<" Мін залишилось: "<< (ptr + i)->Score <<" Відсоток заповненості поля: "<< (ptr + i)->Difficulty <<"%%; Розмір поля: "<< (ptr + i)->Sizemap << endl;
    }
    system("pause");
    delete[]ptr;

    return 0;

}

void HelpMenu() {
    system("cls");
    cout << "\t\tEnter - Взаємодія з полем\n\t\tF - Поставити флаг\n\t\tУПРАВЛІННЯ:\n\t\t 8  \n\t\t4 6 \t \n\t\t 2" << endl;
    system("pause");
}

void FloodFill(vector<vector<int>>& f_Main, int x, int y, int replacement)
{
    // базовый вариант
    if (f_Main.size() == 0) {
        return;
    }
    // создаем queue и ставим в queue начальный пиксель
    queue<pair<int, int>> q;
    q.push({ x, y });
    // получаем целевой цвет
    int target_Main = f_Main[x][y];

    // целевой цвет такой же, как и замена
    if (target_Main != -2) {
        return;
    }
    // прерываем, когда queue становится пустой
    while (!q.empty())
    {
        // удалить передний узел из очереди и обработать его
        pair<int, int> node = q.front();
        q.pop();

        // (x, y) представляет текущий пиксель
        int x = node.first, y = node.second;

        // заменить текущий цвет пикселя цветом замены
        f_Main[x][y] = replacement;

        // обрабатываем все восемь соседних пикселей текущего пикселя и
        // поставить в queue каждый допустимый пиксель
        for (int k = 0; k < 4; k++)
        {
            // если соседний пиксель в позиции (x + row[k], y + col[k])
            // действителен и имеет тот же цвет, что и текущий пиксель
            if (InRange(f_Main, x + row[k], y + col[k], target_Main))
            {
                // поставить в queue соседний пиксель
                q.push({ x + row[k], y + col[k] });
            }
        }
    }
}

void GameStart(int minesCount, vector<vector<int>> fieldMines, vector<vector<int>> fieldView, int height, int width,int difficulty) {
    const int fieldFlag = 11, fieldOpen = 0, fieldCursor = -1, fieldClosed = -2;
    int end = 1, i = 0, j = 0, iO = 0, jO = 0;

    string name;
    string passWord;
    ifstream fileOut(Temp_U);
    ofstream fileIn(Users,ios::app);
    fieldView[0][0] = fieldCursor;

    int MinesStat = minesCount;
    int Flags = minesCount;

    system("cls");

    do {

        system("cls");
        cout << "\tКількість флажків: " << Flags << "\t Кількість мін: " << MinesStat << "; H - Допомогти\n" << endl;

        for (i = 0; i < height; i++) {

            cout << "\t\t\t";
            for (j = 0; j < width; j++) {
                switch (fieldView[i][j]) {
                    case fieldCursor:   cout << " "; break;
                    case fieldOpen:     cout << "/"; break;
                    case fieldFlag:     cout << "P"; break;
                    case fieldClosed:   cout << "0"; break;
                    default:            cout << fieldView[i][j]; break;
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
                    if (fieldMines[iO][jO] == fieldClosed) {
                        FloodFill(fieldMines, iO, jO, fieldOpen);
                        system("cls");
                        for (i = 0; i < height; i++) {
                            for (j = 0; j < width; j++) {
                                if (fieldMines[i][j] == 0) {
                                    fieldView[i][j] = 0;
                                    for (int k = 0; k < 4; k++) {
                                        if (InRange(fieldView, i + row[k], j + col[k], 0)) {
                                            fieldView[i + row[k]][j + col[k]] = fieldMines[i + row[k]][j + col[k]];
                                        }
                                    }
                                }
                            }
                        }
                    }else {
                        fieldView[iO][jO] = fieldMines[iO][jO];
                    }
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
                cout << "\t\tКАБУМ!!!!!!\n\t\tВаш рекорд: " << minesCount << endl;
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
    

    if (fileOut.is_open()) {
        fileOut >> name;
        fileOut >> passWord;
    }
    fileOut.close();

    if (fileIn.is_open()) {
        fileIn << name;
        fileIn << " ";
        fileIn << passWord;
        fileIn << " ";
        fileIn << minesCount;
        fileIn << " ";
        fileIn << difficulty;
        fileIn << " ";
        fileIn << height * width;
        fileIn << " ";
    }
    fileIn.close();
}

void FieldFilling(int difficulty, int height, int width) {
    int i = 0, j = 0;
    int minesLeft = 0, flags = 0;
    flags = minesLeft = height * width * (difficulty / 100.0);
    vector <vector <int>> playGround(height);
    vector <vector <int>> playGroundOn(height);
    system("cls");

    for (i = 0; i < height; i++)
    {
        playGround[i].resize(width);
        playGroundOn[i].resize(width,-2);
    }

    do {
        i = rand() % height;
        j = rand() % width;

        if ((playGround[i][j] >= 0  && playGround[i][j] <= Mine - 1) && playGround[i][j] != Mine) {
            playGround[i][j] = Mine;

            for (int k = 0; k < 8; k++) {
                if (InRange(playGround, i + row[k], j + col[k],0)) {
                    playGround[i + row[k]][j + col[k]] += 1;
                }
            }
            minesLeft--;
        }
    } while (minesLeft != 0);
    for (int i = 0; i < height;i++) {
        for (int j = 0; j < width; j++) {
            if (playGround[i][j] == 0) {
                playGround[i][j] = -2;
            }
        }
    }
    GameStart(flags, playGround, playGroundOn, height, width, difficulty);
}

void FieldSize(int difficulty) {
    int height = 0, width = 0;

    do {
        system("cls");
        cout << "\t\tРозмірність поля:\n" << endl;

        cout << "\tВведіть висоту поля: "; 
        cin >> height;

        cout << "\tВведіть ширину поля: "; 
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
    ofstream fileIn(Temp_U);
    do {

        do {
            nicknameenter:
            system("cls");
            cout<<"\n\t\tвведіть нік(15 символів): ";
            cin >> userName;

        }while (userName.size() > 15);
        comparison = FileOpen(1, userName,"");

        if (comparison == 1) {
            system("cls");
            cout << "нік зайнято! введіть:\n1 - новий нік\n2- пароль"<<endl;
            switch (_getch()) {
            case K_1: goto nicknameenter;
            case KP_2: {
                passWord = InputPassword();
                comparison = FileOpen(2, userName, passWord);
                break;
              }
            }
        }

    } while (comparison == 1);

    if (comparison != -1) {
        passWord = InputPassword();
    }
    if (fileIn.is_open()) {
        fileIn << userName;
        fileIn << " ";
        fileIn << passWord;
    }
    fileIn.close();
}

void MenuHello() {
    int menuOption = 0;
    int exit = 1;

    do {
        cout << "\t\tСАПЕР V 2.2.9. BETA \n\n" << endl;
        switch (1) {
            case 1:  menuOption == 0 ? cout <<"\t> Нова гра" << endl :        cout <<"\tНова гра" << endl;
            case 2:  menuOption == 1 ? cout <<"\t> Допомога" << endl :        cout <<"\tДопомога" << endl;
            case 3:  menuOption == 2 ? cout <<"\t> Таблиця лідерів" << endl : cout <<"\tТаблиця лідерів" << endl;
            case 4:  menuOption == 3 ? cout <<"\t> Вихід" << endl :           cout <<"\tВихід" << endl;
        }

        //cout << _getch();
        /*becouse of bug*/

        switch (_getch()) {
            case KP_8: menuOption > 0 ? menuOption-- : menuOption = 3; break;
            case KP_2: menuOption < 3 ? menuOption++ : menuOption = 0; break;
            case Enter: {
                switch (menuOption) {
                    case 0: InputUsername(); break;
                    case 1: HelpMenu(); break;
                    //case 2: FileOpen(0, "", ""); break;
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
    FileOpen(0, "", "");
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
  - Добавить АККАУНТЫ для игроков +
        - пароль +
  
  - Алгоритм открытия
  - Немного интерактива
  - Пасхалки
  */