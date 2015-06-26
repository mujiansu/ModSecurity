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

#ifdef __cplusplus
#include <ctime>
#include <iostream>
#include <list>
#include <iomanip>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <vector>
#endif

#include <stdlib.h>
#include <stddef.h>

#ifndef HEADERS_MODSECURITY_ASSAY_H_
#define HEADERS_MODSECURITY_ASSAY_H_

#ifndef __cplusplus
typedef struct Assay_t Assay;
typedef struct Rules_t Rules;
#endif

#include "modsecurity/intervention.h"



#ifdef __cplusplus

namespace ModSecurity {

class ModSecurity;
class Assay;
class Rules;
namespace actions {
class Action;
}
namespace operators {
class Operator;
}

class ModSecurityHeader {
 public:
    ModSecurityHeader(char *key, char *value)
        : _key(key),
        _value(value)
        { }

    char *_key;
    char *_value;
};


class ModSecurityCollectionsVariables :
    public std::unordered_map<std::string,
        std::unordered_map<std::string, std::string>> {
 public:
};


class ModSecurityStringVariables :
    public std::unordered_map<std::string, std::string> {
 public:
};

/** @ingroup ModSecurity_CPP_API */
class Assay {
 public:
    Assay(ModSecurity *assay, Rules *rules);
    ~Assay();

    /** TODO: Should be an structure that fits an IP address */
    int processConnection(char *ip);
    int processURI(char *uri);


    int processRequestHeaders();
    int addRequestHeader(const std::string& key, const std::string& value);
    int addRequestHeader(const unsigned char *key, const unsigned char *value);
    int addRequestHeader(const unsigned char *key, size_t len_key,
        const unsigned char *value, size_t len_value);

    int processRequestBody();
    int appendRequestBody(const unsigned char *body, size_t size);

    int processResponseHeaders();
    int addResponseHeader(const std::string& key, const std::string& value);
    int addResponseHeader(const unsigned char *key, const unsigned char *value);
    int addResponseHeader(const unsigned char *key, size_t len_key,
        const unsigned char *value, size_t len_value);

    int processResponseBody();
    int appendResponseBody(const unsigned char *body, size_t size);

    int processLogging();

    ModSecurityIntervention *intervention();

    void cleanup();

    const char *getResponseBody();
    int getResponseBodyLenth();

    std::string resolve_variable(std::string);

    void store_variable(std::string, std::string);
    void store_variable(std::string,
        std::unordered_map<std::string, std::string>);

    ModSecurityStringVariables m_variables_strings;

    void debug(int, std::string);
    std::vector<actions::Action *> actions;

 private:
    std::ofstream myfile;
    Rules *m_rules;
    char *m_ipAddress;
    char *m_uri;
    std::ostringstream m_requestBody;
    std::ostringstream m_responseBody;
    ModSecurityCollectionsVariables m_variables_collections;
};


#endif

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup ModSecurity_C_API */
Assay *msc_new_assay(ModSecurity *ms, Rules *rules);

/** @ingroup ModSecurity_C_API */
int msc_process_connection(Assay *assay, char *ip);

/** @ingroup ModSecurity_C_API */
int msc_process_request_headers(Assay *assay);

/** @ingroup ModSecurity_C_API */
int msc_add_request_header(Assay *assay, const unsigned char *key,
    const unsigned char *value);

/** @ingroup ModSecurity_C_API */
int msc_add_n_request_header(Assay *assay, const unsigned char *key,
    size_t len_key, const unsigned char *value, size_t len_value);

/** @ingroup ModSecurity_C_API */
int msc_process_request_body(Assay *assay);

/** @ingroup ModSecurity_C_API */
int msc_append_request_body(Assay *assay,
    const unsigned char *body, size_t size);

/** @ingroup ModSecurity_C_API */
int msc_process_response_headers(Assay *assay);
/** @ingroup ModSecurity_C_API */
int msc_add_response_header(Assay *assay, const unsigned char *key,
    const unsigned char *value);
/** @ingroup ModSecurity_C_API */
int msc_add_n_response_header(Assay *assay, const unsigned char *key,
    size_t len_key, const unsigned char *value, size_t len_value);

/** @ingroup ModSecurity_C_API */
int msc_process_response_body(Assay *assay);
/** @ingroup ModSecurity_C_API */
int msc_append_response_body(Assay *assay,
    const unsigned char *body, size_t size);

/** @ingroup ModSecurity_C_API */
int msc_process_uri(Assay *assay, char *uri);
/** @ingroup ModSecurity_C_API */
const char *msc_get_response_body(Assay *assay);
/** @ingroup ModSecurity_C_API */
int msc_get_response_body_length(Assay *assay);

/** @ingroup ModSecurity_C_API */
void msc_assay_cleanup(Assay *assay);

/** @ingroup ModSecurity_C_API */
ModSecurityIntervention *msc_intervention(Assay *assay);

/** @ingroup ModSecurity_C_API */
int msc_process_logging(Assay *assay);

#ifdef __cplusplus
}
}  // namespace ModSecurity
#endif


#endif  // HEADERS_MODSECURITY_ASSAY_H_
