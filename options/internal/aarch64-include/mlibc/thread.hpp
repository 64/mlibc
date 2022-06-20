#pragma once

#include <stdint.h>
#include <mlibc/tcb.hpp>

namespace mlibc {

inline Tcb *get_current_tcb() {
	uintptr_t ptr = (uintptr_t)__builtin_thread_pointer();
	return reinterpret_cast<Tcb *>(ptr);
}

} // namespace mlibc
