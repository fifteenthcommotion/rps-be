#include "rps.h"

int main() {
	char username [256];
	char password [256];
	char * qs = getenv("QUERY_STRING");
	sqlite3 *pdb;
	sqlite3_open(DB_PATH,&pdb);
	int outcode = parseqs(qs,username,password,NULL,NULL,NULL);
	failonout(outcode,pdb);
	outcode = auth(username,password,pdb);
	failonout(outcode,pdb);

	success_200("success",pdb);

}
