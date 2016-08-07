#ifndef _TOME_FIELD_DESCRIPTOR_HPP
#define _TOME_FIELD_DESCRIPTOR_HPP

#include <string>

#include "field_type.hpp"

namespace tome
{
    //!Represents the description of a single field within a model.
    class FieldDescriptor
    {
    public:

        //! Default constructor.
        //! @param name The name of the field.
        //! @param type The type of the field.
        //! @param required A boolean indicating whether or not the field is required.
        FieldDescriptor(std::string name, FIELD_TYPE type, bool required);

        //! @returns The name of the field.
        std::string get_name();

        //! @returns The type of the field.
        FIELD_TYPE get_type();

        //! @returns A boolean indicating whether the field is required or not.
        bool is_required();

    private:
        std::string m_name;
        FIELD_TYPE m_type;
        bool m_required;
    };
}
#endif
