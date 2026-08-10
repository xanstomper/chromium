#ifndef ULTRALIGHT_SECURITY_NETWORK_LOCK_H_
#define ULTRALIGHT_SECURITY_NETWORK_LOCK_H_

#include <string>

namespace ultralight {
namespace security {

// Enforces strict privacy routing.
// When enabled, guarantees no silent fallback to direct connections
// if a proxy/VPN route disappears.
class NetworkLock {
 public:
  enum class RoutingMode {
    DIRECT,
    PROXY_STRICT,
    TOR_STRICT,
    OFFLINE_LOCKDOWN
  };

  static NetworkLock& GetInstance();

  void SetMode(RoutingMode mode);
  
  // Evaluates every socket creation request.
  // Returns false if the request violates the routing mode.
  bool IsSocketAllowed(const std::string& destination_ip, int port);

  // Checks DNS resolution policy (e.g. enforcing DoH).
  bool IsDnsResolutionAllowed(const std::string& hostname);

 private:
  NetworkLock();
  ~NetworkLock();

  RoutingMode current_mode_ = RoutingMode::DIRECT;
  bool is_panic_mode_active_ = false;
};

}  // namespace security
}  // namespace ultralight

#endif  // ULTRALIGHT_SECURITY_NETWORK_LOCK_H_
