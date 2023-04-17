#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#include <conio.h>
#include <windows.h>
#include "Miner.h"
using namespace std;

typedef const int keyPressedValue;
typedef const int fileValue;
typedef const short int consolePosition;
typedef const int color;

char fileTempUser[] = "user_temp.txt";
char fileMainUsers[] = "users.txt";
HANDLE consoleWindow = GetStdHandle(STD_OUTPUT_HANDLE);
consolePosition centerX = 45;
consolePosition centerY = 5;
keyPressedValue KP_8 = 56, KP_4 = 52, KP_2 = 50, KP_6 = 54;
keyPressedValue Enter = 13, F = 102, H = 104;
color selected = 206;
color selectedNot = 62;
color warningOrError = 79;
color difficulty = 47;
color black = 0;
color cursor = 68, open = 256, mineFlag = 175, closed = 136;
fileValue Mine = 9;
fileValue fieldFlag = 11, fieldOpen = 0, fieldCursor = -1, fieldClosed = -2;
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
    ifstream file(fileMainUsers);
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

void fileBubleSort(int countOfLines, struct user ptr[]) {
    bool exit;
    int tempSum=0, tempScore=0, tempSizeMap=0, tempDifficulty=0;
    string tempName, tempPassword;
    for (int i = 0; i < countOfLines; i++) {
        if (countOfLines > 1) {
            do {
                exit = false;
                for (int i = 0; i < countOfLines; i++) {
                    if (i+1!=countOfLines && ptr[i + 1].sum > ptr[i].sum) {

                        tempSum = ptr[i].sum;
                        tempScore = ptr[i].score;
                        tempSizeMap = ptr[i].size;
                        tempDifficulty = ptr[i].difficulty;
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
                        ptr[i + 1].difficulty = tempDifficulty;
                        ptr[i + 1].userName = tempName;
                        ptr[i + 1].passWord = tempPassword;
                        exit = true;
                    }
                }
            } while (exit);
        }
    }
    for (int i = 0; i < countOfLines; i++) {
        cout << i + 1 << " Місце; - Нік: " << ptr[i].userName << " Мін залишилось: " << ptr[i].score << " Відсоток заповненості поля: " << ptr[i].difficulty << "%; Розмір поля: " << ptr[i].size << endl;
    }
}

int fileOpen(int Comparison, string Name, string Password) {
    const int countOfLines = lines();
    int tempScore = 0, tempSizeMap = 0, tempDifficuty = 0, tempSum = 0;
    user* ptr = new user[countOfLines];
    bool exit = true;
    ifstream file(fileMainUsers);
    string tempName, tempPassword;
    system("cls");
    if (file.peek() == EOF)
    {
        if (Comparison == 0) {
            cout<<"\n\tЗаписів нема! Ви - перший!"<<endl;
            SetConsoleTextAttribute(consoleWindow, selected);
            system("pause");
            SetConsoleTextAttribute(consoleWindow, black);
        }
        return 0;
    }
    for(int i = 0;i<countOfLines;i++){
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

    fileBubleSort(countOfLines, ptr);

    SetConsoleTextAttribute(consoleWindow, selected);
    system("pause");
    SetConsoleTextAttribute(consoleWindow, black);
    delete[]ptr;

    return 0;
}

void helpMenu() {
    system("cls");
    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX-5, centerY});
    cout << "Enter - Взаємодія з полем";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX-5, centerY + 1});
    cout << "F - Поставити флаг";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX-5, centerY + 2});
    cout << "УПРАВЛІННЯ:";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 3});
    cout << "8";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX - 2, centerY + 4});
    cout << "4";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX + 2, centerY + 4});
    cout << "6";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 5});
    cout << "2";
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleCursorPosition(consoleWindow, {centerX-5, centerY + 7});
    SetConsoleTextAttribute(consoleWindow, selected);
    system("pause");
    SetConsoleTextAttribute(consoleWindow, black);
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

void commonInput(string name, string passWord, int minesCount, int difficulty, int size) {
    ofstream fileIn;
    fileIn.open(fileMainUsers, ofstream::app);

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
    int countOfLines = lines();
    if (countOfLines == 0) {
        return 0;
    }
    int tempSum, tempScore, tempSizeMap, tempDifficulty;
    bool sameName=false;

    string tempName, tempPassword;
    ifstream file(fileMainUsers);
    ofstream fileRewrite;
    user* ptr = new user[countOfLines];

    for (int i = 0; i < countOfLines; i++) {
        file >> ptr[i].userName;
        file >> ptr[i].passWord;
        file >> ptr[i].score;
        file >> ptr[i].difficulty;
        file >> ptr[i].size;
    }
    file.close();
   
    for (int i = 0; i < countOfLines; i++) {
        if (name == ptr[i].userName) {
            sameName = true;
            if (countOfLines == 1) { 
                fileRewrite.open(fileMainUsers);
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

    if (!sameName) {
        return 0;
    }
    fileRewrite.open(fileMainUsers);

    for (int i = 0; i < countOfLines-1; i++) {
        if (fileRewrite.is_open()) {
            commonInput(ptr[i].userName, ptr[i].passWord, ptr[i].score, ptr[i].difficulty, ptr[i].size);
        }
        
    }
    fileRewrite.close();
    return 0;
}

void gameFileTemptToMain(string name, string passWord, int minesCount, int difficulty,int size) {
    ifstream fileOut(fileTempUser);

    if (fileOut.is_open()) {
        fileOut >> name;
        fileOut >> passWord;
    }
    fileOut.close();

    structCheck(name, passWord, minesCount, difficulty, size);

    commonInput(name, passWord, minesCount, difficulty, size);
}

void gameFieldOutputView(vector<vector<int>> fieldView,int height, int width, int flags, int minesStat, int iO, int jO) {
    system("cls");
    short int centerMoveY = centerY;
    short int centerMoveX = centerX;

    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, {centerX-10, centerY-2});
    cout << "Кількість флажків: " << flags << " Кількість мін: " << minesStat << "; H - Допомогти";
    SetConsoleTextAttribute(consoleWindow, black);

    for (int i = 0; i < height; i++) {

        centerMoveY += 1;
        SetConsoleCursorPosition(consoleWindow, {centerMoveX, centerMoveY});
        for (int j = 0; j < width; j++) {
            centerMoveX += 1;
            SetConsoleCursorPosition(consoleWindow, {centerMoveX, centerMoveY});
            if (i == iO && j == jO) {
                continue;
            }
            switch (fieldView[i][j]) {
                case fieldOpen: {
                    SetConsoleTextAttribute(consoleWindow, cursor);
                    cout << " ";
                    break;
                }
                case fieldFlag: {
                    SetConsoleTextAttribute(consoleWindow, mineFlag);
                    cout << " ";
                    break;
                }
                case fieldClosed: {
                    SetConsoleTextAttribute(consoleWindow, closed);
                    cout << " ";
                    break;
                }
                default: {
                    SetConsoleTextAttribute(consoleWindow, selected);
                    cout << fieldView[i][j];
                    break;
                }
            }
            SetConsoleTextAttribute(consoleWindow, black);
        }
        centerMoveX = centerX;
    }
}

void gameFieldOutputEnd(vector<vector<int>> fieldMines, int height, int width, int flags, int minesStat,int minesCount,int& end) {
    system("cls");
    short int centerMoveY = centerY;
    short int centerMoveX = centerX;
    
    for (short int i = 0; i < height; i++) { 
        centerMoveY += 1;
        SetConsoleCursorPosition(consoleWindow, {centerMoveX, centerMoveY});
        for (int j = 0; j < width; j++) {
            centerMoveX += 1;
            SetConsoleCursorPosition(consoleWindow, {centerMoveX, centerMoveY});
            if (fieldMines[i][j] == Mine) {
                SetConsoleTextAttribute(consoleWindow, selected);
                cout << "*";
            }
            else {
                SetConsoleTextAttribute(consoleWindow, selectedNot);
                cout << "0";
            }
            SetConsoleTextAttribute(consoleWindow, black);
        }
        centerMoveX = centerX;
        cout << endl;
    }

    centerMoveY += 1;
    SetConsoleCursorPosition(consoleWindow, {centerX, centerMoveY});
    SetConsoleTextAttribute(consoleWindow, warningOrError);
    cout << "КАБУМ!!!!!!";
    SetConsoleTextAttribute(consoleWindow, black);

    centerMoveY += 1;
    SetConsoleCursorPosition(consoleWindow, { centerX, centerMoveY });
    SetConsoleTextAttribute(consoleWindow, selected);
    cout << "Ваш рекорд : " << minesCount ;
    SetConsoleTextAttribute(consoleWindow, black);

    SetConsoleTextAttribute(consoleWindow, selected);
    system("pause");
    SetConsoleTextAttribute(consoleWindow, black);
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

        gameFieldOutputView(fieldView, height, width, flags, minesStat, iO, jO);
       
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
                    gameFieldOutputEnd(fieldMines, height, width, flags, minesStat, minesCount, end);
                    end = 0;
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
            SetConsoleCursorPosition(consoleWindow, {centerX, centerY});
            SetConsoleTextAttribute(consoleWindow, selected);
            printf("ПЕРЕМОГА!!! ВИ ЗМОГЛИ!!!");
            SetConsoleTextAttribute(consoleWindow, black);

            SetConsoleCursorPosition(consoleWindow, { centerX, centerY+1 });
            SetConsoleTextAttribute(consoleWindow, selected);
            system("pause");
            SetConsoleTextAttribute(consoleWindow, black);
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
        SetConsoleCursorPosition(consoleWindow, {centerX, centerY - 1});
        SetConsoleTextAttribute(consoleWindow, selected);
        cout << "Розмірність поля:" << endl;
        SetConsoleTextAttribute(consoleWindow, black);

        SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 1});
        SetConsoleTextAttribute(consoleWindow, selectedNot);
        cout << "Введіть висоту поля: "; 
        SetConsoleTextAttribute(consoleWindow, selected);
        cin >> height;
        SetConsoleTextAttribute(consoleWindow, black);

        SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 2});
        SetConsoleTextAttribute(consoleWindow, selectedNot);
        cout << "Введіть ширину поля: "; 
        SetConsoleTextAttribute(consoleWindow, selected);
        cin >> width;
        SetConsoleTextAttribute(consoleWindow, black);
    } while (height < 2 || width < 2);

    fieldFilling(difficulty, height, width);
}

int difficultyMenu() {
    int diffuculty = 0;
    int menuOption = 0;
    int exit = 1;

    system("cls");
    do {
        SetConsoleTextAttribute(consoleWindow, selected);
        SetConsoleCursorPosition(consoleWindow, {centerX, centerY - 1});
        cout << "Виберіть рівень складності:";
        SetConsoleTextAttribute(consoleWindow, black);
        switch (1) {
            case 1: {
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 1});
                SetConsoleTextAttribute(consoleWindow, difficulty);
                if (menuOption == 0) {
                    cout << "> Легко";
                }
                else { 
                    cout << "Легко";
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 2: {
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 2});
                SetConsoleTextAttribute(consoleWindow, difficulty + 16);
                if (menuOption == 1) {
                    cout << "> Середнє";
                }
                else {
                    cout << "Середнє"; 
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 3: {
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 3});
                SetConsoleTextAttribute(consoleWindow, difficulty + 32);
                if (menuOption == 2) {
                    cout << "> Важко";
                }
                else {
                    cout << "Важко";
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 4: {
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 4});
                SetConsoleTextAttribute(consoleWindow, difficulty + 48);
                if (menuOption == 3) {
                    cout << "> Хардкор";
                }
                else {
                    cout << "Хардкор";
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 5: {
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 5});
                SetConsoleTextAttribute(consoleWindow, difficulty + 54);
                if (menuOption == 4) {
                    cout << "> Налаштувати";
                }
                else {
                    cout << "Налаштувати";
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 6: {
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 6});
                if (menuOption == 5) {
                    SetConsoleTextAttribute(consoleWindow, selected);
                    cout << "> Назад";
                }
                else {
                    SetConsoleTextAttribute(consoleWindow, selectedNot);
                    cout << "Назад";
                }
                SetConsoleTextAttribute(consoleWindow, black);
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
                            SetConsoleCursorPosition(consoleWindow, {centerX, centerY});
                            SetConsoleTextAttribute(consoleWindow, selectedNot);
                            cout << "Введіть відсоток заповненості поля мінами: ";
                            SetConsoleTextAttribute(consoleWindow, selected);
                            cin >> diffuculty;
                            SetConsoleTextAttribute(consoleWindow, black);
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
        SetConsoleTextAttribute(consoleWindow, selectedNot);
        SetConsoleCursorPosition(consoleWindow, {centerX, centerY});
        cout << "Введіть пароль(до 30 символів)!: ";
        SetConsoleTextAttribute(consoleWindow, selected);
        cin >> passWord;
        
    } while (passWord.size() > 30);
    SetConsoleTextAttribute(consoleWindow, black);
    return passWord;
}

string inputUsername() {
    string userName;
    do {
        system("cls");
        SetConsoleTextAttribute(consoleWindow, selectedNot);
        SetConsoleCursorPosition(consoleWindow, {centerX, centerY});
        cout << "введіть нік(15 символів): ";
        SetConsoleTextAttribute(consoleWindow, selected);
        cin >> userName;
        
    } while (userName.size() > 15);
    SetConsoleTextAttribute(consoleWindow, black);
    return userName;
}

void authorizationTempFileInput(string userName,string passWord) {
    ofstream fileIn(fileTempUser);
    if (fileIn.is_open()) {
        fileIn << userName;
        fileIn << " ";
        fileIn << passWord;
    }
    fileIn.close();
}

void authorization() {
    system("cls");
    int comparison = 0;
    int menuOption = 0;
    int exit = 1;
    string passWord;
    string userName;
    do {
        nicknameenter:
        userName = inputUsername();
        comparison = fileOpen(1, userName,"");

        if (comparison == 1) {
            passwordAgain:
            system("cls");

            do {
                SetConsoleTextAttribute(consoleWindow, warningOrError);
                SetConsoleCursorPosition(consoleWindow, {centerX, centerY - 1});
                cout << "нік зайнято! введіть:";
                SetConsoleTextAttribute(consoleWindow, black);
                switch (1) {
                    case 1: {
                        SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 1});
                        if (menuOption == 0) {
                            SetConsoleTextAttribute(consoleWindow, selected);
                            cout << "> Новий нік";
                        }
                        else {
                            SetConsoleTextAttribute(consoleWindow, selectedNot);
                            cout << "Новий нік";
                        }
                        SetConsoleTextAttribute(consoleWindow, black);
                    }
                    case 2: {
                        SetConsoleCursorPosition(consoleWindow, {centerX, centerY + 2});
                        if (menuOption == 1) {
                            SetConsoleTextAttribute(consoleWindow, selected);
                            cout << "> Пароль";
                        }
                        else {
                            SetConsoleTextAttribute(consoleWindow, selectedNot);
                            cout << "Пароль";
                        }
                        SetConsoleTextAttribute(consoleWindow, black);
                    }
                }

                switch (_getch()) {
                case KP_8: {
                    menuOption > 0 ? menuOption-- : menuOption = 1;
                    break;
                }
                case KP_2: {
                    menuOption < 1 ? menuOption++ : menuOption = 0;
                    break;
                }
                case Enter: {
                    switch (menuOption) {
                        case 0: {
                            goto nicknameenter;
                        }
                        case 1: {
                            passWord = inputPassword();
                            comparison = fileOpen(2, userName, passWord);
                            if (comparison == 1) {
                                goto passwordAgain;
                            }
                            break;
                        }
                    }
                    break;
                }
                }
                system("cls");
            } while (exit);
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
        SetConsoleTextAttribute(consoleWindow, selected);
        SetConsoleCursorPosition(consoleWindow, {centerX, centerY - 1});
        cout << "САПЕР REALISE ";
        SetConsoleTextAttribute(consoleWindow, black);
        switch (1) {
            case 1: {
                
                SetConsoleCursorPosition(consoleWindow, {centerX+1, centerY + 1});
                if (menuOption == 0) {
                    SetConsoleTextAttribute(consoleWindow, selected);
                    cout << "> Нова гра" << endl;
                }
                else {
                    SetConsoleTextAttribute(consoleWindow, selectedNot);
                    cout << "Нова гра" << endl;
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 2: {  
                
                SetConsoleCursorPosition(consoleWindow, {centerX + 1, centerY + 2});
                if (menuOption == 1) {
                    SetConsoleTextAttribute(consoleWindow, selected);
                    cout << "> Допомога";
                }
                else {
                    SetConsoleTextAttribute(consoleWindow, selectedNot);
                    cout << "Допомога";
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 3: {
                
                SetConsoleCursorPosition(consoleWindow, {centerX + 1, centerY + 3});
                if (menuOption == 2) {
                    SetConsoleTextAttribute(consoleWindow, selected);
                    cout << "> Таблиця лідерів";
                }
                else {
                    SetConsoleTextAttribute(consoleWindow, selectedNot);
                    cout << "Таблиця лідерів";
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
            case 4: {
                SetConsoleCursorPosition(consoleWindow, {centerX + 1, centerY + 4});
                if (menuOption == 3) {
                    SetConsoleTextAttribute(consoleWindow, selected);
                    cout << "> Вихід";
                }
                else {
                    SetConsoleTextAttribute(consoleWindow, selectedNot);
                    cout << "Вихід";
                }
                SetConsoleTextAttribute(consoleWindow, black);
            }
        }

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
    SetConsoleTextAttribute(consoleWindow, selected);
    SetConsoleCursorPosition(consoleWindow, { centerX,centerY + 3 });
    cout <<"\tДо зустрічі!" << endl;
    SetConsoleCursorPosition(consoleWindow, { centerX,centerY + 7 });
    SetConsoleTextAttribute(consoleWindow, 15);
}

int main() {
    SetConsoleOutputCP(1251);
    menuHello();
}