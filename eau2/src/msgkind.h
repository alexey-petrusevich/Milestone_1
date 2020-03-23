#pragma once

typedef unsigned char byte;

enum Headers {
    INT,
    DOUBLE,
    BOOL,
    STRING,
    INT_ARRAY,
    DOUBLE_ARRAY,
    BOOL_ARRAY,
    STRING_ARRAY,
    SIZ,
    SOCK
};

enum class MsgKind {
    Ack,
    Nack,
    Put,
    Reply,
    Get,
    WaitAndGet,
    Status,
    Kill,
    Register,
    Directory
};
