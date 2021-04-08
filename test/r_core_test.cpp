#include "r_core/core.h"
#include <iostream>
int main(int argc, char **argv)
{
    auto core = std::make_shared<r_core::Core>();

    while (true)
    {
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "start")
        {
            core->run();
        }
        else if (cmd == "pause")
        {
            core->pause();
        }
        else if (cmd == "resume")
        {
            core->resume();
        }
        else if (cmd == "stop")
        {
            core->stop();
        }
        else if (cmd == "quit")
        {
            core->stop();
            break;
        }

    }
}
