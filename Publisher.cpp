#include <zmq.hpp>
#include "zhelpers.hpp"

int main (int argc, char *argv[]) {

    // Prepare context, publisher and topic
    zmq::context_t context (2);
    zmq::socket_t publisher (context, ZMQ_PUB);
    publisher.connect("tcp://localhost:5556");
    std::cout << "server started" << std::endl;
    const char *topic = (argc > 1)? argv [1]: "default";

    // interupt helper function
    s_catch_signals ();

    while (1) {
        try {
            std::string message = "some message";
            // Send topic
            s_sendmore (publisher, topic);
            // Send message
            s_send (publisher, message);

            std::cout << "[" << topic << "] " << message << std::endl;
            zmq_sleep(1);
        }
        catch(zmq::error_t& e) {
            std::cout << "W: interrupt received, proceeding…" << std::endl;
        }
        if (s_interrupted) {
            std::cout << "W: interrupt received, killing publisher…" << std::endl;
            break;
        }
    }
    return 0;
}