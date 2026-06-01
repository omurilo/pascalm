use axum::{routing::{get, post}, Router};
use std::ffi::{CStr, CString};
use std::os::raw::c_char;
use std::sync::OnceLock;
use tokio::runtime::Runtime;

// Global runtime to ensure all async tasks share the same engine
static RUNTIME: OnceLock<Runtime> = OnceLock::new();

fn get_runtime() -> &'static Runtime {
    RUNTIME.get_or_init(|| Runtime::new().expect("Failed to create Tokio runtime"))
}

#[repr(C)]
pub struct HttpResponse {
    pub inner_ptr: *mut std::ffi::c_void,
}

#[repr(C)]
pub struct HttpListener {
    pub inner_ptr: *mut std::ffi::c_void,
}

#[repr(C)]
pub struct HttpRouter {
    pub inner_ptr: *mut std::ffi::c_void,
}

#[no_mangle]
pub unsafe extern "C" fn HttpGet(url_ptr: *const c_char) -> HttpResponse {
    let c_str = unsafe { CStr::from_ptr(url_ptr) };
    let url = c_str.to_str().unwrap_or("invalid utf8").to_string();

    println!("[Rust StdLib] HttpGet: {}", url);
    let resp = get_runtime().block_on(async move { 
        reqwest::get(url).await.expect("Request failed") 
    });

    HttpResponse {
        inner_ptr: Box::into_raw(Box::new(resp)) as *mut std::ffi::c_void,
    }
}

#[no_mangle]
pub unsafe extern "C" fn HttpPost(url_ptr: *const c_char, body_ptr: *const c_char) -> HttpResponse {
    let url = unsafe { CStr::from_ptr(url_ptr) }.to_str().unwrap().to_string();
    let body = unsafe { CStr::from_ptr(body_ptr) }.to_str().unwrap().to_string();

    println!("[Rust StdLib] HttpPost: {}", url);
    let resp = get_runtime().block_on(async move {
        reqwest::Client::new()
            .post(url)
            .body(body)
            .send()
            .await
            .expect("Request failed")
    });

    HttpResponse {
        inner_ptr: Box::into_raw(Box::new(resp)) as *mut std::ffi::c_void,
    }
}

#[no_mangle]
pub extern "C" fn HttpJson(resp: HttpResponse) -> *const c_char {
    if resp.inner_ptr.is_null() { return std::ptr::null(); }
    
    let response = unsafe { Box::from_raw(resp.inner_ptr as *mut reqwest::Response) };
    let json_text = get_runtime().block_on(async move { 
        response.text().await.unwrap_or_else(|_| "{}".to_string()) 
    });

    let c_string = CString::new(json_text).unwrap();
    c_string.into_raw()
}

#[no_mangle]
pub extern "C" fn HttpListen(port: i32) -> HttpListener {
    println!("[Rust StdLib] Listening on 0.0.0.0:{}", port);
    let listener = get_runtime().block_on(async move {
        tokio::net::TcpListener::bind(format!("0.0.0.0:{}", port))
            .await
            .expect("Failed to bind port")
    });

    HttpListener {
        inner_ptr: Box::into_raw(Box::new(listener)) as *mut std::ffi::c_void,
    }
}

#[no_mangle]
pub extern "C" fn NewHttpRouter() -> HttpRouter {
    let app: Router<()> = Router::new().route("/health", get(|| async { "PASCALM_CORE_UP" }));

    HttpRouter {
        inner_ptr: Box::into_raw(Box::new(app)) as *mut std::ffi::c_void,
    }
}

pub type PascalHandler = extern "C" fn() -> *const c_char;

#[no_mangle]
pub unsafe extern "C" fn HttpRoute(
    router: HttpRouter,
    path: *const c_char,
    method: *const c_char,
    handler: PascalHandler,
) -> HttpRouter {
    let axum_router = (*(router.inner_ptr as *mut Router<()>)).clone();
    let path_str = CStr::from_ptr(path).to_str().unwrap().to_string();
    let method_str = CStr::from_ptr(method).to_str().unwrap().to_string().to_lowercase();

    println!("[Rust StdLib] Route registered: {} [{}]", path_str, method_str);
    
    let new_router = match method_str.as_str() {
        "get" => {
            let p = path_str.clone();
            axum_router.route(&path_str, get(move || async move {
                println!("[Rust StdLib] Request received: GET {}", p);
                let result_ptr = handler();
                if result_ptr.is_null() { return String::new(); }
                let res = CStr::from_ptr(result_ptr).to_string_lossy().into_owned();
                println!("[Rust StdLib] Pascal response length: {}", res.len());
                res
            }))
        },
        "post" => {
            let p = path_str.clone();
            axum_router.route(&path_str, post(move || async move {
                println!("[Rust StdLib] Request received: POST {}", p);
                let result_ptr = handler();
                if result_ptr.is_null() { return String::new(); }
                CStr::from_ptr(result_ptr).to_string_lossy().into_owned()
            }))
        },
        _ => panic!("Method {} not supported", method_str),
    };
    
    // We update the pointer to the new router
    std::ptr::drop_in_place(router.inner_ptr as *mut Router<()>);
    
    HttpRouter {
        inner_ptr: Box::into_raw(Box::new(new_router)) as *mut std::ffi::c_void,
    }
}

#[no_mangle]
pub unsafe extern "C" fn HttpServe(listener: HttpListener, router: HttpRouter) {
    let axum_listener = *Box::from_raw(listener.inner_ptr as *mut tokio::net::TcpListener);
    let axum_router = *Box::from_raw(router.inner_ptr as *mut axum::Router);
    
    println!("[Rust StdLib] Server entering blocking loop...");
    get_runtime().block_on(async move {
        axum::serve(axum_listener, axum_router).await.expect("Server failed to run");
    });
}
