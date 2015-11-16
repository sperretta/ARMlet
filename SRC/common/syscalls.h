/** \file syscalls.h
 * Header file containing syscall function definitions.
 */
#ifndef __SYSCALL_H__
#define __SYSCALL_H__

// Following 3 defines are used for syscall offset calculation.

#define SCA 0xD201D002 /**< SCA */
#define SCB 0x422B0009 /**< SCB */
#define SCE 0x80010070 /**< SCE */

/** Function type void fn_name( void ); */
typedef void( *sc_vv )( void );

/** Syscall number 0x0477. */
const unsigned int sc0477[] = { SCA, SCB, SCE, 0x0477 };
/** void EnableGetkeyToMainFunctionReturn( void ); */
#define EnableGetkeyToMainFunctionReturn ( *( sc_vv )sc0477 )

/** Syscall number 0x0478. */
const unsigned int sc0478[] = { SCA, SCB, SCE, 0x0478 };
/** void DisableGetkeyToMainFunctionReturn( void ); */
#define DisableGetkeyToMainFunctionReturn ( *( sc_vv )sc0478 )

#endif
