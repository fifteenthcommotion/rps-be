#include "rps.h"

int auth(char username[256], char password[256], sqlite3 *pdb) {
	sqlite3_stmt *pst;
	const char *st_tail;
	int flag = 0;
	char buffer[SQLMAXLEN];
	char * token;
	const char * db_pass;

	snprintf(buffer,SQLMAXLEN,"SELECT password from players WHERE username=='%.255s'",username);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	flag = sqlite3_step(pst);
	while (flag==SQLITE_BUSY) flag = sqlite3_step(pst);
	if (flag==SQLITE_ROW) db_pass = sqlite3_column_text(pst,0);
	sqlite3_finalize(pst);
	if (flag==SQLITE_DONE) return USER_NONEXISTENT;
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);
	if (strncmp(db_pass,password,255)!=0) return PASS_INVALID;
	
	return AUTH_SUCCESS;
}

int verifyinroom(char username[256], char roomid[20], sqlite3 *pdb) {
	sqlite3_stmt *pst;
	const char *st_tail;
	int flag = 0;
	char buffer[SQLMAXLEN];
	char * token;
	const char * p1;
	const char * p2;

	snprintf(buffer,SQLMAXLEN,"SELECT p1,p2 FROM rooms WHERE ROWID=='%.19s'",roomid);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	flag = sqlite3_step(pst);
	while (flag==SQLITE_BUSY) flag = sqlite3_step(pst);
	if (flag==SQLITE_ROW) {
		p1 = sqlite3_column_text(pst,0);
		p2 = sqlite3_column_text(pst,1);
	}
	sqlite3_finalize(pst);
	if (flag==SQLITE_DONE) return ROOM_NONEXISTENT;
	if (strncmp(username,p1,255)==0 || strncmp(username,p2,255)==0) return VERIFY_ROOM_OK;
	else return PLAYER_NOT_IN_ROOM;

}
