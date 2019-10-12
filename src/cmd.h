#pragma once
#include <redismodule.h>

int CommandCount(RedisModuleCtx* ctx, RedisModuleString** argv, int argc);
