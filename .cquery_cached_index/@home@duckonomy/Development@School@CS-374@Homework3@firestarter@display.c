/* display.c defines a simple function for retrieving
 *  an application's DISPLAY environment value.
 *  Prototype is in display.h...
 *
 *  Joel Adams, Fall 2007.
 */

#include <stdio.h>   /* fprintf() */
#include <stdlib.h>  /* getenv() */
#include <string.h>  /* strcmp() */
#include "display.h"

char* getDisplay() {
	char * display = getenv("DISPLAY");
	if ( !display ) {
		fprintf(stderr, "\n*** Fatal: DISPLAY variable not set.\n");
		exit(1);
	}
	return display;
}

