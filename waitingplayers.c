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

	sqlite3_stmt *pst;
	const char *st_tail;
	int flag = 0;
	char buffer [SQLMAXLEN];

	snprintf(buffer,SQLMAXLEN,"SELECT username FROM waitingplayers");
	sqlite3_prepare(pdb,buffer,SQLMAXLEN,&pst,&st_tail);
	flag = sqlite3_step(pst);

	char outstr [4096];
	*outstr = '\0';
	int current = 0;
	while (flag==SQLITE_ROW){
		if (4096-current < 257) break;
		current += snprintf(outstr+current,4096-current,"%.255s\n",sqlite3_column_text(pst,0));
		flag = sqlite3_step(pst);
	}
	sqlite3_finalize(pst);
	if (flag==SQLITE_ERROR) fail_500("SQLITE_ERROR",pdb);
	if (flag==SQLITE_MISUSE) fail_500("SQLITE_MISUSE",pdb);
	if (flag==SQLITE_BUSY) fail_500("SQLITE_BUSY",pdb);
	
	success_200(outstr,pdb);

}
