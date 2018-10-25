/*
 * ip_test.c
 * Handler for test IP packets (protocol 0)
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "dbg.h"
#include "node.h"

#include "ip_test.h"

// Prototypes
void iptest_init(void);
void send_cmd(const char *line);
void test_handler(int id, struct in_addr src, struct in_addr dst, void *buf, size_t len);


void iptest_init(void)
{
    // Register the CLI command
    register_command("send",
		     "[ip] [protocol] [payload]: sends payload with protocol=protocol to virtual-ip ip",
		     send_cmd);

    // Register the packet handler
    register_packet_handler(0, &test_handler);
}

void iptest_destroy(void)
{
    unregister_packet_handler(0);
}


// CLI command for sending test IP packets
void send_cmd(const char *line)
{
  char ip_string[INET_ADDRSTRLEN];
  struct in_addr ip_addr;
  uint8_t protocol;
  int num_consumed;

  if (sscanf(line, "send %s %" SCNu8 "%n", ip_string, &protocol, &num_consumed) != 2) {
    dbg(DBG_ERROR, "syntax error (usage: send [ip] [protocol] [payload])\n");
  } else if (inet_pton(AF_INET, ip_string, &ip_addr) == 0) {
    dbg(DBG_ERROR, "syntax error (malformed ip address)\n");
  } else if (strlen(line + num_consumed + 1) < 1) {
    dbg(DBG_ERROR, "syntax error (payload unspecified)\n");
  } else if (ip_send(ip_addr, protocol,
		     line + num_consumed + 1, strlen(line + num_consumed + 1)) < 0) {
    dbg(DBG_ERROR, "sending to unreachable address\n");
  }
}



// IP packet handler for test packets
void test_handler(int id, struct in_addr src, struct in_addr dst,
			 void *buf, size_t len) {
	char src_str[INET_ADDRSTRLEN] = {0};
	char dst_str[INET_ADDRSTRLEN] = {0};
	inet_ntop(AF_INET, &src, src_str, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &dst, dst_str, INET_ADDRSTRLEN);

	printf("---Node received packet!---\n"
	       "\tarrived link   : %d\n"
	       "\tsource IP      : %s\n"
	       "\tdestination IP : %s\n"
	       "\tprotocol       : 0\n"
	       "\tpayload length : %d\n"
	       "\tpayload        : ",
	       id, src_str, dst_str, (int)len);
	fflush(stdout);
	assert(write(STDOUT_FILENO, buf, len) >= 0);
	printf("\n---------------------------\n");
}

