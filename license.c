#include "rps.h"

int main() {
	printf("Content-type: text/plain; charset=utf-8\n");
	printf("Status: 200 OK\n\n");
	printf("  rps-be: a collection of cgi scripts to play rock paper scissors over the web\n\
    Copyright (C) 2018  fifteenthcommotion\n\
\n\
    This program is free software: you can redistribute it and/or modify\n\
    it under the terms of the GNU Affero General Public License as\n\
    published by the Free Software Foundation, either version 3 of the\n\
    License, or (at your option) any later version.\n\
\n\
    This program is distributed in the hope that it will be useful,\n\
    but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
    GNU Affero General Public License for more details.\n\
\n\
    You should have received a copy of the GNU Affero General Public License\n\
    along with this program.  If not, see <https://www.gnu.org/licenses/>.\n\n");
	printf("Source code for this version of the program is availible at <%s>\n",AGPL_SRC_LINK);
	printf("(the person hosting this program is responsible for maintaining the accuracy of link above)\n");

}
