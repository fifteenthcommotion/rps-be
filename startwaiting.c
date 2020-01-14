#include "rps.h"

int main () {

	char username [256];
	char password [256];
	char * qs = getenv("QUERY_STRING");
	sqlite3 *pdb;
	sqlite3_open(DB_PATH,&pdb);
	int outcode = parseqs(qs,username,password,NULL,NULL,NULL);
	failonout(outcode,pdb);
	outcode = auth(username,password,pdb);
	failonout(outcode,pdb);
	if (isplaying(username,pdb)) fail_400("User already playing",pdb);

	sqlite3_stmt *pst;
	const char *st_tail;
	int flag = 0;
	char buffer [SQLMAXLEN];


	snprintf(buffer,SQLMAXLEN,"INSERT INTO waitingplayers (username) VALUES ('%.255s')",username);

	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);

	flag = sqlite3_step(pst);
	while (flag==SQLITE_BUSY) flag = sqlite3_step(pst);

	sqlite3_finalize(pst);

	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);
	
	success_200("success",pdb);

}
