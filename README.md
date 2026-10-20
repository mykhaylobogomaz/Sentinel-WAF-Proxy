# Sentinel-WAF-Proxy

High-Performance C++20 Reverse Proxy with Layer 7 WAF Inspection and Resilience Engine.

## Architecture & Key Features

*   **1 MiB Strict Body Buffering**: Mitigates DoS and memory exhaustion attacks.
*   **JSON Smuggling & Parser-Disagreement Defense**: Performs control character inspection and structured payload validation.
*   **Resilient Circuit Breaker Pattern**: Handles backend failure cascades with Closed, Open, and Half-Open states.
*   **Asynchronous I/O Core**: Powered by modern C++20 and [Asio](https://think-async.com/Asio/).

## Tech Stack

*   **Language**: C++20
*   **Libraries**: Asio, nlohmann/json, GoogleTest
*   **Build System**: CMake (FetchContent)

## Building & Testing (Windows cmd.exe / MSVC)

```cmd
cmake -B build
cmake --build build --config Release
```

### Run Security Tests
```cmd
build\Release\waf_tests.exe
```

### Run Proxy
```cmd
build\Release\waf_proxy.exe 8080
```

## Example Usage

### Successful Request (200 OK)
```bash
curl -X POST -d '{"key": "value"}' http://localhost:8080/ -v
```

### Blocked Request (400 Bad Request)
```bash
# Request containing control character \x01
curl -X POST -d '{"key": "val"}'$'\x01' http://localhost:8080/ -v
```

## License

MIT License.
