#include "network.h"
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>

namespace Network {
    void init() {
        sceNetInit();
        sceNetCtlInit();
    }
}
