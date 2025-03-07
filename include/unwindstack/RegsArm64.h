/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LIBUNWINDSTACK_REGS_ARM64_H
#define _LIBUNWINDSTACK_REGS_ARM64_H

#include <stdint.h>

#include <functional>

#include <unwindstack/Elf.h>
#include <unwindstack/Regs.h>
#include <unwindstack/MachineArm64.h>

namespace unwindstack {

// Forward declarations.
class Memory;

class RegsArm64 : public RegsImpl<uint64_t> {
 public:
  RegsArm64();
  virtual ~RegsArm64() = default;

  ArchEnum Arch() override final;

  uint64_t GetPcAdjustment(uint64_t rel_pc, Elf* elf) override;

  bool SetPcFromReturnAddress(Memory* process_memory) override;

  bool StepIfSignalHandler(uint64_t rel_pc, Elf* elf, Memory* process_memory) override;

  void IterateRegisters(std::function<void(const char*, uint64_t)>) override final;

  uint64_t pc() override;
  uint64_t sp() override;

  void set_pc(uint64_t pc) override;
  void set_sp(uint64_t sp) override;

  static Regs* Read(void* data);

  static Regs* CreateFromUcontext(void* ucontext);

  void ResetPseudoRegisters() override;
  bool SetPseudoRegister(uint16_t id, uint64_t value) override;
  bool GetPseudoRegister(uint16_t id, uint64_t* value) override;

  bool IsRASigned();

  void SetPACMask(uint64_t mask);

 protected:
  uint64_t pseudo_regs_[Arm64Reg::ARM64_PREG_LAST - Arm64Reg::ARM64_PREG_FIRST];
  uint64_t pac_mask_ = 0;
};

}  // namespace unwindstack

#endif  // _LIBUNWINDSTACK_REGS_ARM64_H
