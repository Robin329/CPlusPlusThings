/*
 * Copyright (C) 2012 Cyril Hrubis <chrubis@suse.cz>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Further, this software is distributed without any warranty that it is
 * free of the rightful claim of any third person regarding infringement
 * or the like.  Any license provided herein, whether implied or
 * otherwise, applies only to this software file.  Patent licenses, if
 * any, provided herein do not apply to combinations of this program with
 * other software, or any other product whatsoever.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <sys/wait.h>

#include "proc.h"

int main(void)
{
	pid_t pid;
	volatile int i;

	pid = fork();

	if (pid == 0) {
		fprintf(stderr, "I'm Child\n");
	} else {
		fprintf(stderr, "I'm Parent pid -->> %d\n", pid);
	}
	switch (pid) {
	case -1:
		fprintf(stderr, "Fork failed");
		break;
	case 0:
		fprintf(stderr, "Child starts\n");
		for (i = 0; i < 10; i++) {
			usleep(10000);
			fprintf(stderr, "i:%d\n", i);
		}

		fprintf(stderr, "Child about to sleep\n");

		pause();

		fprintf(stderr, "Child woken up\n");

		return 0;
		break;
	default:
		/* Wait for child to sleep */
		fprintf(stderr, "Parent waits for child to fall asleep\n");
		fprintf(stderr, "Child sleeping, wake it\n");
		break;
	}

	return 0;
}
