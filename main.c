/*
	author : Marijn J. Werbrouck
	I use *.xbm files as bitmaps
	(make sure your bitmaps have a width of a multiple of 8)
*/

#include <stdio.h>
#include "pattern1.xbm"
#include "pattern2.xbm"
#include "pattern3.xbm"
#include "pattern4.xbm"

#define NEURONS 64

int weights[NEURONS][NEURONS];
int recognize[NEURONS];
int pat1[NEURONS];
int pat2[NEURONS];
int pat3[NEURONS];

void update_neuron(int x){
	int i = 0;
	int j = 0;
	while(i < NEURONS){
		j += weights[i][x] * recognize[i];
		i++;
	}
	if(j < 0){
		recognize[x] = 0;
	} else {
		recognize[x] = 1;
	}
}

void insert_img(int *pattern, char *x_bits){
	int i = 0;
	int j = 0;
	while(i < NEURONS / 8){
		int i1 = 128;
		int j1 = 7;
		while(i1 >= 1){
			if(x_bits[i] >= i1){
				x_bits[i] -= i1;
				pattern[j + j1] = 1;
			}
			i1 /= 2;
			j1--;
		}
		j += 8;
		i++;
	}
}

void train(int *pattern){
	int i = 0;
	int j = 0;
	while(i < NEURONS){
		while(j < NEURONS){
			if(i != j){
				weights[i][j] += (2 * pattern[i] - 1) * (2 * pattern[j] - 1);
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void print_pat(int *pattern){
	int i = 0;
	while(i < NEURONS){
		if(i % 8 == 0){
			printf("\n");
		}
		if(pattern[i] == 1){
			printf("  ");
		} else {
			printf("[]");
		}
		i++;
	}
	printf("\n");
}

void update_all(){
	int i = 0;
	int j = 0;
	while(i < 10){
		while(j < NEURONS){
			update_neuron(j);
			j++;
		}
		i++;
	}
}

int main(){
	insert_img(pat1, pattern1_bits);
	insert_img(pat2, pattern2_bits);
	insert_img(pat3, pattern3_bits);
	insert_img(recognize, pattern4_bits);
	
	train(pat1);
	train(pat2);
	train(pat3);

	print_pat(recognize);

	update_all();

	print_pat(recognize);
	return 0;
}