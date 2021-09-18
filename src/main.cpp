#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <unistd.h>

std::string execCmd(std::string cmd) {

  std::string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  cmd.append(" 2>&1");

  stream = popen(cmd.c_str(), "r");
  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
  }
  return data;
}

std::vector<std::string> split(std::string &text, std::string &delimiter){
    std::vector<std::string> words;

    size_t pos;
    while ((pos = text.find(delimiter)) != std::string::npos) {
        words.push_back(text.substr(0, pos));
        text.erase(0, pos + delimiter.length());
    }
    return words;
}


int usageLnCount(std::string &text){
    int count = 0;
    auto str = text.c_str();
    for(int i = 0; i < text.size(); i++)
        if(str[i] == '\n')
            count++;
    return count;
}

 
int main(){	
    std::cout << "Demon has been started\nTo stop it press \"Ctrl+c\".\n" << std::endl;
    bool barIsRunning = false;

    while(true){
        auto output = execCmd("wmctrl -l");

        int windowsCount = usageLnCount(output);

        if(windowsCount == 1 && !barIsRunning){
            barIsRunning = true;
            std::cout << "Cutefish statusbar has been restarted."  << std::endl;
            system("bash -c \"pkill cutefish-status ; cutefish-statusbar &\"");
            
        } else if (windowsCount == 0) 
            barIsRunning = false;
        
        usleep(500);
    }

    return 0;
}
