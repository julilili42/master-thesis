/* Nativer Harness um core.h: derselbe Kern auf einem Stack-Puffer, mit Selbsttest. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "core.h"

int main(void)
{
    unsigned char pkt[64] = {0};
    unsigned char dst[ETH_ALEN] = {1, 2, 3, 4, 5, 6};
    unsigned char src[ETH_ALEN] = {0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    memcpy(pkt, dst, ETH_ALEN);
    memcpy(pkt + ETH_ALEN, src, ETH_ALEN);

    assert(core_process(pkt, pkt + sizeof pkt) == 0);
    assert(memcmp(pkt, src, ETH_ALEN) == 0 && memcmp(pkt + ETH_ALEN, dst, ETH_ALEN) == 0);
    assert(core_process(pkt, pkt + 8) == -1); /* zu kurz, darf nicht anfassen */
    puts("core_process ok");
    return 0;
}
