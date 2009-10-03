#ifndef _LIGHTTPD_CORE_LUA_H_
#define _LIGHTTPD_CORE_LUA_H_

#include <lighttpd/base.h>
#include <lua.h>

#define li_lua_lock(srv) g_mutex_lock((srv)->lualock);
#define li_lua_unlock(srv) g_mutex_unlock((srv)->lualock);

LI_API void lua_init_chunk_mt(lua_State *L);
LI_API liChunk* lua_get_chunk(lua_State *L, int ndx);
LI_API int lua_push_chunk(lua_State *L, liChunk *c);
LI_API liChunkQueue* lua_get_chunkqueue(lua_State *L, int ndx);
LI_API int lua_push_chunkqueue(lua_State *L, liChunkQueue *cq);

LI_API void lua_init_connection_mt(lua_State *L);
LI_API liConnection* lua_get_connection(lua_State *L, int ndx);
LI_API int lua_push_connection(lua_State *L, liConnection *con);

LI_API void lua_init_environment_mt(lua_State *L);
LI_API liEnvironment* lua_get_environment(lua_State *L, int ndx);
LI_API int lua_push_environment(lua_State *L, liEnvironment *env);

LI_API void lua_init_http_headers_mt(lua_State *L);
LI_API liHttpHeaders* lua_get_http_headers(lua_State *L, int ndx);
LI_API int lua_push_http_headers(lua_State *L, liHttpHeaders *headers);

LI_API void lua_init_physical_mt(lua_State *L);
LI_API liPhysical* lua_get_physical(lua_State *L, int ndx);
LI_API int lua_push_physical(lua_State *L, liPhysical *phys);

LI_API void lua_init_request_mt(lua_State *L);
LI_API liRequest* lua_get_request(lua_State *L, int ndx);
LI_API int lua_push_request(lua_State *L, liRequest *req);

LI_API liRequestUri* lua_get_requesturi(lua_State *L, int ndx);
LI_API int lua_push_requesturi(lua_State *L, liRequestUri *uri);

LI_API void lua_init_response_mt(lua_State *L);
LI_API liResponse* lua_get_response(lua_State *L, int ndx);
LI_API int lua_push_response(lua_State *L, liResponse *resp);

LI_API void lua_init_vrequest_mt(lua_State *L);
LI_API liVRequest* lua_get_vrequest(lua_State *L, int ndx);
LI_API int lua_push_vrequest(lua_State *L, liVRequest *vr);


/* return 1 if value is found in mt (on top of the stack), 0 if it is not found (stack balance = 0)
 * table, key on stack at pos 0 and 1 (i.e. __index metho)
 */
LI_API int li_lua_metatable_index(lua_State *L);

LI_API void li_lua_init(liServer *srv, lua_State *L);

LI_API int li_lua_push_traceback(lua_State *L, int narg);

LI_API void li_lua_restore_globals(lua_State *L);
LI_API void li_lua_new_globals(lua_State *L);

/* joinWith " " (map tostring parameter[from..to]) */
LI_API GString* lua_print_get_string(lua_State *L, int from, int to);

/* pairs() for a GHashTable GString -> GString:
 *   Don't modify the hastable while iterating:
 *   - no new keys
 *   - no delete
 *  Modifying values is fine; g_hash_table_insert() as long as the key already exists too.
 * The returned "next" function has an internal state, it ignores the table/state and previous key parameter.
 * returns: <next>, nil, nil on the stack (and 3 as c function)
 */
LI_API int li_lua_ghashtable_gstring_pairs(lua_State *L, GHashTable *ht);

#endif