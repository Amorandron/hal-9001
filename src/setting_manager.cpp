
#include "setting_manager.h"

void hal::SettingManager::set_setting(const string& type, const string& value) {
    settings[type] = value;
}

hal::string hal::SettingManager::get_setting(const string& type) const {
    if(settings.find(type) == settings.end())
        return "";
    else
        return settings[type];
}

int hal::SettingManager::get_int_setting(const string& type) const {
    if(settings.find(type) == settings.end())
        return 0;
    else
        return std::stoi(settings[type].get());
}

std::tuple<hal::string, hal::string> hal::SettingManager::get_name_setting() const {
    if(settings.find("player_names") == settings.end())
        return {"", ""};
    else {
        string hs = settings["player_names"];
        return {hs.split(',')[0], hs.split(',')[1]};
    }
}
