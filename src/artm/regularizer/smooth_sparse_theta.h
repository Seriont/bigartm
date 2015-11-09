// Copyright 2014, Additive Regularization of Topic Models.

// Author: Murat Apishev (great-mel@yandex.ru)

#ifndef SRC_ARTM_REGULARIZER_SMOOTH_SPARSE_THETA_H_
#define SRC_ARTM_REGULARIZER_SMOOTH_SPARSE_THETA_H_

#include <memory>
#include <string>
#include <vector>

#include "artm/messages.pb.h"
#include "artm/regularizer_interface.h"
#include "artm/core/transform_function.h"

namespace artm {
namespace regularizer {

class SmoothSparseThetaAgent : public RegularizeThetaAgent {
 public:
  explicit SmoothSparseThetaAgent(std::shared_ptr<artm::core::TransformFunction> func)
    : transform_function_(func) { }
  virtual void Apply(int item_index, int inner_iter, int topics_size, float* theta) const;

 private:
  friend class SmoothSparseTheta;

  std::vector<float> topic_weight;
  std::vector<float> alpha_weight;

  std::shared_ptr<artm::core::TransformFunction> transform_function_;
};

class SmoothSparseTheta : public RegularizerInterface {
 public:
  explicit SmoothSparseTheta(const SmoothSparseThetaConfig& config);

  virtual std::shared_ptr<RegularizeThetaAgent>
  CreateRegularizeThetaAgent(const Batch& batch, const ModelConfig& model_config, double tau);

  virtual google::protobuf::RepeatedPtrField<std::string> topics_to_regularize();

  virtual bool Reconfigure(const RegularizerConfig& config);

 private:
  SmoothSparseThetaConfig config_;
  std::shared_ptr<artm::core::TransformFunction> transform_function_;
};

}  // namespace regularizer
}  // namespace artm

#endif  // SRC_ARTM_REGULARIZER_SMOOTH_SPARSE_THETA_H_
