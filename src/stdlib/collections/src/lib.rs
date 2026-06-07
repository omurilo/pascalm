//! `collections` — handle-based dynamic data structures for PascalM.
//!
//! PascalM has no generics, so each structure stores `i64` values and is handed
//! to Pascal as an opaque `integer` handle (a leaked `Box` pointer, like the
//! `json` unit). Because every Pascal value of interest — integers, booleans,
//! enum ordinals, even string/handle pointers — fits in an `i64`, this single
//! element type is enough to build lists of lists, lookup tables, and so on.
//!
//! Ownership is manual: every `*New` must be paired with a `*Free`. Operations
//! on a null/zero handle are no-ops (returning `0`/`false`), so a missing
//! structure never crashes the program.

use std::collections::HashMap;
use std::ffi::CStr;
use std::os::raw::c_char;

/// Unit-initialization hook — every `use`d unit needs one; nothing to set up.
#[no_mangle]
pub extern "C" fn collections_init() {}

// ---------------------------------------------------------------------------
// List — a growable vector of i64.
// ---------------------------------------------------------------------------

unsafe fn list_mut<'a>(handle: i64) -> Option<&'a mut Vec<i64>> {
    if handle == 0 {
        None
    } else {
        Some(&mut *(handle as *mut Vec<i64>))
    }
}

#[no_mangle]
pub extern "C" fn coll_list_new() -> i64 {
    Box::into_raw(Box::new(Vec::<i64>::new())) as i64
}

#[no_mangle]
pub unsafe extern "C" fn coll_list_push(handle: i64, value: i64) {
    if let Some(list) = list_mut(handle) {
        list.push(value);
    }
}

/// 0-based element read; out-of-range (or null handle) yields 0.
#[no_mangle]
pub unsafe extern "C" fn coll_list_get(handle: i64, index: i64) -> i64 {
    if index < 0 {
        return 0;
    }
    list_mut(handle)
        .and_then(|list| list.get(index as usize).copied())
        .unwrap_or(0)
}

/// 0-based element write; out-of-range (or null handle) is a no-op.
#[no_mangle]
pub unsafe extern "C" fn coll_list_set(handle: i64, index: i64, value: i64) {
    if index < 0 {
        return;
    }
    if let Some(list) = list_mut(handle) {
        if let Some(slot) = list.get_mut(index as usize) {
            *slot = value;
        }
    }
}

#[no_mangle]
pub unsafe extern "C" fn coll_list_len(handle: i64) -> i64 {
    list_mut(handle).map(|list| list.len() as i64).unwrap_or(0)
}

/// Remove and return the last element; 0 if empty or null.
#[no_mangle]
pub unsafe extern "C" fn coll_list_pop(handle: i64) -> i64 {
    list_mut(handle).and_then(|list| list.pop()).unwrap_or(0)
}

#[no_mangle]
pub unsafe extern "C" fn coll_list_free(handle: i64) {
    if handle != 0 {
        drop(Box::from_raw(handle as *mut Vec<i64>));
    }
}

// ---------------------------------------------------------------------------
// Map — a hash map from owned string keys to i64 values.
// ---------------------------------------------------------------------------

unsafe fn map_mut<'a>(handle: i64) -> Option<&'a mut HashMap<String, i64>> {
    if handle == 0 {
        None
    } else {
        Some(&mut *(handle as *mut HashMap<String, i64>))
    }
}

unsafe fn key_of(key: *const c_char) -> Option<String> {
    if key.is_null() {
        None
    } else {
        Some(CStr::from_ptr(key).to_string_lossy().into_owned())
    }
}

#[no_mangle]
pub extern "C" fn coll_map_new() -> i64 {
    Box::into_raw(Box::new(HashMap::<String, i64>::new())) as i64
}

#[no_mangle]
pub unsafe extern "C" fn coll_map_put(handle: i64, key: *const c_char, value: i64) {
    if let (Some(map), Some(k)) = (map_mut(handle), key_of(key)) {
        map.insert(k, value);
    }
}

/// Value for `key`, or 0 when absent / null handle.
#[no_mangle]
pub unsafe extern "C" fn coll_map_get(handle: i64, key: *const c_char) -> i64 {
    match (map_mut(handle), key_of(key)) {
        (Some(map), Some(k)) => map.get(&k).copied().unwrap_or(0),
        _ => 0,
    }
}

#[no_mangle]
pub unsafe extern "C" fn coll_map_has(handle: i64, key: *const c_char) -> bool {
    match (map_mut(handle), key_of(key)) {
        (Some(map), Some(k)) => map.contains_key(&k),
        _ => false,
    }
}

#[no_mangle]
pub unsafe extern "C" fn coll_map_delete(handle: i64, key: *const c_char) {
    if let (Some(map), Some(k)) = (map_mut(handle), key_of(key)) {
        map.remove(&k);
    }
}

#[no_mangle]
pub unsafe extern "C" fn coll_map_len(handle: i64) -> i64 {
    map_mut(handle).map(|map| map.len() as i64).unwrap_or(0)
}

#[no_mangle]
pub unsafe extern "C" fn coll_map_free(handle: i64) {
    if handle != 0 {
        drop(Box::from_raw(handle as *mut HashMap<String, i64>));
    }
}
