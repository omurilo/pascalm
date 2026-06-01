#[no_mangle]
pub extern "C" fn pascal_runtime_init() {
    // Initialization
}

#[no_mangle]
pub extern "C" fn pascal_sqrt(n: f64) -> f64 {
    n.sqrt()
}

#[no_mangle]
pub extern "C" fn pascal_halt(_exit_code: i32) {
    //std::process::exit(exit_code);
}
