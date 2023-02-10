TCP classes
============================

The TCP classes can be used with :cpp:class:`imebra::StreamWriter` and :cpp:class:`imebra::StreamReader` to
send and receive data through a TCP stream.

A TCP server socket (a socket that listen for incoming connection) can be realized with the class
:cpp:class:`imebra::TCPListener`, while a TCP client (a socket that initiates a connection with a
server) can be realized with the class :cpp:class:`imebra::TCPStream`.

:cpp:class:`imebra::TCPListener` creates a new :cpp:class:`imebra::TCPStream` for each accepted incoming connection.

Both :cpp:class:`imebra::TCPListener` and :cpp:class:`imebra::TCPStream` expose blocking methods (except for
the constructors which connect to the peer in non-blocking mode).
You can exit a blocking method to terminate by closing the socket or by calling the terminate() method.


