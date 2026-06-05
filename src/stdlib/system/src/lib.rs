#[no_mangle]
pub extern "C" fn pascal_runtime_init() {
    // Basic runtime initialization for Pascal programs.
    // Can be used to set up global allocators, panic handlers, etc.
}

/// Unit-initialization hook. The compiler emits a `<unit>_init` call for every
/// used unit; `system` is implicitly used by every program, so it must expose
/// this (no-op) symbol.
#[no_mangle]
pub extern "C" fn system_init() {}

#[no_mangle]
pub extern "C" fn pascal_sqrt(n: f64) -> f64 {
    n.sqrt()
}

/// Ordinal-to-character conversion (Pascal `Chr`).
#[no_mangle]
pub extern "C" fn pascal_chr(n: i64) -> i8 {
    n as i8
}

/// Character-to-ordinal conversion (Pascal `Ord`).
#[no_mangle]
pub extern "C" fn pascal_ord(c: i8) -> i64 {
    (c as u8) as i64
}

#[no_mangle]
pub extern "C" fn pascal_halt(exit_code: i32) {
    std::process::exit(exit_code);
}

/// Concatenates two null-terminated C strings into a freshly allocated
/// null-terminated buffer. Ownership is handed off to the generated Pascal
/// code (which has no free), so the buffer is intentionally leaked.
#[no_mangle]
pub extern "C" fn pascal_strcat(a: *const u8, b: *const u8) -> *mut u8 {
    unsafe {
        let len_a = c_strlen(a);
        let len_b = c_strlen(b);
        let mut buf: Vec<u8> = Vec::with_capacity(len_a + len_b + 1);
        for i in 0..len_a {
            buf.push(*a.add(i));
        }
        for i in 0..len_b {
            buf.push(*b.add(i));
        }
        buf.push(0);
        let ptr = buf.as_mut_ptr();
        core::mem::forget(buf);
        ptr
    }
}

unsafe fn c_strlen(s: *const u8) -> usize {
    if s.is_null() {
        return 0;
    }
    let mut len = 0usize;
    while *s.add(len) != 0 {
        len += 1;
    }
    len
}

// Basic memory allocation functions for dynamic arrays/records if needed
#[no_mangle]
pub unsafe extern "C" fn sys_alloc_mem(size: usize) -> *mut std::ffi::c_void {
    let layout = std::alloc::Layout::from_size_align(size, 8).unwrap();
    std::alloc::alloc_zeroed(layout) as *mut std::ffi::c_void
}

#[no_mangle]
pub unsafe extern "C" fn sys_free_mem(ptr: *mut std::ffi::c_void, size: usize) {
    if !ptr.is_null() {
        let layout = std::alloc::Layout::from_size_align(size, 8).unwrap();
        std::alloc::dealloc(ptr as *mut u8, layout);
    }
}
