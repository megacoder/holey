/*
 *------------------------------------------------------------------------
 * vim: ts=8 sw=8
 *------------------------------------------------------------------------
 * Author:   reynolds (Tommy Reynolds)
 * Filename: holey.c
 * Created:  2006-12-30 13:24:32
 *------------------------------------------------------------------------
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>

#include <gcc-compat.h>

static	char *		fn = "./biggun";
static	off_t const	maxsize = ((off_t) 4) * 1024 * 1024;
static	size_t const	wlen = 512;
static	off_t		point;
static	unsigned	nonfatal;

/*
 *------------------------------------------------------------------------
 * main: central control logic
 *------------------------------------------------------------------------
 */

int
main(
	int		argc	unused_,
	char * *	argv	unused_
)
{
	int		fd;
	unsigned char *	window;

	unlink( fn );
	fd = open(
		fn, 
		(O_RDWR | O_CREAT),
		0644
	);
	if( fd == -1 )	{
		perror( fn );
		exit( 1 );
	}
	if( ftruncate( fd, maxsize ) )	{
		perror( "ftruncate( fd, maxsize )" );
		exit( 1 );
	}
	point = getpagesize() * 1;
	window = mmap(
		NULL,
		wlen,
		(PROT_READ | PROT_WRITE),
		(MAP_SHARED),
		fd,
		point
	);
	assert( window != MAP_FAILED );
	window[ 0 ] = 0xAA;
	if( munmap( window, wlen ) )	{
		perror( "munmap" );
		exit( 1 );
	}
	if( ftruncate( fd, point + 1 ) )	{
		perror( "ftruncate" );
	}
	close( fd );
	return( nonfatal ? 1 : 0 );
}
