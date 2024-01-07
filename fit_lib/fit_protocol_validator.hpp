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

#if !defined(PROTOCOL_VALIDATOR_HPP)
#define PROTOCOL_VALIDATOR_HPP

#include "fit.hpp"

namespace fit {
class MesgDefinition;
class Mesg;

class Validator {
 public:
  virtual ~Validator() {}

  virtual bool ValidateMesg(const Mesg& mesg) = 0;
  virtual bool ValidateMesgDefn(const MesgDefinition& defn) = 0;
};

class ProtocolValidator : public Validator {
 public:
  ProtocolValidator() = delete;
  explicit ProtocolValidator(ProtocolVersion version);
  ~ProtocolValidator();

  bool ValidateMesg(const Mesg& mesg) override final;
  bool ValidateMesgDefn(const MesgDefinition& defn) override final;

 private:
  Validator* validator;
};

class V1Validator : public Validator {
 public:
  bool ValidateMesg(const Mesg& mesg) override final;
  bool ValidateMesgDefn(const MesgDefinition& defn) override final;
};

}  // namespace fit

#endif  // defined(PROTOCOL_VALIDATOR_HPP)
