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
const int fieldFlag = 11, fieldOpen = 0, fieldCursor = -1, fieldClosed = -2;
int row[] = { -1,  0, 0, 1, 1, -1, -1,  1};
int col[] = {  0, -1, 1, 0, 1, -1,  1, -1};

struct user{
    string userName;
    string passWord;
    int score;
    int difficulty;
    int size;
    int sum;
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
 
int inRange(vector<vector<int>>& field, int i, int j, int target) {
     if (target == 0) {
         return(i >= 0 && i < field.size()) && (j >= 0 && j < field[0].size() && field[i][j] != Mine);
     }
     else {
         return (i >= 0 && i < field.size()) && (j >= 0 && j < field[0].size())
             && field[i][j] == target;
     }
}

int fileOpen(int Comparison, string Name, string Password) {
    int i = 0;
    int countOfLines = lines();
    const int countOfLines_C = lines();
    int tempScore = 0, tempSizeMap = 0, tempDifficuty = 0, tempSum = 0;
    user* ptr = new user[countOfLines_C];
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
    for(int i =0;i<countOfLines_C;i++){
        file >> ptr[i].userName;
        file >> ptr[i].passWord;
        file >> ptr[i].score;
        file >> ptr[i].difficulty;
        file >> ptr[i].size;
        ptr[i].sum = ptr[i].difficulty + ptr[i].size - ptr[i].score;
        switch (Comparison) {
            case 1: {
            if (Name == ptr[i].userName) {
                return 1;
            }
        };
            case 2: {
                if (Name == ptr[i].userName) {
                    if (Password == ptr[i].passWord) {
                        return -1;
                    }
                }
            }
        }
    }
    file.close();

    if (Comparison == 1) {
        return 0;
    }
    else if (Comparison == 2) {
        return 1;
    }

    for (i = 0; i < countOfLines_C; i++) {

        do {

            exit = false;
            for (i = 0; i < countOfLines_C; i++) {

                    if (ptr[i + 1].sum > 0 && ptr[i + 1].sum > ptr[i].sum) {
                        tempSum = ptr[i].sum;
                        tempScore = ptr[i].score;
                        tempSizeMap = ptr[i].size;
                        tempDifficuty = ptr[i].difficulty;
                        tempName = ptr[i].userName;
                        tempPassword = ptr[i].passWord;

                        ptr[i].sum = ptr[i + 1].sum;
                        ptr[i].score = ptr[i + 1].score;
                        ptr[i].size = ptr[i + 1].size;
                        ptr[i].difficulty = ptr[i + 1].difficulty;
                        ptr[i].userName = ptr[i + 1].userName;
                        ptr[i].passWord = ptr[i + 1].passWord;

                        ptr[i + 1].sum = tempSum;
                        ptr[i + 1].score = tempScore;
                        ptr[i + 1].size = tempSizeMap;
                        ptr[i + 1].difficulty = tempDifficuty;
                        ptr[i + 1].userName = tempName;
                        ptr[i + 1].passWord = tempPassword;
                        exit = true;
                    }
            }
        } while (exit);
    }
    for (i = 0; i < countOfLines_C; i++) {
        cout << "" << i + 1 << " Місце; - Нік: " << ptr[i].userName << " Мін залишилось: " << ptr[i].score << " Відсоток заповненості поля: " << ptr[i].difficulty << "%; Розмір поля: " << ptr[i].size << endl;
    }
    system("pause");
    delete[]ptr;

    return 0;

}
/*decompose FileOpen*/

void helpMenu() {
    system("cls");
    cout << "\t\tEnter - Взаємодія з полем\n\t\tF - Поставити флаг\n\t\tУПРАВЛІННЯ:\n\t\t 8  \n\t\t4 6 \t \n\t\t 2" << endl;
    system("pause");
}

void floodFill(vector<vector<int>>& fieldMine, int x, int y, int replacement)
{
    queue<pair<int, int>> q;
    q.push({ x, y });

    int target_Main = fieldMine[x][y];

    if (target_Main != -2) {
        return;
    }

    while (!q.empty())
    {
        pair<int, int> node = q.front();
        q.pop();

        int x = node.first, y = node.second;

        fieldMine[x][y] = replacement;

        for (int k = 0; k < 4; k++)
        {
            if (inRange(fieldMine, x + row[k], y + col[k], target_Main))
            {
                q.push({ x + row[k], y + col[k] });
            }
        }
    }
}

void commonInput(bool rewrite, string name, string passWord, int minesCount, int difficulty, int size) {
    ofstream fileIn;
    if (rewrite) {
        fileIn.open(Users);
    }
    else {
        fileIn.open(Users, ios::app);
    }

    if (fileIn.is_open()) {
        fileIn << name;
        fileIn << " ";
        fileIn << passWord;
        fileIn << " ";
        fileIn << minesCount;
        fileIn << " ";
        fileIn << difficulty;
        fileIn << " ";
        fileIn << size;
        fileIn << "\n";
    }
    fileIn.close();
}

int structCheck(string name, string password, int score, int difficulty, int sizemap) {
    int countOfLines_C = lines();
    int tempSum, tempScore, tempSizeMap, tempDifficulty;

    string tempName, tempPassword;
    ifstream file(Users);
    ofstream fileRewrite;
    user* ptr = new user[countOfLines_C];

    for (int i = 0; i < countOfLines_C; i++) {
        file >> ptr[i].userName;
        file >> ptr[i].passWord;
        file >> ptr[i].score;
        file >> ptr[i].difficulty;
        file >> ptr[i].size;
    }
    file.close();
    cout << endl;
    for (int i = 0; i < countOfLines_C; i++) {
        if (name == ptr[i].userName) {
            if (countOfLines_C == 1) {
                fileRewrite.open(Users);
                fileRewrite.close();
                return 0;
            }
            if (ptr[i + 1].userName.size() <= 30) {
                tempScore = ptr[i].score;
                tempSizeMap = ptr[i].size;
                tempDifficulty = ptr[i].difficulty;
                tempName = ptr[i].userName;
                tempPassword = ptr[i].passWord;

                ptr[i].score = ptr[i + 1].score;
                ptr[i].size = ptr[i + 1].size;
                ptr[i].difficulty = ptr[i + 1].difficulty;
                ptr[i].userName = ptr[i + 1].userName;
                ptr[i].passWord = ptr[i + 1].passWord;

                ptr[i + 1].score = tempScore;
                ptr[i + 1].size = tempSizeMap;
                ptr[i + 1].difficulty = tempDifficulty;
                ptr[i + 1].userName = tempName;
                ptr[i + 1].passWord = tempPassword;
            }
        }
    }
    fileRewrite.open(Users);
    for (int i = 0; i < countOfLines_C - 1; i++) {
        if (fileRewrite.is_open()) {
            commonInput(true, ptr[i].userName, ptr[i].passWord, ptr[i].score, ptr[i].difficulty, ptr[i].size);
        }
        
    }
    fileRewrite.close();
    return 0;
}

void gameFileTemptToMain(string name, string passWord, int minesCount, int difficulty,int size) {
    ifstream fileOut(Temp_U);

    if (fileOut.is_open()) {
        fileOut >> name;
        fileOut >> passWord;
    }
    fileOut.close();

    structCheck(name, passWord, minesCount, difficulty, size);

    commonInput(false, name, passWord, minesCount, difficulty, size);
}

void gameFieldOutputView(vector<vector<int>> fieldView,int height, int width, int flags, int minesStat) {
    system("cls");
    cout << "\tКількість флажків: " << flags << "\t Кількість мін: " << minesStat << "; H - Допомогти\n" << endl;
    for (int i = 0; i < height; i++) {

        cout << "\t\t\t";
        for (int j = 0; j < width; j++) {
            switch (fieldView[i][j]) {
                case fieldCursor: {
                    cout << " ";
                    break;
                }
                case fieldOpen: {
                    cout << "/";
                    break;
                }
                case fieldFlag: {
                    cout << "P";
                    break;
                }
                case fieldClosed: {
                    cout << "0";
                    break;
                }
                default: {
                    cout << fieldView[i][j];
                    break;
                }
            }
        }
        cout << endl;
    }
}

void gameFieldOutputEnd(vector<vector<int>> fieldMines, int height, int width, int flags, int minesStat,int minesCount,int& end) {
    for (int i = 0; i < height; i++) {
        cout << "\t\t\t";
        for (int j = 0; j < width; j++) {

            if (fieldMines[i][j] == Mine) {
                cout << "*";
            }
            else {
                cout << "0";
            }
        }
        cout << endl;
    }
    cout << "\t\tКАБУМ!!!!!!\n\t\tВаш рекорд: " << minesCount << endl;
    end = 0;
    system("pause");
}

void gameEnterFilling(vector<vector<int>> fieldMines, vector<vector<int>>& fieldView, int i, int j) {
    for (int k = 0; k < 4; k++) {
        if (inRange(fieldView, i + row[k], j + col[k], 0)) {
            fieldView[i + row[k]][j + col[k]] = fieldMines[i + row[k]][j + col[k]];
        }
    }
}

void gameEnterCheck(vector<vector<int>> fieldMines, vector<vector<int>>& fieldView, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (fieldMines[i][j] == 0) {
                fieldView[i][j] = 0;
                gameEnterFilling(fieldMines,fieldView,i,j);
            }
        }
    }
}

void gameMain(int minesCount, vector<vector<int>> fieldMines, vector<vector<int>> fieldView, int height, int width,int difficulty) {
    int end = 1, iO = 0, jO = 0;

    string name;
    string passWord;
    fieldView[0][0] = fieldCursor;

    int minesStat = minesCount;
    int flags = minesCount;

    do {

        gameFieldOutputView(fieldView, height, width, flags, minesStat);
       
        switch (_getch()) {

            case KP_8:{
                if (iO > 0) {
                    iO--;
                    if (fieldView[iO + 1][jO] == fieldCursor) {
                        fieldView[iO + 1][jO] = fieldClosed;
                    }
                }
                else {
                    iO = 0;
                }
                if (fieldView[iO][jO] == fieldClosed) {
                    fieldView[iO][jO] = fieldCursor;
                }
            break;
            }

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
            }

            case KP_4: {
                if (jO > 0) {
                    jO--;
                    if (fieldView[iO][jO + 1] == fieldCursor) {
                        fieldView[iO][jO + 1] = fieldClosed;
                    }
                }
                else {
                    jO = 0;
                }

                if (fieldView[iO][jO] == fieldClosed) {
                    fieldView[iO][jO] = fieldCursor;
                }
            break;
            }

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
            }

            case Enter: {
                if (fieldMines[iO][jO] != Mine) {
                    if (fieldView[iO][jO] != fieldFlag) {
                        if (fieldMines[iO][jO] == fieldClosed) {
                            floodFill(fieldMines, iO, jO, fieldOpen);
                            system("cls");
                            gameEnterCheck(fieldMines, fieldView, height, width);
                        }else {
                            fieldView[iO][jO] = fieldMines[iO][jO];
                        }
                    }
                }
                else {
                    gameFieldOutputEnd(fieldView, height, width, flags, minesStat, minesCount, end);
                }
            break;
            }

            case F: {
                if (fieldView[iO][jO] == fieldCursor) {
                    if (fieldMines[iO][jO] == Mine) {
                        minesCount--; flags--; fieldView[iO][jO] = fieldFlag;
                    }
                    else {
                        flags--;
                        fieldView[iO][jO] = fieldFlag;
                    }
                }
                else if (fieldView[iO][jO] == fieldFlag) {
                    fieldView[iO][jO] = fieldCursor;
                    flags++;
                    if (fieldMines[iO][jO] == Mine) {
                        minesCount++;
                    }
                }
             break;
            }

            case H: {
                helpMenu();
                break;
            }

        }

        if (minesCount == 0) {
            end = 0;
            system("cls");
            printf("\t\tПЕРЕМОГА!!! ВИ ЗМОГЛИ!!!\n");
            system("pause");
        }

    } while (end);
    
    gameFileTemptToMain(name, passWord, minesCount, difficulty, height* width);
}

void fieldMinesToEmptyValue(vector<vector<int>>& field, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (field[i][j] == 0) {
                field[i][j] = -2;
            }
        }
    }
}

void fieldCreating(vector<vector<int>>& field, vector<vector<int>>& fieldOn, int height, int width) {
    for (int i = 0; i < height; i++)
    {
            fieldOn[i].resize(width, -2);
            field[i].resize(width);
    }
}

void fieldFilling(int difficulty, int height, int width) {
    int i = 0, j = 0;
    int minesLeft = 0, flags = 0;
    flags = minesLeft = height * width * (difficulty / 100.0);

    vector <vector <int>> fieldMines(height);
    vector <vector <int>> fieldView(height);
    fieldCreating(fieldMines, fieldView, height, width);
   
    do {
        i = rand() % height;
        j = rand() % width;

        if ((fieldMines[i][j] >= 0  && fieldMines[i][j] <= Mine - 1) && fieldMines[i][j] != Mine) {
            fieldMines[i][j] = Mine;

            for (int k = 0; k < 8; k++) {
                if (inRange(fieldMines, i + row[k], j + col[k],0)) {
                    fieldMines[i + row[k]][j + col[k]] += 1;
                }
            }
            minesLeft--;
        }
    } while (minesLeft != 0);

    fieldMinesToEmptyValue(fieldMines, height, width);
    gameMain(flags, fieldMines, fieldView, height, width, difficulty);
}

void fieldSize(int difficulty) {
    int height = 0, width = 0;

    do {
        system("cls");
        cout << "\t\tРозмірність поля:\n" << endl;

        cout << "\tВведіть висоту поля: "; 
        cin >> height;

        cout << "\tВведіть ширину поля: "; 
        cin >> width;
    } while (height < 2 || width < 2);

    fieldFilling(difficulty, height, width);
}

int difficultyMenu() {
    int diffuculty = 0;
    int menuOption = 0;
    int exit = 1;

    system("cls");
    do {

        cout << "\t\tВиберіть рівень складності:\n" << endl;

        switch (1) {
            case 1: {
                menuOption == 0 ? cout << "\t> Легко" << endl : cout << "\tЛегко" << endl;
            }

            case 2: {
                menuOption == 1 ? cout << "\t> Середнє" << endl : cout << "\tСереднє" << endl; 
            }

            case 3: {
                menuOption == 2 ? cout << "\t> Важко" << endl : cout << "\tВажко" << endl; 
            }

            case 4: {
                menuOption == 3 ? cout << "\t> Хардкор" << endl : cout << "\tХардкор" << endl; 
            }

            case 5: {
                menuOption == 4 ? cout << "\t> Налаштувати" << endl : cout << "\tНалаштувати" << endl; 
            }

            case 6: {
                menuOption == 5 ? cout << "\t> Назад" << endl : cout << "\tНазад" << endl; 
            }
        }

        switch (_getch()) {
            case KP_8: { 
                menuOption > 0 ? menuOption-- : menuOption = 5;
                break;
            }

            case KP_2: {
                menuOption < 5 ? menuOption++ : menuOption = 0;
                break;
            }

            case Enter: {
                switch (menuOption) {
                    case 0: { 
                        diffuculty = 15;
                        break;
                    }

                    case 1: {
                        diffuculty = 25;
                        break;
                    }

                    case 2: {
                        diffuculty = 50;
                        break;
                    }

                    case 3: { 
                        diffuculty = 75;
                        break;
                    }

                    case 4: {
                        do {
                            system("cls");
                            cout << "\t\tВведіть відсоток заповненості поля мінами: ";
                            cin >> diffuculty;
                        } while (diffuculty > 99 || diffuculty <= 0);
                        break;
                    }
                    case 5: {
                        return 0;
                    }
                };
            exit = 0;
            break;
            }
        };
    system("cls");
    } while (exit);

    fieldSize(diffuculty);
}

string inputPassword() {
    string passWord;
    do {
        system("cls");
        cout << "Введіть пароль(до 30 символів)!: ";
        cin >> passWord;

    } while (passWord.size() > 30);

    return passWord;
}

string inputUsername() {
    string userName;
    do {
        system("cls");
        cout << "\n\t\tвведіть нік(15 символів): ";
        cin >> userName;

    } while (userName.size() > 15);
    return userName;
}

void authorizationTempFileInput(string userName,string passWord) {
    ofstream fileIn(Temp_U);
    if (fileIn.is_open()) {
        fileIn << userName;
        fileIn << " ";
        fileIn << passWord;
    }
    fileIn.close();
}

void authorization() {
    system("cls");
    int comparison=0;
    string passWord;
    string userName;
    do {
        nicknameenter:
        userName = inputUsername();
        comparison = fileOpen(1, userName,"");

        if (comparison == 1) {
            system("cls");
            passwordAgain:
            cout << "нік зайнято! введіть:\n1 - новий нік\n2 - пароль" << endl;

            switch (_getch()) {
            case K_1: { 
                goto nicknameenter;
            }
            case KP_2: {
                passWord = inputPassword();
                comparison = fileOpen(2, userName, passWord);
                if (comparison == 1) {
                    goto passwordAgain;
                }
                break;
              }
            }
        }

    } while (comparison == 1);

    if (comparison == 0) {
        passWord = inputPassword();
    }

    authorizationTempFileInput(userName, passWord);
    difficultyMenu();
}

void menuHello() {
    int menuOption = 0;
    int exit = 1;

    do {
        cout << "\t\tСАПЕР V 2.2.9. BETA \n\n" << endl;
        switch (1) {
            case 1: {
                menuOption == 0 ? cout << "\t> Нова гра" << endl : cout << "\tНова гра" << endl;
            }

            case 2: {  
                menuOption == 1 ? cout << "\t> Допомога" << endl : cout << "\tДопомога" << endl; 
            }

            case 3: {
                menuOption == 2 ? cout << "\t> Таблиця лідерів" << endl : cout << "\tТаблиця лідерів" << endl; 
            }

            case 4: {
                menuOption == 3 ? cout << "\t> Вихід" << endl : cout << "\tВихід" << endl; 
            }
        }

        //cout << _getch();
        /*becouse of bug*/

        switch (_getch()) {
            case KP_8: {
                menuOption > 0 ? menuOption-- : menuOption = 3;
                break; 
            }

            case KP_2: {
                menuOption < 3 ? menuOption++ : menuOption = 0;
                break; 
            }

            case Enter: {
                switch (menuOption) {
                    case 0: {
                        authorization();
                        break;
                    }

                    case 1: {
                        helpMenu();
                        break;
                    }

                    case 2: {
                        fileOpen(0, "", "");
                        break;
                    }

                    case 3: {
                        exit = 0;
                        break;
                    }
                }
            break;
            }
        }
        system("cls");
    } while (exit);

    cout <<"\tДо зустрічі!" << endl;
}

int main() {
    SetConsoleOutputCP(1251);
    menuHello();
}
/*алгоритм открытия ячеек

  файл +

  вин апи
- Меню по центру
- Цветной текст

  Осталось доработать:
  - Добавить профиль игрока +
        - Ввод ника +
        - Проверка файла +
  - Добавить таблицу рекордов +
        - распознование +
  - Добавить АККАУНТЫ для игроков +
        - пароль +
  
  - Алгоритм открытия +
  - Немного интерактива
  - Пасхалки
  */