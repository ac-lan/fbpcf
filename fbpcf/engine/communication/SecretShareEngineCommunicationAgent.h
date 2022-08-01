/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "fbpcf/engine/communication/IPartyCommunicationAgent.h"
#include "fbpcf/engine/communication/ISecretShareEngineCommunicationAgent.h"

namespace fbpcf::engine::communication {

/**
 * This object will operate with an underlying commnuication agent
 */
class SecretShareEngineCommunicationAgent final
    : public ISecretShareEngineCommunicationAgent {
 public:
  SecretShareEngineCommunicationAgent(
      int myId,
      std::map<int, std::unique_ptr<IPartyCommunicationAgent>> agentMap)
      : myId_{myId}, agentMap_{std::move(agentMap)} {}

  /**
   * @inherit doc
   */
  std::map<int, __m128i> exchangeKeys(
      const std::map<int, __m128i>& keys) override;

  /**
   * @inherit doc
   */
  std::vector<bool> openSecretsToAll(
      const std::vector<bool>& secretShares) override;

  /**
   * @inherit doc
   */
  std::vector<uint64_t> openSecretsToAll(
      const std::vector<uint64_t>& secretShares) override;

  /**
   * @inherit doc
   */
  std::vector<bool> openSecretsToParty(
      int id,
      const std::vector<bool>& secretShares) override;

  /**
   * @inherit doc
   */
  std::vector<uint64_t> openSecretsToParty(
      int id,
      const std::vector<uint64_t>& secretShares) override;

  /**
   * @inherit doc
   */
  std::pair<uint64_t, uint64_t> getTrafficStatistics() const override;

 private:
  int myId_;
  std::map<int, std::unique_ptr<IPartyCommunicationAgent>> agentMap_;
};

} // namespace fbpcf::engine::communication
