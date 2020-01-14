#include "rps.h"

int main() {

	char username [256];
	char password [256];
	char roomid[20];
	char * qs = getenv("QUERY_STRING");
	sqlite3 *pdb;
	sqlite3_open(DB_PATH,&pdb);
	int outcode = parseqs(qs,username,password,NULL,roomid,NULL);
	failonout(outcode,pdb);
	outcode = auth(username,password,pdb);
	failonout(outcode,pdb);
	outcode = verifyinroom(username,roomid,pdb);
	failonout(outcode,pdb);


	sqlite3_stmt *pst;
	const char *st_tail;
	int flag = 0;
	char buffer [SQLMAXLEN];

	char p1 [256];
	char p2 [256];
	char p1move [2];
	char p2move [2];
	int p1knows = 0;
	int p2knows = 0;

	getroominfo(roomid,p1,p2,p1move,p2move,&p1knows,&p2knows,pdb);

	int isp1 = 0;
	if (strncmp(p1,username,255) == 0) isp1 = 1;

	const char * returnval;
	if (isp1) {
		if (*p1move == '0') fail_400("Have not yet played this turn",pdb);
		returnval = p2move;
		if (*p2move != '0') p1knows = 1;
	}
	else {
		if (*p2move == '0') fail_400("Have not yet played this turn",pdb);
		returnval = p1move;
		if (*p1move != '0') p2knows = 1;
	}

	if ((p1knows && p2knows) && *p1move == '4' || *p2move == '4') deleteroom(roomid,pdb);
	else if (p1knows && p2knows) updateroom(roomid,"0","0",0,0,pdb);
	else updateroom(roomid,"0","0",0,0,pdb);

	success_200(returnval,pdb);

}
