
#include "line/line.h"

const Part part_line = 
{
    sizeof(Line),
    parse_buffer_lines,
    print_line_stream
};
