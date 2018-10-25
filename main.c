/*
 * main.c - IP Reference node example
 */

#include "dbg.h"
#include "node.h"

#include "ip_test.h"


int main(int argc, char **argv)
{
    int ret;

    if (argc != 2) {
	dbg(DBG_ERROR, "usage: %s <linkfile>\n", argv[0]);
	return -1;
    }
    char *lnx_filename = argv[1];

    node_init(lnx_filename);

    // Any setup you need to do before the node starts happens here
    iptest_init();

    while(1) {
	ret = node_read_cli();

	if (ret == NODE_CLI_EXIT) {
	    break;
	}
    }

    // Any cleanup you need to do before the node shuts down happens here
    unregister_packet_handler(0);

    // Cleanup all resources before exiting
    node_destroy();

    return 0;

}
