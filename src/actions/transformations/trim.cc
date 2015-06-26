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

#include "actions/transformations/trim.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

#include "modsecurity/assay.h"
#include "actions/transformations/transformation.h"
#include "actions/action.h"

namespace ModSecurity {
namespace actions {
namespace transformations {

static inline std::string *ltrim(std::string *s) {
    s->erase(s->begin(), std::find_if(s->begin(), s->end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

static inline std::string *rtrim(std::string *s) {
    s->erase(std::find_if(s->rbegin(), s->rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s->end());
    return s;
}

static inline std::string *trim(std::string *s) {
    return ltrim(rtrim(s));
}

Trim::Trim(std::string action)
    : Transformation(action) {
    this->action_kind = 1;
}

std::string & Trim::evaluate(std::string value,
    Assay *assay) {
    return *trim(&value);
}

}  // namespace transformations
}  // namespace actions
}  // namespace ModSecurity
