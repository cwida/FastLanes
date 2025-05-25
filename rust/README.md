# Publishing & Building the **fls‑rs** Rust crate

This guide walks you (and CI) through every step required to turn the FastLanes Rust bindings into a versioned release
on [https://crates.io](https://crates.io). It assumes you are in the project‑root and have the tooling listed below.

---

## 1 Prerequisites

| Tool                  | Minimum             | Why                                                                                  |
|-----------------------|---------------------|--------------------------------------------------------------------------------------|
| **Rust toolchain**    | 1.77.0 (stable)     | Needed for `cargo set-version`. Older toolchains work if you install **cargo‑edit**. |
| **cargo‑edit**        | latest              | Autoinstalled by the Makefile when missing.                                          |
| **C & C++ compilers** | clang/gcc           | CMake builds the C++ core; `cxx-build` compiles the bridge shim.                     |
| **CMake**             | ≥3.18               | Generates the FastLanes static library.                                              |
| **Git**               | with annotated tags | The Makefile reads the latest `vX.Y.Z` tag to version the crate.                     |

> **Tip:** On fresh CI runners nothing but `rustup` and the host compiler toolchain are usually pre‑installed. The
> Makefile’s `version-bump-rust` rule installs `cargo-edit` automatically if the sub‑command is missing.

---

## 2 Project layout recap

```
FastLanes/
├─ mk/               # this Makefile lives here
├─ rust/             # Cargo workspace member (crate root)
│  ├─ src/
│  ├─ build.rs       # emits VERGEN_* vars & builds C++
│  └─ vendor/fastlanes/ (optional)  # vendored fallback for crates.io build
├─ include/ & src/   # C++ headers & source used when building from Git checkout
└─ CMakeLists.txt    # top‑level CMake build for C++ core
```

---

## 3 One‑liner cheat‑sheet

```bash
# 1. Tag the release (annotated tag `v0.2.0`)
git tag -s v0.2.0 -m "FastLanes 0.2.0"

# 2. Dry‑run the publish to be safe
make dry-run-rust       # rewrites Cargo.toml → 0.2.0

# 3. Publish for real
make publish-rust       # uploads if the dry‑run looked good
```

All other common tasks:

| Action                          | Command                 |
|---------------------------------|-------------------------|
| **Build (optimised)**           | `make build-rust`       |
| Install to local prefix         | `make install-rust`     |
| Run example program             | `make run-rust-example` |
| Format Rust sources             | `make rust-format`      |
| Clean artefacts & vendored copy | `make clean-rust`       |

---

## 4 How the Makefile automates versioning

1. `version-bump-rust` (called by both *publish* targets) executes

   ```make
   GIT_TAG := $(shell git describe --tags --abbrev=0)
   SEMVER  := $(patsubst v%,%,$(GIT_TAG))
   ```

   extracting **`0.2.0`** from the last tag `v0.2.0`.
2. It ensures **`cargo-set-version`** is available:

   ```make
   command -v cargo-set-version || cargo install cargo-edit -q
   ```
3. Finally, it writes that semver into *every* `Cargo.toml` in the
   workspace:

   ```make
   cargo set-version 0.2.0 --manifest-path rust/Cargo.toml --workspace
   ```
4. The subsequent `cargo publish` therefore uploads `fls-rs v0.2.0`.

### Common pitfalls

| Symptom                                     | Cause & Fix                                                                                               |
|---------------------------------------------|-----------------------------------------------------------------------------------------------------------|
| `✘ No git tag found`                        | You forgot to create an annotated tag. Run `git tag -s vX.Y.Z -m "…"`.                                    |
| `no such command: set-version`              | Toolchain <1.77 and **cargo-edit** not installed. The rule now auto‑installs it.                          |
| Crate builds but prints `v0.0.0` at runtime | You’re using `env!("CARGO_PKG_VERSION")` instead of the Git‑derived constant `env!("VERGEN_GIT_SEMVER")`. |

---

## 5 Publishing from CI

1. **GitHub Actions secret:** add `CRATES_IO_TOKEN`.
2. Checkout, install LLVM/Clang and libc++ (see existing workflow).
3. Add a final job step:

   ```yaml
   - name: Publish fls-rs
     run: |
       cargo login $CRATES_IO_TOKEN
       make publish-rust
   ```

   Because the Makefile bumps the manifest first, the workflow will
   fail early if no Git tag is present.

---

## 6 Updating the vendored C++ sources

When you change headers or C++ code in the main workspace:

```bash
make update-fastlanes-src  # copies src/include → rust/vendor/… & commits
```

This ensures the crate remains buildable when fetched from
crates.io (where the Git workspace is *not* available).

---

## 7 FAQ

<details>
<summary>What if I need to yank a version?</summary>

```bash
cargo yank --vers 0.2.0
```

Remember to tag the repo with a new point‑release afterwards.

</details>

<details>
<summary>The C++ build fails on crates.io but works locally.</summary>

Make sure you ran `make update-fastlanes-src` before publishing and that
no absolute include paths leak into the build (`-I/usr/local/include`).

</details>

<details>
<summary>Why don’t we inject the Git tag directly from build.rs?</summary>

Cargo locks the crate version from `Cargo.toml` **before** running the
build script. Overwriting it afterwards has no effect, so we edit the
manifest up‑front instead.

</details>

---

Happy releasing! 🎉
