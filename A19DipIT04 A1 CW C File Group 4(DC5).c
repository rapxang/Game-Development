#include <stdio.h>
//using structure to save players detail
struct players{
	char playername[20];
	int gameplayed;
};
enum { FALSE, TRUE };
enum { EMPTY, TIGER, GOAT };

int position_ok(x,y){return 0<=x && x<5 && 0<=y && y<5;}

void print_board(int board[5][5]){

	printf("welcome to the game\n");
  int x,y;
  for(y=0;y<5;y++){
    if(y==0) printf("  0 1 2 3 4\n");
    printf("%d ",y);
    for(x=0;x<5;x++){
      switch(board[y][x]){
      case EMPTY:
        printf("_");
        break;
      case TIGER:
        printf("T");
        break;
      case GOAT:
        printf("G");
        break;
      default:
        fprintf(stderr, "Position is not valid!");
        break;
      }
      printf(" ");
    }
    printf("\n");
  }
  fflush(stdin);
}
//code to select the position to put goats
void put_goat(int board[5][5]){
  printf("select the position to put your goat\n");
  fflush(stdin);
  int x, y;
  while(TRUE){
    scanf("%d %d",&y,&x);
    if(position_ok(x,y)){
      if(board[y][x]==EMPTY) break;
      else printf("that position already exists animal!\n");
    }else printf("position is invalid!\n");
    printf("please position to put goat\n");
    fflush(stdin);
  }
  board[y][x]=GOAT;
  print_board(board);
}
//codes to select the position and move the tigers
void move_tiger(int board[5][5]){
  printf(" select the tiger to move\n");
  int x, y;
  while(TRUE){
    scanf("%d %d",&y,&x);
    if(position_ok(x,y)){
      if(board[y][x]==TIGER) break;
      else printf("doesn't exists tiger that position!\n");
    }else printf("position is invalid!\n");
    printf("select the tiger position");
    fflush(stdin);
  }
  printf("please select the direction to move your  tiger\n");
  int dx,dy,next_x,next_y,eat_goat=FALSE;
  while(TRUE){
    scanf("%d %d",&dy,&dx);
    if(dx!=0 && dy!=0 && ((x-y)%2)!=0){
      printf("you can't move that direction!\n");
    }else{
      next_x=x+dx;
      next_y=y+dy;
      if(position_ok(next_x,next_y)){
        if(board[next_y][next_x]==EMPTY) break;
        else if(board[next_y][next_x]==GOAT) {
          next_x=next_x+dx;
          next_y=next_y+dy;
          if(position_ok(next_x,next_y)){
            if(board[next_y][next_x]==EMPTY){
              eat_goat=TRUE;
              break;
            }
          }
        }
      }
      printf("you can't move tiger there!\n");
    }
    printf("please select the  direction to move tiger\n");
    fflush(stdin);
  }
  board[y][x]=EMPTY;
  board[next_y][next_x]=TIGER;
  if(eat_goat)board[y+dy][x+dx]=EMPTY;
  print_board(board);
}

void main()
{
	//creating a file to save the details of a player
	printf("Please Enter the Player Details to save\n");
    struct players p;
    FILE *a;
    a= fopen("players.txt", "w");
    printf("Enter the Player Name\n");
    gets(p.playername);
    printf("Enter the number of game played\n");
    scanf("%d",&p.gameplayed);
    fprintf(a,"Player Name= %s \n Game Played= %d", p.playername, p.gameplayed);
    fclose(a);
{

	//switch case to select the options
	printf("TRAP THE TIGERS\n");
	int a;
	printf("1--new game\n");
	printf("2--continue\n");
	printf("3--instructions\n");
	printf("4--exit\n");
	printf("enter the character\n");
	scanf("%d",&a);
	switch(a)
	{
		case 1:
		printf("new game\n");
		break;
		case 2:
		printf("continue\n");
		break;
		case 3:
		printf("Command the position of the goats and tiger in binary form.(rows*column). example-0 press enter 0,1 press enter 1.\n You are suppose to trap the tigers to its non movable place to win the game.\n GOOD LUCK!\n");
		break;
		case 4:
		printf("THANK YOU FOR PLAYING!\n");
		fclose(a);
		break;
		default:
		printf("you entered wrong character\n");
	}
  int remaining_goat=20;
  int board[5][5];
  int x, y;
  for(y=0;y<5;y++){
    for(x=0;x<5;x++){
      board[y][x]=EMPTY;
      if( ((x==0)||(x==4))&&((y==0)||(y==4)) ){
        board[y][x]=TIGER;
      }
    }
  }
  //code that shows the remaining goats after each move of goats
 print_board(board);
  while(remaining_goat!=0){
    put_goat(board);
    remaining_goat--;
    printf("remaining goat is: %d\n",remaining_goat);
    move_tiger(board);
}
}
}


