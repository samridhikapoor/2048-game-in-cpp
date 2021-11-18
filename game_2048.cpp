#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <stack>
#include <vector>

using namespace std;

int TotalScore = 0;

int UndoLimit = 0;

int UndoScore = 0;
class Game2048
{
    stack<vector<vector<int>>> UndoStack; 
    stack<int> StackScore;
    
	string Name;
    int Grid[4][4];
    int CopyGrid[4][4];
    void Initialize();
    void Show();
    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    int isFULL();
    int RandomTile(int o);
    void AddUp();
    void AddDown();
    void AddLeft();
    void AddRight();
    void GenerateNewTile();
    int CalMaximum();
    void Instructions();
    int GameOver();
    void DisplayEnd();
    void DisplayWin();
    void DisplayLose();
    void Restart();

public:
    void LetsPlay();
    Game2048()
    {
        // Default constructor
    }
};

void Game2048 ::Instructions()
{
    cout << "\nInstructions for playing 2048 are:: \n"
         << endl;
    cout << "> The game starts with 1 or 2 randomly placed numbers in a 4x4 Grid (16 cells).\n"<<endl;
    cout << "> For moving tiles enter \nw-move up\na-move left\nd-move right\ns-move down\n"
         << endl;
    cout << "> When two tiles with same number, they merge into one. \n\n> When 2048 is created, the player wins!\n"
         << endl;
    cout<<"> Please don't try to undo consecutively\n"<<endl;
    cout << "> Maximum 5 undo operations are supported\n"<<endl;
	cout<<"> New 2s and 4s will appear randomly on an empty cell with each move you make.\n"<<endl;
	cout<<"> Your objective is to make 2048 in a cell without getting stuck!\n\n\n"<<endl;;
    Show();
}

int Game2048 ::RandomTile(int o)
{
    int index;
    index = rand() % o + 0; 
    return index;
}

void Game2048 ::DisplayLose()
{
    cout<<"\n\n\n\t\t\t  :: [ G A M E  O V E R ] ::"
	    <<"\n\n\n\n\t\t\t     SCORE\t    NAME";
	printf("\n\n\t\t\t    %6d\t    ",TotalScore);
	cin>>Name;
    exit(0);
}

void Game2048 ::Restart()
{
    char ch;
    cout << "\nAre you sure to Restart the game??\n\n";
    cout << "enter y to Restart and n to continue.\n\n";
    cin >> ch;
    if (ch == 'y')
    {
        TotalScore = 0;
        UndoScore = 0;
        UndoStack = stack<vector<vector<int>>>();
        StackScore = stack<int>();
        Initialize();
    }
}

int Game2048 ::isFULL()    
{
    int f = 1;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (Grid[i][j] == 0)
            {
                f = 0;
                break;
            }
        }
    }
    return f;
}

void Game2048 ::DisplayWin()
{
    char ch;
    cout<<endl<<endl;
	cout<<"\n\t\t\t  :: [  YOU MADE "<<TotalScore<<"!  ] ::"
	    <<"\n\n\t\t\t  :: [ YOU WON THE GAME ] ::"
	    <<"\n\n\n\n\t\t\t    SCORE\t    NAME";
	printf("\n\n\t\t\t    %6d\t    ",TotalScore);
    cout << "Do you wish to continue???\n";
    cout << "Enter y to continue and n to quit\n\n";
    cin >> ch;
    if (ch == 'n')
    {
        DisplayEnd();
    }
}

int Game2048 ::CalMaximum()
{
    int i, j;
    int max = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (Grid[i][j] > max)
            {
                max = Grid[i][j];
            }
        }
    }
    return max;
}

void Game2048 ::DisplayEnd()
{
    cout << "\nYour final Score is :: " << TotalScore << endl
         << endl;
    cout << "THANKS FOR TRYING!!!\n\n"
         << endl;
    exit(0);
}

int Game2048 ::GameOver()
{
    int i, j, flag = 1;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (Grid[i][j] == Grid[i][j + 1])     
            {
                flag = 0;
                break;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    if (flag == 1)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (Grid[i][j] == Grid[i + 1][j])     
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 0)
            {
                break;
            }
        }
    }
    return flag;
}

void Game2048 ::GenerateNewTile()
{ 
    int flag = 1;
    if (!isFULL())
    {
        while (flag)
        {
            int i = RandomTile(4);
            int j = RandomTile(4);
            if (Grid[i][j] == 0)
            {
                int y = rand() % 10 + 0;
                if (y < 8)
                {
                    Grid[i][j] = 2;
                }
                else
                {
                    Grid[i][j] = 4;
                }
                flag = 0;
            }
        }
    }
}

void Game2048 ::Initialize()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Grid[i][j] = 0;
            CopyGrid[i][j] = 0;
        }
    }
    int i = RandomTile(4);
    int j = RandomTile(4);
    Grid[i][j] = 2;
    i = RandomTile(4);
    j = RandomTile(4);
    Grid[i][j] = 2;
    Show();
}

void Game2048 ::MoveUp()
{
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 4; j++)
        {
            if (!Grid[j][i])
            {
                for (int k = j + 1; k < 4; k++) 
                    if (Grid[k][i])
                    {
                        Grid[j][i] = Grid[k][i]; 
                        Grid[k][i] = 0;       
                        break;
                    }
            }
        }
}

void Game2048 ::MoveDown()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (!Grid[j][i])
            {
                for (int k = j - 1; k >= 0; k--)
                {
                    if (Grid[k][i])
                    {
                        Grid[j][i] = Grid[k][i];
                        Grid[k][i] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void Game2048 ::MoveLeft()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (!Grid[i][j])
            {
                for (int k = j + 1; k < 4; k++)
                {
                    if (Grid[i][k])
                    {
                        Grid[i][j] = Grid[i][k];
                        Grid[i][k] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void Game2048 ::MoveRight()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j >= 0; j--)
        {
            if (!Grid[i][j])
            {
                for (int k = j - 1; k >= 0; k--)
                {
                    if (Grid[i][k])
                    {
                        Grid[i][j] = Grid[i][k];
                        Grid[i][k] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void Game2048 ::AddUp()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Grid[j][i] && Grid[j][i] == Grid[j + 1][i])
            {
                Grid[j][i] = Grid[j][i] + Grid[j + 1][i];
                Grid[j + 1][i] = 0;
                TotalScore += Grid[j][i];
                UndoScore += Grid[j][i];
            }
        }
    }
}

void Game2048 ::AddDown()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (Grid[j][i] && Grid[j][i] == Grid[j - 1][i])
            {
                Grid[j][i] = Grid[j][i] + Grid[j - 1][i];
                Grid[j - 1][i] = 0;
                TotalScore += Grid[j][i];
                UndoScore += Grid[j][i];
            }
        }
    }
}

void Game2048 ::AddLeft()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Grid[i][j] && Grid[i][j] == Grid[i][j + 1])
            {
                Grid[i][j] = Grid[i][j] + Grid[i][j + 1];
                Grid[i][j + 1] = 0;
                TotalScore += Grid[i][j];
                UndoScore += Grid[i][j];
            }
        }
    }
}

void Game2048 ::AddRight()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j > 0; j--)
        {
            if (Grid[i][j] && Grid[i][j] == Grid[i][j - 1])
            {
                Grid[i][j] = Grid[i][j] + Grid[i][j - 1];
                Grid[i][j - 1] = 0;
                TotalScore = TotalScore + Grid[i][j];
                UndoScore += Grid[i][j];
            }
        }
    }
}


void Game2048 ::LetsPlay()
{
    int flag = 0;
    char choice, ch;
    Initialize();
    cin >> choice;

    while ((choice == 'w' || choice == 'a' || choice == 's' || choice == 'd' || choice == 'q' || choice == 'i' || choice == 'u' || choice == 'r'))
    {
       
        if (choice != 'u')
        {
            vector<vector<int>> current_copy;
            current_copy.resize(4);
            for (int m = 0; m < 4; m++)
            {
                for (int n = 0; n < 4; n++)
                {
                    current_copy[m].push_back(Grid[m][n]);
                }
            }
            UndoStack.push(current_copy);
        }

        if(choice !='u'){
        	for(int m=0;m<4;m++){
        		for(int n=0;n<4;n++){
        			CopyGrid[m][n]=Grid[m][n];
        		}
         	}
         }

        switch (choice)
        {

        case 'w':
            UndoScore = 0;
            MoveUp();
            AddUp();
            MoveUp();
            GenerateNewTile();
            Show();
            StackScore.push(UndoScore);
            break;

        case 's':
            UndoScore = 0;
            MoveDown();
            AddDown();
            MoveDown();
            GenerateNewTile();
            Show();
            StackScore.push(UndoScore);
            break;

        case 'a':
            UndoScore = 0;
            MoveLeft();
            AddLeft();
            MoveLeft();
            GenerateNewTile();
            Show();
            StackScore.push(UndoScore);
            break;
 
        case 'd':
            UndoScore = 0;
            MoveRight();
            AddRight();
            MoveRight();
            GenerateNewTile();
            Show();
            StackScore.push(UndoScore);
            break;

        case 'q':
            cout << "Are you sure you want to quit??\nEnter y to quit and n to continue!\n"
                 << endl;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                DisplayEnd();
            }
            Show();
            break;

        case 'i':
            Instructions();
            break;
 
        case 'r':
            Restart();
            break;
   
        case 'u':
            if (UndoLimit < 5)
            { 
                if (!UndoStack.empty())
                {
                    vector<vector<int>> previous_copy = UndoStack.top();
                    UndoStack.pop();
                    for (int m = 0; m < 4; m++)
                    {
                        for (int n = 0; n < 4; n++)
                        {
                            Grid[m][n] = previous_copy[m][n];
                        }
                    }
                    TotalScore -= StackScore.top();     
                    StackScore.pop();
                    UndoLimit += 1;
                }
                else
                {
                    cout << "\n\nundo not POSSIBLE, reached initial state!!!\n\n";
                    Show();
                }
            }
            else
            {
                Show();
                cout << "\n\nYou cannot undo the matrix more than 5 times.\n\nSorry!!!\n"
                     << endl;
            }
        }
        int find_max = CalMaximum();
        if (find_max == 2048)
        {
            DisplayWin();
        }

        if (isFULL())
        {
            if (GameOver())
            {
                DisplayLose();
            }
        }
        cout << "enter choice: " << endl;
        cin >> choice;
        while (choice != 'w' && choice != 's' && choice != 'd' && choice != 'a' && choice != 'q' && choice != 'i' && choice != 'u' && choice != 'r')
        {
            cout << "\nYou had entered the wrong choice!\nPlease enter correct choice to continue!" << endl;
            cin >> choice;
        }
    }
}

void Game2048 ::Show()
{ 
    cout << "\n\t\t\t       ::[ 2048 GAME ]::\n\n";
    cout << "\t\t\t\t\t\t Created by: Samridhi Kapoor (2K20/IT/128), Vaishnavi (2K20/IT/159)\n\n";
    cout << "  TotalScore :: " << TotalScore << endl
         << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "\t\t     |";

        for (int j = 0; j < 4; j++)
        {
            if (Grid[i][j])
                printf("%4d    |", Grid[i][j]);
            else
                printf("%4c    |", ' ');
        }

        cout << endl
             << endl;
    }

    cout<<"\n\n Controls (+ :: o)\t\t\t\tu - undo\tr - Restart\n\n\tW\t\t     ^\t\t\ti - Instructions\tq - quit\n\t\t\t\t\t\t\t\t"
		    <<" \n   A    S    D\t\t<    v    >\t\t\t     ."
		    <<" \n\t\t\t\t                             ";
}

int main()
{
    string password = "123";
    string passwordEntry;
    string username;
    int attempts = 1;
    cout<<"\n\t\t\t..........WELCOME..........\n";
    cout<<"\n\t\t\t     ::[ 2048 Game ]::\n"<<endl;
    cout<<"\t\t\tPlease enter your Username: ";
    cin>>username;
    cout << "\t\t\tPlease enter your password: ";
    cin>>passwordEntry;
    cout<<endl;
    
    while ( passwordEntry != password && attempts <=2 )
    {
        cout << "Please try again: ";
        cin>>passwordEntry;
        cout<<endl;
        attempts++;    
    }
    
    if ( passwordEntry == password && attempts <=3 )
    {
        cout << "\n\t\t\t\tACCESS GRANTED!\n\n\t\t------------------------------------------------\n\n";
    }
    else
    {
        cout << "Sorry, only 3 attempts are allowed!";
		exit(0);
    }
    

    Game2048 p;
    srand(time(NULL));
    p.LetsPlay();
    return 0;
}