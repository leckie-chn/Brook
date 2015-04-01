// Copyright 2015 PKU-Cloud
// Author : Chao Ma (mctt90@gmail.com)
//
#ifndef COMMUNICATION_COMMUNICATOR_H_
#define COMMUNICATION_COMMUNICATOR_H_

namespace brook {

//-----------------------------------------------------------------------
// The interface implemented by 'real' Communicators.
//-----------------------------------------------------------------------
template <typename Message>
class Communicator {
public:
    virtual ~Communicator() {}

    virtual bool Initialize() = 0;

    /* Send:
     * - send a message package to a specified server.
     */
    virtual int Send(Message&) = 0;

    /* Receive:
     * - receive a message package from any agent.
     */
    virtual int Receive(Message&) = 0;

    virtual bool Finalize() = 0;
};

} // namespace brook

#endif // COMMUNICATION_COMMUNICATOR_H_
