/* Gemeinsamer Verarbeitungskern: wird identisch für XDP (clang -target bpf)
 * und nativ (cc) übersetzt. Keine Schleifen, kein Heap, Bounds-Check vor jedem Zugriff. */
#include <linux/if_ether.h>

#ifndef __always_inline
#define __always_inline inline __attribute__((always_inline))
#endif

static __always_inline int core_process(unsigned char *pkt, unsigned char *end)
{
    struct ethhdr *eth = (struct ethhdr *)pkt;
    if ((unsigned char *)(eth + 1) > end)
        return -1;
    unsigned char tmp[ETH_ALEN];
    __builtin_memcpy(tmp, eth->h_source, ETH_ALEN);
    __builtin_memcpy(eth->h_source, eth->h_dest, ETH_ALEN);
    __builtin_memcpy(eth->h_dest, tmp, ETH_ALEN);
    return 0;
}
