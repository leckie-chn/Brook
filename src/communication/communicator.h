// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_COMMUNICATOR_H_
#define COMMUNICATION_COMMUNICATOR_H_

#include <string>

namespace brook {

//-----------------------------------------------------------------------
// The interface implemented by 'real' Communicators.
//-----------------------------------------------------------------------
class Communicator {
public:
    virtual ~Communicator() {}

    /* Send:
     * - send a message package to a specified server.
     * - actually write message into buffer
     * Return:
     * > 0 : bytes send
     * - 1 : error
     * Note:
     * - The first 4 bytes is the receive_id (represented by uint32) and
     *   it will be written to buffer but not sent to server.
     */
    virtual int Send(void *src, int size) = 0;

    virtual int Send(const std::string &src) = 0;

    /* Receive:
     * - receive a message package from any agent.
     * - actually read a message out from buffer
     * Return:
     * > 0 : bytes received
     * - 1 : error
     */
    virtual int Receive(void* dest, int max_size) = 0;

    virtual int Receive(std::string *dest) = 0;
};

} // namespace brook

#endif // COMMUNICATION_COMMUNICATOR_H_
