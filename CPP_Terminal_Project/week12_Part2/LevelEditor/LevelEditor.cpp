#include <iostream>
#include<conio.h>
#include<windows.h>
#include<fstream>

using namespace std;

constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;

constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEscape = 27;
constexpr int kBackSpace = 8;
constexpr int kEnter = 13;

void GetLevelDimentions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);

int GetIndexFromXY(int x, int y, int width);
void DisplayTopBorder(int width);
void DisplayBottomBorder(int width);
void DisplayLeftBorder();
void DisplayRightBorder();

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int Height);
void SaveLevel(char* pLevel, int width, int height);

void DisplayLegend();

void RunEditor(char* pLevel, int width, int height);

int main()
{
    char* pLevel = nullptr;
    int Levelwidth;
    int LevelHeight;
    bool done = false;

    while (!done) {

        system("cls");

        cout << "Please select one of the following options:" << endl;
        cout << "1. Load Level" << endl;
        cout << "2. New Level" << endl;
        cout << "3. Quit" << endl;

        int input;
        cin >> input;

        if (input == 1) {

            // Load Level
            cout << "Enter Level name: ";
            string levelName;
            cin >> levelName;

            levelName.insert(0, "../");

            ifstream levelFile;
            levelFile.open(levelName);

            if (!levelFile) {

                cout << "Opening file failed!" << endl;
            }
            else {

                constexpr int tempSize = 25;
                char temp[tempSize];

                levelFile.getline(temp, tempSize, '\n');
                Levelwidth = atoi(temp);

                levelFile.getline(temp, tempSize, '\n');
                LevelHeight = atoi(temp);

                pLevel = new char[Levelwidth * LevelHeight];
                levelFile.read(pLevel, LevelHeight * Levelwidth);
                levelFile.close();

                RunEditor(pLevel, Levelwidth, LevelHeight);

                delete[] pLevel;
                pLevel = nullptr;

            }
        }
        else if (input == 2) {

            // New Level
            GetLevelDimentions(Levelwidth, LevelHeight);

            pLevel = new char[Levelwidth * LevelHeight];

            for (int i = 0; i < Levelwidth * LevelHeight; i++) {

                pLevel[i] = ' ';

            }
            RunEditor(pLevel, Levelwidth, LevelHeight);

            delete[] pLevel;
            pLevel = nullptr;
        }
        else {

            done = true;
        }

    }

}

void RunEditor(char* pLevel, int width, int height){
    int cursorX = 0;
    int cursorY = 0;

    bool DoneEditing = false;

    while (!DoneEditing) {

        system("cls");
        DisplayLevel(pLevel, width, height, cursorX, cursorY);
        DisplayLegend();
        DoneEditing = EditLevel(pLevel, cursorX, cursorY, width, height);
    }

    system("cls");
    DisplayLevel(pLevel, width, height, -1, -1);

    SaveLevel(pLevel, width, height);


}

void GetLevelDimentions(int& width, int& height) {

    cout << "Enter the width of your level: ";
    cin >> width;

    cout << "Enter the height of your level: ";
    cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY) {

    DisplayTopBorder(width);

    for (int y = 0; y < height; y++) {

        DisplayLeftBorder();
        for (int x = 0; x < width; x++) {

            if (cursorX == x && cursorY == y) {

                cout << kCursor;
            }
            else {

                int index = GetIndexFromXY(x, y, width);
                cout << pLevel[index];
            }
        }
        DisplayRightBorder();
    }

    DisplayBottomBorder(width);
}

int GetIndexFromXY(int x, int y, int width) {

    return x + y * width;
}

void DisplayTopBorder(int width) {

    cout << kTopLeftBorder;
    for (int i = 0; i < width; i++) {

        cout << kHorizontalBorder;
    }
    cout << kTopRightBorder << endl;
}

void DisplayBottomBorder(int width) {

    cout << kBottomLeftBorder;
    for (int i = 0; i < width; i++) {

        cout << kHorizontalBorder;
    }
    cout << kBottomRightBorder << endl;
}

void DisplayLeftBorder() {

    cout << kVerticalBorder;
}

void DisplayRightBorder() {

    cout << kVerticalBorder << endl;
}

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int Height) {

    int newCursorX = cursorX;
    int newCursorY = cursorY;

    int intInput = _getch();

    if (intInput == kArrowInput) {

        int arrowInput = _getch();

        switch (arrowInput) {

        case kLeftArrow:
            newCursorX--;
            break;

        case kRightArrow:
            newCursorX++;
            break;

        case kUpArrow:
            newCursorY--;
            break;

        case kDownArrow:
            newCursorY++;
            break;
        }

        if (newCursorX < 0)
            newCursorX = 0;
        else if (newCursorX == width)
            newCursorX = width - 1;
        if (newCursorY < 0)
            newCursorY = 0;
        else if (newCursorY == width)
            newCursorY = width - 1;

        cursorX = newCursorX;
        cursorY = newCursorY;

    }
    else {

        if (intInput == kEscape) {
            return true;
        }
        else if (intInput == kBackSpace) {

            //ignore
        }
        else if (intInput == kEnter) {

            //ignore
        }
        else {
            int index = GetIndexFromXY(newCursorX, newCursorY, width);
            pLevel[index] = (char)intInput;
        }
    }
    return false;
}

void SaveLevel(char* pLevel, int width, int height) {

    cout << "Pick a name for your level file (eg. Level1.txt): ";
    string levelName;
    cin >> levelName;

    levelName.insert(0, "../");

    ofstream levelFile;
    levelFile.open(levelName);
    if (!levelFile) {

        cout << "Opening file failed!" << endl;
    }
    else {

        levelFile << width << endl;
        levelFile << height << endl;
        levelFile.write(pLevel, width * height);
        if (!levelFile) {

            cout << "Write failed!" << endl;
        }
        levelFile.close();
    }
}

void DisplayLegend() {

    cout << "Arrow to move cursor." << endl;
    cout << "ESC to finish editing." << endl;
    cout << "+ | - for walls." << endl;
    cout << "@ for player start." << endl;
    cout << "r g b for keys." << endl;
    cout << "R G B for doors." << endl;
    cout << "$ for money." << endl;
    cout << "v for vertical moving enemy." << endl;
    cout << "h for horizontal moving enemy." << endl;
    cout << "e for non-moving enemy." << endl;
    cout << "X for end." << endl;
}