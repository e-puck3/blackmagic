/**
 * @file	platform_commands.h
 * @brief  	Custom GDB commands added to the default ones
 * 
 * @written by  		Daniel Burnier
 * @creation date		11.08.2017
 * @modified by 		Eliot ferragni
 * last modification	27.02.2019
 */

#if defined(PLATFORM_COMMANDS_DEFINE)
/********************************************/
/* Begining of platform dedicated commands. */
/********************************************/

static bool cmd_example(target *t, int argc, const char **argv);

/***************************************/
/* End of platform dedicated commands. */
/***************************************/
#undef PLATFORM_COMMANDS_DEFINE
#endif

#if defined(PLATFORM_COMMANDS_LIST)
/****************************************************/
/* Begining of List of platform dedicated commands. */
/* IMPORTANT : Each line MUST finish with "\"       */
/****************************************************/

	{"example", (cmd_handler)cmd_example, "This is an example command to how how to add a custom command to GDB" }, \

/***********************************************/
/* End of List of platform dedicated commands. */
/***********************************************/
#undef PLATFORM_COMMANDS_LIST
#endif

#if defined(PLATFORM_COMMANDS_CODE)
/****************************************************/
/* Begining of Code of platform dedicated commands. */
/****************************************************/

static bool cmd_example(target *t, int argc, const char **argv)
{
	(void)t;
	
	gdb_outf("You entered %d args to the command\n", argc-1);
	return true;
}

/***********************************************/
/* End of Code of platform dedicated commands. */
/***********************************************/
#undef PLATFORM_COMMANDS_CODE
#endif
