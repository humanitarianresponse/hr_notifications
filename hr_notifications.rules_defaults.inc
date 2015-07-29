<?php
/**
 * @file
 * hr_notifications.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function hr_notifications_default_rules_configuration() {
  $items = array();
  $items['rules_hr_submit_to_reliefweb'] = entity_import('rules_config', '{ "rules_hr_submit_to_reliefweb" : {
      "LABEL" : "Submit to Reliefweb",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "flag" ],
      "ON" : { "flag_flagged_hr_reliefweb" : [] },
      "DO" : [
        { "mail" : {
            "to" : "submit@reliefweb.int",
            "subject" : "[HumanitarianResponse] New content submitted",
            "message" : "A new content was submitted on Humanitarianresponse. You can see it here: [flagged-node:url].",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_user_has_no_role'] = entity_import('rules_config', '{ "rules_user_has_no_role" : {
      "LABEL" : "User has no role",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "2",
      "OWNER" : "rules",
      "TAGS" : [ "user_no_role" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "NOT og_user_has_role" : {
            "account" : [ "account" ],
            "group" : [ "account:og-user-node:0" ],
            "roles" : { "value" : {
                "administrator member" : "administrator member",
                "editor" : "editor",
                "manager" : "manager",
                "contributor" : "contributor",
                "access-editor" : "access-editor",
                "access-manager" : "access-manager",
                "bundle member" : "bundle member"
              }
            }
          }
        },
        { "entity_is_of_type" : { "entity" : [ "site:og-context--node" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "site:og-context--node" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your  membership request was approved for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \\u0027[group:title]\\u0027 located at [group:url]",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] joined [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] joined [group:title] in [group:url]"
          }
        }
      ]
    }
  }');
  $items['rules_user_is_a_manager'] = entity_import('rules_config', '{ "rules_user_is_a_manager" : {
      "LABEL" : "User is Manager",
      "PLUGIN" : "reaction rule",
      "WEIGHT" : "1",
      "OWNER" : "rules",
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "og_user_has_role" : {
            "account" : [ "account" ],
            "group" : [ "account:og-user-node:0" ],
            "roles" : { "value" : { "manager" : "manager" } }
          }
        },
        { "entity_is_of_type" : { "entity" : [ "site:og-context--node" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "site:og-context--node" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your  membership request was approved for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \\u0027[group:title]\\u0027 located at [group:url]",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] joined [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] joined [group:title] in [group:url]"
          }
        }
      ]
    }
  }');
  $items['rules_user_is_editor'] = entity_import('rules_config', '{ "rules_user_is_editor" : {
      "LABEL" : "User is Editor",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "user_is_editor" ],
      "REQUIRES" : [ "rules", "og" ],
      "ON" : { "og_user_insert" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "og-membership:state" ], "value" : "1" } },
        { "entity_is_of_type" : { "entity" : [ "og-membership:group" ], "type" : "node" } },
        { "og_user_has_role" : {
            "account" : [ "account" ],
            "group" : [ "account:og-user-node:0" ],
            "roles" : { "value" : { "editor" : "editor" } }
          }
        },
        { "entity_is_of_type" : { "entity" : [ "site:og-context--node" ], "type" : "node" } }
      ],
      "DO" : [
        { "variable_add" : {
            "USING" : { "type" : "node", "value" : [ "site:og-context--node" ] },
            "PROVIDE" : { "variable_added" : { "group" : "Added variable" } }
          }
        },
        { "mail" : {
            "to" : [ "account:mail" ],
            "subject" : "Your  membership request was approved for \\u0027[group:title]\\u0027\\r\\n",
            "message" : "[account:name],\\r\\n\\r\\nYou are now a member in the group \\u0027[group:title]\\u0027 located at [group:url]",
            "language" : [ "" ]
          }
        },
        { "mail" : {
            "to" : [ "group:author:mail" ],
            "subject" : "[account:name] joined [group:title]",
            "message" : "[group:author:name],\\r\\n\\r\\n[account:name] joined [group:title] in [group:url]"
          }
        }
      ]
    }
  }');
  return $items;
}