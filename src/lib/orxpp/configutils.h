/*
 * configutils.h
 *
 *  Created on: Nov 20, 2015
 *      Author: Enis Bayramoğlu
 */

#ifndef ORXPP_CONFIGUTILS_H_
#define ORXPP_CONFIGUTILS_H_

#include <utils/orxString.h>
#include <core/orxConfig.h>
#include "list.h"

namespace orx {


inline const char * Persist(const char * str) {
    return orxString_GetFromID(orxString_GetID(str));
}


class ConfigSectionGuard {
	bool guarded = false;
public:
    ConfigSectionGuard(const char * section_name) {
    	if(section_name != nullptr) {
            orxConfig_PushSection(section_name);
            guarded = true;
    	}
    }
    ~ConfigSectionGuard() {
    	if(guarded) orxConfig_PopSection();
    }
};


const size_t STACK_BUF_SIZE = 32;
class ConfigListBuilder {
public:
    ConfigListBuilder & operator << (const char * str) {
        list.push_back(Persist(str));
        return *this;
    }
    void WriteToConfig(const char * section) {
        size_t count = list.size();
        if(count < STACK_BUF_SIZE) WriteWithBuffer(section, count);
        else {
            const char ** strings = new const char *[count];
            list.copy_to_buffer(strings, count);
            orxConfig_SetListString(section, strings, count);
            delete strings;
        }
    }
private:
    orx::LinkList<const char *> list;
    void WriteWithBuffer(const char * section, size_t count) {
        const char * strings[STACK_BUF_SIZE];
        list.copy_to_buffer(strings);
        orxConfig_SetListString(section, strings, count);
    }
};


}
#endif

