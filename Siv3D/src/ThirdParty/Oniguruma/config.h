/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define to 1 if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to 1 if you have `alloca', as a function or macro. */
/* #undef HAVE_ALLOCA */

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
/* #undef HAVE_ALLOCA_H */

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H  1

/* Define to 1 if you have the <sys/times.h> header file. */
/* #undef HAVE_SYS_TIMES_H */

/* Define to 1 if you have the <sys/time.h> header file. */
/* #undef HAVE_SYS_TIME_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H  1

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H  1

/* Name of package */
#define PACKAGE  onig

/* Define to the version of this package. */
#define PACKAGE_VERSION  6.9.5

/* The size of `int', as computed by sizeof. */
//#define SIZEOF_INT  4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG  (LONG_MAX == 2147483647L ? 4 : 8)

/* Define if enable CR+NL as line terminator */
/* #undef USE_CRNL_AS_LINE_TERMINATOR */

/* Version number of package */
#define VERSION  6.9.5

# if defined(_MSC_VER)
	# pragma warning (disable: 4100)
	# pragma warning (disable: 4131)
	# pragma warning (disable: 4201)
	# pragma warning (disable: 4244)
	# pragma warning (disable: 4245)
	# pragma warning (disable: 4389)
	# pragma warning (disable: 4456)
	# pragma warning (disable: 4701)
# endif
