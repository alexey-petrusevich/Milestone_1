#pragma once

typedef unsigned char byte;


enum Headers{
    INT, SIZ, DBL, STR, SOCK, D_ARRAY, S_ARRAY
};


enum class MsgKind {
    Ack, Nack, Put, Reply, Get, WaitAndGet, Status, Kill, Register, Directory
};
