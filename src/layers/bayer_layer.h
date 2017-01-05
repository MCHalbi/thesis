// Copyright 2017
// Author: Lukas Halbritter <halbritl@informatik.uni-freiburg.de>

#ifndef CAFFE_BAYER_LAYER_H_
#define CAFFE_BAYER_LAYER_H_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

template <typename Dtype>
class BayerLayer : public Layer<Dtype> {
 public:
  explicit BayerLayer(const LayerParameter& param)
    : Layer<Dtype>(param) {}
  
  virtual inline const char* type() const { return "Bayer"; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top);

  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
};

}  // namespace caffe

#endif  // CAFFE_BAYER_LAYER_H_
