#pragma once

/**
 * @brief This file represents various types of messages to be sent across the
 * networks as well as headers of serialized objects.
 * @file msgkind.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

typedef unsigned char byte;

/**
 * @brief Represents headers of serialized objects. Works in accord with
 * serializer.h and deserializer.h.
 * @file msgkind.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
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

/**
 * @brief Represents types of messages to be sent across the network.
 * @file msgkind.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */
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
