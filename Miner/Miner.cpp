#include <stdio.h>
#include <conio.h>
#include <windows.h>

FILE* fp;
char Temp_U[] = "user_temp.txt";
char Users[] = "users.txt";
const int KP_8 = 56;
const int KP_4 = 52;
const int KP_2 = 50;
const int KP_6 = 54;
const int K_ONE = 49;
const int Enter = 13;
const int F = 102;
const int H = 104;
const int Mine = 9;

struct User
{
    char Name[15];
    char Password[30];
    int Score;
    int Difficulty;
    int Sizemap;
    int Sum;
};

int lines()
{
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

    lines_count++;
    fclose(fp);
    return lines_count - 1;
}

int FileOpen(int Comparison, char Name[15], char Password[30])
{
    system("cls");
    int i = 0;
    int CountOfLines = lines();
    int TempScore = 0;
    int TempSizeMap = 0;
    int TempDifficuty = 0;
    int TempSum = 0;
    int CountOfLines_S = lines();
    bool exit = true;
    char TempName[15], TempPassword[30];
    struct User* ptr;

    if ((fp = fopen(Users, "r+")) == NULL)
    {
        if (Comparison == 0)
        {
            printf("\n\tЗаписів нема! Ви - перший!\n");
            system("pause");
        }
        return 0;
    }

    ptr = (struct User*)malloc(CountOfLines * sizeof(struct User));

    while (CountOfLines != 0)
    {
        fscanf(fp, "%s%s%d%d%d", (ptr + i)->Name, (ptr + i)->Password, &((ptr + i)->Score), &((ptr + i)->Difficulty), &((ptr + i)->Sizemap));
        switch (Comparison) {
        case 1:
            if (strcmp(Name, (ptr + i)->Name) == 0)
                return 1;
            break;

        case 2:
            if (strcmp(Name, (ptr + i)->Name) == 0)
            {
                if (strcmp(Password, (ptr + i)->Password) == 0)\
                    return -1;
            }
            break;
        }

        (ptr + i)->Sum = (ptr + i)->Difficulty + (ptr + i)->Sizemap - (ptr + i)->Score;
        printf("%s %s %d %d %d\n", (ptr + i)->Name, (ptr + i)->Password, (ptr + i)->Score, (ptr + i)->Difficulty, (ptr + i)->Sizemap);
        i++;
        CountOfLines--;
    }

    fclose(fp);
    if (Comparison >= 1)
    {
        return 0;
    }

    for (i = 0; i < CountOfLines_S; i++)
    {
        do
        {
            exit = false;
            for (i = 0; i < CountOfLines_S; i++)
            {
                if ((ptr + 1 + i)->Sizemap > 0)
                {
                    if ((ptr + i)->Sum < (ptr + 1 + i)->Sum)
                    {
                        TempSum = (ptr + i)->Sum;
                        TempScore = (ptr + i)->Score;
                        TempSizeMap = (ptr + i)->Sizemap;
                        TempDifficuty = (ptr + i)->Difficulty;
                        strcpy(TempName, (ptr + i)->Name);
                        strcpy(TempPassword, (ptr + i)->Password);

                        (ptr + i)->Sum = (ptr + 1 + i)->Sum;
                        (ptr + i)->Score = (ptr + 1 + i)->Score;
                        (ptr + i)->Sizemap = (ptr + 1 + i)->Sizemap;
                        (ptr + i)->Difficulty = (ptr + 1 + i)->Difficulty;
                        strcpy((ptr + i)->Name, (ptr + 1 + i)->Name);
                        strcpy((ptr + i)->Password, (ptr + 1 + i)->Password);

                        (ptr + 1 + i)->Sum = TempSum;
                        (ptr + 1 + i)->Score = TempScore;
                        (ptr + 1 + i)->Sizemap = TempSizeMap;
                        (ptr + 1 + i)->Difficulty = TempDifficuty;
                        strcpy((ptr + 1 + i)->Name, TempName);
                        strcpy((ptr + 1 + i)->Password, TempPassword);
                        exit = true;
                    }
                }
            }
        } while (exit);
    }

    for (i = 0; i < CountOfLines_S; i++)
    {
        printf("%d Місце - Нік: %s; Мін залишилось: %d; Відсоток заповненості поля: %d%%; Розмір поля: %d\n", i + 1, (ptr + i)->Name, (ptr + i)->Score, (ptr + i)->Difficulty, (ptr + i)->Sizemap);
    }

    system("pause");
    free(ptr);
    return 0;
}

void HelpMenu()
{
    system("cls");
    printf("\t\tEnter - Взаємодія з полем\n\t\tF - Поставити флаг\n\t\tУПРАВЛІННЯ:\n\t\t 8  \n\t\t4 6 \t \n\t\t 2\n");
    system("pause");
}

void GameStart(int MinesCount, int** FieldMines, int** FieldView, int Height, int Width, int Difficulty)
{
    const int FieldFlag = 11;
    const int FieldOpen = 10;
    const int FieldCursor = -1;
    const int FieldClosed = 0;

    int End = 1;
    int i = 0;
    int j = 0;
    int iO = 0;
    int jO = 0;

    FILE* fp_temp;
    char Name[15], Password[30];
    FieldView[0][0] = FieldCursor;
    int MinesStat = MinesCount;
    int Flags = MinesCount;
    int Cursor = 0;

    system("cls");

    do {
        system("cls");
        printf("\tКількість флажків: %d\t Кількість мін: %d; H - Допомогти\n\n", Flags, MinesStat);
        for (i = 0; i < Height; i++)
        {
            printf("\t\t\t");
            for (j = 0; j < Width; j++)
            {
                switch (FieldView[i][j])
                {
                case FieldCursor:
                    printf(" ");
                    break;
                case FieldOpen:
                    printf("/");
                    break;
                case FieldFlag:
                    printf("P");
                    break;
                case FieldClosed:
                    printf("0");
                    break;
                default:
                    printf("%d", FieldView[i][j]);
                    break;
                }
            }
            printf("\n");
        }

        Cursor = _getch();
        switch (Cursor)
        {
        case KP_8:
            if (iO > 0)
            {
                iO--;
                if (FieldView[iO + 1][jO] == FieldCursor)FieldView[iO + 1][jO] = FieldClosed;
            }
            else
            {
                iO = FieldClosed;
            }

            if (FieldView[iO][jO] == FieldClosed)
            {
                FieldView[iO][jO] = FieldCursor;
                break;
            }

        case KP_2:
            if (iO < Height - 1)
            {
                iO++;
                if (FieldView[iO - 1][jO] == FieldCursor)
                {
                    FieldView[iO - 1][jO] = FieldClosed;
                }
            }
            else
            {
                iO = Height - 1;
            }

            if (FieldView[iO][jO] == FieldClosed)
            {
                FieldView[iO][jO] = FieldCursor;
            }
            break;

        case KP_4:
            if (jO > 0)
            {
                jO--;
                if (FieldView[iO][jO + 1] == FieldCursor)FieldView[iO][jO + 1] = FieldClosed;
            }
            else
            {
                jO = FieldClosed;
            }

            if (FieldView[iO][jO] == FieldClosed)
            {
                FieldView[iO][jO] = FieldCursor;
                break;
            }

        case KP_6:
            if (jO < Width - 1)
            {
                jO++;
                if (FieldView[iO][jO - 1] == FieldCursor)
                {
                    FieldView[iO][jO - 1] = FieldClosed;
                }
            }
            else
            {
                jO = Width - 1;
            }

            if (FieldView[iO][jO] == FieldClosed)
            {
                FieldView[iO][jO] = FieldCursor; break;
            }

        case Enter: if (FieldMines[iO][jO] != Mine)
        {
            if (FieldView[iO][jO] != FieldFlag) { FieldMines[iO][jO] == FieldClosed ? FieldView[iO][jO] = FieldOpen : FieldView[iO][jO] = FieldMines[iO][jO]; }
        }
                  else
        {
            system("cls");

            for (i = 0; i < Height; i++)
            {
                printf("\t\t\t");

                for (j = 0; j < Width; j++)
                {
                    if (FieldMines[i][j] == Mine)
                    {
                        printf("*");
                    }
                    else
                    {
                        printf("0");
                    }
                }
                printf("\n");
            }
            printf("\t\tКАБУМ!!!!!!\n\t\tВаш рекорд: %d\n", MinesCount);
            End = 0;
            system("pause");
        }
                  break;

        case F: if (FieldView[iO][jO] == FieldCursor)
        {
            if (FieldMines[iO][jO] == Mine)
            {
                MinesCount--;
                Flags--;
                FieldView[iO][jO] = FieldFlag;
            }

            else
            {
                Flags--;
                FieldView[iO][jO] = FieldFlag;
            }
        }
              else if (FieldView[iO][jO] == FieldFlag)
        {
            FieldView[iO][jO] = FieldCursor;
            Flags++;

            if (FieldMines[iO][jO] == Mine)
            {
                MinesCount++;
            }
        }
              break;

        case H:
            HelpMenu();
            break;
        }

        if (MinesCount == 0)
        {
            End = 0;
            system("cls");
            printf("\t\tПЕРЕМОГА!!! ВИ ЗМОГЛИ!!!\n");
            system("pause");
        }

    } while (End);

    fp_temp = fopen(Temp_U, "r");
    fscanf(fp_temp, "%s%s", Name, Password);
    fclose(fp_temp);
    fp = fopen(Users, "a");
    fprintf(fp, "%s %s %d %d %d \n", Name, Password, MinesCount, Difficulty, Height * Width);
    fclose(fp);
}

void FieldFilling(int Difficulty, int Height, int Width) {
    int i = 0;
    int j = 0;
    int MinesLeft = 0; \
        int Flags = MinesLeft = Height * Width * (Difficulty / 100.0);

    int** Playground = (int**)malloc(Height * sizeof(int*));
    int** PlaygroundOn = (int**)malloc(Height * sizeof(int*));

    system("cls");

    for (i = 0; i < Height; i++)
    {
        Playground[i] = (int*)malloc(Width * sizeof(int));
        PlaygroundOn[i] = (int*)malloc(Width * sizeof(int));

        for (j = 0; j < Width; j++)
        {
            Playground[i][j] = 0;
            PlaygroundOn[i][j] = 0;
        }
    }

    do
    {
        i = rand() % Height;
        j = rand() % Width;

        if ((Playground[i][j] >= 0 && Playground[i][j] <= Mine - 1) && Playground[i][j] != Mine)
        {
            Playground[i][j] = Mine;
            if (((i + 1) < Height) && Playground[i + 1][j] != Mine)
            {
                Playground[i + 1][j] += 1;
            }

            if (((i - 1) >= 0) && Playground[i - 1][j] != Mine)
            {
                Playground[i - 1][j] += 1;
            }

            if (((j - 1) >= 0) && Playground[i][j - 1] != Mine)
            {
                Playground[i][j - 1] += 1;
            }

            if (((j + 1) < Width) && Playground[i][j + 1] != Mine)
            {
                Playground[i][j + 1] += 1;
            }

            if (((i - 1) >= 0) && ((j - 1) >= 0) && Playground[i - 1][j - 1] != Mine)
            {
                Playground[i - 1][j - 1] += 1;
            }

            if (((i + 1) < Height) && ((j + 1) < Width) && Playground[i + 1][j + 1] != Mine)
            {
                Playground[i + 1][j + 1] += 1;
            }

            if (((i - 1) >= 0) && ((j + 1) < Width) && Playground[i - 1][j + 1] != Mine)
            {
                Playground[i - 1][j + 1] += 1;
            }

            if (((i + 1) < Height) && ((j - 1) >= 0) && Playground[i + 1][j - 1] != Mine)
            {
                Playground[i + 1][j - 1] += 1;
            }

            MinesLeft--;
        }
    } while (MinesLeft != 0);

    GameStart(Flags, Playground, PlaygroundOn, Height, Width, Difficulty);

    for (i = 0; i < Height; i++)
    {
        free(PlaygroundOn[i]);
        free(Playground[i]);
    }

    free(PlaygroundOn);
    free(Playground);
}

void FieldSize(int Difficulty)
{
    int Height = 0;
    int Width = 0;

    do {
        system("cls");
        printf("\t\tРозмірність поля:\n\n");
        printf("\tВведіть висоту поля: "); scanf_s("%d", &Height);
        printf("\tВведіть ширину поля: "); scanf_s("%d", &Width);
    } while (Height < 2 || Width < 2);

    FieldFilling(Difficulty, Height, Width);
}

int DifficultyMenu()
{
    int Diffuculty = 0;
    int MenuControl = 0;
    int MenuOption = 0;
    int Exit = 1;

    system("cls");
    do {
        printf("\t\tВиберіть рівень складності:\n\n");
        switch (1) {
        case 1:MenuOption == 0 ? printf("\t> Легко\n") : printf("\tЛегко\n");
        case 2:MenuOption == 1 ? printf("\t> Середнє\n") : printf("\tСереднє\n");
        case 3:MenuOption == 2 ? printf("\t> Важко\n") : printf("\tВажко\n");
        case 4:MenuOption == 3 ? printf("\t> Хардкор\n") : printf("\tХардкор\n");
        case 5:MenuOption == 4 ? printf("\t> Налаштувати\n") : printf("\tНалаштувати\n");
        case 6:MenuOption == 5 ? printf("\t> Назад\n") : printf("\tНазад\n");
        }

        MenuControl = _getch();
        switch (MenuControl) {
        case KP_8: MenuOption > 0 ? MenuOption-- : MenuOption = 5; break;
        case KP_2:MenuOption < 5 ? MenuOption++ : MenuOption = 0; break;
        case Enter:
            switch (MenuOption) {
            case 0:
                Diffuculty = 15;
                break;
            case 1:
                Diffuculty = 25;
                break;
            case 2:
                Diffuculty = 50;
                break;
            case 3:
                Diffuculty = 75;
                break;
            case 4:
                do {
                    system("cls");
                    printf("\t\tВведіть відсоток заповненості поля мінами: ");
                    scanf_s("%d", &Diffuculty);
                } while (Diffuculty > 99 || Diffuculty <= 0);
                break;
            case 5:
                return 0;
                break;
            };
            Exit = 0;
            break;
        }
        system("cls");
    } while (Exit);

    FieldSize(Diffuculty);
}

char* InputPassword()
{
    char Password[31];

    do {
        system("cls");
        printf("Введіть пароль(до 30 символів)!: ");
        scanf("%s", Password);
    } while (strlen(Password) > 30);

    return Password;
}

void InputUsername()
{
    system("cls");
    int Comparison;
    char Password[31];
    char Username[16];

    do {
        do {
        NicknameEnter:
            system("cls");
            printf("\n\t\tВведіть нік(15 символів): ");
            scanf("%s", Username);
        } while (strlen(Username) > 15);

        Comparison = FileOpen(1, Username, 0);

        if (Comparison == 1)
        {
            system("cls");
            printf("Нік зайнято! Введіть:\n1 - новий нік\n2- пароль\n");

            switch (_getch())
            {
            case K_ONE: goto NicknameEnter;
                break;
            case KP_2:strcpy(Password, InputPassword()); Comparison = FileOpen(2, Username, Password);
                break;
            }
        }
    } while (Comparison == 1);

    if (Comparison != -1)
    {
        strcpy(Password, InputPassword());
    }

    fp = fopen(Temp_U, "w");
    fprintf(fp, "%s %s\n", Username, Password);
    fclose(fp);
}

void MenuHello()
{
    int MenuControl = 0;
    int MenuOption = 0;
    int Exit = 1;

    do {
        printf("\t\tСАПЕР V 2.2.8. BETA \n\n");

        switch (1)
        {
        case 1:  MenuOption == 0 ? printf("\t> Нова гра\n") : printf("\tНова гра\n");
        case 2:  MenuOption == 1 ? printf("\t> Допомога\n") : printf("\tДопомога\n");
        case 3:  MenuOption == 2 ? printf("\t> Таблиця лідерів\n") : printf("\tТаблиця лідерів\n");
        case 4:  MenuOption == 3 ? printf("\t> Вихід\n") : printf("\tВихід\n");
        }
        MenuControl = _getch();
        printf("%d", MenuControl);

        switch (MenuControl)
        {
        case KP_8: MenuOption > 0 ? MenuOption-- : MenuOption = 3; break;
        case KP_2:MenuOption < 3 ? MenuOption++ : MenuOption = 0; break;
        case Enter:

            switch (MenuOption)
            {
            case 0:
                InputUsername();
                DifficultyMenu();
                break;
            case 1:
                HelpMenu();
                break;
            case 2:
                FileOpen(0, 0, 0);
                break;
            case 3:
                Exit = 0;
                break;
            }
            break;
        }
        system("cls");
    } while (Exit);
    printf("\tДо зустрічі!\n");
}

int main()
{
    SetConsoleOutputCP(1251);
    MenuHello();
}

/*алгоритм открытия ячеек

  файл +
  
- Refactoring +
  
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
