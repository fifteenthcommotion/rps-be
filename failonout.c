#include "rps.h"

void failonout(int outcode, sqlite3 *pdb) {
	if (outcode == QUERY_STRING_MISSING) fail_400("Query string missing",pdb);
	if (outcode == USER_NOT_SPECIFIED) fail_400("Username not specified",pdb);
	if (outcode == USER_NOT_ALNUM) fail_400("Username not alphanumeric",pdb);
	if (outcode == PASS_NOT_SPECIFIED) fail_400("Password not specified",pdb);
	if (outcode == PASS_NOT_ALNUM) fail_400("Password not alphanumeric",pdb);
	if (outcode == TARGET_NOT_SPECIFIED) fail_400("Target not specified",pdb);
	if (outcode == TARGET_NOT_ALNUM) fail_400("Target not alphanumeric",pdb);
	if (outcode == ROOM_NOT_SPECIFIED) fail_400("Room not specified",pdb);
	if (outcode == ROOM_NOT_NUM) fail_400("Room not numeric",pdb);
	if (outcode == MOVE_NOT_SPECIFIED) fail_400("Move not specified",pdb);
	if (outcode == MOVE_INVALID) fail_400("Move invalid",pdb);

	if (outcode == USER_NONEXISTENT) fail_400("User nonexistent",pdb);
	if (outcode == PASS_INVALID) fail_400("Password invalid",pdb);

	if (outcode == ROOM_NONEXISTENT) fail_400("Room nonexistent",pdb);
	if (outcode == PLAYER_NOT_IN_ROOM) fail_400("Player not in room",pdb);
}
