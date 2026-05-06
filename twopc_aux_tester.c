/*-------------------------------------------------------------------------
 *
 * twopc_aux_tester.c
 *    Example extension with simple XactCallback for testing two-phase commit
 *
 * Copyright (c) 2023, PostgreSQL Global Development Group
 *
 * IDENTIFICATION
 *    contrib/twopc_aux_tester/twopc_aux_tester.c
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"
#include "miscadmin.h"
#include "access/xact.h"
#include "utils/guc.h"

PG_MODULE_MAGIC_EXT(
                    .name = "twopc_aux_tester",
                    .version = PG_VERSION
);

/* GUC variables */
static bool twopc_aux_tester_enabled = true;
static bool twopc_aux_tester_error_on_prepare = false;
static int  twopc_aux_tester_log_level = LOG;

/* Callback function prototype */
static void twopc_aux_tester_callback(XactEvent event, void *arg);

/*
 * Callback function called on transaction events
 */
static void
twopc_aux_tester_callback(XactEvent event, void *arg)
{
    /* If callback is disabled, do nothing */
    if (!twopc_aux_tester_enabled)
        return;

    /* Log event based on type */
    switch (event)
    {
        case XACT_EVENT_COMMIT:
            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: transaction COMMIT")));
            break;
            
        case XACT_EVENT_ABORT:
            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: transaction ABORT")));
            break;
            
        case XACT_EVENT_PREPARE:

            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: transaction PREPARE")));
            break;
            
        case XACT_EVENT_PRE_COMMIT:
            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: PRE_COMMIT")));
            break;
            
        case XACT_EVENT_PARALLEL_COMMIT:
            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: PARALLEL_COMMIT")));
            break;
            
        case XACT_EVENT_PARALLEL_ABORT:
            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: PARALLEL_ABORT")));
            break;
            
        case XACT_EVENT_PRE_PREPARE:
            if (twopc_aux_tester_error_on_prepare)
                elog(ERROR, "injected error");

            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: PRE_PREPARE")));
            break;
            
        default:
            ereport(twopc_aux_tester_log_level,
                    (errmsg("twopc_aux_tester: unknown event %d", event)));
            break;
    }
}

/*
 * _PG_init - module initialization function
 */
void
_PG_init(void)
{
    /* Define GUC variables */
    DefineCustomBoolVariable("twopc_aux_tester.error_on_prepare",
                             "Enable/disable transaction PREPARE event error",
                             NULL,
                             &twopc_aux_tester_error_on_prepare,
                             false,
                             PGC_SUSET,
                             GUC_NO_SHOW_ALL | GUC_NOT_IN_SAMPLE,
                             NULL,
                             NULL,
                             NULL);

    DefineCustomBoolVariable("twopc_aux_tester.enabled",
                             "Enable/disable transaction event logging",
                             NULL,
                             &twopc_aux_tester_enabled,
                             true,
                             PGC_SUSET,
                             GUC_NO_SHOW_ALL | GUC_NOT_IN_SAMPLE,
                             NULL,
                             NULL,
                             NULL);
    
    DefineCustomIntVariable("twopc_aux_tester.log_level",
                            "Log level for transaction events",
                            "0=DEBUG5, 10=DEBUG1, 11=LOG, 12=INFO, 13=NOTICE, 14=WARNING",
                            &twopc_aux_tester_log_level,
                            LOG,
                            DEBUG5,
                            WARNING,
                            PGC_SUSET,
                            GUC_NO_SHOW_ALL | GUC_NOT_IN_SAMPLE,
			                NULL,
                            NULL,
                            NULL);
        

    /* Reserve GUC prefix to prevent conflicts */
    MarkGUCPrefixReserved("twopc_aux_tester");
    
    /* Register callback for transaction events */
    RegisterXactCallback(twopc_aux_tester_callback, NULL);
    
    ereport(LOG,
            (errmsg("twopc_aux_tester: module initialized, callback registered")));
}

/*
 * _PG_fini - module cleanup function
 */
void
_PG_fini(void)
{
    /* Unregister callback */
    UnregisterXactCallback(twopc_aux_tester_callback, NULL);
    
    ereport(LOG,
            (errmsg("twopc_aux_tester: module unloaded, callback removed")));
}

