// As we are already using BoringSSL for the TPM's crypto library, it makes
// sense to also use BoringSSL for getting randomness.
#include "Platform.h"

#include <openssl/rand.h>

int32_t _plat__GetEntropy(uint8_t *entropy, uint32_t amount) {
  if (RAND_bytes(entropy, amount) != 1) {
    return -1;
  }
  return amount;
}
