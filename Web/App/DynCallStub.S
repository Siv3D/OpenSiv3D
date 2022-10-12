.section .text,"",@

.globl fakeDynCall_v

fakeDynCall_v:
  .functype fakeDynCall_v (i32) -> ()
  local.get 0
  call_indirect () -> ()
end_function