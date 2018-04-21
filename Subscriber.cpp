#include <zmq.hpp>
#include "zhelpers.hpp"

int main (int argc, char *argv[])
{
    // Prepare context, subscriber and topic
    zmq::context_t context (2);
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5555");

    //  Subscribe to topic
    const char *filter = (argc > 1)? argv [1]: "default";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    // interupt helper function
    s_catch_signals ();

    while (1) {
        try {
            //  Read envelope with address
            std::string address = s_recv(subscriber);
            //  Read message contents
            std::string message = s_recv(subscriber);

            std::cout << "[" << address << "] " << message << std::endl;
        }
        catch(zmq::error_t& e) {
            std::cout << "W: interrupt received, proceeding…" << std::endl;
        }
        if (s_interrupted) {
            std::cout << "W: interrupt received, killing subscriber…" << std::endl;
            break;
        }
    }
}
