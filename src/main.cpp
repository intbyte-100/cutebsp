#include "ShellInputStream.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <unistd.h>



int main(){	
    std::cout << "Demon has been started\nTo stop it press \"Ctrl+c\".\n" << std::endl;
    bool barIsAbove = false;

    std::string cmd("bspc subscribe");
    ShellInputStream stream(cmd);

    while (true) {
        auto str = stream.nextString();
        if(str[str.length()-3] == '='){
            system("xdo lower -N cutefish-statusbar -t $(xdo id -N Bspwm -n root)");
            std::cout << "the status bar was move to below" << std::endl;
        } else {
            system("xdo raise -N cutefish-statusbar -t $(xdo id -N Bspwm -n root)");
            std::cout << "the status bar was move to above" << std::endl;
        }
    }

    return 0;
}
