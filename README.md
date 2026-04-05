
# Toralizer 🧅

A lightweight system-level tool written in C that anonymizes any Linux command by routing its traffic through the **Tor network** — without modifying the original program at all.

```bash
toralize curl http://check.torproject.org
# Connected to Proxy
# Connected through the proxy. ✅
```

---

## How It Works

Toralizer compiles into a **shared library** (`.so`) and uses `LD_PRELOAD` to intercept the `connect()` syscall at runtime. When any program tries to make a network connection, Toralizer silently redirects it through Tor's SOCKS4 proxy running on `127.0.0.1:9050` — no changes to the original program needed.

```
Your Command → connect() intercepted → SOCKS4 Request → Tor Proxy (9050) → Destination
```

---

## Features

- 🔒 Routes any Linux command through Tor anonymously
- ⚡ Lightweight — written in pure C
- 🔗 Uses SOCKS4 protocol for proxy communication
- 🪝 Leverages `LD_PRELOAD` to hook `connect()` at runtime
- 🛠️ No modification to the target program required

---

## Requirements

- Linux / WSL (Ubuntu recommended)
- GCC
- Tor

---

## Installation

**1. Clone the repository**
```bash
git clone  https://github.com/adolf-rizzler848/-toralizer
cd toralizer
```

**2. Install and start Tor**
```bash
sudo apt update && sudo apt install -y tor
sudo service tor start        # use this on WSL (not systemctl)
```

**3. Run the setup script**
```bash
sudo chmod +x setup.sh
./setup.sh
```

Or **build manually:**
```bash
cd src
gcc toralize.c -o toralize.so -fPIC -shared -ldl -D_GNU_SOURCE
sudo cp toralize.so /usr/local/bin/
sudo cp toralize.h /usr/local/include/
```

**4. Add the alias** (so `toralize <cmd>` works)
```bash
echo 'alias toralize="LD_PRELOAD=/usr/local/bin/toralize.so"' >> ~/.bashrc
source ~/.bashrc
```

---

## Usage

```bash
toralize <any-command>
```

**Examples:**
```bash
toralize curl http://check.torproject.org
toralize curl http://check.torproject.org/api/ip
toralize wget http://example.com
```

> ⚠️ **Note:** Tor must be running before using Toralizer. Always run `sudo service tor start` first.

---

## Troubleshooting

| Issue | Fix |
|-------|-----|
| `Connection refused` | Tor isn't running — run `sudo service tor start` |
| Port 9050 not open | Verify with `ss -tlnp \| grep 9050` |
| Build fails | Install gcc: `sudo apt install build-essential` |
| HTTPS requests fail | SOCKS4 doesn't resolve hostnames — use IP or HTTP |

---

## Under the Hood

| Concept | What I learned |
|--------|----------------|
| **Socket Programming** | Raw TCP socket creation, connection management in C |
| **SOCKS4 Protocol** | Manually constructing proxy request/response structs, byte ordering with `htons()` |
| **Tor Internals** | Layered relay routing, how traffic is anonymized at a protocol level |
| **LD_PRELOAD** | Intercepting libc functions at runtime using shared libraries |

---

## Disclaimer

This tool is built for **educational purposes** and understanding of network programming concepts. Use responsibly and in accordance with your local laws.

---

## License

[MIT](LICENSE)

---

<p align="center">Built with 🧠 and way too many segfaults.</p>
