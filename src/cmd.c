#include "cmd.h"

#include <redismodule.h>
#include <stdlib.h>

#include "utils.h"

#define INFO_PROCESSED "total_commands_processed:"
#define INFO_PROCESSED_LEN (strlen(INFO_PROCESSED))
#define INFO_SEPERATOR "\r\n"

static int _myCallCount = 0;

int CommandCount(RedisModuleCtx* ctx, RedisModuleString** argv, int argc) {
  _myCallCount++;  // ignore call for "INFO" call

  RedisModuleCallReply* reply;
  reply = RedisModule_Call(ctx, "INFO", "c", "stats");
  int replyType = RedisModule_CallReplyType(reply);

  if (replyType == REDISMODULE_REPLY_STRING) {
    int fail = 1;
    size_t len;
    const char* ptr = RedisModule_CallReplyStringPtr(reply, &len);
    const char* p1 = StrFind(ptr, INFO_PROCESSED, len);
    if (p1) {
      const char* p2 = StrFind(p1, INFO_SEPERATOR, len - (p1 - ptr));
      if (p2) {
        // dec my call "INFO" command
        // add this calling "‫‪COMMANDCOUNT‬‬" command
        int num = StrInt(p1 + INFO_PROCESSED_LEN, p2 - p1 - INFO_PROCESSED_LEN) - _myCallCount + 1;
        RedisModule_ReplyWithLongLong(ctx, num);
        fail = 0;
      }
    }

    if (fail) {
      RedisModule_ReplyWithSimpleString(ctx, "unknown call output");
    }
  } else if (replyType == REDISMODULE_REPLY_ERROR) {
    RedisModule_ReplyWithSimpleString(ctx, "error on call");
  } else {
    RedisModule_ReplyWithSimpleString(ctx, "unknown call type");
  }

  return REDISMODULE_OK;
}
