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
/** Function type void fn_name( char ); */
typedef void( *sc_vc )( char );

/** Syscall number 0x0477. */
static const unsigned int sc0477[] = { SCA, SCB, SCE, 0x0477 };
/** void EnableGetkeyToMainFunctionReturn( void ); */
#define EnableGetkeyToMainFunctionReturn ( *( sc_vv )sc0477 )

/** Syscall number 0x0478. */
static const unsigned int sc0478[] = { SCA, SCB, SCE, 0x0478 };
/** void DisableGetkeyToMainFunctionReturn( void ); */
#define DisableGetkeyToMainFunctionReturn ( *( sc_vv )sc0478 )

/** Syscall number 0x0811. */
static const unsigned int sc0811[] = { SCA, SCB, SCE, 0x0811 };
/** void Cursor_SetFlashOn( char flash_style ); */
#define Cursor_SetFlashOn ( *( sc_vc )sc0811 )

/** Syscall number 0x0812. */
static const unsigned int sc0812[] = { SCA, SCB, SCE, 0x0812 };
/** void Cursor_SetFlashOff( void ); */
#define Cursor_SetFlashOff ( *( sc_vv )sc0812 )

#endif
