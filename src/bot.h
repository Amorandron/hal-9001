
#ifndef HAL_9001_BOT_H
#define HAL_9001_BOT_H

#include <chrono>
#include <iostream>
#include <string>

#include "mcts/mcts.h"
#include "mc/montecarlo.h"
#include "rulebased/rulebased.h"
#include "field.h"
#include "util/halstring.h"
#include "setting_manager.h"

namespace hal {
    const int BUFFER_MS = 10;
    const int EXTRA_TIME[] = {
        500, 500, 500, 300, 300,
        300, 300, 300, 300, 200,
        200, 200, 200, 100, 100,
        100, 0,   0,   0,   0
    };

    class Bot {
    public:
        Bot()
            : field(0, 0) {}

        bool read();

    private:
        SettingManager sm;

        // Settings
        int timebank_max;
        int timebank;
        int time_per_move;
        std::tuple<string, string> player_names;
        string your_bot;
        int your_botid;
        Disc your_botdisc;
        int round;

        Field field;

        bool settings();
        void update(const String& type, const String& value);
        void move(int tpm);
        Move move_helper(int& tpm);
    };
}

#endif