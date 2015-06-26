/**
 * ModSecurity, http://www.modsecurity.org/
 * Copyright (c) 2015 Trustwave Holdings, Inc. (http://www.trustwave.com/)
 *
 * You may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * If any of the files related to licensing are missing or if you have any
 * other questions related to licensing please contact Trustwave Holdings, Inc.
 * directly using the email address security@modsecurity.org.
 *
 */

#include "actions/action.h"

#include <iostream>
#include <string>

#include "modsecurity/assay.h"
#include "actions/block.h"
#include "actions/redirect.h"
#include "actions/status.h"
#include "actions/rule_id.h"
#include "actions/phase.h"

namespace ModSecurity {
namespace actions {


std::string & Action::evaluate(std::string value,
    Assay *assay) {
    return value;
}


bool Action::evaluate(Assay *assay) {
    return true;
}


bool Action::evaluate(Rule *rule) {
    return true;
}


void Action::fill_intervention(ModSecurityIntervention *i) {
}

Action *Action::instantiate(std::string name) {
    std::string status("status:");
    std::string redirect("redirect:");
    std::string block("block");
    std::string phase("phase:");
    std::string rule_id("id:");

    if (name.compare(0, status.length(), status) == 0) {
        return new Status(name);
    }
    if (name.compare(0, redirect.length(), redirect) == 0) {
        return new Redirect(name);
    }
    if (name.compare(0, block.length(), block) == 0) {
        return new Block(name);
    }
    if (name.compare(0, phase.length(), phase) == 0) {
        return new Phase(name);
    }
    if (name.compare(0, rule_id.length(), rule_id) == 0) {
        return new RuleId(name);
    }

    return new Action(name);
}

}  // namespace actions
}  // namespace ModSecurity
