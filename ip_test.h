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
void iptest_destroy(void);


#endif /* IP_TEST_H */
