/*
 * node.h - IP/TCP Reference Implementation
 */
#ifndef NODE_H
#define NODE_H

#include <netinet/ip.h>

#define NODE_CLI_INVALID -1 // An invalid command was specified
#define NODE_CLI_EXIT -2    // User entered exit command

typedef void (*command_handler_t)(const char *);

/*
 * Initialize an IP node, based on a lnx file
 */
void node_init(char *lnx_filename);

/*
 * Clean up resources for a node (call before exiting)
 */
void node_destroy(void);

/*
 * Read a line from stdin and process it using the node's CLI Returns
 * 0 on success, NODE_CLI_INVALID if the command given was not a valid
 * command.  If NODE_CLI_EXIT is returned, the user entered the "exit"
 * command and the program should cleanup and quit accordingly.
 */
int node_read_cli(void);

/*
 * Register a CLI command, given a commmand string, a description for the
 * helo command, and a handler function.
 * The handler function must take a single char * as argument and return void.
 */
void register_command(const char *command, const char *description, command_handler_t handler);

/*
 * Explicitly run a CLI command cmd, given an input string
 *
 * It should not be necessary to use this command in most
 * cases--instead, call node_read_cli to do all of the input
 * processing automatically.
 */
int run_command(const char *cmd, const char *input);

/*
 * Print the list of commands, equivalent to running "help"
 */
void print_commands(void);


// Signature for IP packet handler
typedef void (*packet_handler_t)(int, struct in_addr, struct in_addr,
				 void *, size_t);

/*
 * Register an IP packet handler for a given protocol number
 */
void register_packet_handler(uint8_t prot, packet_handler_t handler);

/*
 * Unregister the packet handler for a given protocol number
 */
void unregister_packet_handler(uint8_t prot);

/*
 * Send a raw IP packet with payload buf of size len to address dst
 * on the given protocol
 */
int ip_send(struct in_addr dst, uint8_t prot, const void *buf, size_t len);




#endif /* NODE_H */
