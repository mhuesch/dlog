#include "entry.h"

entries::entry::entry() : from(0), to(0)
{ }

bool entries::entry::valid() const
{
    return this->from > 0
        && (this->to == 0 || this->to >= this->from);
}

bool entries::entry::complete() const
{
    return this->valid()
        && this->to > 0
        && !this->activity.empty();
}