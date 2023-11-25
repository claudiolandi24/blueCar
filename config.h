#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

namespace config {
extern QString adminPwdHash;

bool readConfigFile();
} // namespace config

#endif // CONFIG_H
