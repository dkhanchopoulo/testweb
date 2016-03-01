#pragma once
#include <string>

// copy from boost asio example by Dimitris

namespace httpservice{

struct reply;
struct request;

/// The common handler for all incoming requests.
class cRequestHandler
{
public:
  cRequestHandler(const cRequestHandler&) = delete;
  cRequestHandler& operator=(const cRequestHandler&) = delete;

  /// Construct with a directory containing files to be served.
  explicit cRequestHandler(const std::string& doc_root);

  /// Handle a request and produce a reply.
  void handle_request(const request& req, reply& rep);

private:
  /// The directory containing the files to be served.
  std::string doc_root_;

  /// Perform URL-decoding on a string. Returns false if the encoding was
  /// invalid.
  static bool url_decode(const std::string& in, std::string& out);
};

}

