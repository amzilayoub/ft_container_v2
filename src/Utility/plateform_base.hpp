/*
** This little header file is to fix the issue with
** compiling the project on linux vs MAcOs.
*/

#pragma once

#if defined (__linux__)

# define ptrdiff_t __gnu_cxx::ptrdiff_t

# define NULL (void*)0

# define nullptr NULL

#endif