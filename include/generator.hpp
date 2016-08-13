#ifndef _TOME_GENERATOR_HPP
#define _TOME_GENERATOR_HPP

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <string>
#include <vector>

namespace tome
{
    //Forward declarations.
    class ITemplateEngine;
    class ModelDescriptor;

    //! Represents the interface of a code generator.
    class IGenerator
    {
    public:
        typedef boost::shared_ptr<ITemplateEngine> engine_ptr;

        //! Represents a filename, filecontent pair.
        typedef std::pair<std::string, std::string> file;

        virtual ~IGenerator();

        //! Default constructor.
        IGenerator();

        //!Engine constructor.
        //! @param p_engine A shared_ptr to the template engine the generator will use.
        IGenerator(const engine_ptr& p_engine);

        //! Generates the code files for a model.
        //! @param descriptor The model descriptor for the model to be generated.
        //! @returns A list of generated code files.
        virtual std::vector<file> generate(const ModelDescriptor& descriptor) = 0;

        //! @returns Whether or not an engine has been assigned to the generator.
        bool has_engine();

        //! @returns A pointer to the template engine used by the generator.
        engine_ptr get_engine();

        //! Sets the engine in use by this generator.
        void set_engine(const engine_ptr& p_engine);

    private:
        engine_ptr m_pEngine;
    };
}
#endif
