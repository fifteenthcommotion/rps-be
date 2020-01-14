# rps - a simple way to play rock paper scissors over the web

## Web API

Endpoint	|     | Args			| Returns
----------------|:---:|-------------------------|--------------------------------------------------
join		| GET | user,pass		| "success"
testlogin	| GET | user,pass		| "success"
startwaiting	| GET | user,pass		| "success"
stopwaiting	| GET | user,pass		| "success"
waitingplayers	| GET | user,pass		| newline-separated list of players in waiting list
joinplayer	| GET | user,pass,targ		| roomid of newly-created room
whereami	| GET | user,pass		| roomid (0 if room does not yet exist)
play		| GET | user,pass,room,move	| opponent's move (0 if opponent has not played)
getoppdecision	| GET | user,pass,room		| opponent's move (0 if opponent has not played)
isnewturn	| GET | user,pass,room		| 0 if both players have played, 1 otherwise
license		| GET | (none)			| AGPLv3 copyright notice and link to source code

Argument|Maximum length	| Meaning
--------|:-------------:|--------------------------------------------
user	| 255		| username
pass	| 255		| password
targ	| 255		| target player
room	| 19		| room id (sqlite rowid of the room)
move	| 1		| 1: rock, 2: paper, 3: scissors, 4: end game

Code 400 message		| Meaning
--------------------------------|:--------:
Query string missing		| Query string expected but not found
Username not specified		| user argument empty or nonexistent
Username not alphanumeric	| user argument not alphanumeric (SQL sanitization)
Password not specified		| pass argument empty or nonexistent
Password not alphanumeric	| pass argument not alphanumeric (SQL sanitization, can't be bothered to store passwords hashed)
Target not specified		| targ argument empty or nonexistent
Target not alphanumeric		| targ argument not alpganumeric (SQL sanitization)
Room not specified		| room argument empty or nonexistent
Room not numeric		| room argument not numeric (SQL sanitization)
Move not specified		| move argument empty or nonexistent
Move invalid			| move argument not in valid range (1,2,3,4)
User nonexistent		| supplied username has not been registered (authentication failure)
Password invalid		| supplied password does not match records (authentication failure)
Room nonexistent		| supplied room id does not point to an existing room
Player not in room		| authenticated player is not registered as a player in specified room
User already playing		| authenticated player cannot join waitingplayers or another room while already in a room 
Already played this turn	| move violates proper game flow: user has already played this turn
Username and targetplayer match	| user attempted to join themselves for a game (this is not allowed)

## Lobby flow

- Register using `join`
- Test login using `testlogin` (optional)

Either:
- Get list of availible players with `waitingplayers`
- Join a player with `joinplayer`, get room id as the return value
- Begin playing
Or:
- Join waiting list with `startwaiting`
- Periodically call `whereami` until recieving non-zero room id, or give up and `joinplayer` right after verifying `whereami` is zero
- Begin playing



## Game flow

- player 1 `play`s, gets 0 as return, begins periodically calling `getoppdecision`
- player 2 `play`s, gets player 1's move in return, begins periodically calling `isnewturn`
- player 1 recieves player 2's move from `getoppdecision`, this initializes the next turn, player 1 is ready to `play`
- player 2 recieves 1 from `isnewturn` and knows he can `play` again



## Backend setup

- Either make the `/var/www/cgi-data/` directory or modify `rps.h` to point to a different location
- Copy or link the excecutables necessary for the web api into your cgi-bin directory (all executables in rps-be except dbsetup)
- Run `dbsetup`, change database ownership to `www-data` or equivalent

## AGPLv3 compliance

If you make nontrivial changes to the source code (changing database location is trivial), please update the `AGPL_SRC_LINK` constant in `rps.h` to point to a valid copy of your source code.
