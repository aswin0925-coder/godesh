# Day 1 TCP Echo Server

This project is a small C++ TCP echo server built with POSIX sockets.
It listens on port `6379`, accepts one client at a time, and sends back
whatever the client types.

## What this project does

- Creates a TCP server socket
- Binds to `0.0.0.0:6379`
- Waits for a client connection
- Reads data from the client
- Echoes the same data back

## Requirements

- Linux or another Unix-like system
- `g++`
- `nc` (netcat) for testing, or `telnet` as a fallback

## Step-by-step setup

### 1. Open the project folder

Make sure your terminal is inside the folder that contains `day1.cpp`.

### 2. Build the program

Run:

```bash
g++ day1.cpp -o day1
```

If the command succeeds, it creates an executable named `day1`.

### 3. Start the server

Run:

```bash
./day1
```

The terminal will look like it is waiting. That is normal because the server is
listening for a client connection.

### 4. Open a second terminal

Keep the server running in the first terminal, then open another terminal in the
same folder.

### 5. Connect to the server

Run:

```bash
nc 127.0.0.1 6379
```

### 6. Type a message

Type any text and press Enter. The server should send the same text back.

### 7. Stop the program

Press `Ctrl+C` in the server terminal to stop the server.

## Example test

```bash
./day1
```

In another terminal:

```bash
echo "hello" | nc 127.0.0.1 6379
```

Expected output:

```bash
hello
```

## Notes

- The server is single-threaded, so it handles one client at a time.
- The input buffer is 1024 bytes.
- Port `6379` may already be in use by another service, so you may need to stop
	that service or change the port in `day1.cpp`.

## Troubleshooting

- If build fails, check that `g++` is installed.
- If the server says `Bind failed`, another program may already be using port
	`6379`.
- If `nc` is not installed, try `telnet 127.0.0.1 6379` instead.
