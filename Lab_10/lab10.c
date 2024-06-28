#include "apue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

void put_pull_rod(int signum);
void fish_eating();
void exit_game(int signum);

int fishNum = 0;	// counting fish number
int eat = 0;	// used as a boolean
int state = 0;  // control round
int backup = 0; // store the dtat before put rod

int main(void){
	
	
	struct sigaction sig_put_pull_rod;
	sig_put_pull_rod.sa_handler = put_pull_rod;
	
	sigemptyset (&sig_put_pull_rod.sa_mask);
	sig_put_pull_rod.sa_flags = 0;
	sigaction (SIGINT, &sig_put_pull_rod, NULL);
	
	struct sigaction sig_exit_game;
	sig_exit_game.sa_handler = exit_game;
	
	sigemptyset (&sig_exit_game.sa_mask);
	sig_exit_game.sa_flags = 0;
	sigaction (SIGTSTP, &sig_exit_game, NULL);

	struct sigaction sig_fish_eating;
	sig_fish_eating.sa_handler = fish_eating;
	
	sig_fish_eating.sa_flags = 0;
	sigaction (SIGALRM, &sig_fish_eating, NULL);
	
	
	while (1){
		if (state == 0) {	
			if (backup == fishNum && eat) printf("The bait was eaten!!\n");
			else if (backup != fishNum && eat) {
				printf("Catch a Fish!!\n");
				printf("Totally caught fishes: %d\n", fishNum);
			}
			printf("Fishing rod is ready!\n"); 
			eat = 0;
			backup = fishNum;
			state = -1;
		}
	}

		

	return 0;
}


void put_pull_rod(int signum){
	static int call = 0;
	srand(time(NULL));
	if (call == 0) {	//first call
		printf("\nPut the fishing rod \n"); 
		state = -1;
		sleep(1);	//wait one second
		printf("Bait into water, waiting fish...\n");
		alarm( 2+rand()%5 ); //time domain 2 ~ 7
		call = 1;
	}		
	else {	//second call
		call = 0; 
		printf("\nPull the fishing rod \n");
		alarm(0);
		state = 0;
	}
}

void fish_eating() {
	if (eat == 0 ) { //first call
		printf("A fish is biting,pull the fish rod \n");
		eat = 1;
		fishNum++;
		alarm(5);	//player shold pull his rod in 5 sec, otherwise fish escaped
	}
	else { //second call
		printf("The fish was escaped!!\n");
		fishNum = backup; 	//the fishNum is same as previous state
	}
}

void exit_game(int signum){
	printf("\nTotally caught fishes: %d\n", backup); // avoid exit during fishing
	exit(0);
}

