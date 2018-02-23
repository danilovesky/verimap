# verimap

VeriMap is a design kit for converting single-rail RTL netlists into a dual-rail circuits resistant to DPA attacks.

The main features of the toolkit are:

* Easy to integrate in a conventional EDA flow.
* Generated circuits are hazard-free.
* Support for two architectures: self-timed dual-rail or clocked dual-rail.
* Generated circuits preserve DFT features incorporated at the logic synthesis stage.
* Negative logic optimisation to reduce the size of the circuit and shorten the critical path.
* Alternating spacer protocol to resist DPA attacks by making the power consumption data-independent.
