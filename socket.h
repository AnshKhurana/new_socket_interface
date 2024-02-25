#include <iostream>
#include <unistd.h>
#include <sys/socket.h>

using namespace std;


struct NetworkAddr
{
    string ip;
    int port;
    bool IPV6=false;
};


class Socket
{
    public:

        /** Create a socket object based on specified options.
         * 
         * \param port
         *    The port to bind the socket to.
         * 
         * \param backlog
         *    The maximum number of pending connections
         *    that can be queued up at any one time.
         * 
        */
        Socket(int port, int backlog=10);
        
        /**
         * Cleans up the resources 
         * used by the socket.
        */
        ~Socket();

        /**
         * Set a specific option for the socket.
         * 
         * \param key
         *  The key for the option to be set. 
         * 
         * \param value
         *  The value to be set for the option.
        */
        bool set_socket_option(string key, int value);
        
        /**
         * Returns the value of the specified option.
         * 
         * \param key
         *  The key for the option to be retrieved.
         * 
         * \return
         *  The value of the option.
        */
        int get_socket_option(string key);

        /**
         *  Connect to another socket for 
         *  communication based on the input
         *  NetworkAddr.
         * 
         * \param network_addr
         *  The address of the socket to connect to.
         * 
         * \return
         * True if the connection was successful.
        */        
        bool connect(NetworkAddr network_addr);
        
        
        /**
         * Accepts a connection from the backlog
         * of connections queued up on this socket.
         * 
         * Valid only if a port was specifed in the
         * constructor.
         * 
         * \return
         * A new socket object representing the 
         * connection.
         * 
        */
        Socket accept();
        
        
        /**
         * Sends the complete message to the
         * connection as one entity/packet.
        */
        void send(string message);

        /**
         *  Retrieves a message or part of a message
         *  queued up on the connection.
         * 
         *  \param num_bytes
         *      Optional parameter for the 
         * 
         *  \return 
         *   The message retrieved from the connection.
        */
        string receive(int num_bytes=-1);

        bool get_peername(NetworkAddr &addr);
        
        /**
         * Disables all incoming data
         * operation on the sockets.
         * 
         * If something was sent to this socket before
         * this method is called, it will still be received.
         * 
         * \return
         *  True if the operation was successful,
        */
        bool stop_reading();

        /**
         * Disables all outgoing data
         * operation on the sockets.
         * 
         * If something was sent on the socket before 
         * this method is called, it will still be sent. 
         * 
         * \return
         *  True if the operation was successful,
        */
        bool stop_writing();

        /**
         * Calls the destructor of the
         * socket object and cleans up
         * all the resouces.
        */
        bool close();
    
    private: 
        Socket &other;


};