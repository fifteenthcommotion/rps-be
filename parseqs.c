#include "rps.h"

int parseqs(char *qs, char username[256], char password[256], char targetplayer[256], char roomid[20], char move[2]) {
	char * token;
	if (qs==NULL || qs[0]=='\0') return QUERY_STRING_MISSING;

	if (username) *username = '\0';
	if (password) *password = '\0';
	if (targetplayer) *targetplayer = '\0';
	if (roomid) *roomid = '\0';
	if (move) *move = '\0';

	token = strtok(qs,"&");
	while (token != NULL) {
		if (username && strncmp(token,"user=",5) == 0) snprintf(username,256,"%.255s",token+5);
		else if (password && strncmp(token,"pass=",5) == 0) snprintf(password,256,"%.255s",token+5);
		else if (targetplayer && strncmp(token,"targ=",5) == 0) snprintf(targetplayer,256,"%.255s",token+5);
		else if (roomid && strncmp(token,"room=",5) == 0) snprintf(roomid,20,"%.19s",token+5);
		else if (move && strncmp(token,"move=",5) == 0) snprintf(move,2,"%.1s",token+5);
		token = strtok(NULL,"&");
	}

	if (username) {
		if (*username == '\0') return USER_NOT_SPECIFIED;
		for (int i = 0; i < 256; ++i) {
			if (username[i] == '\0') break;
			if (!isalnum(username[i])) return USER_NOT_ALNUM;
		}
	}
	if (password) {
		if (*password == '\0') return PASS_NOT_SPECIFIED;
		for (int i = 0; i < 256; ++i) {
			if (password[i] == '\0') break;
			if (!isalnum(password[i])) return PASS_NOT_ALNUM;
		}
	}
	if (targetplayer) {
		if (*targetplayer == '\0') return TARGET_NOT_SPECIFIED;
		for (int i = 0; i < 256; ++i) {
			if (targetplayer[i] == '\0') break;
			if (!isalnum(targetplayer[i])) return TARGET_NOT_ALNUM;
		}
	}
	if (roomid) {
		if (*roomid == '\0') return ROOM_NOT_SPECIFIED;
		for (int i = 0; i < 20; ++i) {
			if (roomid[i] == '\0') break;
			if (!isdigit(roomid[i])) return ROOM_NOT_NUM;
		}
	}
	if (move) {
		if (*move == '\0') return MOVE_NOT_SPECIFIED;
		if (*move < '1' || *move > '4') return MOVE_INVALID;
	}

	return QUERY_STRING_PARSE_OK;
}
