
#ifndef HAL_9001_SETTING_MANAGER_H
#define HAL_9001_SETTING_MANAGER_H

#include <map>
#include <string>
#include <vector>

#include "util/halstring.h"

namespace hal {
    class SettingManager {
    public:
        bool settings_taken;

        void set_setting(const string& type, const string& value);
        string get_setting(const string& type) const;
        int get_int_setting(const string& type) const;
        std::tuple<string, string> get_name_setting() const;

    private:
        mutable std::map<string, string> settings;
    };
}

#endif
