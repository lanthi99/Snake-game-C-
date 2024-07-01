#include <iostream> //iostream is a header file that allows us to use cout and endl
#include <conio.h> //conio.h is a header file that allows us to use _kbhit() and _getch() (collection of windows' console input/output functions)
using namespace std; //using namespace std allows us to use cout and endl without the std:: prefix

//variables for the player
bool gameOver;

//variables for the map
const int width = 20;
const int height = 20;

//variables to keep track of the position of the snake
int x, y;
int tailX[100], tailY[100]; //arrays to keep track of the tail of the snake
int nTail; //length of the tail of the snake

//variables to keep track of the position of the fruit
int fruitX, fruitY, score;

//variable to keep track of the direction of the snake (press keys, change direction of the snake)
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //enum is a user-defined data type that consists of integral constants
eDirection dir; //dir is a variable of type eDirection

void Setup()
{
    gameOver = false;

    //initial direction of the snake
    dir = STOP; //initial direction of the snake is STOP (not moving until we press on arrow keys)

    //initial position of the snake is in the middle of the map
    x = width / 2; //initial position of the snake is in the middle of the map
    y = height / 2; //initial position of the snake is in the middle of the map

    //initial position of the fruit --> random position
    fruitX = rand() % width; //rand() generates a random number between 0 and the width of the map
    fruitY = rand() % height; //rand() generates a random number between 0 and the height of the map
    
    //initial score is 0
    score = 0; 
}

void Draw()
{
    system("clear"); //clear the console

    //display top wall of the map (first row)
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl; //move to the next line

    //display the body of the map
    for (int i = 0; i < height; i++) { //loop through the rows (starting form second row)
        for (int j = 0; j < width; j++) { //loop through the columns in each row
            if (j == 0) { //if column = 0
                cout << "#";
            }

            //display the head of the snake (if i (row) = position y and j (column) = position x of the snake) 
            if (i == y && j == x) {
                cout << "O"; 
            }

            //display the fruit (if i (row) = position of the fruit y and j (column) = position of the fruit x)
            else if (i == fruitY && j == fruitX) {
                cout << "F";
            }

            else {
                bool print = false;
                //draw the tail of the snake
                for (int k = 0; k < nTail; k++){
                    if (i == tailY[k] && j == tailX[k]) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) //if the tail is not printed
                    cout << " "; //empty space
            }            
            if (j == width - 1) //if last column
            {
                cout << "#";
            }
        }
        cout << endl; //move to the next line after each row
    }

    //display bottom wall of the map
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl; //move to the next line
    cout << "Score: " << score << endl; //display the score
}

//function to take input from the user, handling the controls of the snake
void Input() 
{
    //if a key is pressed, change the direction of the snake accordingly to the key pressed
    if (_kbhit()) //return positive number if a key is pressed, return 0 otherwise
    {
       switch (_getch()) { //getch returns the ASCII value of the key that was pressed
            case 'a': //if the key pressed is 'a'
                dir = LEFT; //change the direction of the snake to the left
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'w':
                dir = UP;
                break;
            case 'x':
                gameOver = true;
                break;
       }

        
    }
}

//function to move the snake
void Logic()
{
    int prevX = tailX[0]; //store the previous x position of the snake
    int prevY = tailY[0]; //store the previous y position of the snake
    int prev2X, prev2Y; //store the previous x and y position of the snake
    tailX[0] = x; //so that the tail follows the head
    tailY[0] = y; //so that the tail follows the head

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i]; //store the previous x position of the tail
        prev2Y = tailY[i]; //store the previous y position of the tail
        tailX[i] = prevX; //update the x position of the tail
        tailY[i] = prevY; //update the y position of the tail
        prevX = prev2X; //update the previous x position of the tail
        prevY = prev2Y; //update the previous y position of the tail
    }
    
    //update the position of the snake according to the direction
    switch (dir) //switch statement to change the position of the snake according to the direction
    {
        case LEFT:
            x--; //decrease the x position of the snake by 1
            break;
        case RIGHT;
            x++; //increase the x position of the snake by 1    
            break;
        case UP:
            y--; //decrease the y position of the snake by 1
            break;
        case DOWN:
            y++; //increase the y position of the snake by 1
            break;
        default:
            break;
    }

    //if the snake hits the wall, the game is over
    if (x > width || x < 0 || y > height || y < 0) { //if the snake hits the wall
        gameOver = true;
    }

    //if the snake hits itself, the game is over
    for (int i = 0; i < nTail; i++) { //loop through the tail of the snake
        if (tailX[i] == x && tailY[i] == y) { //if the snake hits itself
            gameOver = true;
        }
    }

    //if the snake eats the fruit, increase the SCORE + generate NEW fruit + increase the tail of the snake
    if (x == fruitX && y == fruitY) {
        //increase the score
        score += 10;

        //generate new fruit
        fruitX = rand() % width;
        fruitY = rand() % height;

        //increase the tail of the snake
        nTail++;

    }

}


int main()
{
    Setup(); //call the setup function to initialize the game
    while (!gameOver) //Game loop, while the game is not over
    {
        Draw(); //call the draw function to display the map
        Input(); //call the input function to handle the controls of the snake
        Logic(); //call the logic function to move the snake
    }
    return 0;
}


