#include <boost/regex.hpp>
#include <assert.h>

#include "template_error.hpp"
#include "simple_template_engine.hpp"

tome::SimpleTemplateEngine::SimpleTemplateEngine()
{
    m_recursive = false;
    m_has_context = false;
    m_context = std::map<std::string, std::string>();
}

tome::SimpleTemplateEngine::SimpleTemplateEngine(const std::map<std::string, std::string>& context)
{
    m_recursive = false;
    set_context(context);
}

tome::SimpleTemplateEngine::SimpleTemplateEngine(bool recursive)
{
    set_recursive(recursive);
    m_has_context = false;
    m_context = std::map<std::string, std::string>();
}

tome::SimpleTemplateEngine::SimpleTemplateEngine(const std::map<std::string, std::string>& context, bool recursive)
{
    set_recursive(recursive);
    set_context(context);
}

tome::SimpleTemplateEngine::~SimpleTemplateEngine()
{

}

std::string tome::SimpleTemplateEngine::render(const std::string& tmpl)
{
    std::vector<std::string> errors;
    std::string result = render(tmpl, &errors);

    if(errors.size() != 0)
    {
        throw TemplateError("Error(s) were detected when attempting to render this template.");
    }

    return result;
}

std::string tome::SimpleTemplateEngine::render(const std::string& tmpl, std::vector<std::string>* p_errors)
{
    std::string result;

    //Sanity check.
    if(!has_context())
        throw TemplateError("Engine does not yet have a context.");

    // Do step.
    size_t substitution_count = do_step(tmpl, &result, p_errors);

    //Cancel out early if not in recursive mode.
    if(!is_recursive())
        return result;

    size_t substitution_count_old = 0;
    size_t deadlock_counter = 0;
    while(substitution_count != 0)
    {
        //Repeat
        p_errors->clear();
        substitution_count = do_step(result, &result, p_errors);

        //Deadlock checking.
        //If the same amount of substitutions as last time was made.
        if(substitution_count == substitution_count_old)
        {
            //Increase the counter.
            deadlock_counter++;
        }
        else
        {
            //Else reset it.
            deadlock_counter = 0;
        }

        //If the deadlock counter has counted to 100
        if(deadlock_counter == 100)
        {
            throw TemplateError("A deadlock was detected when attempting to render this template.");
        }

        //Reassign the old value.
        substitution_count_old = substitution_count;
    }

    return result;
}

bool tome::SimpleTemplateEngine::has_context()
{
    return m_has_context;
}

bool tome::SimpleTemplateEngine::is_recursive()
{
    return m_recursive;
}

void tome::SimpleTemplateEngine::set_context(const std::map<std::string, std::string>& context)
{
    this->m_has_context = true;
    this->m_context = context;
}

void tome::SimpleTemplateEngine::set_recursive(bool recursive)
{
    this->m_recursive = recursive;
}

size_t tome::SimpleTemplateEngine::do_step(const std::string& tmpl, std::string* p_result, std::vector<std::string>* p_errors)
{
    std::string temp = tmpl;
    boost::regex reg("\\$([\\w_]+)", boost::regex_constants::egrep);
    boost::smatch match;

    size_t index = 0;
    size_t substitution_count = 0;
    boost::match_flag_type flags = boost::match_default;
    std::string::const_iterator start, end;

    //Assign iterators.
    start = tmpl.begin();
    end = tmpl.end();

    while(boost::regex_search(start, end, match, reg, flags))
    {
        //Update iterator.
        start = match[0].second;

        std::string full = match[0];
        std::string key = match[1];
        if(m_context.count(key) == 0)
        {
            p_errors->push_back(key);
            continue;
        }

        //Retrieve value.
        std::string value = m_context[key];

        //Scan the temp string for the full match.
        size_t found = temp.find(full, index);

        //Should never happen
        assert(found != std::string::npos);

        //Replace.
        temp.replace(found, full.length(), value);

        //Update index and substitution count.
        index = found + value.length();
        substitution_count++;
    }

    //Assign the result string.
    *p_result = temp;

    return substitution_count;
}
