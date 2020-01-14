#include "rps.h"

int main() {

	char username [256];
	char password [256];
	char roomid [256];
	char * qs = getenv("QUERY_STRING");
	sqlite3 *pdb;
	sqlite3_open(DB_PATH,&pdb);
	int outcode = parseqs(qs,username,password,NULL,roomid,NULL);
	failonout(outcode,pdb);
	outcode = auth(username,password,pdb);
	failonout(outcode,pdb);
	outcode = verifyinroom(username,roomid,pdb);
	failonout(outcode,pdb);

	if (bothplayed(roomid,pdb)) success_200("0",pdb);
	success_200("1",pdb);
	
}
