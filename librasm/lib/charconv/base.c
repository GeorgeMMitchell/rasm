#include <librasm/lib/charconv/base.h>

const struct charconv_base_traits charconv_base_2 = {"0b", 2, 1, 0x1};

const struct charconv_base_traits charconv_base_8 = {"0", 1, 3, 0x7};

const struct charconv_base_traits charconv_base_16 = {"0x", 2, 4, 0xF};
