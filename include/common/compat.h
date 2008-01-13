/*
  include/common/compat.h
  Operating system compatibility interface.

  Copyright (C) 2000-2008 Willy Tarreau - w@1wt.eu
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, version 2.1
  exclusively.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _COMMON_COMPAT_H
#define _COMMON_COMPAT_H

/*
 * Gcc before 3.0 needs [0] to declare a variable-size array
 */
#if  __GNUC__  < 3
#define VAR_ARRAY	0
#else
#define VAR_ARRAY
#endif

/* This is needed on Linux for Netfilter includes */
#include <sys/socket.h>
#include <sys/types.h>
#include <common/config.h>

/* INTBITS
 * how many bits are needed to code the size of an int on the target platform.
 * (eg: 32bits -> 5)
 */
#define	INTBITS	        5

/* this is for libc5 for example */
#ifndef TCP_NODELAY
#define TCP_NODELAY     1
#endif

#ifndef SHUT_RD
#define SHUT_RD	        0
#endif

#ifndef SHUT_WR
#define SHUT_WR	        1
#endif

/* AIX does not define MSG_DONTWAIT. We'll define it to zero, and test it
 * wherever appropriate.
 */
#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT	0
#endif

#if defined(TPROXY) && defined(NETFILTER)
#include <linux/netfilter_ipv4.h>
#endif

/* On Linux, IP_TRANSPARENT and/or IP_FREEBIND generally require a kernel patch */
#if defined(CONFIG_HAP_LINUX_TPROXY)
#if !defined(IP_FREEBIND)
#define IP_FREEBIND 15
#endif /* !IP_FREEBIND */
#if !defined(IP_TRANSPARENT)
#define IP_TRANSPARENT 19
#endif /* !IP_TRANSPARENT */
#endif /* CONFIG_HAP_LINUX_TPROXY */

/* We'll try to enable SO_REUSEPORT on Linux 2.4 and 2.6 if not defined.
 * There are two families of values depending on the architecture. Those
 * are at least valid on Linux 2.4 and 2.6, reason why we'll rely on the
 * NETFILTER define.
 */
#if !defined(SO_REUSEPORT) && defined(NETFILTER)
#if    (SO_REUSEADDR == 2)
#define SO_REUSEPORT 15
#elif  (SO_REUSEADDR == 0x0004)
#define SO_REUSEPORT 0x0200
#endif /* SO_REUSEADDR */
#endif /* SO_REUSEPORT */

#if defined(__dietlibc__)
#include <strings.h>
#endif

#endif /* _COMMON_COMPAT_H */

/*
 * Local variables:
 *  c-indent-level: 8
 *  c-basic-offset: 8
 * End:
 */
