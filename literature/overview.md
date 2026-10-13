# Overview

## Comparison of Frameworks for High-Performance Packet IO

Comparison netmap, PF_RING_ZC and Intel DPDK.

Running on the same CPU, equipped with the same 10 Gbit NICs while using packet forwarders applying the same algorithm for
each of three frameworks respectively to provide a fair comparison between them.

DPDK and PF_RING_ZC perform packet processing entirely in user space.
Linux does entire packet handling in kernel space, provides high degree of security and robustness.
netmap uses both, kernel and user space.
Performance DPDK & PF_RING_ZC > netmap

## Performance Implications at the Intersection of AF_XDP and Programmable NICs

Performative AF_XDP (Native Mode) needs a XDP Driver for the NIC.

Native XDP runs in the Kernel -> Each packet travels through the PCI connection in to the kernel -> CPU is overloaded at high bandwidths.

Offloaded XDP -> Offloading XDP Driver to the Smart NIC -> Special NIC is needed, hardware development is expensive -> CPU only gets a fraction of packets -> Complex Smart NIC (entire logic of AF_XDP is translated in hardware).

Hybrid discussed in the paper -> Uses a less complex Smart NIC (executes a eBPF program and filters packets) -> If a packet should be forwared to AF_XDP, executes a eBPF program in the kernel which then redirects packet to AF_XDP socket.
Redirect logic of AF_XDP is implemented in Kernel instead of Hardware.

To do this, paper updates OpenNIC driver to support loading of eBPF programs.

Unlike other kernel-bypass libraries (e.g. DPDK), AF_XDP enables mixed mode deployment -> NIC can share between kernel-bypass applications and traditional linux socket API (no bypass).

## The eXpress Data Path: Fast Programmable Packet Processing in the Operating System Kernel

Introduction of XDP
Network stacks in general purpose operating systems are typically optimised for flexibility, which means they perform too many operations per packet to be able to keep up with these high packet rates.

Performance does not quite match DPDK, but has offers other advantages:

- Cooperative integration into regular network stack
- Transparent to applications running on the host
- Does not require dedicated full CPU cores to packet processing

Benchmark XDP vs DPDK
Focus on three metrics:

- Packet drop performance
- CPU usage: XDP scales CPU usage with packet load, instead of dedicating CPU cores exclusively to packet processing.
- Packet forwarding performance

Challenge is processing many packets per second, rather then many bytes per second.
Repeat tests with increasing number of cores dedicated to packet processing.

DPDK dedicates a full core to packet processing, CPU usage is always pegged at 100%.

## A survey on accelerating technologies for fast network packet processing in Linux environments

Gives overview for fast netwrok packet processors.

### Hardware solutions

- TCP offloaded engines
- RDMA - Remote Direct Memory Access
- Programmable NICs
- GPU packet processing

### Software solutions

- Kernel bypass
- netmap
- DPDK
- RF_RING ZC

### In-Kernel processing

- XDP

## uXDP: Frictionless XDP Deployments in Userspace

XDP runs in user space via DPDK reimplementation.
Two modi:

- Packet is written into user space (shared memory). Good if most of the packets are processed / dropped in user space. Bad If `XDP_PASS` then packet copied back into the kernel via a virtual interface (expensive).
- AF_XDP Mode: Packet is written into kernel but directly transfered into user space. Good if many packets pass through kernel `XDP-PASS`. Bad if most of them are processed in user space.

No code change -> uXDP allows to run eBPF Program in DPDK.
