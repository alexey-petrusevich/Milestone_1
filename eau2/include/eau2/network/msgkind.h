#pragma once
/**
 * @brief This file represents various types of messages to be sent across the
 * networks.
 * @file msgkind.h
 * @author Aliaksei Petrusevich <petrusevich.a@husky.neu.edu>
 * @author Megha Rao <rao.m@husky.neu.edu>
 * @date March 30, 2020
 */

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
