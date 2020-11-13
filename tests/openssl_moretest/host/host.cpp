// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <openenclave/host.h>
#include <openenclave/internal/calls.h>
#include <openenclave/internal/error.h>
#include <openenclave/internal/tests.h>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <thread>

#include "openssl_moretest_u.h"

#define TEST_GROUP_DIGEST 0

extern oe_result_t schema_test_digest(oe_enclave_t* enclave);

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s ENCLAVE_PATH TEST_NUMBER\n", argv[0]);
        exit(1);
    }
    oe_enclave_t* enclave;
    const uint32_t flags = oe_get_create_flags();

    oe_result_t result = oe_create_openssl_moretest_enclave(
        argv[1], OE_ENCLAVE_TYPE_SGX, flags, nullptr, 0, &enclave);
    OE_TEST(result == OE_OK);
    result = ecall_set_rdrand_engine(enclave);
    OE_TEST(result == OE_OK);
    switch (atoi(argv[2]))
    {
        case TEST_GROUP_DIGEST:
            result = schema_test_digest(enclave);
            break;
        default:
            result = OE_UNEXPECTED;
            break;
    }
    OE_TEST(result == OE_OK);
    // Clean up the enclave
    if (enclave)
        oe_terminate_enclave(enclave);

    return 0;
}
