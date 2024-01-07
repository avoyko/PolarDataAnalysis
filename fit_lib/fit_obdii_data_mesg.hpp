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

#if !defined(FIT_OBDII_DATA_MESG_HPP)
#define FIT_OBDII_DATA_MESG_HPP

#include "fit_mesg.hpp"

namespace fit {

class ObdiiDataMesg : public Mesg {
 public:
  class FieldDefNum final {
   public:
    static const FIT_UINT8 Timestamp = 253;
    static const FIT_UINT8 TimestampMs = 0;
    static const FIT_UINT8 TimeOffset = 1;
    static const FIT_UINT8 Pid = 2;
    static const FIT_UINT8 RawData = 3;
    static const FIT_UINT8 PidDataSize = 4;
    static const FIT_UINT8 SystemTime = 5;
    static const FIT_UINT8 StartTimestamp = 6;
    static const FIT_UINT8 StartTimestampMs = 7;
    static const FIT_UINT8 Invalid = FIT_FIELD_NUM_INVALID;
  };

  ObdiiDataMesg(void) : Mesg(Profile::MESG_OBDII_DATA) {}

  ObdiiDataMesg(const Mesg& mesg) : Mesg(mesg) {}

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of timestamp field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsTimestampValid() const {
    const Field* field = GetField(253);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid();
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns timestamp field
  // Units: s
  // Comment: Timestamp message was output
  ///////////////////////////////////////////////////////////////////////
  FIT_DATE_TIME GetTimestamp(void) const {
    return GetFieldUINT32Value(253, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set timestamp field
  // Units: s
  // Comment: Timestamp message was output
  ///////////////////////////////////////////////////////////////////////
  void SetTimestamp(FIT_DATE_TIME timestamp) {
    SetFieldUINT32Value(253, timestamp, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of timestamp_ms field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsTimestampMsValid() const {
    const Field* field = GetField(0);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid();
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns timestamp_ms field
  // Units: ms
  // Comment: Fractional part of timestamp, added to timestamp
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT16 GetTimestampMs(void) const {
    return GetFieldUINT16Value(0, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set timestamp_ms field
  // Units: ms
  // Comment: Fractional part of timestamp, added to timestamp
  ///////////////////////////////////////////////////////////////////////
  void SetTimestampMs(FIT_UINT16 timestampMs) {
    SetFieldUINT16Value(0, timestampMs, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns number of time_offset
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT8 GetNumTimeOffset(void) const {
    return GetFieldNumValues(1, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of time_offset field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsTimeOffsetValid(FIT_UINT8 index) const {
    const Field* field = GetField(1);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid(index);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns time_offset field
  // Units: ms
  // Comment: Offset of PID reading [i] from start_timestamp+start_timestamp_ms.
  // Readings may span accross seconds.
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT16 GetTimeOffset(FIT_UINT8 index) const {
    return GetFieldUINT16Value(1, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set time_offset field
  // Units: ms
  // Comment: Offset of PID reading [i] from start_timestamp+start_timestamp_ms.
  // Readings may span accross seconds.
  ///////////////////////////////////////////////////////////////////////
  void SetTimeOffset(FIT_UINT8 index, FIT_UINT16 timeOffset) {
    SetFieldUINT16Value(1, timeOffset, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of pid field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsPidValid() const {
    const Field* field = GetField(2);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid();
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns pid field
  // Comment: Parameter ID
  ///////////////////////////////////////////////////////////////////////
  FIT_BYTE GetPid(void) const {
    return GetFieldBYTEValue(2, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set pid field
  // Comment: Parameter ID
  ///////////////////////////////////////////////////////////////////////
  void SetPid(FIT_BYTE pid) {
    SetFieldBYTEValue(2, pid, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns number of raw_data
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT8 GetNumRawData(void) const {
    return GetFieldNumValues(3, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of raw_data field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsRawDataValid(FIT_UINT8 index) const {
    const Field* field = GetField(3);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid(index);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns raw_data field
  // Comment: Raw parameter data
  ///////////////////////////////////////////////////////////////////////
  FIT_BYTE GetRawData(FIT_UINT8 index) const {
    return GetFieldBYTEValue(3, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set raw_data field
  // Comment: Raw parameter data
  ///////////////////////////////////////////////////////////////////////
  void SetRawData(FIT_UINT8 index, FIT_BYTE rawData) {
    SetFieldBYTEValue(3, rawData, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns number of pid_data_size
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT8 GetNumPidDataSize(void) const {
    return GetFieldNumValues(4, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of pid_data_size field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsPidDataSizeValid(FIT_UINT8 index) const {
    const Field* field = GetField(4);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid(index);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns pid_data_size field
  // Comment: Optional, data size of PID[i]. If not specified refer to SAE
  // J1979.
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT8 GetPidDataSize(FIT_UINT8 index) const {
    return GetFieldUINT8Value(4, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set pid_data_size field
  // Comment: Optional, data size of PID[i]. If not specified refer to SAE
  // J1979.
  ///////////////////////////////////////////////////////////////////////
  void SetPidDataSize(FIT_UINT8 index, FIT_UINT8 pidDataSize) {
    SetFieldUINT8Value(4, pidDataSize, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns number of system_time
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT8 GetNumSystemTime(void) const {
    return GetFieldNumValues(5, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of system_time field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsSystemTimeValid(FIT_UINT8 index) const {
    const Field* field = GetField(5);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid(index);
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns system_time field
  // Comment: System time associated with sample expressed in ms, can be used
  // instead of time_offset. There will be a system_time value for each raw_data
  // element. For multibyte pids the system_time is repeated.
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT32 GetSystemTime(FIT_UINT8 index) const {
    return GetFieldUINT32Value(5, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set system_time field
  // Comment: System time associated with sample expressed in ms, can be used
  // instead of time_offset. There will be a system_time value for each raw_data
  // element. For multibyte pids the system_time is repeated.
  ///////////////////////////////////////////////////////////////////////
  void SetSystemTime(FIT_UINT8 index, FIT_UINT32 systemTime) {
    SetFieldUINT32Value(5, systemTime, index, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of start_timestamp field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsStartTimestampValid() const {
    const Field* field = GetField(6);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid();
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns start_timestamp field
  // Comment: Timestamp of first sample recorded in the message. Used with
  // time_offset to generate time of each sample
  ///////////////////////////////////////////////////////////////////////
  FIT_DATE_TIME GetStartTimestamp(void) const {
    return GetFieldUINT32Value(6, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set start_timestamp field
  // Comment: Timestamp of first sample recorded in the message. Used with
  // time_offset to generate time of each sample
  ///////////////////////////////////////////////////////////////////////
  void SetStartTimestamp(FIT_DATE_TIME startTimestamp) {
    SetFieldUINT32Value(6, startTimestamp, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Checks the validity of start_timestamp_ms field
  // Returns FIT_TRUE if field is valid
  ///////////////////////////////////////////////////////////////////////
  FIT_BOOL IsStartTimestampMsValid() const {
    const Field* field = GetField(7);
    if (FIT_NULL == field) {
      return FIT_FALSE;
    }

    return field->IsValueValid();
  }

  ///////////////////////////////////////////////////////////////////////
  // Returns start_timestamp_ms field
  // Units: ms
  // Comment: Fractional part of start_timestamp
  ///////////////////////////////////////////////////////////////////////
  FIT_UINT16 GetStartTimestampMs(void) const {
    return GetFieldUINT16Value(7, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }

  ///////////////////////////////////////////////////////////////////////
  // Set start_timestamp_ms field
  // Units: ms
  // Comment: Fractional part of start_timestamp
  ///////////////////////////////////////////////////////////////////////
  void SetStartTimestampMs(FIT_UINT16 startTimestampMs) {
    SetFieldUINT16Value(7, startTimestampMs, 0, FIT_SUBFIELD_INDEX_MAIN_FIELD);
  }
};

}  // namespace fit

#endif  // !defined(FIT_OBDII_DATA_MESG_HPP)
