/*
 *  Copyright (c) 2014, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include "proxygen/lib/http/codec/HTTP1xCodec.h"
#include "proxygen/lib/http/codec/SPDYCodec.h"
#include "proxygen/lib/http/codec/TransportDirection.h"
#include "proxygen/lib/http/codec/test/MockHTTPCodec.h"
#include "proxygen/lib/http/session/test/HTTPSessionMocks.h"

#include <folly/Memory.h>

template <class MyCodec, class Version>
typename std::enable_if<
  std::is_enum<Version>::value,
  std::unique_ptr<MyCodec> >::type
makeClientCodec(Version version) {
  return folly::make_unique<MyCodec>(
    proxygen::TransportDirection::UPSTREAM, version);
}

template <class MyCodec, class Version>
typename std::enable_if<
  std::is_same<MyCodec, proxygen::HTTP1xCodec>::value,
  std::unique_ptr<MyCodec> >::type
makeClientCodec(Version version) {
  return folly::make_unique<MyCodec>(
    proxygen::TransportDirection::UPSTREAM);
}

template <class MyCodec, class Version>
typename std::enable_if<
  std::is_same<MyCodec, proxygen::MockHTTPCodec>::value,
  std::unique_ptr<MyCodec> >::type
makeClientCodec(Version version) {
  return folly::make_unique<MyCodec>();
}

template <class MyCodec, class Version>
typename std::enable_if<
  std::is_enum<Version>::value,
  std::unique_ptr<MyCodec> >::type
makeServerCodec(Version version) {
  return folly::make_unique<MyCodec>(
    proxygen::TransportDirection::DOWNSTREAM,
    (Version)version);
}

template <class MyCodec, class Version>
typename std::enable_if<
  std::is_same<MyCodec, proxygen::HTTP1xCodec>::value,
  std::unique_ptr<MyCodec> >::type
makeServerCodec(Version version) {
  return folly::make_unique<MyCodec>(
    proxygen::TransportDirection::DOWNSTREAM);
}

template <class MyCodec, class Version>
typename std::enable_if<
  std::is_same<MyCodec, proxygen::MockHTTPCodec>::value,
  std::unique_ptr<MyCodec> >::type
makeServerCodec(Version version) {
  return folly::make_unique<MyCodec>();
}
