#include "config.h"
#include "alcyone.h"
#include <boost/thread.hpp>
#include <boost/program_options.hpp>

namespace options= boost::program_options;

int main(int argc, char **argv)
{
    options::options_description desc("Allowed Options");
    options::variables_map vm;
    int playFlare;
    int verbosity;
    int hostPort;

    desc.add_options()
    ( "help", "produce help message")
    ( "flare", options::value<int>(&playFlare)->default_value(DEFAULT_PLAY_FLARE), 
      "play introductory flare")
    ( "verbose", options::value<int>(&verbosity)->default_value(DEFAULT_VERBOSITY),
      "verbose mode" )
    ( "port", options::value<int>(&hostPort)->default_value(DEFAULT_HOST_PORT),
      "server port" )
    ;
    options::store(options::parse_command_line(argc, argv, desc), vm);
    options::notify(vm);

    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        return 1;
    }

    Alcyone alcyone;
    MIDI midi;
    alcyone.setVerbosity(verbosity);
    alcyone.setHostPort(hostPort);
    alcyone.setMidi(&midi);

    if(playFlare) {
        alcyone.playFlare();
    }
    boost::thread alcyoneMain(&Alcyone::start, &alcyone);
    alcyoneMain.join();
    return 0;
}
