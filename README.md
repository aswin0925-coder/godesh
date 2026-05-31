# PhotonDB

PhotonDB is an end-semester project that aims to become a Redis-inspired key-value database.
The current codebase contains the first networking prototype: a small TCP server that listens on port `6379` and echoes back whatever a client sends.

## Project overview

The goal of PhotonDB is to grow from a basic socket server into a simple in-memory database with commands, persistence, and client interaction.
Right now, the project is focused on proving the networking layer works correctly.

## Current features

- Starts a TCP server using POSIX sockets
- Binds to `0.0.0.0:6379`
- Accepts one client at a time
- Reads data from the client
- Sends the same data back to the client

## Requirements

- Linux or another Unix-like system
- `g++`
- `nc` (netcat) for testing, or `telnet` as a fallback

## Getting started

### 1. Open the project folder

Make sure your terminal is inside the folder that contains `photondb.cpp`.

### 2. Build the project

Run:

```bash
g++ photondb.cpp -o day1
```

If the command succeeds, it creates an executable named `day1`.

### 3. Start PhotonDB

Run:

```bash
./day1
```

The terminal will stay busy because the server is now waiting for a client connection.

### 4. Open a second terminal

Keep the server running in the first terminal, then open another terminal in the same folder.

### 5. Connect to the server

Run:

```bash
nc 127.0.0.1 6379
```

### 6. Send a message

Type any text and press Enter.
PhotonDB should send the same text back.

### 7. Stop the server

Press `Ctrl+C` in the server terminal to stop PhotonDB.

## Quick test

You can also test it with a single command:

```bash
echo "hello" | nc 127.0.0.1 6379
```

Expected output:

```bash
hello
```

## Roadmap

Planned next steps for PhotonDB include:

- Adding key-value commands such as `SET` and `GET`
- Storing data in memory instead of echoing raw input
- Supporting multiple clients more cleanly
- Adding persistence so data survives restarts
- Building a small client protocol similar to Redis

## Limitations

- The server is single-threaded, so it handles one client at a time.
- The current buffer size is 1024 bytes.
- Port `6379` may already be used by another service such as Redis.
- This version is only the networking foundation, not a full database yet.

## Troubleshooting

- If the build fails, make sure `g++` is installed.
- If you see `Bind failed`, another program may already be using port `6379`.
- If `nc` is not installed, try `telnet 127.0.0.1 6379` instead.
