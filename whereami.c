#include "rps.h"

int main() {

	char username[256];
	char password[256];
	char * qs = getenv("QUERY_STRING");
	sqlite3 *pdb;
	sqlite3_open(DB_PATH,&pdb);
	int outcode = parseqs(qs,username,password,NULL,NULL,NULL);
	failonout(outcode,pdb);
	outcode = auth(username,password,pdb);
	failonout(outcode,pdb);

	sqlite3_stmt *pst;
	const char *st_tail;
	int flag = 0;
	char buffer[SQLMAXLEN];
	char rowid[20];
	const char * rowidptrtmp;

	snprintf(buffer,SQLMAXLEN,"SELECT ROWID FROM rooms WHERE p1=='%.255s' OR p2='%.255s'",username,username);
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	flag = sqlite3_step(pst);
	while (flag==SQLITE_BUSY) flag = sqlite3_step(pst);
	if (flag==SQLITE_ROW) {
		rowidptrtmp = sqlite3_column_text(pst,0);
		snprintf(rowid,20,"%.19s",rowidptrtmp);
	}
	sqlite3_finalize(pst);
	if (flag==SQLITE_DONE) success_200("0",pdb);
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);

	success_200(rowid,pdb);
}
