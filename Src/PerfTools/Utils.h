#ifndef PERFTOOLS_UTILS_HPP
#define PERFTOOLS_UTILS_HPP

#define PERFTOOLS_USE_QT 0

#if PERFTOOLS_USE_QT == 1
#include <QDebug>
#include <QString>
#endif

#include <iostream>
#include <string>

namespace perfTools {

#if PERFTOOLS_USE_QT == 1
inline
auto getOutStream()
{
    return qDebug();
}

inline
QDebug operator<<(QDebug d, const std::string& str) {
    return d << QString::fromStdString(str);
}

#else
inline
std::ostream& getOutStream()
{
    return std::cout;
}
#endif

} // namespace perfTools

#endif // PERFTOOLS_UTILS_HPP
