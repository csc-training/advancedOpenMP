; ModuleID = 'The Accel Module'
source_filename = "The Accel Module"
target datalayout = "e-p:64:64-p1:64:64-p2:32:32-p3:32:32-p4:64:64-p5:32:32-p6:32:32-i64:64-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024-v2048:2048-n32:64-S32-A5-G1-ni:7"
target triple = "amdgcn-amd-amdhsa"

; Function Attrs: noinline
define amdgpu_kernel void @"hello_$ck_L16_1"(i64 %"$$arg_ptr_acc_init_dev_t4_t111") #0 !dbg !5 !scalarlevel !9 !cachelevel !10 !fplevel !9 {
", bb66":
  tail call void @llvm.amdgcn.s.barrier(), !dbg !11 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17
  %r = tail call i32 @llvm.amdgcn.workitem.id.x(), !dbg !11 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17
  %r2.not = icmp eq i32 %r, 0, !dbg !11 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17
  br i1 %r2.not, label %"file ans_hello.F90, line 17, bb58", label %"file ans_hello.F90, line 17, bb55", !dbg !11 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17

"file ans_hello.F90, line 17, bb58":              ; preds = %", bb66"
  %r6 = inttoptr i64 %"$$arg_ptr_acc_init_dev_t4_t111" to i32 addrspace(1)*, !dbg !11 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17
  store i32 0, i32 addrspace(1)* %r6, align 4, !dbg !11, !CrayMri !12 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17
  br label %"file ans_hello.F90, line 17, bb55", !dbg !11 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17

"file ans_hello.F90, line 17, bb55":              ; preds = %"file ans_hello.F90, line 17, bb58", %", bb66"
  tail call void @llvm.amdgcn.s.barrier(), !dbg !11 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:17
  ret void, !dbg !13 ; /pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90:18
}

; Function Attrs: convergent nounwind willreturn
declare void @llvm.amdgcn.s.barrier() #1

; Function Attrs: nounwind readnone speculatable willreturn
declare i32 @llvm.amdgcn.workitem.id.x() #2

attributes #0 = { noinline "amdgpu-flat-work-group-size"="1,1024" "amdgpu-implicitarg-num-bytes"="56" "uniform-work-group-size"="true" }
attributes #1 = { convergent nounwind willreturn }
attributes #2 = { nounwind readnone speculatable willreturn }

!llvm.module.flags = !{!0}
!llvm.dbg.cu = !{!1}
!PDGFunctionMap = !{!3}
!nvvm.annotations = !{!4}

!0 = !{i32 2, !"Debug Info Version", i32 3}
!1 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !2, producer: "Cray Fortran : Version 15.0.1", isOptimized: false, runtimeVersion: 0, emissionKind: NoDebug)
!2 = !DIFile(filename: "/pfs/lustrep2/users/kemilfeld/GPU/BASICS/hello-world/solutions/ans_hello.F90", directory: "/users/kemilfeld/GPU/BASICS/hello-world/solutions")
!3 = !{i32 77, !"hello_$ck_L16_1"}
!4 = !{void (i64)* @"hello_$ck_L16_1", !"kernel", i32 1}
!5 = distinct !DISubprogram(name: "hello_$ck_L16_1", linkageName: "hello_$ck_L16_1", scope: !2, file: !2, line: 16, type: !6, scopeLine: 16, spFlags: DISPFlagDefinition, unit: !1, retainedNodes: !8)
!6 = !DISubroutineType(types: !7)
!7 = !{null}
!8 = !{}
!9 = !{i64 2}
!10 = !{i64 0}
!11 = !DILocation(line: 17, scope: !5)
!12 = !{i64 18014789351505971}
!13 = !DILocation(line: 18, scope: !5)
