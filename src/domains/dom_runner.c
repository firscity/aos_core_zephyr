/*
 * Copyright (c) 2023 EPAM Systems
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <domain.h>
#include <xen_dom_mgmt.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(domains);

extern struct xen_domain_cfg domd_cfg;

int create_domains(void)
{
    int rc;

    rc = domain_create(&domd_cfg, 1);
    if (rc) {
        LOG_ERR("Failed to start Domain-D, rc = %d", rc);
    }

    return rc;
}
