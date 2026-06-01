# PhotonDB

PhotonDB is a lightweight, Redis-inspired TCP server written in C++.
It currently listens on port `6379` and processes simple text commands.

## Project overview

The goal of PhotonDB is to grow from a basic socket server into a small in-memory database with commands, persistence, and client interaction.
Right now, the project focuses on proving the networking layer and command parsing work correctly.

## Current features

- Starts a TCP server using POSIX sockets
- Binds to `0.0.0.0:6379`
- Accepts one client at a time
- Processes line-based text commands
- Supports `PING`, `ECHO <message>`, `HELP`, and `QUIT`
- Recognizes `SET`, `GET`, and `DEL`, but storage is not implemented yet

## Requirements

- Linux or another Unix-like system
- `g++`
- `nc` (netcat) for testing, or `telnet` as a fallback

## Getting started

### 1. Open the project folder

Make sure your terminal is inside the folder that contains `photondb.cpp`.

### 2. Build the project

```bash
g++ photondb.cpp -o day1
```

If the command succeeds, it creates an executable named `day1`.

### 3. Start PhotonDB

```bash
./day1
```

The terminal will stay busy because the server is waiting for a client connection.

### 4. Open a second terminal

Keep the server running in the first terminal, then open another terminal in the same folder.

### 5. Connect to the server

```bash
nc 127.0.0.1 6379
```

### 6. Try commands

Type commands one per line and press Enter.

```text
PING
ECHO hello
HELP
QUIT
```

Expected behavior:

- `PING` returns `PONG`
- `ECHO hello` returns `hello`
- `HELP` lists available commands
- `QUIT` closes the connection

### 7. Stop the server

Press `Ctrl+C` in the server terminal to stop PhotonDB.

## Quick test

```bash
echo "PING" | nc 127.0.0.1 6379
```

Expected output:

```bash
PONG
```

## Roadmap

Planned next steps for PhotonDB include:

- Adding real `SET` and `GET` storage
- Storing data in memory instead of returning placeholder errors
- Supporting multiple clients more cleanly
- Adding persistence so data survives restarts
- Building a small client protocol similar to Redis

## Limitations

- The server is single-threaded, so it handles one client at a time.
- The current buffer size is 1024 bytes.
- `SET`, `GET`, and `DEL` still return placeholder responses.
- Port `6379` may already be used by another service such as Redis.

## Troubleshooting

- If the build fails, make sure `g++` is installed.
- If you see `Bind failed`, another program may already be using port `6379`.
- If `nc` is not installed, try `telnet 127.0.0.1 6379` instead.
