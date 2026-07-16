# tr4mpass Issue Sweep + Hardware-Researcher UX -- Technical Design
# Started: 2026-07-16
# Source vision: notes/fix-issues-hw-usability.md

## Brief
Resolve the ~10 root causes underlying the 56 open issues on `tr4m0ryp/tr4mpass`,
plus reshape the tool's UX for a hardware-fluent / code-shy security researcher.
Design work fanned out to 11 Opus 4.7 cluster subagents in parallel plus a
`/deep-research`-style adversarially-verified investigation of A12+ Path B
feasibility (finder + 3-vote refute panel per claim).

Every subagent brief opens with a fixed authorization block establishing this
is coordinated-disclosure / defensive research on a public research tool with
maintainer-owned repo and researcher-owned hardware, and explicitly excludes
end-user PII / mass targeting / detection-evasion / supply-chain compromise.

_This doc is populated by the background workflow. Sections below are stubs
until agent results are synthesized._

## Recommended Technical Design
_TBD -- populated after workflow completes._

## Decisions
_One T# entry per resolved technical question -- populated after workflow._

## Stack & Libraries
_TBD._

## Architecture
_TBD._

## Decisions Made For You (override in /refine)
_TBD._

## Key Findings
_F# entries populated from agent results._

## References
_R# entries populated from agent-cited URLs._

## Discarded Approaches
_TBD._

## Risks & Open Threads
_TBD._

## Build Plan
_TBD -- phased, dependency-ordered outline for /readyforlaunch._

---

## Workflow provenance
- **Fan-out shape:** one Opus 4.7 subagent per root-cause cluster (11 clusters).
- **A12+ deep research:** 5 web-search angles, then 3-vote adversarial verify
  per extracted claim (2-of-3 refutes kills the claim).
- **Ethical framing:** uniform AUTHORIZATION CONTEXT preamble on every brief.
- **Model:** `opus` (session default Opus 4.7) for all subagents.
- **Concurrency:** cluster agents + A12 finders + A12 verifiers all compete
  for the workflow's 16-agent slot pool.
