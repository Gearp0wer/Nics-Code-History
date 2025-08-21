/* You May Edit This File (Will be Tested/Graded with Original Though!)
 * - vm_settings.h (StrawHat VM)
 * - Copyright: Prof. Kevin Andrea, George Mason University.  All Rights Reserved
 * - Date: Aug 2024
 *
 *   User Configuration Settings for the StrawHat VM System
 */

#ifndef VM_SETTINGS_H
#define VM_SETTINGS_H

// This is the Prompt Formatting for the Shell
#define PROMPT "[StrawHat-VM]$ "

// Set USE_COLORS to 1 for colors or 0 for normal.
#define USE_COLORS 1

// Turns Debug printing on (1) and off (0)
#define DEFAULT_DEBUG 0

// Process-related Settings
#define DEFAULT_PRIORITY 128   
#define MIN_PRIORITY 1
#define MAX_PRIORITY 255
#define STARVING_AGE 5           // If age >= STARVING_AGE, it's starving

// Time to run each Process for between Context Switching
#define SLEEP_USEC        250000 //   250000 = 250ms
#define SLEEP_MIN_USEC    100000 //   100000 = 100ms
#define SLEEP_MAX_USEC  10000000 // 10000000 = 10sec

// Time to wait between Context Switches before Running Next Process
#define BETWEEN_USEC      1000000 //  1000000 =  1000ms = 1 sec
#define BETWEEN_MIN_USEC   100000 //   100000 =   100ms = 0.1 sec
#define BETWEEN_MAX_USEC 10000000 // 10000000 = 10000ms = 10 sec


//////////////////////////////////////////////////////////////////////
//  Do not modify anything below this line. 
//////////////////////////////////////////////////////////////////////
#define DO_SUSPEND 0  // Does StrawHat Support Suspend+Resume of Processes? (0 - no, 1 - yes)
#define DO_MLFQ 1     // Does StrawHat Support MLFQ Operations (promotions) (0 - no, 1 - yes)
#define LOCAL_CMDS_ONLY 0 // Restricts Shell to local folder binaries only (recompile lib on change)
#define MAX_CMD_LINE 256 // Max characters in a user input
#define MAX_STATUS   512 // Max characters in a status message
#define MAX_PROC 64  // Max Processes Runnable
#define MAX_CMD  256 // Max size of a single command
#define MAX_PATH 512 // Max size of a command with full absolute path
#define MAX_ARGS 16  // Max number of args for a single shell command

#endif
