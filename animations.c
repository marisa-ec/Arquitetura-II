#include <ncurses.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>


void *preencher_matriz(char *animation, int animacao[][16][10]);


int cores[8] = { COLOR_WHITE,
	             COLOR_RED,
	             COLOR_GREEN,
	             COLOR_YELLOW,
	             COLOR_BLUE,
	             COLOR_MAGENTA,
	             COLOR_CYAN,
	             COLOR_BLACK};

int main(int argc, char *argv[])
{
	initscr();
	curs_set(0);
	cbreak();
	noecho();
	nodelay(stdscr, TRUE); 
	keypad(stdscr,TRUE);
	start_color();
	int quant = 5;
	for (int i = 1; i < 8; ++i)
		init_pair(i, cores[i], cores[0]);
	bkgd(COLOR_PAIR(1));
	int animacao[15][16][10];
	int i, j, k;
	preencher_matriz(argv[1], animacao);
	while(quant)
	{
		for (i = 0; i < 15; ++i)
		{ 
			for (j = 0; j < 16; ++j)
			{
				for (k = 0; k < 10; ++k)
				{
					move(j, k);
					if(animacao[i][j][k] == 0)
						printw(" ");	
					else
					{
						attron(COLOR_PAIR(animacao[i][j][k]));
						printw("#");
						attroff(COLOR_PAIR(animacao[i][j][k]));
					}
				}
			}
			refresh();
			sleep(1);
		}
		quant --;
	}	

	endwin();

	return 0;
}


void *preencher_matriz(char *animation, int animacao[][16][10])
{
	int i, j, k;
	int d;
	FILE *file;
	file = fopen(animation, "r");
	if (!file)
		printf("Error ao abrir arquivo!\n");
	
	//while(fscanf(file, "%s", &led) != EOF)
	//{
		
			for (i = 0; i < 15; ++i)
			{ 
				for (j = 0; j < 16; ++j)
				{	
					for (k = 0; k < 10; ++k)
					{
						fscanf(file, "%1d", &d);
						animacao[i][j][k] = d;
					}
				}
			}					
	//}

	fclose(file);


}
