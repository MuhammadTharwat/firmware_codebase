#include "stdint.h"
#include "stdbool.h"
#include "string.h"
#include "diagnostic_log.hpp"
#ifndef ASSERT_H_
#define ASSERT_H_

#ifdef __TEST
#define _ASSERT(cond)                                                        \
	do                                                                       \
	{                                                                        \
		if (!(cond))                                                         \
		{                                                                    \
			DBG_LOG_ERR("[ASSERT] in function %s() , line %d\r\n",           \
						__FUNCTION__, __LINE__);                             \
			DIAGNOSTIC_LOG_STR("[ASSERT] in Function ", false);              \
			DIAGNOSTIC_LOG_STR((char *)__FUNCTION__, false);                 \
			DIAGNOSTIC_LOG_STR_U32(" Line ", __LINE__, radix_decimal, true); \
			while (1)                                                        \
				;                                                            \
		}                                                                    \
	} while (0);
#else
#define _ASSERT(cond)                                                    \
	do                                                                   \
	{                                                                    \
		if (!(cond))                                                     \
		{                                                                \
			DBG_LOG_ERR("[ASSERT] in function %s() , line %d\r\n",       \
						__FUNCTION__, __LINE__);                         \
			DIAGNOSTIC_LOG_ASSERT((char *)__FUNCTION__, __LINE__, true); \
			while (1)                                                    \
			{                                                            \
				system_assertion_action();                               \
			}                                                            \
		}                                                                \
	} while (0);
#endif

static inline void assert(bool expression)
{
	_ASSERT(expression);
}
#endif