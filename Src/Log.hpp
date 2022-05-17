#pragma once

#ifndef NO_ERROR_LOG
#define ENABLE_ERROR_LOG
#endif

#ifdef ENABLE_LOG

    #define LOG(x) std::cout<<x
    #define LOGL(x) LOG(x)<<"\n"
    #define LOGP(x) std::cout<<__PRETTY_FUNCTION__<<": l."<<__LINE__<<" : "<<x
    #define LOGPL(x) LOGP(x)<<"\n"

#else

    #define LOG(x);
    #define LOGL(x);
    #define LOGP(x);
    #define LOGPL(x);

#endif

#ifdef ENABLE_ERROR_LOG
    #define LOGE(x) std::cerr<<__PRETTY_FUNCTION__<<": l."<<__LINE__<<" : "<<x
#else
    #define LOGE(x);
#endif

#define LOGE(x) std::cerr<<__PRETTY_FUNCTION__<<": l."<<__LINE__<<" : "<<x

