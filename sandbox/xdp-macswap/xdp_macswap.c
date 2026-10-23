/* XDP-Rahmen um core.h: MAC-Swap und zurück auf dasselbe Interface. */
#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>
#include "core.h"

SEC("xdp")
int xdp_macswap(struct xdp_md *ctx)
{
    unsigned char *data = (void *)(long)ctx->data;
    unsigned char *end  = (void *)(long)ctx->data_end;
    return core_process(data, end) ? XDP_PASS : XDP_TX;
}

char _license[] SEC("license") = "GPL";
