/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once
#include "fbpcf/engine/tuple_generator/IProductShareGenerator.h"
#include "fbpcf/engine/tuple_generator/oblivious_transfer/IBidirectionObliviousTransfer.h"
#include "fbpcf/engine/util/IPrg.h"

namespace fbpcf::engine::tuple_generator {

/**
 * This is a product shares generator that uses OT as underlying object to
 * operate.
 */
class ProductShareGenerator final : public IProductShareGenerator {
 public:
  ProductShareGenerator(
      std::unique_ptr<util::IPrg> prg,
      std::unique_ptr<oblivious_transfer::IBidirectionObliviousTransfer>
          bidirectionObliviousTransfer)
      : prg_{std::move(prg)},
        bidirectionObliviousTransfer_{std::move(bidirectionObliviousTransfer)} {
  }

  /**
   * @inherit doc
   */
  std::vector<bool> generateBooleanProductShares(
      const std::vector<bool>& left,
      const std::vector<bool>& right) override;

  /**
   * @inherit doc
   */
  std::vector<uint64_t> generateIntegerProductShares(
      const std::vector<uint64_t>& left,
      const std::vector<uint64_t>& right) override;

  std::pair<uint64_t, uint64_t> getTrafficStatistics() const override {
    return bidirectionObliviousTransfer_->getTrafficStatistics();
  }

 private:
  std::unique_ptr<util::IPrg> prg_;
  std::unique_ptr<oblivious_transfer::IBidirectionObliviousTransfer>
      bidirectionObliviousTransfer_;
};

} // namespace fbpcf::engine::tuple_generator
