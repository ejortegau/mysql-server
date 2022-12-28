//
// Created by ejortegau on 11/6/22.
//
#include "audit_latency_per_client_label.h"

#include <iostream>
#include "my_sys.h"

static int audit_latency_per_client_label_plugin_notify(MYSQL_THD thd, mysql_event_class_t event_class,
                             const void *event) {
  std::cout << "thread_id " <<thd_get_thread_id(thd) <<"\tevent_class " << event_class
      << "\tevent " << event << std::endl;

  return 0;
}

/*
  Plugin type-specific descriptor
*/

static struct st_mysql_audit audit_latency_per_client_label_plugin_descriptor = {
    MYSQL_AUDIT_INTERFACE_VERSION, /* interface version    */
    nullptr,                       /* release_thd function */
    audit_latency_per_client_label_plugin_notify,             /* notify function      */
    {0,
     0,
     0,
     0, /* This event class is currently not supported. */
     0,
     0,
     0,
     0,
     0,
     (unsigned long)MYSQL_AUDIT_QUERY_ALL,
     0,
     0,
     0
    }
};

static int audit_latency_per_client_label_plugin_init(void *arg MY_ATTRIBUTE((unused))) {
  return 0;
}

static int audit_latency_per_client_label_plugin_deinit(void *arg MY_ATTRIBUTE((unused))) {
  return 0;
}

/*
  Plugin status variables for SHOW STATUS
*/

static SHOW_VAR simple_status[] = {};

static SYS_VAR *system_variables[] = {

//    MYSQL_SYSVAR(abort_message),
//    MYSQL_SYSVAR(abort_value),
//
//    MYSQL_SYSVAR(event_order_check),
//    MYSQL_SYSVAR(event_order_check_consume_ignore_count),
//    MYSQL_SYSVAR(event_order_started),
//    MYSQL_SYSVAR(event_order_check_exact),
//
//    MYSQL_SYSVAR(event_record_def),
//    MYSQL_SYSVAR(event_record),
    nullptr
};


/*
  Plugin library descriptor
*/

mysql_declare_plugin(audit_null){
    MYSQL_AUDIT_PLUGIN,                         /* type                            */
    &audit_latency_per_client_label_plugin_descriptor, /* descriptor                      */
    "AUDIT_LATENCY_PER_CLIENT",                 /* name                            */
    "Eduardo J. Ortega U.",                     /* author                          */
    "Simple Audit Plugin to measure latency",   /* description                     */
    PLUGIN_LICENSE_GPL,
    audit_latency_per_client_label_plugin_init,   /* init function (when loaded)     */
    nullptr,                  /* check uninstall function        */
    audit_latency_per_client_label_plugin_deinit, /* deinit function (when unloaded) */
    0x0003,                   /* version                         */
    simple_status,            /* status variables                */
    system_variables,         /* system variables                */
    nullptr,
    0,
} mysql_declare_plugin_end;

