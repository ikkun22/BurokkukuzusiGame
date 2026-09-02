//ƒpƒhƒ‹‚Ì’Ç‰Á
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

 #define FIELD_WIDTH   (14)
 #define FIELD_HEIGHT  (FIELD_WIDTH * 2)
 #define FPS           (10)
 #define INTERVAL     (1000 / FPS)
 #define PADDLE_WIDTH   (4)
 
 int ballX;
 int ballY;
 int ballVelocityX = 1;
 int ballVelocityY = 1;
 
 int paddleX=(FIELD_WIDTH - PADDLE_WIDTH)/2;
 int paddleY=FIELD_HEIGHT-3;
 
 int main(){
 	clock_t lastClock = clock();
 	while(1){
 		clock_t nowClock = clock();
 		if(nowClock >= lastClock + INTERVAL){
 			ballX += ballVelocityX;
 			ballY += ballVelocityY;
 			
 			if(ballX <= 0)
 			ballVelocityX = 1;
 			
 			if(ballX >= FIELD_WIDTH - 1)
 			ballVelocityX = -1;
 			
 			if(ballY <= 0)
 			ballVelocityY = 1;
 			
 			if(ballY >= FIELD_HEIGHT - 1)
 			ballVelocityY = -1;
 			
 		system("cls");
 	for (int x = 0; x < FIELD_WIDTH+2; x++)
 	printf("¡");
 	printf("\n");
 	
 	for (int y = 0; y < FIELD_HEIGHT; y++){
 		printf("¡");
 		for (int x = 0; x < FIELD_WIDTH; x++){
 			if((x==ballX)&&(y==ballY))
 			printf("œ");
 			else if((y==paddleY)&&(x>=paddleX)&&(x<paddleX+PADDLE_WIDTH))
 			printf("¡");
 			else
 			printf(" ");
 		}
 		printf("¡");
 		printf("\n");
 	}
 	
 	for (int x = 0; x < FIELD_WIDTH+2; x++)
 	printf("¡");
 			
 			lastClock = nowClock;
 		}
 	}
 	getch();
 }