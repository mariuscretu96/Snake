#include <conio.h>
#include <windows.h>
#include <SFML/Graphics.hpp>
using namespace sf;
bool gOver = true;
bool snake = true;
const int width = 30;
const int height = 20;
const int lenght=30; //definire dimensiuni harta

int x, y, fruitX, fruitY, speedX, speedY, score;

int tailX[100], tailY[100];
int nTail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

//prestabilire valori incepere joc
void Setup()
{
	gOver = false;
	dir = STOP;
	x = (lenght * width) / 2;
	y = (lenght * height) / 2;
	fruitX = rand() % ( lenght * width );
	fruitY = rand() % ( lenght * height );
	score = 0;
}
//imput tastatura
void Draw()
{
    RenderWindow window(VideoMode(width*lenght, height*lenght), "SNake - Marius Cretu!");
    Texture t1,t;
    t1.loadFromFile("images/fundal2.jpg");
    t.loadFromFile("images/sarpe.png");

    Sprite sprite1(t1);
    Sprite sprite(t);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(sprite1);
        for (int i = 0; i < lenght * height; i++)
        {
            for (int j = 0; j < lenght * width; j++)
            {
                if (i == y && j == x){
                    sprite.setPosition(i , j);
                    window.draw(sprite);
                }
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            sprite.setPosition(i , j);
                            window.draw(sprite);
                            print = true;
                        }
                    }
                }
            }
        }
    window.display();
    }
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	} //implementare coada snake


	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gOver = true;
			break;
		}
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1; //teleportare pe partea opusa

    //suicide
	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y) // daca coada se intalneste cu capul sarpelui
			{gOver = true;}

    //trecere peste fruct
	if (x == fruitX && y == fruitY)
	{
		score += 10; //incrementare scor;
		fruitX = rand() % width;
		fruitY = rand() % height; //spamare fruct
		nTail++; //crestere lungime coada
	}

}

void Play()
{
    Setup();
    while(snake)
    {
        Draw();
        Logic();
    }
}



int main()
{
    Play();
    return 0;
}
