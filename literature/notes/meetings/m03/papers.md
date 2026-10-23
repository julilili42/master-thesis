## „Comparison of Frameworks for High-Performance Packet IO“ (2015) [1]

### Goal

Survey and Analysis of most prominent high-performance packet IO Frameworks. Introduction of cost model, to predict throughput.

### Measured technologies

Netmap, PF_RING ZC, DPDK

### Metrics

- Throughput vs CPU Load cycle
- Throughput vs. Memory access size
- L1, L2, L3 Cache misses for DPDK
- Throughput vs. Task CPU cycles vs Batch size
- Latency vs. Batch size

### Use-Cases

L2FWD with emulated CPU task and random memory access.

### Setup

Three distinct servers: Source (MoonGen packet generator), forwarder with Framework and sink.
Use minimum packet size for all measurements, to maximize load on framework.

### Linkrates

10 Gbit/s

### Notes

Available CPU cycles main limiting factor of software packet processing. Influenced by overhead caused by the complexity of packet processing, time CPU spends waiting for data to arrive in cache, effect of different batch sizes.
Introduction of task emulator

- CPU tasks: Software to produce constant load per packet on the CPU (number of CPU cycles to wait).
- Memory tasks: Access data structures with randomized addresses while transferring packets.

[1] https://ieeexplore.ieee.org/document/7110118

## „The eXpress Data Path: Fast Programmable Packet Processing in the Operating System Kernel“ (2018) [2]

### Goal

Provide alternative to kernel bypass. Keeps application isolation, security mechanisms, high performance and integrates with existing systems.

### Measured technologies

XDP, DPDK, Linux kernel network stack

### Metrics:

- Paket drop: Throughput (Mpps) vs. #cores
- CPU Usage vs offered load (one core): Measured with mpstat [3]
- Throughput (Mpps) vs #cores: DPDK (different NIC) vs XDP (same NIC) vs XDP (different NIC)
- Packet forwarding latency: Average, maximum, < 10 mu s

- L3-Routing Performance: Linux Network Stack vs XDP
- DOS Protection: Parse packet header, perform tests & drop packet
- Load balancing

### Use-Cases

- L3 routing: XDP table lookup vs Linux routing, single route and full BGP table (Mpps on single core)
- DoS mitigation: Parse header, perform tests, drop.
- L4 Load balancing: Katran [4], Mpps vs #cores

### Setup

TRex packet generator connected to DUT with two NICs. Cores selected via Receive Side Scaling (RSS)

### Linkrates

100 Gbit/s

[2] https://dl.acm.org/doi/10.1145/3281411.3281443

[3] https://man7.org/linux/man-pages/man1/mpstat.1.html

[4] https://github.com/facebookincubator/katran

## „Demystifying the Performance of XDP BPF“ (2019) [5]

### Goal

When does eBPF/XDP offloading pay off when is it detrimental. Offloading targets: Kernel (device driver) and SmartNIC

### Measured Technologies

Offloaded XDP (SmartNIC), Native XDP (Kernel device driver), AF_XDP (generic mode only since the NIC's driver did not support a driver-specific AF_XDP mode at the time)

### Metrics

- Paket drop: Throughput (Mpps) vs. #cores
- Throughput vs. processing complexity
- Response time vs. packet rate (DNS ping)
- Response time vs. packet rate with hash-map lookup
- Map update rate (entries / s)

### Use Cases

- Packet Drop
- Emulated CPU load (IP Checksum)
- DNS ping (hard coded reply)
- Memory lookup (DNS response cache)
- Cache updates

### Setup

DUT with one NIC and two ports. Traffic from up to four machines via 10 Gbit/s switch.

### Linkrate

10 Gbit/s

### Notes

Same XDP program runs at all execution points.

[5] https://ieeexplore.ieee.org/document/8806651
