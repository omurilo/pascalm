use std::ffi::CStr;
use std::ffi::CString;
use std::os::raw::c_char;

#[no_mangle]
pub extern "C" fn strings_init() {}

#[no_mangle]
pub unsafe extern "C" fn str_len(str: *const c_char) -> usize {
    CStr::from_ptr(str).to_bytes().len()
}

#[no_mangle]
pub unsafe extern "C" fn str_int_to_str(i: usize) -> *const c_char {
    let empty = b"\0".as_ptr() as *const c_char;
    match CString::new(i.to_string()) {
        Ok(st) => st.into_raw(),
        _ => empty,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_str_to_int(str: *const c_char) -> usize {
    match CStr::from_ptr(str).to_str() {
        Ok(s) => match s.parse() {
            Ok(sf) => sf,
            _ => 0,
        },
        _ => 0,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_upper_case(str: *const c_char) -> *const c_char {
    let empty = b"\0".as_ptr() as *const c_char;
    let lstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s.to_uppercase(),
        Err(_) => return empty,
    };
    match CString::new(lstr) {
        Ok(st) => st.into_raw(),
        _ => empty,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_lower_case(str: *const c_char) -> *const c_char {
    let empty = b"\0".as_ptr() as *const c_char;
    let lstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s.to_lowercase(),
        Err(_) => return empty,
    };
    match CString::new(lstr) {
        Ok(st) => st.into_raw(),
        _ => empty,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_trim(str: *const c_char) -> *const c_char {
    let empty = b"\0".as_ptr() as *const c_char;
    let tstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s.trim(),
        Err(_) => return empty,
    };

    match CString::new(tstr) {
        Ok(st) => st.into_raw(),
        _ => empty,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_substring(
    str: *const c_char,
    start: usize,
    len: usize,
) -> *const c_char {
    let empty = b"\0".as_ptr() as *const c_char;
    let sstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s,
        Err(_) => return empty,
    };
    let chars: Vec<char> = sstr.chars().collect();
    if start >= chars.len() {
        return empty;
    }

    let result: String = chars.iter().skip(start).take(len).collect();

    match CString::new(result) {
        Ok(st) => st.into_raw(),
        Err(_) => empty,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_index_of(str: *const c_char, sub: *const c_char) -> usize {
    let sstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s,
        Err(_) => return 0,
    };
    let substr = match CStr::from_ptr(sub).to_str() {
        Ok(s) => s,
        Err(_) => return 0,
    };

    let Some(idx) = sstr.find(substr) else {
        return 0;
    };

    idx + 1
}

#[no_mangle]
pub unsafe extern "C" fn str_contains(str: *const c_char, sub: *const c_char) -> bool {
    let sstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s,
        Err(_) => return false,
    };
    let substr = match CStr::from_ptr(sub).to_str() {
        Ok(s) => s,
        Err(_) => return false,
    };

    let Some(_) = sstr.find(substr) else {
        return false;
    };

    return true;
}

#[no_mangle]
pub unsafe extern "C" fn str_replace(
    str: *const c_char,
    search: *const c_char,
    repl: *const c_char,
) -> *const c_char {
    let empty = b"\0".as_ptr() as *const c_char;
    let sstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s,
        Err(_) => return empty,
    };
    let searchstr = match CStr::from_ptr(search).to_str() {
        Ok(s) => s,
        Err(_) => return empty,
    };
    let replstr = match CStr::from_ptr(repl).to_str() {
        Ok(s) => s,
        Err(_) => return empty,
    };

    let fs = sstr.replace(searchstr, replstr);

    match CString::new(fs) {
        Ok(st) => st.into_raw(),
        Err(_) => empty,
    }
}

#[no_mangle]
pub unsafe extern "C" fn str_split(str: *const c_char, sep: *const c_char) -> i64 {
    let sstr = match CStr::from_ptr(str).to_str() {
        Ok(s) => s,
        Err(_) => return 0,
    };
    let sepstr = match CStr::from_ptr(sep).to_str() {
        Ok(s) => s,
        Err(_) => return 0,
    };

    let lstr: Vec<i64> = sstr
        .split(sepstr)
        .map(|s| match CString::new(s) {
            Ok(st) => st.into_raw() as i64,
            _ => 0,
        })
        .collect();
    Box::into_raw(Box::new(lstr)) as i64
}

#[no_mangle]
pub unsafe extern "C" fn str_join(handle: i64, sep: *const c_char) -> *const c_char {
    let empty = b"\0".as_ptr() as *const c_char;
    let sepstr = match CStr::from_ptr(sep).to_str() {
        Ok(s) => s,
        Err(_) => return empty,
    };

    let list = &mut *(handle as *mut Vec<i64>);

    let lstr: Vec<&str> = list
        .iter()
        .map(
            |h| match CStr::from_ptr(h.to_owned() as *const c_char).to_str() {
                Ok(s) => s,
                Err(_) => "",
            },
        )
        .collect();

    match CString::new(lstr.join(sepstr).to_owned()) {
        Ok(st) => st.into_raw(),
        _ => empty,
    }
}
