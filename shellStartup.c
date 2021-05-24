#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#define offsetLines 15

char *stripToLastParens(char *cwd) {
		if(strlen(cwd) == 1) return cwd;
		cwd += strlen(cwd);
		while (*cwd != '/') {
			cwd--;
		}
		if(!strcmp(cwd, "/conorbrandon")) return "~";
		return cwd;
	}

int main(int argc, char *argv[])
{
	int counter = 0;
	char files[1024][1024];
	memset(&files[counter], 0, 1024);
	FILE *fp = popen("ls -1", "r");
	while (fgets(&files[counter], 1024, fp) != NULL) {
		counter++;
		memset(&files[counter], 0, 1024);
	}
	pclose(fp);
	char *offsetMacLines[offsetLines] = {
	"      /____________ /  |",
	"     | ___________ |   |",
	"     ||           ||   |",
	"     ||     " KGRN "" KWHT "     ||   |",
	"     ||   " KGRN "hello" KWHT "   ||   |",
	"     ||___________||   | ",
	"     |   _______   |  /  ",
	"    /|  (_______)  | /   ",
	"   ( |_____________|/    ",
	"    \\                   ",
	".=======================.",
	"| ::::::::::::::::  ::: |",
	"| ::::::::::::::[]  ::: |",
	"|   -----------     ::: |",
	"`-----------------------'"
	};
	char cwd[PATH_MAX];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf(KWHT "         ______________ \n");	
	printf(KWHT "        /             /|");	printf(KRED "\tToday is %s", ctime(&t));	
	printf(KWHT "       /             / |");	printf(KYEL "\tYou are at %s. You can navigate to:\n" KWHT, getcwd(cwd, sizeof(cwd)) ? stripToLastParens(cwd) : "");
	int otherCounter = 0;
	while(otherCounter < offsetLines - 1) {
		printf(KWHT "%s", offsetMacLines[otherCounter]);
		if(otherCounter < counter) printf(KCYN "\t%s", files[otherCounter]);
		else printf("\n");
		otherCounter++;
	}
	printf(KWHT "%s", offsetMacLines[otherCounter]);
	if(otherCounter < counter) printf(KBLU "\tand %d more...\n", counter - otherCounter);
	else printf("\n");
	exit(0);
}