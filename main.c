#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH  480
#define WINDOW_HEIGHT 480
#define BLOCK_SIZE 20
#define PLAYER_SIZE 16

void drawRect(int x, int y, int w, int h){
	glBegin(GL_QUADS); //glColor3f( (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f); printf("%f\n", x);
	glVertex2f(x, y);
	glVertex2f(x, y+h);
	glVertex2f(x+w, y+h);
	glVertex2f(x+w, y);
	glEnd();
}

int grid[WINDOW_WIDTH/BLOCK_SIZE][WINDOW_HEIGHT/BLOCK_SIZE];

void initGrid(){
	for(int x = 0; x < WINDOW_WIDTH/BLOCK_SIZE; x++){
		for(int y = 0; y < WINDOW_HEIGHT/BLOCK_SIZE; y++){
			grid[x][y] = 0;
		}
	}
}

void drawMap(){
	glPushMatrix();
	//glTranslatef(-1.0f, x, 0.0f);
	glColor3f(1.0f, 0.0f, 1.0f);
	for(int x = 0; x < WINDOW_WIDTH/BLOCK_SIZE; x++){
		for(int y = 0; y < WINDOW_HEIGHT/BLOCK_SIZE; y++){
			switch(grid[x][y]){
				case 0:
					glColor3f(0.3f, 0.05f, 0.0f);
					break;
				case 1:
					glColor3f(0.0f, 0.15f, 0.0f);
					break;
			}
			//glColor3f( (float)x*BLOCK_SIZE/WINDOW_WIDTH, 0.0f, 0.0f );
			drawRect(x*BLOCK_SIZE, y*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
		}
	}
	glPopMatrix();
}

typedef struct{
	int x,y;
	//Player(int ax,int ay) : x(ax), y(ay) { }
} Player;

int main(){
	if(!glfwInit()){
		printf("Error killing nibbies!\n");
		return 1;
	}
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "cringe", NULL, NULL);
	glfwMakeContextCurrent(window);
	if(glewInit() != GLEW_OK){
		printf("Error initializing GLEW\n");
		return 1;
	}
	glOrtho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, 0.0f, 10.0f);

	initGrid(grid);

	Player player = {4, 3};
	

	int keywait = 0;
	int keywaitmax = 5;
	int moved = 0;
	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.3f, 0.05f, 0.0f, 1.0f);
		if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS){
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		if(keywait == 0){
			if(!keywait)
			if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
				player.y += 1;
				keywait++;
			}
			if(!keywait)
			if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
				player.y -= 1;
				keywait++;
			}
			if(!keywait)
			if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
				player.x -= 1;
				keywait++;
			}
			if(!keywait)
			if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
				player.x += 1;
				keywait++;
			}
		}else{
			keywait++;
			if(keywait > keywaitmax){
				keywait = 0;
			}
		}
		float z = -1.5f + glfwGetTime() * 0.1f;
		printf("%f\n", z);
		drawRect(player.x*BLOCK_SIZE + (BLOCK_SIZE-PLAYER_SIZE)/2, player.y*BLOCK_SIZE + (BLOCK_SIZE-PLAYER_SIZE)/2, PLAYER_SIZE, PLAYER_SIZE);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
