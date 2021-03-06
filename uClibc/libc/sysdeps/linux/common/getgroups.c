/* vi: set sw=4 ts=4: */
/*
 * getgroups() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include <grp.h>

libc_hidden_proto(getgroups)

#if defined(__NR_getgroups32)
# undef __NR_getgroups
# define __NR_getgroups __NR_getgroups32
_syscall2(int, getgroups, int, size, gid_t *, list);

#elif __WORDSIZE == 64
_syscall2(int, getgroups, int, size, gid_t *, list);

#else

libc_hidden_proto(sysconf)
#define MIN(a,b) (((a)<(b))?(a):(b))

#define __NR___syscall_getgroups __NR_getgroups
static inline _syscall2(int, __syscall_getgroups,
		int, size, __kernel_gid_t *, list);

int getgroups(int size, gid_t groups[])
{
	if (unlikely(size < 0)) {
ret_error:
		__set_errno(EINVAL);
		return -1;
	} else {
		int i, ngids;
		__kernel_gid_t *kernel_groups;

		size = MIN(size, sysconf(_SC_NGROUPS_MAX));
		kernel_groups = (__kernel_gid_t *)malloc(sizeof(*kernel_groups) * size);
		if (size && kernel_groups == NULL)
			goto ret_error;

		ngids = __syscall_getgroups(size, kernel_groups);
		if (size != 0 && ngids > 0) {
			for (i = 0; i < ngids; i++) {
				groups[i] = kernel_groups[i];
			}
		}

		if (kernel_groups)
			free(kernel_groups);
		return ngids;
	}
}
#endif

libc_hidden_def(getgroups)
