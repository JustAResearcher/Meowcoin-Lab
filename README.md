# Meowcoin-Lab

Meowcoin consensus layer ported onto **Meowcoin Core v30.2** — a modern, maintained C++20 codebase.

## What Is This?

This repository takes the battle-tested Meowcoin Core v30.2 codebase and replaces its consensus rules with Meowcoin's:

- **Multi-algorithm PoW** — X16RV2 → KAWPOW → MEOWPOW progression, plus Scrypt-based AuxPoW (merged mining)
- **Asset layer foundation** — UTXO-based asset issuance, transfer, and management (Ravencoin-derived)
- **LWMA / DGW difficulty adjustment** — replacing Meowcoin's 2016-block retarget with per-block algorithms
- **AuxPoW (merged mining)** — Scrypt-based auxiliary proof-of-work for merge-mined blocks
- **Meowcoin P2P protocol** — custom message types, service flags, and network magic

## Build Status

| Item | Status |
|------|--------|
| Compiler | MSVC 19.44 / VS 2022 / C++20 / x64 |
| Errors | **0** |
| Warnings | **0** |
| Regtest smoke test | Genesis block connects, node reaches "Done loading" |

## Architecture

Built on Meowcoin Core v30.2 (commit `4d7d5f6b79`), with Meowcoin consensus from commit `5e22826efc`.

### PoW Algorithm Timeline

| Era | Algorithm | Activation (Mainnet) |
|-----|-----------|---------------------|
| Genesis → Oct 2022 | X16RV2 | Block 0 (nTime=1661730843) |
| Oct 2022 → Mar 2024 | KAWPOW | nTime ≥ 1662493424 |
| Mar 2024 → present | MEOWPOW | nTime ≥ 1710799200 |
| Merged-mining blocks | Scrypt (AuxPoW) | Any height (version flag) |

### Key Modified Files

| Area | Files |
|------|-------|
| Block header / versioning | `primitives/pureheader.h`, `primitives/block.cpp`, `primitives/block.h` |
| PoW hash algorithms | `pow_hash.cpp`, `crypto/ethash/`, `algo/`, `crypto/scrypt.cpp` |
| Consensus parameters | `kernel/chainparams.cpp`, `consensus/params.h` |
| Validation | `validation.cpp`, `pow.cpp`, `pow.h` |
| AuxPoW | `auxpow.cpp`, `auxpow.h`, `rpc/auxpow_miner.cpp` |
| Asset layer | `assets/` (foundation — DB, types, messages, rewards) |
| P2P protocol | `net_processing.cpp`, `protocol.h`, `net.h` |
| Difficulty | `pow.cpp` (LWMA + DGW) |

## Building

### Prerequisites

- Visual Studio 2022 (C++20)
- CMake 4.x+
- vcpkg at `C:\vcpkg` (or adjust path)

### Configure & Build

```powershell
cd meowcoin
cmake -B build -G "Visual Studio 17 2022" -A x64 `
  -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake `
  -DVCPKG_MANIFEST_NO_DEFAULT_FEATURES=ON `
  -DBUILD_GUI=OFF -DWITH_ZMQ=OFF -DENABLE_WALLET=OFF `
  -DBUILD_TESTS=OFF -DBUILD_BENCH=OFF -DBUILD_FUZZ_BINARY=OFF

cmake --build build --config Release --target meowcoind meowcoin-cli
```

### Smoke Test

```powershell
.\build\bin\Release\meowcoind.exe --printtoconsole --regtest --datadir=.\testrun
```

## Validation Report

See [VALIDATION_REPORT.md](VALIDATION_REPORT.md) for a detailed analysis of:

1. **PoW-on-load analysis** — where PoW checks happen, what was changed, comparison to Meowcoin
2. **Algo selection correctness** — hash algorithm dispatch, powLimit per-algo, X16R/X16RV2 transition
3. **Historical chain validation test plan** — step-by-step plan to prove equivalence against real Meowcoin chain data

## Next Steps

- [ ] Verify mainnet genesis hash and re-enable assertions
- [ ] Full IBD sync against Meowcoin mainnet
- [ ] Automated PoW test vectors for each era
- [ ] Checkpoint optimization for KAWPOW/MEOWPOW blocks
- [ ] Wallet integration
- [ ] GUI support

## License

Released under the terms of the MIT license. See [COPYING](COPYING) for details.

Based on [Meowcoin Core](https://github.com/Meowcoin-Foundation/Meowcoin) v30.2 and [Meowcoin](https://meowcoin.cc).
