#include "rps.h"

int main() {
	sqlite3 *pdb;
	sqlite3_stmt *pst;
	int flag = 0;
	const char *st_tail;
	sqlite3_open(DB_PATH,&pdb);
	char bufferlist[3][SQLMAXLEN] = {
"CREATE TABLE IF NOT EXISTS players (username TEXT(255) NOT NULL, password TEXT(255) NOT NULL, UNIQUE(username))", 
"CREATE TABLE IF NOT EXISTS waitingplayers (username TEXT(255) NOT NULL, UNIQUE(username) ON CONFLICT IGNORE)", 
"CREATE TABLE IF NOT EXISTS rooms (p1 TEXT(255) NOT NULL, p2 TEXT(255) NOT NULL, p1move INT NOT NULL DEFAULT 0, p2move INT NOT NULL DEFAULT 0, p1knows BOOLEAN NOT NULL DEFAULT 0, p2knows BOOLEAN NOT NULL DEFAULT 0, CHECK(p1move IN (0,1,2,3,4) AND p2move IN (0,1,2,3,4) AND p1knows IN (0,1) AND p2knows IN (0,1)))"
	};
	for (int i = 0; i < sizeof(bufferlist)/SQLMAXLEN; ++i) {
		sqlite3_prepare(pdb,bufferlist[i],SQLMAXLEN,&pst,&st_tail);
		flag = sqlite3_step(pst);
		while (flag==SQLITE_BUSY) flag = sqlite3_step(pst);
		sqlite3_finalize(pst);
		if (flag==SQLITE_ERROR || flag==SQLITE_MISUSE) break;
	}
	if (flag==SQLITE_ERROR) printf("FAILED: SQLITE_ERROR\n");
	else if (flag==SQLITE_MISUSE) printf("FAILED: SQLITE_MISUSE\n");
	else if (flag==SQLITE_DONE) printf("DONE!\n");
	sqlite3_close(pdb);
}
