/********DO NOT MODIFY THIS SECTION************
 * 
 * EECS 22 : Advanced C Programming
 * Winter 2020, Prof. Quoc-Viet Dang
 * 
 * HW1  : Bingo Simulator
 * Template file : Bingo.c
 * 
 * Created on Jan 5, 2020, 10:56 PM by Bo Tsai <bo.tsai@uci.edu>
 */
/**********************************************
 
// Enter your name, last name and UCInet ID below://
 * 
 * *****************************
 * First Name : Allison 
 * Last Name: Cornell
 * UCInet ID: 33917133
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*Declare your function definitions in the section below*/
/*You may add other functions if needed*/
/*********************************************************/



/*********************************************************/

/*Declare your global variables below (if any)*/
/**************************************************/



/**************************************************/

/*Colors (you can add or remove from this list*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


/*Main function*/
int main(int argc, char** argv) {
int numplayers;
int sizeboard;
char name[numplayers][64];
char tempname[64];
int i,j,k,m,n,q,p;
FILE *myfile;
myfile = fopen("BingoSampleInput1.txt", "r");
if(myfile == NULL){
    fprintf(stderr, "File BingoSampleInput1.txt cannot be opened\n");
    exit(1);
    }
fscanf(myfile, "%d %d", &numplayers, &sizeboard); /*read file to get number of players and size of the board*/
printf("Start the game\n");
int board[numplayers][sizeboard][sizeboard];
for(i=0; i<numplayers; i++){
    fscanf(myfile, "%s", tempname);
    strcpy(name[i], tempname);
    printf("***%s***\n", name[i]);
    for(j=0; j<sizeboard; j++){
        for(k=0; k<sizeboard; k++){
            fscanf(myfile, "%d", &board[i][j][k]);
            printf("%d ", board[i][j][k]);
        }
        printf("\n");    
    }
}
int callersize;
callersize = sizeboard * sizeboard;
int caller[callersize];

for(m=0; m<callersize; m++){
    fscanf(myfile, "%d", &caller[m]);
    }
    printf("\n");
/*game simulation starts*/
int checked[numplayers][sizeboard][sizeboard];
int checknames[numplayers];
int colors[numplayers][sizeboard][sizeboard];
int colors1[numplayers][sizeboard][sizeboard];
int win = 0;
int win1 = 0;
int win2 = 0;
int win3 = 0;

for(int i=0;i<numplayers;i++){ /*initialize checknames, colors, and colors1 as 0*/
    checknames[i]=0;  
    for(int d=0; d<sizeboard; d++){
        for(int e=0; e<sizeboard; e++){
            colors[i][d][e]=0;
            colors1[i][d][e]=0;
        }
    }
}
for(n=0; n<callersize; n++){ /*goes through all of the called numbers*/
    printf("Caller called: %d\n", caller[n]);
    for(i=0; i<numplayers; i++){ /*goes through each player*/
        for(q=0; q<sizeboard; q++){ /*nested for loops will check through each players entire board*/
            for(p=0; p<sizeboard; p++){
                if(caller[n] == board[i][q][p]){ /*if the number called is in the players board then*/

                    checked[i][q][p] = 1; /*mark of same position in checked*/
                }
            }
           
        }
        
        /*check all cases for a win if someone wins*/
        for(j=0; j<sizeboard; j++){ /*check rows*/
            win = 0;
            for(k=0; k<sizeboard; k++){
                if(checked[i][j][k] == 1){
                    win = win +1;
                }
                if(win == sizeboard){
                    k = sizeboard;
                    j = sizeboard;
                    checknames[i] = 1;
              
                }
            }
        }
        for(j=0; j<sizeboard; j++){ /*checks columns*/
            win1 = 0;
            for(k=0; k<sizeboard; k++){
                if(checked[i][k][j] == 1){
                    win1 = win1 +1;
                }
                if(win1 == sizeboard){
                    k = sizeboard;
                    j = sizeboard;
                    checknames[i] = 1;
                }
            }
        }
	win2 = 0;
        for(j=0; j<sizeboard; j++){ /*checks first diagonal*/
                if(checked[i][j][j] == 1){
                    win2 = win2 +1;
                }
                if(win2 == sizeboard){
                    j = sizeboard;
                    checknames[i] = 1;
                }
            
        }
        int j=0;
        int k = sizeboard - 1;
        win3 = 0;
        while (j<sizeboard && k>=0){ /*checks second diagonal*/
            if(checked[i][j][k] == 1){
                    win3 = win3 +1;
                }
                if(win3 == sizeboard){
                    k = sizeboard;
                    j = sizeboard;
                    checknames[i] = 1;
                }
            k--;
            j++;
        }
        
        if(checknames[i] == 1){ /*if the player wins*/
            printf("***%s Bingo!***\n", name[i]); /*print their name with bingo*/
            for(int x=0; x<sizeboard; x++){
                for(int y=0; y<sizeboard; y++){ /*and print their board with the appropriate colors*/
                   if(colors[i][x][y]==1){ /*if was previously called print number in red*/
                        printf("\x1B[31m");
                        printf("%d ", board[i][x][y]);
                        printf("\x1B[37m");
                    }
                    
                    else if(caller[n]==board[i][x][y]){ /*if currently being called print in green*/
                        printf("\x1B[32m");
                        printf("%d ", board[i][x][y]);
                        printf("\x1B[37m");
                        colors[i][x][y] = 1;
                    }
                   else{
                    printf("%d ", board[i][x][y]);   
                   } 
                }
                printf("\n");
            }
        }
	else
        { 
            printf("***%s***\n", name[i]); /*if they don't win print their name*/
            for(q=0; q<sizeboard; q++){
                for(p=0; p<sizeboard; p++){ /*and print their board with appropriate colors*/
                    if(colors1[i][q][p]==1){ /*if was previously called print number in red*/
                        printf("\x1B[31m");
                        printf("%d ", board[i][q][p]);
                        printf("\x1B[37m");
                    }
                    else if(caller[n]==board[i][q][p]){/*if currently being called print in green*/
                        printf("\x1B[32m");
                        printf("%d ", board[i][q][p]);
                        printf("\x1B[37m");
                        colors1[i][q][p] = 1;
                        colors[i][q][p] = 1;
                    }
                    else{
                    printf("%d ", board[i][q][p]);   
                   } 
                }
                printf("\n");
            }
        }

    }
    for(int b=0; b<numplayers; b++){ /*keeps from calling the next number if a player wins*/
        if(checknames[b] == 1){
        printf("The game result:\n"); /*prints the game result*/
        printf("%d ", caller[n]);
        n = callersize;
        break;
        }
    }
}
for(int r=0; r<numplayers; r++){ /*prints the name of the player(s) who won*/
    if(checknames[r]==1){
        printf("%s ", name[r]);
    }
}
return 0;
}







