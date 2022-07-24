#include "Logger.h"

src::severity_logger<logging::trivial::severity_level> Logger::lg;

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

void Logger::initLogger() {
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