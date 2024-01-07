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

#if !defined(FIT_BLOOD_PRESSURE_MESG_LISTENER_HPP)
#define FIT_BLOOD_PRESSURE_MESG_LISTENER_HPP

#include "fit_blood_pressure_mesg.hpp"

namespace fit {

class BloodPressureMesgListener {
 public:
  virtual ~BloodPressureMesgListener() {}
  virtual void OnMesg(BloodPressureMesg& mesg) = 0;
};

}  // namespace fit

#endif  // !defined(FIT_BLOOD_PRESSURE_MESG_LISTENER_HPP)
