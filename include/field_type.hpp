#ifndef _TOME_FIELD_TYPE_HPP
#define _TOME_FIELD_TYPE_HPP

namespace tome
{
    //! Represents the type of a field.
    enum FIELD_TYPE
    {
        FIELD_TYPE_INT32,
        FIELD_TYPE_UINT32,
        FIELD_TYPE_BOOL,
        FIELD_TYPE_FLOAT32,
        FIELD_TYPE_FLOAT64,
        FIELD_TYPE_STRING,
        FIELD_TYPE_BYTES,
    };
}
#endif
