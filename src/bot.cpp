
#include <cmath>
#include "bot.h"

bool hal::Bot::read() {
    std::string line;

    while(std::getline(std::cin, line)) {
        std::cerr << "Read line \"" << line << "\"." << std::endl;

        std::vector<string> hal_command = string(line).split();
        std::vector<std::string> command;

        for(string& comm : hal_command)
            command.push_back(comm.get());

        if (command[0] == "settings") {
            sm.set_setting(command[1], command[2]);
        } else if (!sm.settings_taken) {
            settings();
        }

        if (command[0] == "update" && command[1] == "game") {
            update(command[2], command[3]);
        }
        else if (command[0] == "action" && command[1] == "move")
            move(std::stoi(command[2]));
        else if(command[0] != "settings")
            return false;
    }
    return true;
}

bool hal::Bot::settings() {
    try {
        sm.settings_taken = true;
        timebank_max = sm.get_int_setting("timebank");
        timebank = timebank_max;
        time_per_move = sm.get_int_setting("time_per_move");
        player_names = sm.get_name_setting();
        your_bot = sm.get_setting("your_bot");
        your_botid = sm.get_int_setting("your_botid");

        if(your_botid == 1)
            your_botdisc = Disc::O;
        else if(your_botid == 0)
            your_botdisc = Disc::X;

        std::cerr << "Creating new field" << std::endl;

        return true;
    }
    catch(std::exception& e) {
        std::cerr << "Some setting was wrong!" << std::endl;
        return false;
    }
}

void hal::Bot::update(const hal::string& type, const hal::string& value) {
    if(type == "round")
        round = std::stoi(value.get());
    else if(type == "field") {
        field = Field(sm.get_int_setting("field_width"), sm.get_int_setting("field_height"));

        int row = 0;
        int col = 0;
        std::vector<hal::string> fields = value.split(',');

        for (hal::string& disc : fields) {
            if (disc == "0") {
                field[row][col] = Disc::X;
            } else if (disc == "1") {
                field[row][col] = Disc::O;
            } else {
                field[row][col] = Disc::None;
            }
            col++;
            if (col == 7) {
                row++;
                col = 0;
            }
        }
    }
}

Move hal::Bot::move_helper(int& timeout) {
    RuleBased rb(field, round);
    MonteCarloTreeSearch mcts(field, your_botdisc);

    timeout -= BUFFER_MS;

    Timer timer;
    timer.start();

    Move rb_move = rb.move();

    if(rb_move == -1) {
        int new_timeout = timeout - timer.elapsed_int();
        std::vector<Move> possible_moves = rb.get_blocked_moves();
        return mcts.move(new_timeout, possible_moves);
    }
    else
        return rb_move;
}

void hal::Bot::move(int timeout) {
    std::cerr << "Started move " << round << " with timeout: " << timeout << std::endl;

    time_per_move = sm.get_int_setting("time_per_move");
    timebank = timeout;

    Move move = move_helper(time_per_move);

    if(move < 0 || move > field.width() - 1)
        std::cout << "no_moves" << std::endl;
    else
        std::cout << "place_disc " << move << std::endl;
}
