use std::ffi::{CStr, CString};
use std::os::raw::c_char;
use serde_json::Value;

#[no_mangle]
pub unsafe extern "C" fn JsonParse(json_ptr: *const c_char) -> *mut std::ffi::c_void {
    let c_str = CStr::from_ptr(json_ptr);
    let json_str = c_str.to_str().unwrap_or("{}");
    let value: Value = serde_json::from_str(json_str).unwrap_or(Value::Null);
    Box::into_raw(Box::new(value)) as *mut std::ffi::c_void
}

#[no_mangle]
pub unsafe extern "C" fn JsonStringify(value_ptr: *mut std::ffi::c_void) -> *const c_char {
    if value_ptr.is_null() { return std::ptr::null(); }
    let value = &*(value_ptr as *const Value);
    let s = serde_json::to_string(value).unwrap_or_else(|_| "{}".to_string());
    CString::new(s).unwrap().into_raw()
}

#[no_mangle]
pub unsafe extern "C" fn JsonGetString(value_ptr: *mut std::ffi::c_void, key_ptr: *const c_char) -> *const c_char {
    if value_ptr.is_null() { return std::ptr::null(); }
    let value = &*(value_ptr as *const Value);
    let key = CStr::from_ptr(key_ptr).to_str().unwrap_or("");
    
    let res = if let Some(v) = value.get(key) {
        if let Some(s) = v.as_str() {
            s.to_string()
        } else {
            v.to_string()
        }
    } else {
        "".to_string()
    };
    
    CString::new(res).unwrap().into_raw()
}

// Temporary stub for JsonUnmarshal to prevent linker errors
#[no_mangle]
pub unsafe extern "C" fn JsonUnmarshal(record_ptr: *mut std::ffi::c_void, schema_ptr: *const std::ffi::c_void, json_ptr: *const c_char) {
    if json_ptr.is_null() || record_ptr.is_null() || schema_ptr.is_null() { return; }
    let c_str = CStr::from_ptr(json_ptr);
    let _json_str = c_str.to_str().unwrap_or("{}");
    // TODO: implement full dynamic record population logic here
}

#[no_mangle]
pub unsafe extern "C" fn JsonFree(value_ptr: *mut std::ffi::c_void) {
    if !value_ptr.is_null() {
        let _ = Box::from_raw(value_ptr as *mut Value);
    }
}
