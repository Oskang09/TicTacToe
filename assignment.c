#include <stdio.h>
#include <string.h>
/*
	Created by Multimedia University Student 
	ID - 1171200356 Name - NG SZE CHEN ( Github - https://github.com/Oskang09 )
	ID - 1171200748 Name - LEE WANG LIN
	ID - 1171200839 Name - TIN CU KANG
	
	Assignment 2 for Trimester 2, Session 2017/2018 DCS5038 Program_Design
*/
void displayBoard(char charray[9], char ptn[2], char name[2][20], int round)
{
	int i;
	printf("\n\n\tTic Tac Toe ( Round - %d )\n\n", round);
    printf("Player %s (%c)  -  Player %s (%c)\n\n\n", name[0], ptn[0], name[1], ptn[1]);
	
	printf("     |     |     \n");
	for (i = 1; i < 10; i++)
	{
		if (i % 3 != 0)
		{
			printf("  %c  |", charray[i - 1]);
		}
		else
		{
			printf("  %c \n", charray[i - 1]);
			if (i != 9)
			{
				printf("_____|_____|_____\n");
			}
    		printf("     |     |     \n");
		}
	}
}
int winner(char board[9], char ptn[2])
{
	int array[5] = 
	{
		0,1,2,3,6
	};
	int hasWinner = -1;
	int i;
	
	for (i = 0; i < sizeof(array) ; i++)
	{
		if (board[i] == '-')
		{
			continue;
		}
		if (i == 0 || i == 3 || i == 6)
		{
			if (board[i] == board[i + 1] && board[i + 1] == board[i + 2])
			{
				hasWinner = i;
				break;
			}
		}
		if (i == 0 || i == 1 || i == 2)
		{
			if (board[i] == board[i + 3] && board[i + 3] == board[i + 6])
			{
				hasWinner = i;
				break;
			}
		}
		if (i == 0)
		{
			if (board[i] == board[i + 4] && board[i + 4] == board[i + 8])
			{
				hasWinner = i;
				break;
			}
		}
		if (i == 2)
		{
			if (board[i] == board[i + 2] && board[i + 2] == board[i + 4])
			{
				hasWinner = i;
				break;
			}
		}
	}
	if (hasWinner != -1)
	{
		for (i = 0; i < 2; i++)
		{
			if (board[hasWinner] == ptn[i])
			{
				return i + 1;
			}
		}
	}
	return 0;	
}
int tictactoe(char name[2][20], char ptn[2], int ro)
{	
	int round = 0;
	int current = 0;
	int slot;
	
	char board[9] = 
	{
		'-', '-', '-',
		'-', '-', '-',
		'-', '-', '-'
	};
	
	while (round < 10)
	{
		if (round == 9)
		{
			displayBoard(board, ptn, name, ro);
			printf("\n\nThat was a draw in round %d", ro);
			return 0;
		}
		else
		{
			current = current % 2 + 1;
			printf("\n");
			
			displayBoard(board, ptn, name, ro);
			
			int isSet;
			do 
			{
				fflush(stdin);
				printf("\nPlayer %s, please enter the slot ( 1 - 9 ) you want to place your %c : ", name[current - 1], ptn[current - 1]);
				scanf("%d", &slot);
				if (slot > 0 && slot < 10)
				{
					if (board[slot - 1] == '-')
					{
						board[slot - 1] = ptn[current - 1];
						isSet = 1;
					}
					else
					{
						int i;
						for (i = 0; i < 2; i++)
						{
							if (board[slot - 1] == ptn[i])
							{
								printf("\nSlot %d has been set with %c by %s", slot, board[slot - 1], name[i]);
							}
						}
						isSet = 0;
					}
				}
				else
				{
					printf("\nPlease insert integer between 1 - 9 !");
					isSet = 0;
				}
			}
			while (isSet == 0);
		}
		round++;
		if (round >= 3)
		{
			int win = winner(board, ptn);
			if (win != 0)
			{
				displayBoard(board, ptn, name, ro);
				printf("\n\nPlayer %s has win round %d with pattern '%c'", name[win - 1], ro, ptn[win - 1]);
				return win;
			}
		}
	}
}
char * winMessage(int num)
{
	switch (num)
	{
		case 1:
			return "Well Played!";
		case 2:
			return "Good Game!";
		case 3:
			return "GGWP!";
		case 4:
			return "GGEZ!";
	}
}
int main()
{
	char option;
	char name[2][20];
	char ptn[2];
	
	int i = 0;
	
	int round = 0;
	int round_player_winned[2] = 
	{
		0,0
	};
	int round_winner = -1;
	char winner_name[20];
	char loser_name[20];
	
	int selector;
	
	
    printf("\tTic Tac Toe\n\n");

	for (i = 0; i < 2; i++)
	{
		fflush(stdin);
		for (;;)
		{
			printf("Please insert player %d name : ", i + 1);
			gets(name[i]);
			if (i == 1 && strcmp(name[i] , name[i - 1]) == 0)
			{
				printf("\nYou cant use the same name with other player!\n\n");
				continue;
			}
			break;
		}
		for (;;)
		{
			printf("Please insert player %d tic pattern (etc X, O, Z, A) : ", i + 1);
			fflush(stdin);
			scanf("%c", &ptn[i]);
			if (i == 1 && ptn[i] == ptn[i - 1])
			{
				printf("\nYou cant use the same tic pattern with other player!\n\n");
				continue;
			}
			printf("\nPlayer %d's Name : %s    |    Player %d's Tic Pattern : %c\n\n", i + 1, name[i], i + 1, ptn[i]);
			break;
		}
	}
	
	do
	{
		round++;
		
		int temp = round_winner;
		round_winner = tictactoe(name, ptn, round);
		
		round_player_winned[round_winner - 1] += 1;
		strcpy(winner_name, (char *)name[round_winner - 1]);
		if (round_winner > 0 && temp > 0)
		{
			strcpy(loser_name, (char *)name[temp - 1]);
			
			if (temp == round_winner)
			{
				printf("\n%s has a win streak", winner_name);
			}
			else
			{
				round_winner = -2;
				printf("\n%s has break %s's win streak!", winner_name, loser_name);
			}
		}
		if (round_winner > 0 || round_winner == -2)
		{
			for (;;)
			{
				printf("\n\n%s select your win message ( 1 - 4 ) : ", winner_name);
				scanf("%d", &selector);
				if (selector > 0 && selector < 5)
				{
					break;
				}
				printf("\n%s : Wrong number select!\n", winner_name);
			}
			
			printf(winMessage(selector));
		}
	
		printf("\n\nDid you want to continue next round? ( Y = Continue ) : ");
		fflush(stdin);
		scanf("%c", &option);
	}
	while (option == 'Y' || option == 'y');
	
    printf("\n\n\tTic Tac Toe\n\n");
    
    printf("Rounds played : %d", round);
    for (i = 0; i < 2; i++)
    {
 	   printf("\nPlayer %s won rounds : %d", name[i], round_player_winned[i]);
	}
	printf("\nDraw rounds : %d", round - (round_player_winned[0] + round_player_winned[1]));
	return 0;
}

