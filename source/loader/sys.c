#include <stdio.h>
#include <ogcsys.h>
#include <stdlib.h>
#include "wiiuse/wpad.h"
#include "mem2.hpp"
#include <string.h>
#include <ogc/lwp_threads.h>
#include <ogc/lwp_watchdog.h>
#include "sys.h"
#include "gecko.h"

#include <ogc/machine/processor.h>
#include "sha1.h"
#include "fs.h"
#include "mem2.hpp"

/* Variables */
static bool reset = false;
static bool shutdown = false;
bool exiting = false;

static bool priiloader_def = false;
static bool return_to_hbc = false;
static bool return_to_menu = false;
static bool return_to_priiloader = false;
static bool return_to_disable = false;
static bool return_to_bootmii = false;

extern void __exception_closeall();
static vu16* const _dspReg = (u16*)0xCC005000;
extern u32 __PADDisableRecalibration(s32 disable);

void __Wpad_PowerCallback()
{
	/* Poweroff console */
	shutdown = 1;
}

void Open_Inputs(void)
{
	/* Initialize Wiimote subsystem */
	PAD_Init();
	WPAD_Init();

	/* Set POWER button callback */
	WPAD_SetPowerButtonCallback(__Wpad_PowerCallback);
	
	WPAD_SetDataFormat(WPAD_CHAN_ALL, WPAD_FMT_BTNS_ACC_IR);
	
	WPAD_SetIdleTimeout(60*5); // idle after 5 minutes
}

void Close_Inputs(void)
{
	u32 cnt;

	/* Disconnect Wiimotes */
	for (cnt = 0; cnt < 4; cnt++)
		WPAD_Disconnect(cnt);

	/* Shutdown Wiimote subsystem */
	WPAD_Shutdown();
}

bool Sys_Exiting(void)
{
	return reset || shutdown || exiting;
}

void Sys_Test(void)
{
	if(reset || shutdown) Close_Inputs();

	if (reset) SYS_ResetSystem(SYS_RESTART, 0, 0);
	else if (shutdown) SYS_ResetSystem(SYS_POWEROFF, 0, 0);
}

void Sys_ExitTo(int option)
{
	priiloader_def = option == PRIILOADER_DEF;
	return_to_hbc = option == EXIT_TO_HBC;
	return_to_menu = option == EXIT_TO_MENU;
	return_to_priiloader = option == EXIT_TO_PRIILOADER;
	return_to_disable = option == EXIT_TO_DISABLE;
	return_to_bootmii = option == EXIT_TO_BOOTMII;

	//magic word to force wii menu in priiloader.
	if(return_to_menu)
	{
		*(vu32*)0x8132FFFB = 0x50756e65;
	}
	else if(return_to_priiloader)
	{
		*(vu32*)0x8132FFFB = 0x4461636f;
	}
	else
	{
		*(vu32*)0x8132FFFB = 0xffffffff;
	}
	DCFlushRange((void *)(0x8132FFFB), 4);
}

void Sys_Exit(void)
{
	if(return_to_disable) return;

	/* Shutdown Inputs */
	Close_Inputs();

	if (return_to_menu || return_to_priiloader || priiloader_def)
		Sys_LoadMenu();
	else if(return_to_bootmii)
		IOS_ReloadIOS(254);

	//else
	if(WII_LaunchTitle(HBC_108) < 0)
		if(WII_LaunchTitle(HBC_HAXX) < 0)
			if(WII_LaunchTitle(HBC_JODI) < 0)
				WII_ReturnToMenu(); //SYS_ResetSystem doesnt work properly with new libogc
}

void __Sys_ResetCallback(void)
{
	reset = true;
}

void __Sys_PowerCallback(void)
{
	shutdown = true;
}


void Sys_Init(void)
{
	/* Set RESET/POWER button callback */
	SYS_SetResetCallback(__Sys_ResetCallback);
	SYS_SetPowerCallback(__Sys_PowerCallback);
}

void Sys_LoadMenu(void)
{
	/* Return to the Wii system menu */
	WII_ReturnToMenu(); //SYS_ResetSystem doesnt work properly with new libogc
}

static void __dsp_shutdown()
{
	u32 tick;

	_dspReg[5] = (DSPCR_DSPRESET|DSPCR_HALT);
	_dspReg[27] &= ~0x8000;
	while(_dspReg[5]&0x400);
	while(_dspReg[5]&0x200);

	_dspReg[5] = (DSPCR_DSPRESET|DSPCR_DSPINT|DSPCR_ARINT|DSPCR_AIINT|DSPCR_HALT);
	_dspReg[0] = 0;
	while((_SHIFTL(_dspReg[2],16,16)|(_dspReg[3]&0xffff))&0x80000000);

	tick = gettick();
	while((gettick()-tick)<44);

	_dspReg[5] |= DSPCR_RES;
	while(_dspReg[5]&DSPCR_RES);
}

//Modified libogc call
void Sys_Shutdown(void)
{
	__dsp_shutdown();
	u32 ret = __PADDisableRecalibration(TRUE);

	__IOS_ShutdownSubsystems();
	__exception_closeall();
	LCDisable();

	__lwp_thread_closeall();
	__PADDisableRecalibration(ret);
}
