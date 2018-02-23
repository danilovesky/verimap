# verimap

VeriMap is a tool for converting single-rail RTL netlists into a
dual-rail circuits resistant to DPA attacks. Its main features are:

* Easy to integrate in a conventional EDA flow.

* Generated circuits are hazard-free and preserve DFT features
incorporated at the logic synthesis stage.

* Support for two architectures: self-timed dual-rail or clocked
dual-rail.

* Negative logic optimisation to reduce the size of the circuit and
shorten the critical path.

* Alternating spacer protocol to resist DPA attacks by making the power
consumption data-independent.
