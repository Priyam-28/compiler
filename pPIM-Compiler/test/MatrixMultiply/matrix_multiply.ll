; ModuleID = 'matrix_multiply.cpp'
source_filename = "matrix_multiply.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind optnone uwtable
define dso_local void @_Z15matrix_multiplyPiS_S_iii(ptr noundef %0, ptr noundef %1, ptr noundef %2, i32 noundef %3, i32 noundef %4, i32 noundef %5) #0 {
  %7 = alloca ptr, align 8
  %8 = alloca ptr, align 8
  %9 = alloca ptr, align 8
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  store ptr %0, ptr %7, align 8
  store ptr %1, ptr %8, align 8
  store ptr %2, ptr %9, align 8
  store i32 %3, ptr %10, align 4
  store i32 %4, ptr %11, align 4
  store i32 %5, ptr %12, align 4
  store i32 0, ptr %13, align 4
  br label %16

16:                                               ; preds = %76, %6
  %17 = load i32, ptr %13, align 4
  %18 = load i32, ptr %10, align 4
  %19 = icmp slt i32 %17, %18
  br i1 %19, label %20, label %79

20:                                               ; preds = %16
  store i32 0, ptr %14, align 4
  br label %21

21:                                               ; preds = %72, %20
  %22 = load i32, ptr %14, align 4
  %23 = load i32, ptr %11, align 4
  %24 = icmp slt i32 %22, %23
  br i1 %24, label %25, label %75

25:                                               ; preds = %21
  %26 = load ptr, ptr %9, align 8
  %27 = load i32, ptr %13, align 4
  %28 = load i32, ptr %11, align 4
  %29 = mul nsw i32 %27, %28
  %30 = load i32, ptr %14, align 4
  %31 = add nsw i32 %29, %30
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds i32, ptr %26, i64 %32
  store i32 0, ptr %33, align 4
  store i32 0, ptr %15, align 4
  br label %34

34:                                               ; preds = %68, %25
  %35 = load i32, ptr %15, align 4
  %36 = load i32, ptr %12, align 4
  %37 = icmp slt i32 %35, %36
  br i1 %37, label %38, label %71

38:                                               ; preds = %34
  %39 = load ptr, ptr %7, align 8
  %40 = load i32, ptr %13, align 4
  %41 = load i32, ptr %12, align 4
  %42 = mul nsw i32 %40, %41
  %43 = load i32, ptr %15, align 4
  %44 = add nsw i32 %42, %43
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds i32, ptr %39, i64 %45
  %47 = load i32, ptr %46, align 4
  %48 = load ptr, ptr %8, align 8
  %49 = load i32, ptr %15, align 4
  %50 = load i32, ptr %11, align 4
  %51 = mul nsw i32 %49, %50
  %52 = load i32, ptr %14, align 4
  %53 = add nsw i32 %51, %52
  %54 = sext i32 %53 to i64
  %55 = getelementptr inbounds i32, ptr %48, i64 %54
  %56 = load i32, ptr %55, align 4
  %57 = mul nsw i32 %47, %56
  %58 = load ptr, ptr %9, align 8
  %59 = load i32, ptr %13, align 4
  %60 = load i32, ptr %11, align 4
  %61 = mul nsw i32 %59, %60
  %62 = load i32, ptr %14, align 4
  %63 = add nsw i32 %61, %62
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds i32, ptr %58, i64 %64
  %66 = load i32, ptr %65, align 4
  %67 = add nsw i32 %66, %57
  store i32 %67, ptr %65, align 4
  br label %68

68:                                               ; preds = %38
  %69 = load i32, ptr %15, align 4
  %70 = add nsw i32 %69, 1
  store i32 %70, ptr %15, align 4
  br label %34, !llvm.loop !6

71:                                               ; preds = %34
  br label %72

72:                                               ; preds = %71
  %73 = load i32, ptr %14, align 4
  %74 = add nsw i32 %73, 1
  store i32 %74, ptr %14, align 4
  br label %21, !llvm.loop !8

75:                                               ; preds = %21
  br label %76

76:                                               ; preds = %75
  %77 = load i32, ptr %13, align 4
  %78 = add nsw i32 %77, 1
  store i32 %78, ptr %13, align 4
  br label %16, !llvm.loop !9

79:                                               ; preds = %16
  ret void
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone uwtable
define dso_local noundef i32 @main() #1 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca [16 x i32], align 16
  %6 = alloca [16 x i32], align 16
  %7 = alloca [16 x i32], align 16
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  store i32 4, ptr %2, align 4
  store i32 4, ptr %3, align 4
  store i32 4, ptr %4, align 4
  store i32 0, ptr %8, align 4
  br label %10

10:                                               ; preds = %18, %0
  %11 = load i32, ptr %8, align 4
  %12 = icmp slt i32 %11, 16
  br i1 %12, label %13, label %21

13:                                               ; preds = %10
  %14 = load i32, ptr %8, align 4
  %15 = load i32, ptr %8, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds [16 x i32], ptr %5, i64 0, i64 %16
  store i32 %14, ptr %17, align 4
  br label %18

18:                                               ; preds = %13
  %19 = load i32, ptr %8, align 4
  %20 = add nsw i32 %19, 1
  store i32 %20, ptr %8, align 4
  br label %10, !llvm.loop !10

21:                                               ; preds = %10
  store i32 0, ptr %9, align 4
  br label %22

22:                                               ; preds = %30, %21
  %23 = load i32, ptr %9, align 4
  %24 = icmp slt i32 %23, 16
  br i1 %24, label %25, label %33

25:                                               ; preds = %22
  %26 = load i32, ptr %9, align 4
  %27 = load i32, ptr %9, align 4
  %28 = sext i32 %27 to i64
  %29 = getelementptr inbounds [16 x i32], ptr %6, i64 0, i64 %28
  store i32 %26, ptr %29, align 4
  br label %30

30:                                               ; preds = %25
  %31 = load i32, ptr %9, align 4
  %32 = add nsw i32 %31, 1
  store i32 %32, ptr %9, align 4
  br label %22, !llvm.loop !11

33:                                               ; preds = %22
  %34 = getelementptr inbounds [16 x i32], ptr %5, i64 0, i64 0
  %35 = getelementptr inbounds [16 x i32], ptr %6, i64 0, i64 0
  %36 = getelementptr inbounds [16 x i32], ptr %7, i64 0, i64 0
  call void @_Z15matrix_multiplyPiS_S_iii(ptr noundef %34, ptr noundef %35, ptr noundef %36, i32 noundef 4, i32 noundef 4, i32 noundef 4)
  ret i32 0
}

attributes #0 = { mustprogress noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
!10 = distinct !{!10, !7}
!11 = distinct !{!11, !7}
