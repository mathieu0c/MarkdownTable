#pragma once

#include <iostream>

// #define ENABLE_LOG
// #define NO_ERROR_LOG

#ifndef NO_ERROR_LOG
#define ENABLE_ERROR_LOG
#endif

#ifdef ENABLE_LOG

    #define LOG(x) std::cout<<x
    #define LOGL(x) LOG(x)<<"\n"
    #define LOGP(x) std::cout<<__PRETTY_FUNCTION__<<": l."<<__LINE__<<" : "<<x
    #define LOGPL(x) LOGP(x)<<"\n"

    #include <regex>
    #include <string>
    #include <string_view>

    #define LOG_REGEX(rxTxt,txt) logRegex(rxTxt,txt)

#else

    #define LOG(x);
    #define LOGL(x);
    #define LOGP(x);
    #define LOGPL(x);

#endif

#ifdef ENABLE_ERROR_LOG
    #define LOGE(x) std::cerr<<"ERR:"<<_FILE_<<":"<<__PRETTY_FUNCTION__<<": l."<<__LINE__<<" : "<<x
    #define LOGEL(x) LOGE(x)<<"\n"
#else
    #define LOGE(x);
    #define LOGEL(x);
#endif

#define RAWE(x) std::cerr<<x
#define RAWEL(x) RAWE(x)<<"\n"
