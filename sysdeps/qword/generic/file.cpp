
#include <bits/ensure.h>
#include <mlibc/debug.hpp>
#include <mlibc/sysdeps.hpp>

#define STUB_ONLY { __ensure(!"STUB_ONLY function was called"); __builtin_unreachable(); }

namespace mlibc {

void sys_libc_log(const char *message) {
	unsigned long res;
	asm volatile ("syscall" : "=a"(res)
			: "a"(0), "D"(0), "S"(message)
			: "rcx", "r11");
}

void sys_libc_panic() {
	__builtin_trap();
}

int sys_tcb_set(void *pointer) STUB_ONLY

int sys_anon_allocate(size_t size, void **pointer) {
	// The qword kernel wants us to allocate whole pages.
	__ensure(!(size & 0xFFF));

	void *res;
	asm volatile ("syscall" : "=a"(res)
			: "a"(6), "D"(0), "S"(size >> 12)
			: "rcx", "r11");
	if(!res)
		return -1;
	*pointer = res;
	return 0;
}

int sys_anon_free(void *pointer, size_t size) STUB_ONLY

#ifndef MLIBC_BUILDING_RTDL
void sys_exit(int status) {
	__builtin_trap();
}
#endif

#ifndef MLIBC_BUILDING_RTDL
int sys_clock_get(int clock, time_t *secs, long *nanos) STUB_ONLY
#endif

int sys_open(const char *path, int flags, int *fd) STUB_ONLY
int sys_close(int fd) STUB_ONLY
int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) STUB_ONLY

#ifndef MLIBC_BUILDING_RTDL
int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) STUB_ONLY
#endif

int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) STUB_ONLY

int sys_vm_map(void *hint, size_t size, int prot, int flags,
		int fd, off_t offset, void **window) STUB_ONLY

#ifndef MLIBC_BUILDING_RTDL
int sys_vm_remap(void *pointer, size_t size, size_t new_size, void **window) STUB_ONLY
#endif // !defined(MLIBC_BUILDING_RTDL)

int sys_vm_unmap(void *pointer, size_t size) STUB_ONLY

#ifndef MLIBC_BUILDING_RTDL
int sys_fstat(int fd, struct stat *statbuf) STUB_ONLY
#endif

#ifndef MLIBC_BUILDING_RTDL
int sys_rename(const char *path, const char *new_path) STUB_ONLY
#endif

#ifndef MLIBC_BUILDING_RTDL
int sys_sigaction(int, const struct sigaction *__restrict, struct sigaction *__restrict) STUB_ONLY
#endif

// All remaining functions are disabled in ldso.
#ifndef MLIBC_BUILDING_RTDL

int sys_futex_wait(int *pointer, int expected) STUB_ONLY
int sys_futex_wake(int *pointer) STUB_ONLY

int sys_open_dir(const char *path, int *handle) STUB_ONLY
int sys_read_entries(int handle, void *buffer, size_t max_size, size_t *bytes_read) STUB_ONLY

int sys_access(const char *path, int mode) STUB_ONLY
int sys_dup(int fd, int flags, int *newfd) STUB_ONLY
int sys_dup2(int fd, int flags, int newfd) STUB_ONLY
int sys_isatty(int fd, int *ptr) STUB_ONLY
int sys_ttyname(int fd, char *buf, size_t size) STUB_ONLY
int sys_stat(const char *path, struct stat *statbuf) STUB_ONLY
int sys_lstat(const char *path, struct stat *statbuf) STUB_ONLY
int sys_chroot(const char *path) STUB_ONLY
int sys_mkdir(const char *path) STUB_ONLY
int sys_tcgetattr(int fd, struct termios *attr) STUB_ONLY
int sys_tcsetattr(int, int, const struct termios *attr) STUB_ONLY
int sys_pipe(int *fds) STUB_ONLY
int sys_readlink(const char *path, void *buffer, size_t max_size, ssize_t *length) STUB_ONLY
int sys_ftruncate(int fd, size_t size) STUB_ONLY
int sys_fallocate(int fd, off_t offset, size_t size) STUB_ONLY
int sys_unlink(const char *path) STUB_ONLY
int sys_symlink(const char *target_path, const char *link_path) STUB_ONLY
int sys_fcntl(int fd, int request, va_list args) STUB_ONLY

int sys_socket(int family, int type, int protocol, int *fd) STUB_ONLY
int sys_socketpair(int domain, int type_and_flags, int proto, int *fds) STUB_ONLY
int sys_accept(int fd, int *newfd) STUB_ONLY
int sys_bind(int fd, const struct sockaddr *addr_ptr, socklen_t addr_length) STUB_ONLY
int sys_connect(int fd, const struct sockaddr *addr_ptr, socklen_t addr_length) STUB_ONLY
int sys_msg_send(int fd, const struct msghdr *hdr, int flags, ssize_t *length) STUB_ONLY
int sys_msg_recv(int fd, struct msghdr *hdr, int flags, ssize_t *length) STUB_ONLY
int sys_sockname(int fd, struct sockaddr *addr_ptr, socklen_t max_addr_length,
		socklen_t *actual_length) STUB_ONLY
int sys_getsockopt(int fd, int layer, int number,
		void *__restrict buffer, socklen_t *__restrict size) STUB_ONLY
int sys_setsockopt(int fd, int layer, int number,
		const void *buffer, socklen_t size) STUB_ONLY

int sys_sleep(time_t *secs, long *nanos) STUB_ONLY
int sys_fork(pid_t *child) STUB_ONLY
void sys_execve(const char *path, char *const argv[], char *const envp[]) STUB_ONLY
int sys_kill(int, int) STUB_ONLY
int sys_waitpid(pid_t pid, int *status, int flags) STUB_ONLY
int sys_sigprocmask(int how, const sigset_t *__restrict set, sigset_t *__restrict retrieve) STUB_ONLY
void sys_yield() STUB_ONLY

gid_t sys_getgid() STUB_ONLY
gid_t sys_getegid() STUB_ONLY
uid_t sys_getuid() STUB_ONLY
uid_t sys_geteuid() STUB_ONLY
pid_t sys_getpid() STUB_ONLY
pid_t sys_getppid() STUB_ONLY

#endif // MLIBC_BUILDING_RTDL

} // namespace mlibc
