
#include <pwd.h>
#include <bits/ensure.h>

#include <mlibc/debug.hpp>

// endpwd() is provided by the platform

struct passwd *getpwent(void) {
	__ensure(!"Not implemented");
	__builtin_unreachable();
}
struct passwd *getpwnam(const char *) {
	__ensure(!"Not implemented");
	__builtin_unreachable();
}
int getpwnam_r(const char *, struct passwd *, char *, size_t, struct passwd **) {
	__ensure(!"Not implemented");
	__builtin_unreachable();
}

struct passwd *getpwuid(uid_t) {
	static thread_local passwd theEntry;
	mlibc::infoLogger() << "mlibc: Broken getpwuid() called!" << frg::endlog;
	theEntry.pw_name = "root";
	theEntry.pw_uid = 0;
	theEntry.pw_gid = 0;
	theEntry.pw_dir = "/root";
	theEntry.pw_shell = "/bin/sh";
	return &theEntry;
}

void endpwent(void) {
	mlibc::infoLogger() << "\e[35mmlibc: endpwent() is a no-op\e[39m" << frg::endlog;
}

int getpwuid_r(uid_t, struct passwd *, char *, size_t, struct passwd **) {
	__ensure(!"Not implemented");
	__builtin_unreachable();
}
void setpwent(void) {
	__ensure(!"Not implemented");
}

