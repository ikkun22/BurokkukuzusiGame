//É{Å[ÉãÇÃí«â¡
#include <stdio.h>
#include <conio.h>

 #define FIELD_WIDTH   (14)
 #define FIELD_HEIGHT  (FIELD_WIDTH * 2)
 
 int ballX;
 int ballY;
 int ballVelocityX = 1;
 int ballVelocityY = 1;
 
 int main(){
 	for (int x = 0; x < FIELD_WIDTH+2; x++)
 	printf("Å°");
 	printf("\n");
 	
 	for (int y = 0; y < FIELD_HEIGHT; y++){
 		printf("Å°");
 		for (int x = 0; x < FIELD_WIDTH; x++){
 			if((x==ballX)&&(y==ballY))
 			printf("Åú");
 			else
 			printf(" ");
 		}
 		printf("Å°");
 		printf("\n");
 	}
 	
 	for (int x = 0; x < FIELD_WIDTH+2; x++)
 	printf("Å°");
 	
 	getch();
 }