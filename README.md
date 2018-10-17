# InvisiSpec-1.0
This repository contains the gem5 implementation of InvisiSpec, a defense mechanism against speculative execution on cache hierarchy.
Please check our paper for design details.

InvisiSpec: Making Speculative Execution Invisible in the Cache Hierarchy.
Mengjia Yan†, Jiho Choi†, Dimitrios Skarlatos, Adam Morrison, Christopher W. Fletcher, and Josep Torrellas. 
Proceedings of the 51th International Symposium on Microarchitecture (**MICRO**), October 2018.


## Major changes in the simulator.

We made following major changes in gem5:
* modify "DerivO3" classes to tracking when instructions reach visibility point, and issue load requests accordingly
* modify "MESI_Two_Level" coherence protocol by adding 3 new transactions: SpecGetS, Expose, Validation
* add a SpecBuffer at each L1, and per-core SpecBuffer LLC


## How to run the simulator?

We added several configuration paramters to the simulator for different modes of InvisiSpec as follows.
* --scheme: configure the 5 modes of the simulator
  * UnsafeBaseline: the unmodified out-of-order CPU
  * SpectreSafeFence: simulate a fence after every branch instruction.
  * FuturisticSafeFence: simulate a fence before every load instruction.
  * SpectreSafeInvisibleSpec: InvisiSpec working under Spectre threat model.
  * FuturisticSafeInvisibleSpec: InvisiSpec working under Futuristic threat model.
* --needsTSO: configure the consistency model
  * True: use TSO
  * False: use RC


Please check `./exp_script/` for example scripts.
The simulator can work using x86 and ARM ISAs. And we have tested it on SPEC and PARSEC benchmarks.


