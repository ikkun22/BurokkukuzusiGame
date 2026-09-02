//フィールドの描画
#include <stdio.h>
#include <conio.h>

 #define FIELD_WIDTH   (14)
 #define FIELD_HEIGHT  (FIELD_WIDTH * 2)
 
 int main(){
 	for (int x = 0; x < FIELD_WIDTH+2; x++)
 	printf("■");
 	printf("\n");
 	
 	for (int y = 0; y < FIELD_HEIGHT; y++){
 		printf("■");
 		for (int x = 0; x < FIELD_WIDTH; x++)
 		printf(" ");
 		printf("■");
 		printf("\n");
 	}
 	
 	for (int x = 0; x < FIELD_WIDTH+2; x++)
 	printf("■");
 	
 	getch();
 }