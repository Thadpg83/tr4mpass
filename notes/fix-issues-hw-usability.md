# fix-issues-hw-usability -- Vision Notes
# Started: 2026-07-16

## The Idea
Two intertwined goals for the tr4mpass activation-lock **research tool**:
1. Work through the outstanding GitHub issues (56 open, 14 closed -- 70 total)
   and land real fixes, not one-offs.
2. Reshape the tool so a **researcher with hardware/iOS-internals experience
   but limited C/Linux tooling background** can drive it end-to-end without
   getting stuck on build systems, dependency mismatches, WSL quirks, or
   silent DFU-detection failures.

The fixing work will be fanned out to **Fable research subagents** (one per
problem cluster, running in parallel via `/flow:research`) so each defect gets
independent, focused investigation instead of a single omnibus pass. Every
subagent brief must open with a standing **research / coordinated-disclosure
authorization** preamble so the request context is unambiguous.

## Why / Intent
- Real researcher pain: the issues repeat the same handful of root causes,
  which means users bounce off before ever exercising the actual bypass paths.
- Target user is **hardware-fluent, code-shy**: they can hold Vol-/Vol+/Power
  in the right sequence, own the right cables, know their chip generation --
  but they should not have to diagnose `pkg-config`, patch a Makefile, or
  guess which libirecovery struct field renamed itself.
- Ethical framing: this is a **research + bug-bounty / coordinated-disclosure
  tool**. Every subagent research brief must state that context so downstream
  models treat the work as authorized security research, not a wild bypass
  request.
- Success = an experienced hardware researcher can `git clone`, run one
  script, get a clear diagnosis, and either proceed to a working bypass on a
  supported device or receive a precise, honest "not supported on this chip
  because X" answer.

## Scope
**In:**
- Root-cause fixes for every open issue that maps to a real defect
- Cross-platform build hardening (macOS, Debian/Ubuntu/Mint, Fedora, Arch, WSL)
- Diagnostic UX: doctor/preflight command, categorized error messages,
  honest per-chip support matrix, workflow docs (Path A vs Path B, manual
  overrides)
- Real feasibility investigation of Path B (A12+) via deep research on
  public prior art, not a stub
- Honest close messages for every open issue -- fixed, WON'T-FIX with
  reason, or DUPLICATE with pointer

**Out:**
- New CLI/GUI surfaces beyond the doctor + existing binary
- Bundling libimobiledevice / libirecovery / libusb sources (dep hell)
- Windows-native support (WSL only; Linux + macOS as native)
- Any assistance that presumes the researcher does NOT own the hardware
- Data-preservation guarantees; we document what is destructive, not
  invent new-preserving flows

## Surfaces & Pages
Concrete things the researcher touches:
- `./start.sh` -- the front-door script (dependency check, build, run)
- The `tr4mpass` binary CLI (with `--cpid`, `--ecid`, `--detect-only`, etc.)
- The diagnostic/log output (what the tool tells the user when something fails)
- `README.md` and any device-support matrix / compatibility page
- Optional: a "doctor" / preflight step that inspects the environment before
  attempting the bypass

## Key Concept Decisions
<!-- Filled in as we agree on things. -->

## Questions for Research
<!-- Sharp technical questions handed verbatim to /flow:research. Each one gets its own Fable subagent. -->

## Open Questions
- How do we group 70 issues into research clusters? One agent per issue is
  wasteful; one agent per root cause is likely right, but the grouping needs
  agreement.
- What does "usable for a hardware researcher" mean concretely -- better
  errors, a doctor command, a device-support matrix, all three, more?
- Do we scope this to "close every open issue" or "fix the root causes that
  close most issues + honestly mark the rest"?
- What is the exact ethical/authorization preamble every subagent brief must
  open with, so the framing is uniform and load-bearing?

## Non-Goals / Rejected Directions
<!-- Filled in as we reject directions. -->

## Issue-cluster snapshot (from the tracker sweep)
Grouping observed in the 70 issues, kept here so discussion can reference
clusters by name:

- **build-deps** -- libcurl / libusb-1.0 headers not found, WSL/Debian/Fedora
  variations (#70, #74, #67, #54, #51, #44, #21, #16*, #4*, #1*)
- **libirecovery-api-drift** -- `info->pid` vs `info->cpid`,
  `IRECV_SEND_OPT_DFU_NOTIFY_FINISH` undeclared (#55, #31, #24, #19)
- **dfu-serial-parsing** -- descriptor index likely off-by-one; CPID/ECID
  never parsed although `irecovery -q` sees them (#45 is the smoking gun;
  #65, #59, #27, #17, #10*, #8*, #6*, #52, #30, #22, #25, #7*)
- **chip-db-integrity** -- mismatched CPID entries across A5/A7/A10 (#53)
- **dfu-to-recovery-transition** -- won't auto-switch, "failed to reach
  dfuIDLE" (#61, #38, #40, #18)
- **path-a-checkm8-stage1** -- I/O error at stage 1/4 on A10 (#46, #47)
- **path-b-a12plus-incomplete** -- identity manipulation fails; core TODO
  admits SRAM offset unknown (#42, #10*, #5*, #12*, plus every "no A12+
  support" request: #57, #72, #75, #33, #43, #3*, #58, #23)
- **env-wsl-user-error** -- WSL USB passthrough, binary-is-a-directory,
  Windows git missing, sudo confusion (#2*, #20, #29, #34, #37, #35, #28,
  #30, #25, #48)
- **workflow-and-manual-overrides** -- how to use `--cpid`/`--ecid`, when to
  use Path A vs Path B (#76, #62, #36)
- **product-questions** -- untethered? cellular after bypass? data preserved?
  MEID/Chinese variants? (#73, #13, #14, #64, #58, #50)
- **research-thread** -- mobileactivationd forging + sealed root partition
  discussion (#77)
- **low-info** -- vague / screenshot-only / duplicates (#60, #15, #33, #11*)

`*` = closed issue but same root cause.
