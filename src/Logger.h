#pragma once
#ifndef CODEGENERATOR_LOGGER_H
#define CODEGENERATOR_LOGGER_H

#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>

namespace logging  = boost::log;
namespace attrs    = boost::log::attributes;
namespace expr     = boost::log::expressions;
namespace src      = boost::log::sources;
namespace keywords = boost::log::keywords;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger< >)

// New macro that includes severity, filename and line number
#define CUSTOM_LOG(logger, sev) \
   BOOST_LOG_STREAM_WITH_PARAMS( \
      (logger), \
         (set_get_attrib("File", path_to_filename(__FILE__))) \
         (set_get_attrib("Line", __LINE__)) \
         (::boost::log::keywords::severity = (boost::log::trivial::sev)) \
   )

// Set attribute and return the new value
template<typename ValueType>
ValueType set_get_attrib(const char* name, ValueType value) {
    auto attr = logging::attribute_cast<attrs::mutable_constant<ValueType>>(logging::core::get()->get_global_attributes()[name]);
    attr.set(value);
    return attr.get();
}

// Convert file path to only the filename
std::string path_to_filename(std::string path) {
    return path.substr(path.find_last_of("/\\")+1);
}

void initLogger() {
    // New attributes that hold filename and line number
    logging::core::get()->add_global_attribute("File", attrs::mutable_constant<std::string>(""));
    logging::core::get()->add_global_attribute("Line", attrs::mutable_constant<int>(0));

    // A file log with time, severity, filename, line and message
    logging::add_file_log (
            keywords::file_name = "sample_%N.log",
            keywords::format = (
                    expr::stream
                            << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d_%H:%M:%S")
                            << ": <" << boost::log::trivial::severity << "> "
                            << '['   << expr::attr<std::string>("File")
                            << ':' << expr::attr<int>("Line") << "] "
                            << expr::smessage
            )
    );
    logging::add_common_attributes();
}
#endif //CODEGENERATOR_LOGGER_H
