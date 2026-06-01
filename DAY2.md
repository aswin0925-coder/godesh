# PhotonDB Day 2 Checklist

Day 2 is about the command-parser stage. The server no longer just echoes raw bytes; it now understands simple commands and returns protocol-style responses.

## Goal

Verify that PhotonDB correctly handles line-based commands and responds in a predictable way.

## What was added

- A `CommandResponse` struct for responses and connection close handling
- A `trim_copy` helper to clean up input
- A `send_all` helper to make sure full responses are sent
- A `handle_command` parser for command routing
- Line-based request handling with newline-delimited commands
- Multi-command sessions over one client connection

## Working commands

- `PING` → returns `PONG`
- `ECHO <message>` → returns the message
- `HELP` → lists available commands
- `QUIT` → returns `BYE` and closes the connection

## Placeholder commands

- `SET` → returns `ERR storage layer not implemented yet`
- `GET` → returns `ERR storage layer not implemented yet`
- `DEL` → returns `ERR storage layer not implemented yet`

## How to test

### 1. Build and run

```bash
g++ photondb.cpp -o day1
./day1
```

### 2. Open a second terminal and connect

```bash
nc 127.0.0.1 6379
```

### 3. Test commands

```text
PING
ECHO hello
HELP
SET mykey myvalue
GET mykey
DEL mykey
QUIT
```

## Expected results

- `PING` → `PONG`
- `ECHO hello` → `hello`
- `HELP` → command list
- `SET`, `GET`, `DEL` → placeholder storage error
- `QUIT` → `BYE`, then connection closes

## Success criteria

- The code compiles without errors.
- The server starts successfully.
- The parser responds to supported commands correctly.
- Placeholder commands fail cleanly.
- The server stays stable across repeated client sessions.

## What to avoid on Day 2

- Do not add real storage yet.
- Do not add persistence yet.
- Do not add concurrency yet.
- Do not change the command format yet.

## Next step

Day 3 should focus on improving the command flow and preparing the storage layer for `SET` and `GET`.

### THANK YOU
