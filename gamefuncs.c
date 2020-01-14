#include "rps.h"

int isplaying(char username[256], sqlite3 *pdb) {

	sqlite3_stmt *pst;
	const char * st_tail;
	int flag = 0;
	char buffer [SQLMAXLEN];

	snprintf(buffer,SQLMAXLEN,"SELECT ROWID FROM rooms WHERE p1=='%.255s' OR p2='%.255s'",username,username);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	do flag = sqlite3_step(pst); while (flag == SQLITE_BUSY);
	sqlite3_finalize(pst);
	if (flag==SQLITE_ROW) return 1;
	if (flag==SQLITE_DONE) return 0;
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);

}

int iswaiting(char username[256], sqlite3 *pdb) {

	sqlite3_stmt *pst;
	const char * st_tail;
	int flag = 0;
	char buffer [SQLMAXLEN];

	snprintf(buffer,SQLMAXLEN,"SELECT ROWID FROM waitingplayers WHERE username=='%.255s'",username);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	do flag = sqlite3_step(pst); while (flag == SQLITE_BUSY);
	sqlite3_finalize(pst);
	if (flag==SQLITE_ROW) return 1;
	if (flag==SQLITE_DONE) return 0;
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);
}

int bothplayed(char roomid[20], sqlite3 *pdb) {
	sqlite3_stmt *pst;
	const char * st_tail;
	int flag = 0;
	char buffer [SQLMAXLEN];

	snprintf(buffer,SQLMAXLEN,"SELECT ROWID FROM rooms WHERE ROWID=='%.19s' AND p1move!='0' AND p2move!='0'",roomid);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	do flag = sqlite3_step(pst); while (flag == SQLITE_BUSY);
	sqlite3_finalize(pst);
	if (flag==SQLITE_ROW) return 1;
	if (flag==SQLITE_DONE) return 0;
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);
}

void getroominfo(char const roomid[20], char p1[256], char p2[256], char p1move[256], char p2move[2], int *pp1knows, int *pp2knows, sqlite3 *pdb) {
	char buffer[SQLMAXLEN];
	const char *st_tail;
	sqlite3_stmt *pst;
	int flag = 0;

	snprintf(buffer,SQLMAXLEN,"SELECT p1,p2,p1move,p2move,p1knows,p2knows FROM rooms WHERE ROWID=='%.19s'",roomid);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	do flag = sqlite3_step(pst); while (flag == SQLITE_BUSY);
	if (flag==SQLITE_ROW) {
		snprintf(p1,256,"%.255s",sqlite3_column_text(pst,0));
		snprintf(p2,256,"%.255s",sqlite3_column_text(pst,1));
		snprintf(p1move,2,"%.1s",sqlite3_column_text(pst,2));
		snprintf(p2move,2,"%.1s",sqlite3_column_text(pst,3));
		*pp1knows = sqlite3_column_int(pst,4);
		*pp2knows = sqlite3_column_int(pst,5);
	}
	sqlite3_finalize(pst);
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLUTE_MISUSE",pdb);

}

void updateroom(char const roomid[20], char const p1move[2], char const p2move[2], int p1knows, int p2knows, sqlite3 *pdb) {
	char buffer[SQLMAXLEN];
	const char *st_tail;
	sqlite3_stmt *pst;
	int flag = 0;

	snprintf(buffer,SQLMAXLEN,"UPDATE rooms SET p1move='%.1s',p2move='%.1s',p1knows='%i',p2knows='%i' WHERE ROWID='%.19s'",p1move,p2move,p1knows,p2knows,roomid);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	do flag = sqlite3_step(pst); while (flag == SQLITE_BUSY);
	sqlite3_finalize(pst);
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLUTE_MISUSE",pdb);

}

void deleteroom(char const roomid[20], sqlite3 *pdb) {
	char buffer[SQLMAXLEN];
	const char *st_tail;
	sqlite3_stmt *pst;
	int flag = 0;

	snprintf(buffer,SQLMAXLEN,"DELETE FROM rooms WHERE ROWID='%.19s'",roomid);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	do flag = sqlite3_step(pst); while (flag == SQLITE_BUSY);
	sqlite3_finalize(pst);
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLUTE_MISUSE",pdb);

}


