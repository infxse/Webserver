# C Webserver

A simple HTTP server written in C from scratch. No frameworks, no libraries — just raw sockets and syscalls.

Built as a side project to learn C and low-level security concepts.

## Features

- TCP socket server on port 8080
- Serves static HTML files from `www/`
- HTTP/1.1 responses with proper headers
- 404 handling for missing files
- Graceful shutdown on Ctrl+C (SIGINT)
- Debug logging to stderr (compile-time toggle)

## Planned

- Parse incoming HTTP requests (method, path, headers)
- Route requests to different files based on path
- Path traversal protection, request size limits, slow client timeouts
- TLS with OpenSSL

## Requirements

- GCC or Clang
- macOS or Linux
- Make

## Setup

Clone the repo and build:

```bash
git clone https://github.com/YOUR_USER/YOUR_REPO.git
cd YOUR_REPO
make build
```

## Usage

Start the server:

```bash
./server
```

Open http://127.0.0.1:8080 in a browser, or test with curl:

```bash
curl http://127.0.0.1:8080/
```

Stop with `Ctrl+C`.

## Make commands

| Command | What it does |
|---------|-------------|
| `make` / `make help` / `make '?'` | Shows available commands |
| `make build` | Compiles changed files and links the `server` binary |
| `make rebuild` | Cleans everything and compiles from scratch |
| `make clean` | Removes all `.o` files and the `server` binary |

## Project structure

```
├── Makefile
├── src/
│   ├── main.c       entry point, signal handling
│   ├── server.c/h   socket setup, bind, listen, accept loop
│   ├── http.c/h     HTTP response building
│   ├── file.c/h     file reading
│   └── log.h        debug logging macro
└── www/
    └── index.html   default page
```

## Customization

Drop your own HTML files into `www/` — the server currently serves `www/index.html` on every request. Request-based routing is coming next.

To disable debug output, set `DEBUG_MODE` to `0` in `src/log.h`.

Port and max connections can be changed in `src/server.h`.
