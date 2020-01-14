#ifndef RPS_H_INCLUDED
#define RPS_H_INCLUDED


#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define SQLMAXLEN 1024
#define DB_PATH "/var/www/cgi-data/rps.db"
#define AGPL_SRC_LINK "https://github.com/fifteenthcommotion/rps-be"

#define QUERY_STRING_PARSE_OK	100
#define QUERY_STRING_MISSING	101
#define USER_NOT_SPECIFIED	102
#define USER_NOT_ALNUM		103
#define PASS_NOT_SPECIFIED	104
#define PASS_NOT_ALNUM		105
#define TARGET_NOT_SPECIFIED	106
#define TARGET_NOT_ALNUM	107
#define ROOM_NOT_SPECIFIED	108
#define ROOM_NOT_NUM		109
#define MOVE_NOT_SPECIFIED	110
#define MOVE_INVALID		111

#define AUTH_SUCCESS		200
#define USER_NONEXISTENT	201
#define PASS_INVALID		202

#define VERIFY_ROOM_OK		300
#define ROOM_NONEXISTENT	301
#define PLAYER_NOT_IN_ROOM	302


int parseqs(char *qs, char username[256], char password[256], char targetplayer[256], char roomid[20], char move[2]);
/* returns 
QUERY_STRING_PARSE_OK
QUERY_STRING_MISSING
USER_NOT_SPECIFIED
USER_NOT_ALNUM
PASS_NOT_SPECIFIED
PASS_NOT_ALNUM
TARGET_NOT_SPECIFIED
TARGET_NOT_ALNUM
ROOM_NOT_SPECIFIED
ROOM_NOT_NUM
MOVE_NOT_SPECIFIED
MOVE_INVALID
*/



int auth(char username[256], char password[256], sqlite3 *pdb);
/*
AUTH_SUCCESS
USER_NONEXISTENT
PASS_INVALID
(not anymore)INTERNAL_SQLITE_ERROR
(not anymore)INTERNAL_SQLITE_MISUSE
*/

int verifyinroom(char username[256], char roomid[20], sqlite3 *pdb);
/*
VERIFY_ROOM_OK
ROOM_NONEXISTENT
PLAYER_NOT_IN_ROOM
*/

void fail_400(const char * const message, sqlite3 *pdb);
void fail_500(const char * const message, sqlite3 *pdb);
void success_200(const char * const message, sqlite3 *pdb);

void failonout(int outcode, sqlite3 *pdb);

int isplaying(char username[256], sqlite3 *pdb);
int iswaiting(char username[256], sqlite3 *pdb);
int bothplayed(char roomid[20], sqlite3 *pdb);
void getroominfo(char const roomid[20], char p1[256], char p2[256], char p1move[256], char p2move[2], int *pp1knows, int *pp2knows, sqlite3 *pdb);
void updateroom(char const roomid[20], char const p1move[2], char const p2move[2], int p1knows, int p2knows, sqlite3 *pdb);
void deleteroom(char const roomid[20], sqlite3 *pdb);

#endif /* RPS_H_INCLUDED */

