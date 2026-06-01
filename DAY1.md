# PhotonDB Day 1 Checklist

Day 1 is about locking down the server foundation before adding real database features.

## Goal

Make sure the current TCP server in `photondb.cpp` builds, runs, and echoes data reliably.

## Tasks

1. Build the project with:

```bash
g++ photondb.cpp -o day1
```

2. Start the server:

```bash
./day1
```

3. Open a second terminal and connect with:

```bash
nc 127.0.0.1 6379
```

4. Type a few messages and confirm the same text comes back.

5. Check that the server stays stable when the client disconnects and reconnects.

6. Clean up obvious code noise in `photondb.cpp` only if it helps readability without changing behavior.

7. Decide the command style PhotonDB will use later, even if you do not implement it yet.

## Success Criteria

- The code compiles without errors.
- The server starts successfully.
- A client can connect and receive echoed text.
- Port `6379` behaves as expected.

## What to avoid on Day 1

- Do not add database commands yet.
- Do not add persistence yet.
- Do not change the project into a different architecture before the server baseline is proven.

## End-of-day result

By the end of Day 1, PhotonDB should still be a simple TCP echo server, but a stable one that is ready for command parsing on Day 2.

### THANK YOU.

