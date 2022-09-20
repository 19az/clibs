#ifndef PARTITION_H
#define PARTITION_H

#include <stdlib.h>

struct Partition {
    size_t size = 0;
    void *partition = NULL;
    void   (*parse_text)           (const char *buffer,
                                    Partition  *partition);

    void   (*print_text_partition) (const char      *buffer,
                                    const Partition *partition);
};

#undef PARTITION_H