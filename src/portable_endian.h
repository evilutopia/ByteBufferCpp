// "License": Public Domain
// I, Mathias Panzenböck, place this file hereby into the public domain. Use it at your own risk for whatever you like.
// In case there are jurisdictions that don't support putting things in the public domain you can also consider it to
// be "dual licensed" under the BSD, MIT and Apache licenses, if you want to. This code is trivial anyway. Consider it
// an example on how to get the endian conversion functions on different platforms.

#ifndef PORTABLE_ENDIAN_H__
#define PORTABLE_ENDIAN_H__


#if (defined(_WIN16) || defined(_WIN32) || defined(_WIN64)) && !defined(__WINDOWS__)

#define __WINDOWS__

#endif

#if defined(__linux__) || defined(__CYGWIN__)

#include <endian.h>

#elif defined(__APPLE__)

#include <libkern/OSByteOrder.h>

#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define betoh16(x) OSSwapBigToHostInt16(x)
#define letoh16(x) OSSwapLittleToHostInt16(x)
 
#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define betoh32(x) OSSwapBigToHostInt32(x)
#define letoh32(x) OSSwapLittleToHostInt32(x)
 
#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define betoh64(x) OSSwapBigToHostInt64(x)
#define letoh64(x) OSSwapLittleToHostInt64(x)

#define __BYTE_ORDER    BYTE_ORDER
#define __BIG_ENDIAN    BIG_ENDIAN
#define __LITTLE_ENDIAN LITTLE_ENDIAN
#define __PDP_ENDIAN    PDP_ENDIAN

#elif defined(__OpenBSD__)

#include <sys/endian.h>

#elif defined(__NetBSD__) || defined(__FreeBSD__) || defined(__DragonFly__)

#include <sys/endian.h>

#define betoh16(x) betoh16(x)
#define letoh16(x) letoh16(x)
               
#define betoh32(x) betoh32(x)
#define letoh32(x) letoh32(x)
               
#define betoh64(x) betoh64(x)
#define letoh64(x) letoh64(x)

#elif defined(__WINDOWS__)

#include <winsock2.h>
#include <sys/param.h>

#if BYTE_ORDER == LITTLE_ENDIAN

#define htobe16(x) htons(x)
#define htole16(x) (x)
#define betoh16(x) ntohs(x)
#define letoh16(x) (x)
 
#define htobe32(x) htonl(x)
#define htole32(x) (x)
#define betoh32(x) ntohl(x)
#define letoh32(x) (x)
 
#define htobe64(x) htonll(x)
#define htole64(x) (x)
#define betoh64(x) ntohll(x)
#define letoh64(x) (x)

#define htobed(x) htonll(x)
#define htoled(x) (x)
#define betohd(x) ntohll(x)
#define letohd(x) (x)

#elif BYTE_ORDER == BIG_ENDIAN

/* that would be xbox 360 */
#define htobe16(x) (x)
#define htole16(x) __builtin_bswap16(x)
#define betoh16(x) (x)
#define letoh16(x) __builtin_bswap16(x)
 
#define htobe32(x) (x)
#define htole32(x) __builtin_bswap32(x)
#define betoh32(x) (x)
#define letoh32(x) __builtin_bswap32(x)
 
#define htobe64(x) (x)
#define htole64(x) __builtin_bswap64(x)
#define betoh64(x) (x)
#define letoh64(x) __builtin_bswap64(x)

#else

#error byte order not supported

#endif

#define __BYTE_ORDER    BYTE_ORDER
#define __BIG_ENDIAN    BIG_ENDIAN
#define __LITTLE_ENDIAN LITTLE_ENDIAN
#define __PDP_ENDIAN    PDP_ENDIAN

#else

#error platform not supported

#endif

#endif


namespace evilutopia
{
namespace util
{
/// @{
/* 浮点数字节序反转 */
inline float reverseFloat( const float inFloat )
{
   float retVal;
   char *floatToConvert = ( char* ) & inFloat;
   char *returnFloat = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnFloat[0] = floatToConvert[3];
   returnFloat[1] = floatToConvert[2];
   returnFloat[2] = floatToConvert[1];
   returnFloat[3] = floatToConvert[0];

   return retVal;
}

inline double reverseDouble( const double inDouble )
{
   double retVal;
   char *doubleToConvert = ( char* ) & inDouble;
   char *returnDouble = ( char* ) & retVal;

   // swap the bytes into a temporary buffer
   returnDouble[0] = doubleToConvert[7];
   returnDouble[1] = doubleToConvert[6];
   returnDouble[2] = doubleToConvert[5];
   returnDouble[3] = doubleToConvert[4];
   returnDouble[4] = doubleToConvert[3];
   returnDouble[5] = doubleToConvert[2];
   returnDouble[6] = doubleToConvert[1];
   returnDouble[7] = doubleToConvert[0];

   return retVal;
}

/// @}

/// @{
//主机字节序（LITTLE_ENDIAN) 转换为网络字节序

inline int16_t HostToNetwork16(int16_t val)
{
  return htobe16(val);
}

inline int32_t HostToNetwork32(int32_t val)
{
  return htobe32(val);
}

inline int64_t HostToNetwork64(int64_t val)
{
  return htobe64(val);
}

inline uint16_t HostToNetwork16(uint16_t val)
{
  return htobe16(val);
}

inline uint32_t HostToNetwork32(uint32_t val)
{
  return htobe32(val);
}

inline uint64_t HostToNetwork64(uint64_t val)
{
  return htobe64(val);
}

// 增加重载函数，方便使用

inline int16_t HostToNetwork(int16_t val)
{
  return HostToNetwork16(val);
}

inline int32_t HostToNetwork(int32_t val)
{
  return HostToNetwork32(val);
}

inline int64_t HostToNetwork(int64_t val)
{
  return HostToNetwork64(val);
}

inline uint16_t HostToNetwork(uint16_t val)
{
  return HostToNetwork16(val);
}

inline uint32_t HostToNetwork(uint32_t val)
{
  return HostToNetwork32(val);
}

inline uint64_t HostToNetwork(uint64_t val)
{
  return HostToNetwork64(val);
}

inline float HostToNetwork(float val)
{

#if BYTE_ORDER == LITTLE_ENDIAN

  return reverseFloat(val);

#elif BYTE_ORDER == BIG_ENDIAN

  return val;

#else

#error byte order not supported

#endif
}

inline double HostToNetwork(double val)
{

#if BYTE_ORDER == LITTLE_ENDIAN

  return reverseDouble(val);

#elif BYTE_ORDER == BIG_ENDIAN

  return val;

#else

#error byte order not supported

#endif
}
/// @}

/// @{
// 网络字节序（BIG_ENDIAN) 转换为主机字节序

inline int16_t NetworkToHost16(int16_t val)
{
  return betoh16(val);
}

inline int32_t NetworkToHost32(int32_t val)
{
  return betoh32(val);
}

inline int64_t NetworkToHost64(int64_t val)
{
  return betoh64(val);
}

inline uint16_t NetworkToHost16(uint16_t val)
{
  return betoh16(val);
}

inline uint32_t NetworkToHost32(uint32_t val)
{
  return betoh32(val);
}

inline uint64_t NetworkToHost64(uint64_t val)
{
  return betoh64(val);
}

// 增加重载函数，方便使用

inline int16_t NetworkToHost(int16_t val)
{
  return NetworkToHost16(val);
}

inline int32_t NetworkToHost(int32_t val)
{
  return NetworkToHost32(val);
}

inline int64_t NetworkToHost(int64_t val)
{
  return NetworkToHost64(val);
}

inline uint16_t NetworkToHost(uint16_t val)
{
  return NetworkToHost16(val);
}

inline uint32_t NetworkToHost(uint32_t val)
{
  return NetworkToHost32(val);
}

inline uint64_t NetworkToHost(uint64_t val)
{
  return NetworkToHost64(val);
}

inline float NetworkToHost(float val)
{

#if BYTE_ORDER == LITTLE_ENDIAN

  return reverseFloat(val);

#elif BYTE_ORDER == BIG_ENDIAN

  return val;

#else

#error byte order not supported

#endif
}

inline double NetworkToHost(double val)
{

#if BYTE_ORDER == LITTLE_ENDIAN

  return reverseDouble(val);

#elif BYTE_ORDER == BIG_ENDIAN

  return val;

#else

#error byte order not supported

#endif
}

/// @}


} // end util 
} // end evilutopia
