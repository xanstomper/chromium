#include "NetworkLock.h"

namespace ultralight {
namespace security {

NetworkLock& NetworkLock::GetInstance() {
  static NetworkLock instance;
  return instance;
}

NetworkLock::NetworkLock() = default;
NetworkLock::~NetworkLock() = default;

void NetworkLock::SetMode(RoutingMode mode) {
  current_mode_ = mode;
  if (mode == RoutingMode::OFFLINE_LOCKDOWN) {
    is_panic_mode_active_ = true;
  }
}

bool NetworkLock::IsSocketAllowed(const std::string& destination_ip, int port) {
  if (is_panic_mode_active_ || current_mode_ == RoutingMode::OFFLINE_LOCKDOWN) {
    return false; // Absolute lockdown
  }

  if (current_mode_ == RoutingMode::PROXY_STRICT) {
    // In strict proxy mode, the only allowed direct sockets are to the proxy IP itself.
    // If destination_ip is not the configured proxy, DROP.
    // Implementation would check against configured proxy endpoint.
    return false; // Conceptual: fail-closed by default unless it's the proxy.
  }

  return true;
}

bool NetworkLock::IsDnsResolutionAllowed(const std::string& hostname) {
  if (is_panic_mode_active_) return false;
  
  // Enforce Encrypted DNS (DoH/DoT) only.
  // We reject system plaintext DNS if in strict mode.
  if (current_mode_ == RoutingMode::PROXY_STRICT) {
    // Return false if attempting to use port 53 UDP/TCP
    // All DNS must route through proxy or DoH.
    return false;
  }
  
  return true;
}

}  // namespace security
}  // namespace ultralight
