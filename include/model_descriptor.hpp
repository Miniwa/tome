#ifndef _TOME_MODEL_DESCRIPTOR_HPP
#define _TOME_MODEL_DESCRIPTOR_HPP

#include <string>
#include <vector>

namespace tome
{
    //Forward declare
    class FieldDescriptor;

    //! Represents the description of a data model, including fields.
    //! @see tome::FieldDescriptor
    class ModelDescriptor
    {
    public:
        //! Default constructor.
        //! @param name The name of the model.
        ModelDescriptor(std::string name);

        //! Constructor including package.
        //! @param name The name of the model.
        //! @param package A dot seperated string that specifices the package in which the model should be located.
        ModelDescriptor(std::string name, std::string package);

        //! @returns The name of the model.
        std::string get_name();

        //! @returns The package in which the model should be located.
        std::string get_package();

        //! @returns The amount of fields in the model.
        size_t get_field_count();

        //! @param index The index of the field.
        //! @returns The field.
        FieldDescriptor* get_field(size_t index);

        //! Adds a field to the model.
        //! @param field The field to add.
        void add_field(const FieldDescriptor& field);

    private:
        std::string m_name;
        std::string m_package;
        std::vector<FieldDescriptor> m_fields;
    };
}
#endif
