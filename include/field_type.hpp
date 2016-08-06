#ifndef _TOME_FIELD_TYPE_HPP
#define _TOME_FIELD_TYPE_HPP

namespace tome
{
    //! Represents the type of a field.
    enum class FIELD_TYPE
    {
        INT32,
        UINT32,
        BOOL,
        FLOAT32,
        FLOAT64,
        STRING,
        BYTES,
    };
}
#endif
