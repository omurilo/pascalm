use std::env;
use std::path::Path;
use std::process::Command;

fn main() {
    lalrpop::process_root().unwrap();

    // Compile runtime_lib.rs to LLVM bitcode
    let out_dir = env::var("OUT_DIR").unwrap();
    let dest_path = Path::new(&out_dir).join("runtime_lib.bc");

    let status = Command::new("rustc")
        .args(&[
            "src/runtime_lib.rs",
            "--crate-type",
            "lib",
            "--emit",
            "llvm-bc",
            "-o",
            dest_path.to_str().unwrap(),
            "-C",
            "opt-level=3",
            "-C",
            "panic=abort",
            "--edition",
            "2021",
        ])
        .status()
        .expect("Failed to run rustc to compile runtime");

    if !status.success() {
        panic!("rustc failed to compile runtime_lib.rs");
    }

    // Compile everything in src/stdlib/
    let stdlib_path = Path::new("src/stdlib");
    if stdlib_path.exists() {
        for entry in std::fs::read_dir(stdlib_path).unwrap() {
            let entry = entry.unwrap();
            let path = entry.path();
            if path.is_dir() {
                let lib_name = path.file_name().unwrap().to_str().unwrap();
                let cargo_toml = path.join("Cargo.toml");
                let lib_rs = path.join("src/lib.rs");
                let dest_path = Path::new(&out_dir).join(format!("lib{}.a", lib_name));

                if cargo_toml.exists() {
                    // Use Cargo for libraries with dependencies
                    let status = Command::new("cargo")
                        .args(&[
                            "build",
                            "--manifest-path",
                            cargo_toml.to_str().unwrap(),
                            "--release",
                        ])
                        .status()
                        .expect("Failed to run cargo build for stdlib");

                    if status.success() {
                        // Recursively find the .a file in target
                        let output = Command::new("find")
                            .args(&[
                                path.join("target").to_str().unwrap(),
                                "-name",
                                &format!("lib{}.a", lib_name),
                            ])
                            .output()
                            .expect("Failed to run find");

                        let stdout = String::from_utf8_lossy(&output.stdout);
                        let artifact_path = stdout
                            .lines()
                            .filter(|l| l.contains("release") && !l.contains("deps"))
                            .next()
                            .unwrap_or(stdout.trim().lines().next().unwrap_or(""));

                        if !artifact_path.is_empty() {
                            std::fs::copy(artifact_path, &dest_path).unwrap();
                        } else {
                            panic!("Could not find built artifact lib{}.a in target", lib_name);
                        }
                    } else {
                        panic!("cargo build failed for stdlib: {}", lib_name);
                    }
                } else if lib_rs.exists() {
                    // Fallback to direct rustc for simple libraries
                    let status = Command::new("rustc")
                        .args(&[
                            lib_rs.to_str().unwrap(),
                            "--crate-type",
                            "staticlib",
                            "-o",
                            dest_path.to_str().unwrap(),
                            "-C",
                            "opt-level=3",
                            "--edition",
                            "2021",
                        ])
                        .status()
                        .expect("Failed to run rustc for stdlib");
                    if !status.success() {
                        panic!("rustc failed to compile stdlib: {}", lib_name);
                    }
                }
                println!("cargo:rerun-if-changed={}", path.display());
            }
        }
    }

    // Generate a helper file to include all libraries automatically
    let mut libs_rs = String::from("pub struct StdLibAsset {\n    pub name: &'static str,\n    pub source: &'static str,\n    pub archive: &'static [u8],\n}\n\n");
    libs_rs.push_str("pub fn get_stdlib_assets() -> Vec<StdLibAsset> {\n    vec![\n");

    if stdlib_path.exists() {
        for entry in std::fs::read_dir(stdlib_path).unwrap() {
            let entry = entry.unwrap();
            let path = entry.path();
            if path.is_dir() {
                let lib_name = path.file_name().unwrap().to_str().unwrap();

                // Find Pascal interface file
                let mut pas_file = path.join(format!("{}.pas", lib_name));
                if !pas_file.exists() {
                    pas_file = path.join(format!("{}.pascalm", lib_name));
                }

                let source_include = if pas_file.exists() {
                    format!(
                        "include_str!(concat!(env!(\"CARGO_MANIFEST_DIR\"), \"/{}\"))",
                        pas_file.to_str().unwrap()
                    )
                } else {
                    "\"\"".to_string()
                };

                libs_rs.push_str(&format!(
                    "        StdLibAsset {{ name: \"{}\", source: {}, archive: include_bytes!(concat!(env!(\"OUT_DIR\"), \"/lib{}.a\")) }},\n",
                    lib_name, source_include, lib_name
                ));
            }
        }
    }
    libs_rs.push_str("    ]\n}\n");
    std::fs::write(Path::new(&out_dir).join("libs.rs"), libs_rs).unwrap();

    println!("cargo:rerun-if-changed=src/runtime_lib.rs");
}
