#ifndef LOTIDESERVER_HPP
#define LOTIDESERVER_HPP

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <regex>


#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/lotiderpc.grpc.pb.h"
#else
#include "lotiderpc.grpc.pb.h"
#endif

#include "LoTide.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using lotiderpc::Request;
using lotiderpc::Response;
using lotiderpc::LoTideRPC;

namespace lotide {

class LoTideServer final : public LoTideRPC::Service {
public:
    Status GetCommand(ServerContext* context, const Request* request,
                  Response* response) override;

    void launch();
private:
    int parseCommand(std::string);
};

}

#endif
