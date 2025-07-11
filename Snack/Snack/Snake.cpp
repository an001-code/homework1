#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <graphics.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

//?????????
#define WIDTH 1040
#define HEIGHT 640
//???????????????
#define SIZE  20
//??????????
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
//???????
#define MAXLEN 1600


typedef struct {
	int x;
	int y;
}SnakeNode;

SnakeNode tmp[MAXLEN];	//???????????????????????????
int speed = 150;		//??????(??????????????)
IMAGE wallImage;       //????
int score=0;	       //????
int difficulty_level = 0;//????????????????
ExMessage msg;     //??????


//?????????
class Snake
{
	friend class Food;
	friend class Wall;
public:
	Snake();					//?????
	void Move();				//???
	void Draw();				//??????
	bool Eat(Food food);	    //?????
	bool Defeat(Wall wall);	//??????
	
private:
	int dirt;					//????
	int length;					//????
	SnakeNode node[MAXLEN];		//?????
	IMAGE ima1, ima2, ima3, ima4, ima5;//?????
};

//??????????
class Food
{
	friend class Snake;
	friend class Wall;
public:
	Food(Snake snake);			//???????
	void Draw();				//???????
private:
	int x, y;					//????
	IMAGE foodImage;
	int food_kind;//???????1-3????????4-9???????10-12????????
};

class Wall
{
	friend class Snake;
	friend class Food;
public:
	Wall(Snake snake,Food food);
	void Draw();
private:
	
	int num;
	SnakeNode wallnode[MAXLEN];
};



void initWall()
{
	loadimage(&wallImage, "wall.png", SIZE, SIZE);
	int wall_x = WIDTH - 260;
	int wall_y = 0;
	while (wall_y <= HEIGHT)
	{
		putimage(wall_x, wall_y, &wallImage);
		wall_y += 20;
	}
}
void printMessage()
{
	char message1[] = "???????????";
	outtextxy(WIDTH-240,20, message1);
	char s1[6];
	sprintf(s1, "%d", score);
	outtextxy(WIDTH - 120,20, s1);//???????

	char message2[] = "??????????????";
	outtextxy(WIDTH - 240, 40, message2);
	char s2[6];
	int _speed = 300 - speed;//??????
	sprintf(s2, "%d", _speed);
	outtextxy(WIDTH - 120, 40, s2);//??????
	//?????????
	char message3[] = "??????????????????";
	outtextxy(WIDTH - 240, 60, message3);
	char message4[] = "??"; char message5[] = "????"; char message6[] = "????";
	outtextxy(WIDTH - 180, 80, message4);
	outtextxy(WIDTH - 180, 100, message5);
	outtextxy(WIDTH - 180, 120, message6);
}


 bool botton()
{


		if (msg.message == WM_LBUTTONDOWN)
		{
			if (msg.x >= WIDTH - 180 && msg.x <= WIDTH - 140 && msg.y >= 80 && msg.y <= 100) {
				difficulty_level = 0;
				return true;
			}
			if (msg.x >= WIDTH - 180 && msg.x <= WIDTH - 140 && msg.y >100 && msg.y <= 120)
			{
				difficulty_level = 2;
				return true;
			}
			if (msg.x >= WIDTH - 180 && msg.x <= WIDTH - 140 && msg.y >120 && msg.y <= 140)
			{
				difficulty_level = 4;
				return true;
			}
		
			return false;
		}
		return false;

}

int main() {
	initgraph(WIDTH, HEIGHT);
	Snake snake;
	
table1:
	Food food(snake);
table2:
	Wall wall(snake, food);
	while (1) {
		BeginBatchDraw();
		FlushBatchDraw();
		while (peekmessage(&msg, EX_MOUSE))//?????????
		{
			if (botton()) goto table2;//??????????????????
		}
		snake.Draw();
		food.Draw();  
		initWall();   
	    wall.Draw();   
		printMessage(); 
		FlushBatchDraw();
		EndBatchDraw();//???????????????????
		if (snake.Eat(food)) {
			goto table1;
		}
		if (snake.Defeat(wall)) {
			break;
		}
		snake.Move(); 
	}
	//?????????
	HWND window = GetHWnd();
	SetWindowText(window, _T("???"));
	MessageBox(window, _T("??????"), _T("???"), MB_OKCANCEL);
	return 0;
}

//???????
Snake::Snake()
{
	this->dirt = RIGHT;
	this->length = 3;
	//?±???0????????????
	for (int i = 0; i < length; i++) {
		this->node[i].x = 60 - ((i + 1) * SIZE);
		this->node[i].y = 0;
	}
	loadimage(&ima1, "snakeHeadUp.png", SIZE, SIZE);
	loadimage(&ima2, "snakeHeadDown.png", SIZE, SIZE);
	loadimage(&ima3, "snakeHeadLeft.png", SIZE, SIZE);
	loadimage(&ima4, "snakeHeadRight.png", SIZE, SIZE);
	loadimage(&ima5, "snakeTail.png", SIZE, SIZE);
}

//???
void Snake::Move() {
	//????????????????
	for (int i = 0; i < this->length; i++) {
		tmp[i].x = this->node[i].x;
		tmp[i].y = this->node[i].y;
	}
	int status = 0;//??????????????????
	if (this->dirt == RIGHT) {
		//?????????
		if (GetAsyncKeyState('W') && status == 0) {
			//this->node[0].y -= SIZE;
			this->dirt = UP;
			status = 1;
		}
		else if (GetAsyncKeyState('S') && status == 0) {
			this->dirt = DOWN;
			status = 1;
		}
		else {
			this->node[0].x += SIZE;
		}
	}
	if (this->dirt == DOWN) {
		//?????????
		if (GetAsyncKeyState('A') && status == 0) {
			//this->node[0].x -= SIZE;
			this->dirt = LEFT;
			status = 1;
		}
		else if (GetAsyncKeyState('D') && status == 0) {
			this->node[0].x += SIZE;
			this->dirt = RIGHT;
			status = 1;
		}
		else {
			this->node[0].y += SIZE;
		}
	}
	if (this->dirt == LEFT) {
		//?????????
		if (GetAsyncKeyState('W') && status == 0) {
			//this->node[0].y -= SIZE;
			this->dirt = UP;
			status = 1;
		}
		else if (GetAsyncKeyState('S') && status == 0) {
			this->node[0].y += SIZE;
			this->dirt = DOWN;
			status = 1;
		}
		else {
			this->node[0].x -= SIZE;
		}
	}
	if (this->dirt == UP) {
		//?????????
		if (GetAsyncKeyState('A') && status == 0) {
			this->node[0].x -= SIZE;
			this->dirt = LEFT;
			status = 1;
		}
		else if (GetAsyncKeyState('D') && status == 0) {
			this->node[0].x += SIZE;
			this->dirt = RIGHT;
			status = 1;
		}
		else {
			this->node[0].y -= SIZE;
		}
	}
	//???
	for (int i = 1; i < this->length; i++) {
		this->node[i].x = tmp[i - 1].x;
		this->node[i].y = tmp[i - 1].y;
	}
	Sleep(speed);
}

//??????
void Snake::Draw() {
	cleardevice();//?????????
	for (int i = 0; i < this->length; i++) {
		if (i == 0) {
			if (this->dirt == UP) { putimage(this->node[i].x, this->node[i].y, &ima1); }
			else if (this->dirt == DOWN) { putimage(this->node[i].x, this->node[i].y, &ima2); }
			else if (this->dirt == LEFT) { putimage(this->node[i].x, this->node[i].y, &ima3); }
			else  { putimage(this->node[i].x, this->node[i].y, &ima4); }
	}
		else {
			putimage(this->node[i].x, this->node[i].y, &ima5);
		}
	}
	
}



//?????
bool Snake::Eat(Food food) {
	if (food.x == this->node[0].x && food.y == this->node[0].y) {
		if (food.food_kind >=9 ) { 
			if(speed>20) speed -= 20; 
			score += 30; 
		}
		else if (food.food_kind <=2) { speed += 20; score += 10; }
		else { score += 20; }

		if (this->node[length - 1].x - this->node[length - 2].x == 0 && this->node[length - 1].y - this->node[length - 2].y == -20) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x;
			this->node[length - 1].y = this->node[length - 2].y - SIZE;
		}
		else if (this->node[length - 1].x - this->node[length - 2].x == 0 && this->node[length - 1].y - this->node[length - 2].y == 20) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x;
			this->node[length - 1].y = this->node[length - 2].y + SIZE;
		}
		else if (this->node[length - 1].x - this->node[length - 2].x == 20 && this->node[length - 1].y - this->node[length - 2].y == 0) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x + SIZE;
			this->node[length - 1].y = this->node[length - 2].y;
		}
		else /*(this->node[length - 1].x - this->node[length - 2].x == -20 && this->node[length - 1].y - this->node[length - 2].y == 0)*/ {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x - SIZE;
			this->node[length - 1].y = this->node[length - 2].y;
		}

		return true;
	}
	return false;
}

//??????
bool Snake::Defeat(Wall wall) {
	//1.???????
	if (this->node[0].x < 0 || this->node[0].x >= WIDTH-280 || this->node[0].y < 0 || this->node[0].y >= HEIGHT) {
		return true;
	}
	//2.?????????????
	for (int i = 1; i < this->length; i++) {
		if (this->node[0].x == this->node[i].x && this->node[0].y == this->node[i].y) {
			return true;
		}
	}
	//3.?????????
	if (difficulty_level)
	{
		for (int i = 0; i < wall.num-1; i++) {
			if (this->node[0].x == wall.wallnode[i].x && this->node[0].y == wall.wallnode[i].y) {
				return true;
			}
		}
	}
	return false;
}

//????????
Food::Food(Snake snake)
{
	loadimage(&foodImage, "china.png", SIZE, SIZE);
table:
	srand((unsigned)time(NULL));
	this->x = (rand() % ((WIDTH-280) / SIZE)) * SIZE;
	this->y = (rand() % (HEIGHT / SIZE)) * SIZE;
	
	for (int i = 0; i < snake.length; i++) {
		if (snake.node[i].x == this->x && snake.node[i].y == this->y) {
			goto table;
		}
	}
	this->food_kind = rand() % 12 + 1;//??????????????
}

//???????
void Food::Draw() {
	putimage(this->x, this->y, &foodImage);
}

//??????????
Wall::Wall(Snake snake, Food food) {
	this->num = difficulty_level * 10 + 1;

	// ?????????????
	if (difficulty_level >= 2) {
		MazeGenerator mg(WIDTH - 280, HEIGHT, SIZE);
		std::vector<SnakeNode> maze = mg.generate();

		int i = 0;
		for (auto& node : maze) {
			if (i >= MAXLEN) break;
			bool conflict = false;
			for (int j = 0; j < snake.length; j++) {
				if (snake.node[j].x == node.x && snake.node[j].y == node.y) {
					conflict = true;
					break;
				}
			}
			if (node.x == food.x && node.y == food.y) conflict = true;

			if (!conflict) {
				wallnode[i++] = node;
			}
		}
		num = i;
	} else {
		// ????
		for (int i = 0; i < num - 1; i++) {
			// ???????
		}
	}
}

//?????????
void Wall::Draw()
{
	for (int i = 0; i < num-1; i++)
	{
		putimage(this->wallnode[i].x, this->wallnode[i].y, &wallImage);
	}
}