# Reference IP Node

Thils repository contains a refrence implementation for the IP
assignment.  Most of the code is provided as a C static library:  you
do not have the source for this code, but you can link it into your
project to provide the functionality.  

## How to use

Most of the functionality is provided by the library, including IP
forwarding, RIP, command line parsing.  You can add functionality in
two forms:  
 - Handlers to be called when the node receives an IP packet for a
   given protocol (eg. test packets, TCP, UDP, etc.)
 - Handlers to add CLI commands (send, recv, connect, etc.)

The file `main.c` contains an example main function that starts up the
node and example handlers that implement the "test packets" used in
the IP assignment.  You can extend this file to support your own work.

The files `ip_test.c` and `ip_test.h` contain the handlers to support
test packets.  There are two handlers:  one to implement the "send"
CLI command, and one to print out packets when they are received.  

`node.h` describes your interface for interacting with the reference
IP implementation.  Read the comments of these functions for details
on how to use each function.

## How to start

To implement TCP using this reference, you will need to do the
following:  
 - Write your own handler to process incoming TCP packets.  From here,
   you can call functions to use your own data structures, etc.
   
 - Add handlers to support all of the CLI commands you need for the
   assignment (connect, send, receive, etc.)
 
 - To send TCP packets, you can use the function
   ip_send(), which will create a packet with a given payload.  For
   TCP, this payload will be a TCP header + the data you are
   sending.  

## Getting Help

If you have any questions about using the reference implemenatation,
please contact the TAs list.  

In particular, if you find yourself needing additional functionality
not exposed in node.h, please do not hesitate to ask and we will
determine the best way to handle the issue.  
