// Copyright 2017
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#include <vector>

#include "caffe/layers/bayer_layer.hpp"

namespace caffe {

template <typename Dtype>
void BayerLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
  const vector<Blob<Dtype>*>& top) {
  // TODO: Implement Forward_cpu
}

template <typename Dtype>
void BayerLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
  const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
  LOG(FATAL) << "BayerLayer cannot do backward.";
}

#ifdef CPU_ONLY
STUB_GPU(BayerLayer);
#endif

INSTANTIATE_CLASS(BayerLayer);
REGISTER_LAYER_CLASS(Bayer);

}  // namespace caffe
