use std::ffi::{CStr, CString};
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn pascal_runtime_init() {
    // Basic runtime initialization for Pascal programs.
    // Can be used to set up global allocators, panic handlers, etc.
}

#[no_mangle]
pub extern "C" fn pascal_sqrt(n: f64) -> f64 {
    n.sqrt()
}

#[no_mangle]
pub extern "C" fn pascal_halt(exit_code: i32) {
    std::process::exit(exit_code);
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
