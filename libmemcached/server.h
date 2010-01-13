/* LibMemcached
 * Copyright (C) 2006-2009 Brian Aker
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license.  See
 * the COPYING file in the parent directory for full text.
 *
 * Summary: String structure used for libmemcached.
 *
 */

#ifndef __MEMCACHED_SERVER_H__
#define __MEMCACHED_SERVER_H__

#ifdef __cplusplus
extern "C" {
#endif

struct memcached_server_st {
  struct {
    bool is_allocated:1;
    bool sockaddr_inited:1;
  } options;
  uint32_t number_of_hosts;
  uint32_t cursor_active;
  in_port_t port;
  int cached_errno;
  int fd;
  uint32_t io_bytes_sent; /* # bytes sent since last read */
  uint32_t server_failure_counter;
  uint32_t weight;
  uint8_t major_version;
  uint8_t micro_version;
  uint8_t minor_version;
  memcached_connection_t type;
  char *read_ptr;
  char *cached_server_error;
  size_t read_buffer_length;
  size_t read_data_length;
  size_t write_buffer_offset;
  struct addrinfo *address_info;
  time_t next_retry;
  memcached_st *root;
  uint64_t limit_maxbytes;
  char read_buffer[MEMCACHED_MAX_BUFFER];
  char write_buffer[MEMCACHED_MAX_BUFFER];
  char hostname[MEMCACHED_MAX_HOST_LENGTH];
};

// Local Only Inline
static inline uint32_t memcached_servers_count(memcached_server_st *servers)
{
  return servers->number_of_hosts;
}

// Local Only Inline
static inline uint32_t memcached_servers_set_count(memcached_server_st *servers, uint32_t count)
{
  return servers->number_of_hosts= count;
}



#define memcached_server_count(A) (A)->number_of_hosts
#define memcached_server_name(A,B) (B).hostname
#define memcached_server_port(A,B) (B).port
#define memcached_server_list(A) (A)->servers
#define memcached_server_list_set(A,B) (A)->servers=(B)
#define memcached_server_response_count(A) (A)->cursor_active

LIBMEMCACHED_API
memcached_return_t memcached_server_cursor(memcached_st *ptr,
                                           memcached_server_fn *callback,
                                           void *context,
                                           uint32_t number_of_callbacks);

LIBMEMCACHED_API
memcached_server_st *memcached_server_by_key(memcached_st *ptr,
                                             const char *key,
                                             size_t key_length,
                                             memcached_return_t *error);

LIBMEMCACHED_API
const char *memcached_server_error(memcached_server_st *ptr);

LIBMEMCACHED_API
void memcached_server_error_reset(memcached_server_st *ptr);

/* These should not currently be used by end users */
/* TODO: Is the above comment valid? If so, how can we unit test these if they
 * aren't exported. If not, we should remove the comment */
LIBMEMCACHED_LOCAL
memcached_server_st *memcached_server_create(memcached_st *memc, memcached_server_st *ptr);

LIBMEMCACHED_LOCAL
memcached_server_st *memcached_server_create_with(memcached_st *memc,
                                                  memcached_server_st *host,
                                                  const char *hostname,
                                                  in_port_t port,
                                                  uint32_t weight,
                                                  memcached_connection_t type);

LIBMEMCACHED_API
void memcached_server_free(memcached_server_st *ptr);

LIBMEMCACHED_LOCAL
memcached_server_st *memcached_server_clone(memcached_server_st *clone,
                                            memcached_server_st *ptr);

LIBMEMCACHED_API
memcached_return_t memcached_server_remove(memcached_server_st *st_ptr);

LIBMEMCACHED_API
memcached_server_st *memcached_server_get_last_disconnect(memcached_st *ptr);

#ifdef __cplusplus
}
#endif

#endif /* __MEMCACHED_SERVER_H__ */