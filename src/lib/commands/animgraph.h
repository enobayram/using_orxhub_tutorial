/*
 * config_processors.h
 *
 *  Created on: Sep 24, 2015
 *      Author: Enis Bayramoglu
 */

#ifndef COMMANDS_ANIMGRAPH_H_
#define COMMANDS_ANIMGRAPH_H_

#include <object/orxObject.h>

#ifdef __cplusplus
extern "C" {
#endif

void ProcessAnimGraph(const char * section);

const orxSTRING orxObjectX_GetAnimForTag(orxOBJECT *_pstObject, const orxSTRING _zAnimTag);

orxSTATUS orxObjectX_SetCurrentAnimByTag(orxOBJECT *_pstObject, const orxSTRING _zAnimTag);

orxSTATUS orxObjectX_SetTargetAnimByTag(orxOBJECT *_pstObject, const orxSTRING _zAnimTag);

orxBOOL orxObjectX_CurrentAnimHasTag(orxOBJECT *_pstObject, const orxSTRING _zAnimTag);

orxBOOL orxObjectX_TargetAnimHasTag(orxOBJECT *_pstObject, const orxSTRING _zAnimTag);

void RegisterAnimGraphCommands();

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_ANIMGRAPH_H_ */

