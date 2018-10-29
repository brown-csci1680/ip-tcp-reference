/*
 * main.c - IP Reference node example
 */

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "dbg.h"
#include "list.h"
#include "node.h"

#include "ip_test.h"

void list_interfaces(void);

int main(int argc, char **argv)
{
    int ret;

    if (argc != 2) {
	dbg(DBG_ERROR, "usage: %s <linkfile>\n", argv[0]);
	return -1;
    }
    char *lnx_filename = argv[1];

    // Initialize resources for the reference node
    node_init(lnx_filename);

    // Print out this node's interface list, as a demo:
    list_interfaces();

    // Any setup you need to do before the node starts happens here
    iptest_init();

    while(1) {
	// Read a line of input and process it using the registered CLI commands
	ret = node_read_cli();

	if (ret == NODE_CLI_EXIT) {
	    break;
	}
    }

    // Any cleanup you need to do before the node shuts down happens here
    iptest_destroy();

    // Cleanup all resources before exiting
    node_destroy();

    return 0;

}


void list_interfaces(void)
{
    list_t list_head;
    char ip_str[INET_ADDRSTRLEN];

    // Fill in the list of interfaces
    build_interface_list(&list_head);

    // Iterate over the interface list, printing each one
    struct link_interface *node;
    list_iterate_begin(&list_head, node, struct link_interface, link) {
	memset(ip_str, 0, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &node->ip_addr, ip_str, INET_ADDRSTRLEN);

	printf("%d:  %s\n", node->id, ip_str);
    } list_iterate_end();

    // Finally, free the interface list
    free_interface_list(&list_head);
}
