/*
 * ip_test.h
 * Handler for test IP packets (protocol 0)
 */

#ifndef IP_TEST_H
#define IP_TEST_H

#include <stddef.h>
#include <netinet/in.h>

#include "node.h"


void iptest_init(void);
void test_handler(int id, struct in_addr src, struct in_addr dst, void * buf, size_t len);


#endif /* IP_TEST_H */
