/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2023 Garmin International, Inc.
// Licensed under the Flexible and Interoperable Data Transfer (FIT) Protocol
// License; you may not use this file except in compliance with the Flexible and
// Interoperable Data Transfer (FIT) Protocol License.
/////////////////////////////////////////////////////////////////////////////////////////////
// ****WARNING****  This file is auto-generated!  Do NOT edit this file.
// Profile Version = 21.126.0Release
// Tag = production/release/21.126.0-0-g0576dfe
/////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(FIT_SPO2_DATA_MESG_LISTENER_HPP)
#define FIT_SPO2_DATA_MESG_LISTENER_HPP

#include "fit_spo2_data_mesg.hpp"

namespace fit {

class Spo2DataMesgListener {
 public:
  virtual ~Spo2DataMesgListener() {}
  virtual void OnMesg(Spo2DataMesg& mesg) = 0;
};

}  // namespace fit

#endif  // !defined(FIT_SPO2_DATA_MESG_LISTENER_HPP)
